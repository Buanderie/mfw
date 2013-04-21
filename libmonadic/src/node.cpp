

// INTERNAL 
#include "node.hpp"

namespace monadic
{
    void Node::start()
    {
        _nodeThread = boost::thread( voost::bind( &Node::run, this ) );
    }

    void Node::run()
    {
        while(1)
        {
            this->tick( 0.0 );
        }
    }
}
