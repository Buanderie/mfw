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
            // ctor & dtor
            NodeEntry( const std::string& dlPath="" );
            virtual ~NodeEntry();
   
            void open( const std::string& dlPath );            
            createNode_t* getConstructorPtr();
            destroyNode_t* getDestructorPtr();
            std::string getNodeName();
                          
        private:
            std::string     _nodeName;
            createNode_t*   _createFuncPtr;
            destroyNode_t*  _destroyFuncPtr;
            void*           _dlref;
    };
}

#endif
