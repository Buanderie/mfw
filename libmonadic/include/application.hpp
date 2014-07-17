#ifndef __APP_HPP__
#define __APP_HPP__

// C
#include <ctime>

// UNIX
#include <sys/time.h>

// STL
#include <vector>
#include <iostream>
#include <string>

// C++11
//#include <chrono>

// INTERNAL
#include "nodemanager.hpp"
#include "node.hpp"
#include "thread.hpp"

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
            Mutex                               _nodeListMtx;
            Mutex                               _timeRefMtx;
            CondVar                             _nodeListCnd;

            // Plugin management
            NodeManager*                        _nodeManager;
            std::string                         _pluginFolder;

            // Time reference
            struct timeval _timeRef;

            void init();
                   
    };
}

#endif //__APP_HPP__
