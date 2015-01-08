
// STL
#include <iostream>
#include <fstream>

// PICOJSON
#include "picojson.hpp"

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
        for( int k = 0; k < numCores*2; ++k )
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

    Guid Application::addLink(const Guid &n1, const Guid &n2, const string &pin1, const string &pin2, size_t bandwidth, Link::LinkMode mode)
    {
        Node* node1 = 0;
        Node* node2 = 0;

        for( map< Guid, Node* >::iterator i = _nodes.begin(); i != _nodes.end(); ++i )
        {
            if( i->second->getGuid() == n1 )
            {
                cout << "FOUND: " << n1 << " - " << i->second << endl;
                node1 = i->second;
            }
            else if( i->second->getGuid() == n2 )
            {
                cout << "FOUND: " << n1 << " - " << i->second << endl;
                node2 = i->second;
            }
        }

        cout << "node1=" << node1 << " - node2=" << node2 << endl;
        cout << "n1=" << n1 << " - n2=" << n2 << endl;
        Pin* p1 = node1->findPinFromLabel( pin1 );
        Pin* p2 = node2->findPinFromLabel( pin2 );
        Link* l = addLink( p1, p2, bandwidth, mode );
        return l->getGuid();

    }

    vector< monadic::Link* > Application::getLinks()
    {
        return _links;
    }

    bool Application::save(const string &filePath)
    {
        _nodeListMtx.lock();
        picojson::object root;
        // Save nodes
        picojson::array nodeArray;
        map< monadic::Guid, monadic::Node* >::iterator nitr;
        for( nitr = _nodes.begin(); nitr != _nodes.end(); ++nitr )
        {
            picojson::object nodeObj = nitr->second->toJSON();
            nodeArray.push_back( picojson::value(nodeObj) );
        }
        root["nodes"] = picojson::value( nodeArray );

        // Save links
        picojson::array linkArray;
        vector< monadic::Link* >::iterator litr;
        for( litr = _links.begin(); litr != _links.end(); ++litr )
        {
            picojson::object linkObj = (*litr)->toJSON();
            linkArray.push_back( picojson::value(linkObj) );
        }
        root["links"] = picojson::value( linkArray );

        string str = picojson::value(root).serialize();
        printf("serialized content = %s\r\n" ,  str.c_str());

        ofstream ofs( filePath.c_str() );
        ofs << str;
        ofs.close();
        _nodeListMtx.unlock();
        return true;
    }

    bool Application::load(const string &filePath)
    {
        _nodeListMtx.lock();
        _nodes.clear();
        _links.clear();

        std::string jsonSource;

        // Load file
        ifstream ifs( filePath.c_str() );
        while(1)
        {
            if( ifs.eof() )
                break;
            string dump;
            getline( ifs, dump );
            jsonSource += dump;
        }
        cout << "source=" << jsonSource << endl;
        const char* json = jsonSource.c_str();
        picojson::value v;
        string err = picojson::parse(v, json, json + strlen(json));

        // obtain a const reference to the map, and print the contents
        picojson::object& root = v.get<picojson::object>();

        const picojson::array& nodeArray = root["nodes"].get<picojson::array>();
        const picojson::array& linkArray = root["links"].get<picojson::array>();

        // parse nodes
        for( int k = 0; k < nodeArray.size(); ++k )
        {
            // retrieve node object
            picojson::object jn = nodeArray[k].get<picojson::object>();
            std::string nguid = jn["guid"].get<string>();
            std::string nkernel = jn["kernel"].get<string>();
            cout << nguid << " - " << nkernel << endl;
            this->addNode( nkernel, monadic::Guid(nguid) );
        }

        cout << "### NODES : " << _nodes.size() << " ###" << endl;
        for( map< Guid, Node* >::iterator i = _nodes.begin(); i != _nodes.end(); ++i )
        {
            cout << i->second->getGuid() << " - " << i->second << endl;
        }

        // parse links
        for( int k = 0; k < linkArray.size(); ++k )
        {
            // retrieve node object
            picojson::object jl = linkArray[k].get<picojson::object>();
            Link::LinkMode lmode = (Link::LinkMode)(int)(jl["mode"].get<double>());
            size_t lbandwidth = (unsigned int)(jl["bandwidth"].get<double>());
            monadic::Guid startNode = monadic::Guid( jl["startnode"].get<string>() );
            monadic::Guid endNode = monadic::Guid( jl["endnode"].get<string>() );
            string startPin = jl["startpin"].get<string>();
            string endPin = jl["endpin"].get<string>();

            cout << "startPin=" << startPin << " - endPin=" << endPin << endl;
            cout << "startNode=" << startNode << " - endNode=" << endNode << endl;

            this->addLink( startNode, endNode, startPin, endPin, lbandwidth, lmode );
        }

        _nodeListMtx.unlock();
        return true;
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

monadic::Node* monadic::Application::addNode( const std::string& nodeType, const monadic::Guid guid )
{
    Node* n = _kernelManager->create( nodeType );

    if( guid == monadic::Guid("00000000-0000-0000-0000-000000000000") )
    {
        n->resetGuid();
    }
    else
    {
        n->setGuid(guid);
    }

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
