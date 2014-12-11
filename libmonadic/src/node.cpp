
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

    Pin *Node::addPin(const std::string &pinLabel, Pin::PinMode mode)
    {
        Pin* p = new Pin( this, pinLabel, mode );
        _pins.push_back(p);
        return p;
    }

    Pin *Node::findPinFromLabel(const string &pinLabel)
    {
        //cout << "this=" << this << " - " << _pins.size() << endl;
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
