#ifndef __THREADWINDOWS_HPP__
#define __THREADWINDOWS_HPP__

#ifdef __WINDOWS__

#include <windows.h>

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
			// Initialize the critical section one time only.
			if (!InitializeCriticalSectionAndSpinCount(&_mtx, 0x00000400))
				return;
		}

		~Mutex(){
			DeleteCriticalSection(&_mtx);
		}

		bool lock(){
			EnterCriticalSection(&_mtx);
			return true;
		}

		bool unlock(){
			LeaveCriticalSection(&_mtx);
		}
	private:
		CRITICAL_SECTION _mtx;
	};

	class CondVar
	{
	public:
		CondVar(){
			InitializeConditionVariable(&_condvar);
		}
		~CondVar(){
			
		}
		void wait(Mutex& mtx){
			SleepConditionVariableCS(&_condvar, &(mtx._mtx), INFINITE);
		}
		void signal()
		{
			WakeAllConditionVariable(&_condvar);
		}
	private:
		CONDITION_VARIABLE _condvar;
	};

	class Thread
	{
	public:

		typedef enum{
			THREAD_ACTIVE = 0,
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
			_thread = CreateThread(NULL, 0, runBinder, (PVOID)1, 0, &_threadId);
			if (!_thread)
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
			while (_threadStatus != THREAD_STOPPED)
			{
				cout << "waitFormTermination" << endl;
				_stopCnd.wait(_statusMtx);
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

		virtual bool run() = 0;

	private:
		static DWORD WINAPI runBinder(LPVOID instance)
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
		HANDLE          _thread;        // Handle
		DWORD           _threadId;      // Id // Initialized at creation but not used further
		Mutex 			_statusMtx;
		CondVar 		_stopCnd;

	protected:
		bool mustStop()
		{
			return (getStatus() == THREAD_WAITSTOP);
		}
	};
}

#endif //__WINDOWS__

#endif//__THREADWINDOWS_HPP__