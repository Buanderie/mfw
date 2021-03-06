
// STL
#include <sstream>

// INTERNAL 
#include "node.hpp"

using namespace std;
using namespace monadic;

namespace monadic
{
    void Node::start()
    {
        //setup();
        //_nodeThread = (void*)(new boost::thread( boost::bind( &Node::run, this ) ));
    }

    void Node::run()
    {/*
        while(1)
        {
            this->tick( 0.0 );
        }
    */
    }

    void Node::enable()
    {
        _nodeMtx.lock();
        _nodeState = Node::NODE_REQUESTING_ACTIVATION;
        _nodeMtx.unlock();
    }

    void Node::disable()
    {
        _nodeMtx.lock();
        _nodeState = Node::NODE_REQUESTING_DEACTIVATION;
        _nodeMtx.unlock();
    }

    void Node::OnLinkConnected(Link *link)
    {
        _connMtx.lock();
        _connCnd.signal();
        _connMtx.unlock();
    }

    void Node::OnLinkDisconnected(Link *link)
    {
        _connMtx.lock();
        _connCnd.signal();
        _connMtx.unlock();
    }

    void Node::waitForConnection()
    {
        _connMtx.lock();
        _connCnd.wait( _connMtx );
        _connMtx.unlock();
    }

    Pin *Node::addPin(const std::string &pinLabel, Pin::PinMode mode)
    {
        Pin* p = new Pin( this, pinLabel, mode );
        _pins.push_back(p);
        return p;
    }

    Pin *Node::findPinFromLabel(const string &pinLabel)
    {
        Pin* ret = 0;
        _nodeMtx.lock();
        for( size_t k = 0; k < _pins.size(); ++k )
        {
            if( _pins[k]->getLabel() == pinLabel )
            {
                ret = _pins[k];
                break;
            }
        }
        _nodeMtx.unlock();
        return ret;
    }

    vector< monadic::Pin* > Node::getPins()
    {
        return _pins;
    }

    bool Node::setParameter(const string &name, Object &value)
    {
        return true;
    }

    Object *Node::getParameter(const string &name)
    {
        return 0;
    }

    picojson::object Node::toJSON()
    {
        picojson::object ret;
        ret["kernel"] = picojson::value(this->getKernelName());
        stringstream sstr;
        sstr << getGuid();
        ret["guid"] = picojson::value(sstr.str());
        return ret;
    }
}
