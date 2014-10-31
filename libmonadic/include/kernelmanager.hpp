#ifndef __NODEMANAGER_HPP__
#define __NODEMANAGER_HPP__

// STL
#include <string>
#include <map>

// INTERNAL
#include "singleton.hpp"
#include "kernel.hpp"

namespace monadic
{
    class KernelManager /* : public Singleton<NodeManager> */
    {
        //friend class Singleton<NodeManager>;

        public:
            KernelManager(){}
            ~KernelManager(){}

            int load( const std::string& kernelModulePath );
            int loadFromDirectory( const std::string& kernelModulePath, bool recursiveSearch = true );
            
            int release(const std::string& kernelName );
            int releaseAll();
            
            Node* create(const std::string& kernelName );
            int destroy( Node* node );
            
        private:
            std::map< std::string, Kernel > _kernelRegistry;

    };
}

#endif
