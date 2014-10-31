
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
        createNode_t* create_node = (createNode_t*) dlsym(kernelModule, "createNode");
        destroyNode_t* destroy_node = (destroyNode_t*) dlsym(kernelModule, "destroyNode");
#elif defined(__WINDOWS__)
        createNode_t* create_node = (createNode_t*)GetProcAddress(kernelModule, "createNode");
        destroyNode_t* destroy_node = (destroyNode_t*)GetProcAddress(kernelModule, "createNode");
#endif

        if (!create_node || !destroy_node) {
            //cerr << "Cannot load symbols: " << dlerror() << '\n';
#ifdef __LINUX__
            dlclose( kernelModule );
#endif
            return 1;
        }
        
        // Create new entry in the registry
        Kernel kernelEntry( create_node, destroy_node );
        //TODO: Is there a better way to retrieve Kernel Name ?
		Node* tmpNode = create_node();
        std::string strKernelName = tmpNode->getKernelName();
        _kernelRegistry.insert ( std::pair<std::string, Kernel>( strKernelName, kernelEntry ) );
        cout << "Loaded kernel module: " << strKernelName << endl;
        return 0;
    }
    
    int KernelManager::release( const std::string& kernelName )
    {
        return 0;
    }
    
    int KernelManager::loadFromDirectory( const std::string& nodeModulePath, bool recursiveSearch )
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
    
    int KernelManager::releaseAll()
    {
        return 0;
    }
    
    Node* KernelManager::create( const std::string& kernelName )
    {
        // THIS COULD CRASH IF KERNEL DOESN'T EXIST
        Kernel ent = _kernelRegistry[ kernelName ];
        Node* nNode = ent.create();
        nNode->_kernelName = kernelName;
        return nNode;
    }
    
    int KernelManager::destroy( Node* node )
    {
        std::string nodeName = node->_kernelName;
        Kernel ent = _kernelRegistry[ nodeName ];
        ent.destroy( node );
        return 0;
    }
    
}
