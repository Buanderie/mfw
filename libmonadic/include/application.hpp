#ifndef __APP_HPP__
#define __APP_HPP__

// C
#include <ctime>

// STL
#include <vector>
#include <queue>
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
#include "guid.hpp"

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
            Node* addNode(const std::string& nodeType , const monadic::Guid guid=std::string("00000000-0000-0000-0000-000000000000") );
            std::vector< monadic::Guid > getNodeIds();
            std::vector< monadic::Node* > getNodes();
            Node* getNode( const monadic::Guid& guid );
            void enableAllNodes();
	    
            // Public Link management API
            Link* addLink( monadic::Pin* pin1, monadic::Pin* pin2, std::size_t bandwidth, monadic::Link::LinkMode mode );
            monadic::Guid addLink( const monadic::Guid& n1, const monadic::Guid& n2, const std::string& pin1, const std::string& pin2, size_t bandwidth, Link::LinkMode mode );

            // Public Application management API
            bool save( const std::string& filePath );
            bool load( const std::string& filePath );

            double getElapsedTime();

            Node* fetchActiveNode();
            void releaseNode(Node* node);

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

            //std::vector< Node* >                _nodes;
            std::map< monadic::Guid, Node* >	_nodes;
            std::queue< Node* >                 _nodeQueue;

            // Link management
            std::vector< Link* >                _links;

            // Time reference
            TimeRef _timeRef;

            void init();
                   
    };
}

#endif //__APP_HPP__
