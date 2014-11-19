#ifndef __APP_HPP__
#define __APP_HPP__

// C
#include <ctime>

// STL
#include <vector>
#include <iostream>
#include <string>

// C++11
//#include <chrono>

// INTERNAL
#include "kernelmanager.hpp"
#include "node.hpp"
#include "link.hpp"
#include "thread.hpp"
#include "timeref.hpp"

using namespace std;

namespace monadic
{
    class ApplicationWorker;
    class Application
    {
        public:

        Application( const std::string& pluginFolder, const std::string& applicationName="Unnamed" ):
                _applicationName(applicationName), _pluginFolder(pluginFolder)
            {
                init();
            }

            virtual ~Application(){}
            
            void start();
            void stop();

            // Public Node management API
            Node* addNode( const std::string& nodeType );
            std::vector< Node* > getNodeList();

            // Public Link management API
            Link* addLink(Node *n1, Node *n2 , size_t bandwidth, Link::LinkMode mode);

            double getElapsedTime();

            Node* fetchActiveNode();
            void releaseNode(Node* node);

            std::vector< Node* >                _nodes;

        protected:
        
        private:
            
            // Generic
            std::string                         _applicationName;

            // Threadpool management
            std::vector< ApplicationWorker* >   _workers;
            monadic::Mutex                      _nodeListMtx;
            monadic::Mutex                      _timeRefMtx;
            monadic::CondVar                    _nodeListCnd;

            // Plugin management
            KernelManager*                      _kernelManager;
            std::string                         _pluginFolder;

            // Link management
            std::vector< Link* >                _links;

            // Time reference
            TimeRef _timeRef;

            void init();
                   
    };
}

#endif //__APP_HPP__
