#ifndef __NODEENTRY_HPP__
#define __NODEENTRY_HPP__

// STL
#include <string>

// INTERNAL
#include "node.hpp"

namespace monadic
{
    class NodeEntry
    {
        public:
            
        private:
            std::string     _nodeName;
            createNode_t    _createFunc;
            destroyNode_t   _destroyFunc;
    };
}

#endif
