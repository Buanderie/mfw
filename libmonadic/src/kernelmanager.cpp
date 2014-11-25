
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

// INTERNAL
#include "kernelmanager.hpp"
#include "filesystem.hpp"

using namespace std;

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
        std::vector< monadic::filesystem::Path > files;
        monadic::filesystem::Path p(nodeModulePath);
        files = p.getChildren( recursiveSearch );

        for( size_t k = 0; k < files.size(); ++k )
        {
            if( files[k].extension() == dlibExtension )
                retCode += load( files[k].str() );
        }
        return retCode;
    }
    
    int KernelManager::releaseAll()
    {
        return 0;
    }
    
    Node* KernelManager::create( const std::string& kernelName )
    {
        // /!\ TODO
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
