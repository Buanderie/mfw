#ifndef __THREADLINUX_HPP__
#define __THREADLINUX_HPP__

#include <pthread.h>

#include <iostream>

using namespace std;

namespace monadic
{
	class CondVar;
	class Mutex
	{
	friend class CondVar;
	public:
		Mutex(){
			pthread_mutex_init(&_mtx, NULL);
		}

		~Mutex(){
			pthread_mutex_destroy(&_mtx);
		}

		bool lock(){
			if(pthread_mutex_lock( &_mtx )) return false;
				return true;
		}

		bool unlock(){
			if(pthread_mutex_unlock( &_mtx )) return false;
				return true;
		}
	private:
		pthread_mutex_t	_mtx;
	};

	class CondVar
	{
	public:
		CondVar(){
			pthread_cond_init( &_condvar, NULL );
		}
		~CondVar(){
			pthread_cond_destroy( &_condvar );
		}
		void wait(Mutex& mtx){
			pthread_cond_wait(&_condvar, &(mtx._mtx));
		}
		void signal()
		{
			pthread_cond_broadcast(&_condvar);
		}
	private:
		pthread_cond_t	_condvar;
	};

	class Thread
	{
	public:
		
		typedef enum{
			THREAD_ACTIVE=0,
			THREAD_WAITSTOP,
			THREAD_STOPPED
		} Status;

		Thread(){
			_threadStatus = THREAD_STOPPED;
		}

		virtual ~Thread(){
			stop();
			waitForTermination();
		}

		virtual bool start()
		{
			int ret = pthread_create( &_thread, NULL, Thread::runBinder, (void*)this );
			if( !ret )
			{
				_threadStatus = THREAD_STOPPED;
				return false;
			}
			else
			{
				_threadStatus = THREAD_ACTIVE;
				return true;
			}
		}

		virtual void stop(){
			_statusMtx.lock();
			_threadStatus = THREAD_WAITSTOP;
			_statusMtx.unlock();
		}

		virtual void waitForTermination(){
			_statusMtx.lock();
			while( _threadStatus != THREAD_STOPPED )
			{
				cout << "waitFormTermination" << endl;
				_stopCnd.wait( _statusMtx );
				cout << "pifpiad" << endl;
			}
			_statusMtx.unlock();
		}

		Thread::Status getStatus()
		{
			_statusMtx.lock();
			Status threadStatus = _threadStatus;
			_statusMtx.unlock();
			return threadStatus;
		}

		virtual bool run()=0;

	private:
		static void* runBinder(void* instance)
		{
			((Thread*)instance)->run();
			cout << "endrun" << endl;
			((Thread*)instance)->_statusMtx.lock();
			cout << "inlock" << endl;
			((Thread*)instance)->_threadStatus = THREAD_STOPPED;
			cout << "lolstop" << endl;
			((Thread*)instance)->_stopCnd.signal();
			cout << "signalled" << endl;
			((Thread*)instance)->_statusMtx.unlock();
			cout << "outlock" << endl;
			return NULL;
		}

		Status			_threadStatus;
		pthread_t		_thread;
		Mutex 			_statusMtx;
		CondVar 		_stopCnd;

	protected:
		bool mustStop()
		{
			return (getStatus() == THREAD_WAITSTOP);
		}
	};
}

#endif//__THREADLINUX_HPP__