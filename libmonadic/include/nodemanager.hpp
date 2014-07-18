#ifndef __NODEMANAGER_HPP__
#define __NODEMANAGER_HPP__

// STL
#include <string>
#include <map>

// INTERNAL
#include "singleton.hpp"
#include "node.hpp"

namespace monadic
{

    typedef struct
    {
        createNode_t* nodeCreator;
        destroyNode_t* nodeDestructor;
        getNodeName_t* nodeDescriptor;
    } NodeManagerEntry_t;
    
    class NodeManager /* : public Singleton<NodeManager> */
    {
        //friend class Singleton<NodeManager>;

        public:
            NodeManager(){}
            ~NodeManager(){}

            int load( const std::string& nodeModulePath );
            int loadFromDirectory( const std::string& nodeModulePath, bool recursiveSearch = true );
            
            int release( const std::string& nodeTypeName );
            int releaseAll();
            
            Node* create( const std::string& nodeName );
            int destroy( Node* node );
            
        private:
            std::map< std::string, NodeManagerEntry_t > _nodeRegistry;

    };
}

#endif
