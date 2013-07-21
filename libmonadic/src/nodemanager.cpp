
// SYSTEM
#include <dlfcn.h>

// STL
#include <iostream>

// BOOST
// Oh yeah.. heavy Boost shit inside core components :/
#include <boost/filesystem.hpp>

// INTERNAL
#include "nodemanager.hpp"

using namespace std;

namespace monadic
{
    int NodeManager::load( const char* nodeModulePath )
    {
        // load the node module library
        void* nodeModule = dlopen( nodeModulePath, RTLD_LAZY );
        if (!nodeModule)
        {
            //cerr << "Cannot load library: " << dlerror() << '\n';
            return 1;    
        }
        
        // load the symbols
        createNode_t* create_node = (createNode_t*) dlsym(nodeModule, "createNode");
        destroyNode_t* destroy_node = (destroyNode_t*) dlsym(nodeModule, "destroyNode");
        getNodeName_t* name_node = (getNodeName_t*) dlsym(nodeModule, "getNodeName");
        if (!create_node || !name_node || !destroy_node) {
            //cerr << "Cannot load symbols: " << dlerror() << '\n';
            dlclose( nodeModule );
            return 1;
        }
        
        // Create new entry in the registry
        NodeManagerEntry_t ent;
        ent.nodeCreator = create_node;
        ent.nodeDestructor = destroy_node;
        ent.nodeDescriptor = name_node;
        char* nodeName = name_node();
        std::string strNodeName = nodeName;
        delete nodeName;
        _nodeRegistry.insert ( std::pair<std::string, NodeManagerEntry_t>( strNodeName,ent ) );
        cout << "Loaded node module: " << strNodeName << endl;
        return 0;
    }
    
    int NodeManager::release( const std::string& nodeTypeName )
    {
        
        return 0;
    }
    
    int NodeManager::loadFromDirectory( const char* nodeModulePath, bool recursiveSearch )
    {
        int retCode = -1;
        if( recursiveSearch )
        {
            for ( boost::filesystem::recursive_directory_iterator end, dir(nodeModulePath); dir != end; ++dir )
            {
                if( !boost::filesystem::is_directory( dir->path() ) && dir->path().extension().string() == ".so" )
                {
                    //cout << *dir << std::endl;
                    retCode += load( dir->path().string().c_str() );
                }                                    
            }
        }
        else
        {
            for ( boost::filesystem::directory_iterator end, dir(nodeModulePath); dir != end; ++dir )
            {
                if( !boost::filesystem::is_directory( dir->path() ) && dir->path().extension().string() == ".so" )
                {
                    //cout << *dir << std::endl;
                    retCode += load( dir->path().string().c_str() );
                }                                 
            }
        }
        return retCode;
    }
    
    int NodeManager::releaseAll()
    {
        return 0;
    }
    
    Node* NodeManager::create( const std::string& nodeTypeName )
    {
        NodeManagerEntry_t ent = _nodeRegistry[ nodeTypeName ];
        Node* nNode = ent.nodeCreator();
        nNode->_nodeTypeName = nodeTypeName;
        return nNode;
    }
    
    int NodeManager::destroy( Node* node )
    {
        std::string nodeName = node->_nodeTypeName;
        NodeManagerEntry_t ent = _nodeRegistry[ nodeName ];
        ent.nodeDestructor( node );
        return 0;
    }
    
}
