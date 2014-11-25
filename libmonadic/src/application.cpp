
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
        for( int k = 0; k < 16; ++k )
        {
        	_workers.push_back( new ApplicationWorker(this) );
        }

        // Create the node manager
        _kernelManager = new KernelManager();
        _kernelManager->loadFromDirectory( _pluginFolder, true );

    }

    void Application::start()
    {
	map< monadic::Guid, Node* >::iterator nitr;
        for( nitr = _nodes.begin(); nitr != _nodes.end(); ++nitr )
            nitr->second->setup();

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
		map< monadic::Guid, Node* >::iterator nitr;
        	// Let's forget about priorities for now
    		for( nitr = _nodes.begin(); nitr != _nodes.end(); ++nitr )
    		{
    			if( nitr->second->getState() == Node::NODE_ACTIVE )
    			{
    				ret = nitr->second;
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
	map< monadic::Guid, Node* >::iterator nitr;
    	_nodeListMtx.lock();
    	for( nitr = _nodes.begin(); nitr != _nodes.end(); ++nitr )
    	{
    		if( node == nitr->second )
    		{
    			if( node->getState() == Node::NODE_BUSY )
    				nitr->second->_nodeState = Node::NODE_ACTIVE;
    			// lol ugly
    			//_nodes.erase( nitr->second->getGuid() );
    			//_nodes.insert( nitr- );
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

    Link *Application::addLink( monadic::Node *n1, monadic::Node *n2, std::size_t bandwidth, monadic::Link::LinkMode mode )
    {
        Link* l = new Link( n1, n2, bandwidth, mode );
	l->resetGuid();
        _links.push_back( l );
        return l;
    }
}

monadic::Node* monadic::Application::addNode( const std::string& nodeType )
{
    Node* n = _kernelManager->create( nodeType );
    n->resetGuid();
    //_nodes.insert( make_pair( n->getGuid(), n ) );
    return n;
}

std::vector< monadic::Node* > getNodeList()
{
    std::vector< monadic::Node* > res;

    return res;
}
