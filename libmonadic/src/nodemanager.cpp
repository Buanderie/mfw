
#ifdef __LINUX__
    static const char * dlibExtension = ".so";
#endif

#ifdef __MACOSX__
    static const char * dlibExtension = ".dylib";
#endif

#ifdef __WINDOWS__
    static const char * dlibExtension = ".dll";
#endif

// SYSTEM
#ifdef __LINUX__
	#include <dlfcn.h>
#elif defined(__WINDOWS__)
#include <Windows.h>
#endif

// STL
#include <iostream>

// BOOST
// Oh yeah.. heavy Boost shit inside core components :/
#define BOOST_FILESYSTEM_VERSION 2
#include <boost/filesystem.hpp>

// INTERNAL
#include "nodemanager.hpp"

using namespace std;

#if BOOST_VERSION < 104400
using namespace boost::filesystem;
#else
using namespace boost::filesystem2;
#endif

namespace monadic
{
    int NodeManager::load( const std::string& nodeModulePath )
    {
        // load the node module library
#ifdef __LINUX__
        void* nodeModule = dlopen( nodeModulePath.c_str(), RTLD_LAZY );
#elif defined(__WINDOWS__)
		HMODULE nodeModule = LoadLibrary(nodeModulePath.c_str());
#endif
        if (!nodeModule)
        {
            //cerr << "Cannot load library: " << dlerror() << '\n';
            return 1;    
        }
        
        // load the symbols
#ifdef __LINUX__
        createNode_t* create_node = (createNode_t*) dlsym(nodeModule, "createNode");
        destroyNode_t* destroy_node = (destroyNode_t*) dlsym(nodeModule, "destroyNode");
        getNodeName_t* name_node = (getNodeName_t*) dlsym(nodeModule, "getNodeName");
#elif defined(__WINDOWS__)
		createNode_t* create_node = (createNode_t*)GetProcAddress(nodeModule, "createNode");
		destroyNode_t* destroy_node = (destroyNode_t*)GetProcAddress(nodeModule, "createNode");
		getNodeName_t* name_node = (getNodeName_t*)GetProcAddress(nodeModule, "createNode");
#endif

        if (!create_node || !name_node || !destroy_node) {
            //cerr << "Cannot load symbols: " << dlerror() << '\n';
#ifdef __LINUX__
            dlclose( nodeModule );
#endif
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
    
    int NodeManager::loadFromDirectory( const std::string& nodeModulePath, bool recursiveSearch )
    {
        int retCode = -1;

        if( recursiveSearch )
        {
            for ( boost::filesystem::recursive_directory_iterator end, dir(nodeModulePath.c_str()); dir != end; ++dir )
            {
                if( !boost::filesystem::is_directory( dir->path() ) && dir->path().extension() == dlibExtension )
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
                if( !boost::filesystem::is_directory( dir->path() ) && dir->path().extension() == dlibExtension )
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
