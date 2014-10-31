
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
#include "kernelmanager.hpp"

using namespace std;

#if BOOST_VERSION < 104400
using namespace boost::filesystem;
#else
using namespace boost::filesystem2;
#endif

namespace monadic
{
    int KernelManager::load(const std::string& kernelModulePath )
    {
        // load the node module library
#ifdef __LINUX__
        void* kernelModule = dlopen( kernelModulePath.c_str(), RTLD_LAZY );
#elif defined(__WINDOWS__)
        HMODULE kernelModule = LoadLibrary(kernelModulePath.c_str());
#endif
        if (!kernelModule)
        {
            //cerr << "Cannot load library: " << dlerror() << '\n';
            return 1;    
        }
        
        // load the symbols
#ifdef __LINUX__
        createNode_t* create_node = (createNode_t*) dlsym(nodeModule, "createNode");
        destroyNode_t* destroy_node = (destroyNode_t*) dlsym(nodeModule, "destroyNode");
#elif defined(__WINDOWS__)
		createNode_t* create_node = (createNode_t*)GetProcAddress(nodeModule, "createNode");
		destroyNode_t* destroy_node = (destroyNode_t*)GetProcAddress(nodeModule, "createNode");
#endif

        if (!create_node || !destroy_node) {
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
		Node* tmpNode = create_node();
		std::string strNodeName = tmpNode->getTypeName();
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
