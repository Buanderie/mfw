
// STL
#include <iostream>

// INTERNAL
#include "application.hpp"
#include "applicationworker.hpp"
#include "system.hpp"

using namespace std;

namespace monadic
{
    void Application::init()
    {
        int numCores = System::getNumCores();
        for( int k = 0; k < numCores; ++k )
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
        {
            nitr->second->setup();
        }

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
        // Update the queue if needed
        map< monadic::Guid, monadic::Node* >::iterator nitr;
        for( nitr = _nodes.begin(); nitr != _nodes.end(); ++nitr )
        {
            if( nitr->second->getState() == Node::NODE_REQUESTING_ACTIVATION )
            {
                nitr->second->setState( Node::NODE_ACTIVE );
                _nodeQueue.push( nitr->second );
                _nodeListCnd.signal();
            }
            else if( nitr->second->getState() == Node::NODE_REQUESTING_DEACTIVATION )
            {
                nitr->second->setState( Node::NODE_INACTIVE );
            }
        }
        _nodeListMtx.unlock();
        //

        _nodeListMtx.lock();
        while(1)
        {
            if( _nodeQueue.size() > 0 )
            {
                Node* n = _nodeQueue.front();
                _nodeQueue.pop();
                ret = n;
            }

            if( ret == NULL )
            {
                _nodeListCnd.wait( _nodeListMtx );
            }
            else
            {
                ret->setState( Node::NODE_BUSY );
                break;
            }
        }
        _nodeListMtx.unlock();

        return ret;
    }

    void Application::releaseNode( Node* node )
    {
        _nodeListMtx.lock();
        if( node->getState() == Node::NODE_BUSY )
        {
            node->setState( Node::NODE_ACTIVE );
            _nodeQueue.push( node );
            _nodeListCnd.signal();
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

    Link *Application::addLink( monadic::Pin* pin1, monadic::Pin* pin2, std::size_t bandwidth, monadic::Link::LinkMode mode )
    {
        Link* l = new Link( pin1, pin2, bandwidth, mode );
        l->resetGuid();
        _links.push_back( l );
        return l;
    }

    Node *Application::getNode(const Guid &guid)
    {
        map< monadic::Guid, Node* >::iterator nitr;
        if( nitr != _nodes.end() )
            return nitr->second;
        else
            return 0;
    }

    void Application::enableAllNodes()
    {
        map< monadic::Guid, monadic::Node* >::iterator nitr;
        for( nitr = _nodes.begin(); nitr != _nodes.end(); ++nitr )
        {
            nitr->second->enable();
        }
    }

}

monadic::Node* monadic::Application::addNode( const std::string& nodeType )
{
    Node* n = _kernelManager->create( nodeType );
    n->resetGuid();
    _nodes.insert( make_pair( n->getGuid(), n ) );
    return n;
}

std::vector< monadic::Guid > monadic::Application::getNodeIds()
{
    std::vector< monadic::Guid > res;
    map< monadic::Guid, monadic::Node* >::iterator nitr;
    for( nitr = _nodes.begin(); nitr != _nodes.end(); ++nitr )
    {
        res.push_back( nitr->first );
    }
    return res;
}

vector< monadic::Node* > monadic::Application::getNodes()
{
    std::vector< monadic::Node* > res;
    map< monadic::Guid, monadic::Node* >::iterator nitr;
    for( nitr = _nodes.begin(); nitr != _nodes.end(); ++nitr )
    {
        res.push_back( nitr->second );
    }
    return res;
}
