
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
        for( int k = 0; k < 7; ++k )
        {
        	_workers.push_back( new ApplicationWorker(this) );
        }

        // Create the node manager
        _kernelManager = new KernelManager();
        _kernelManager->loadFromDirectory( _pluginFolder, true );

    }

    void Application::start()
    {

        for( int k = 0; k < _nodes.size(); ++k )
            _nodes[k]->setup();

    	for( unsigned int k = 0; k < _workers.size(); ++k )
    	{
    		_workers[k]->start();
    	}
    }

    double Application::getElapsedTime()
    {
    	double ret = 0.0;
    	_timeRefMtx.lock();

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

monadic::Node* monadic::Application::addNode( const std::string& nodeType )
{
    Node* n = _kernelManager->create( nodeType );
    _nodes.push_back( n );
    return n;
}

std::vector< monadic::Node* > getNodeList()
{
    std::vector< monadic::Node* > res;

    return res;
}
