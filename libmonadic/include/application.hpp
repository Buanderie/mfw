#ifndef __APP_HPP__
#define __APP_HPP__

// STL
#include <vector>
#include <iostream>

// BOOST
#include <boost/threadpool.hpp>

// INTERNAL
#include "node.hpp"

using namespace std;

namespace monadic
{
    class Application
    {
        public:
            Application(){
                init();
            }
            virtual ~Application(){}
            
            std::vector< Node* > nodes;  
            
            void start()
            {
                while(1)
                {
                    for( int k = 0; k < nodes.size(); ++k )
                    {
                        //_appThreadPool.schedule( boost::bind( &Node::tick, nodes[k], 0.0 ) );
                        //cout << "node " << k << " priority=" << nodes[k]->getPriority() << endl;
                        boost::threadpool::schedule(_appThreadPool, boost::threadpool::prio_task_func( nodes[k]->getPriority(), boost::bind( &Node::tick, nodes[k], 0.0 ) ) );
                    }
                    _appThreadPool.wait(25);
                }
            }
            
        protected:
        
        private:
            void init();
            
            boost::threadpool::prio_pool _appThreadPool;   
                   
    };
}

#endif
