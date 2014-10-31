

// INTERNAL 
#include "kernel.hpp"

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
}
