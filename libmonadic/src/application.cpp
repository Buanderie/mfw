
// STL
#include <iostream>

// INTERNAL
#include "application.hpp"
#include "applicationworker.hpp"

using namespace std;

namespace monadic
{
    void Application::init()
    {
        //int ncore = boost::thread::hardware_concurrency();
        //cout << "pitaing " << ncore << " cores !" << endl;
        //_appThreadPool = boost::threadpool::prio_pool( boost::thread::hardware_concurrency() - 1 );
        for( int k = 0; k < 8; ++k )
        {
        	_workers.push_back( new ApplicationWorker(this) );
        }
    }

    void Application::start()
    {
    	for( unsigned int k = 0; k < _workers.size(); ++k )
    	{
    		_workers[k]->start();
    	}

    	// Update time reference
    	//_timeRef = time(NULL);
    	gettimeofday(&_timeRef, NULL);
    }

    double Application::getElapsedTime()
    {
    	struct timeval finishtime;
    	gettimeofday(&finishtime, NULL);
    	long msec;
    	double ret;
    	_timeRefMtx.lock();
  		msec=(finishtime.tv_sec-_timeRef.tv_sec)*1000;
  		msec+=(finishtime.tv_usec-_timeRef.tv_usec)/1000;
  		ret = (double)msec / 1000.0;
    	_timeRefMtx.unlock();
    	return ret;
    }

    Node* Application::fetchActiveNode()
    {
    	Node* ret = NULL;
      _nodeListMtx.lock();
    	while( ret == NULL )
    	{
        // Let's forget about priorities for now
    		for( unsigned int k = 0; k < _nodes.size(); ++k )
    		{
    			if( _nodes[k]->getState() == Node::NODE_ACTIVE )
    			{
    				ret = _nodes[k];
    				break;
    			}
    		}

        // Found one to be processed
    		if( ret != NULL )
    		{
    			ret->_nodeState = Node::NODE_BUSY;
    			break;
    		}
    		else
    		{
    			_nodeListCnd.wait( _nodeListMtx );
    		}
    	}
    	_nodeListMtx.unlock();
    	return ret;
    }

    void Application::releaseNode( Node* node )
    {
    	_nodeListMtx.lock();
    	for( int k = 0; k < _nodes.size(); ++k )
    	{
    		if( node == _nodes[k] )
    		{
    			if( node->getState() == Node::NODE_BUSY )
    				_nodes[k]->_nodeState = Node::NODE_ACTIVE;
    			// lol ugly
    			_nodes.erase( _nodes.begin() + k );
    			_nodes.push_back( node );
    			//
    			_nodeListCnd.signal();
    			break;
    		}
    	}
    	_nodeListMtx.unlock();
    }

    void Application::stop()
    {
    	for( unsigned int k = 0; k < _workers.size(); ++k )
    	{
    		_workers[k]->stop();
    	}

    	for( unsigned int k = 0; k < _workers.size(); ++k )
    	{
    		_workers[k]->waitForTermination();
    	}
    }
}
