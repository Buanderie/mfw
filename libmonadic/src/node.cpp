

// INTERNAL 
#include "node.hpp"

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
        cout << "Enabling " << _guid << endl;
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
}
