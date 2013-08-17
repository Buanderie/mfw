#ifndef __APP_HPP__
#define __APP_HPP__

// C
#include <ctime>

// UNIX
#include <sys/time.h>

// STL
#include <vector>
#include <iostream>

// C++11
//#include <chrono>

// INTERNAL
#include "node.hpp"
#include "thread.hpp"

using namespace std;

namespace monadic
{
    class ApplicationWorker;
    class Application
    {
        public:

            Application(){
                init();
            }
            virtual ~Application(){}
            
            void start();
            void stop();

            double getElapsedTime();

            Node* fetchActiveNode();
            void releaseNode(Node* node);

            std::vector< Node* >                _nodes;

        protected:
        
        private:
            
            std::vector< ApplicationWorker* >   _workers;
            Mutex                               _nodeListMtx;
            Mutex                               _timeRefMtx;
            CondVar                             _nodeListCnd;

            // Time reference
            struct timeval _timeRef;

            void init();
                   
    };
}

#endif //__APP_HPP__
