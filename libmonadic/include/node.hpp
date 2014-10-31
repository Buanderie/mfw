#ifndef __NODE_HPP__
#define __NODE_HPP__

// BOOST
//#include <boost/thread.hpp>

// STL
#include <string>

// PLUGIN EXPORT
#if defined(__LINUX__)
#define MONADIC_EXPORT_SYMBOL
#elif defined(__WINDOWS__)
#define MONADIC_EXPORT_SYMBOL __declspec(dllexport)
#endif

// INTERNAL

namespace monadic
{
    class Node
    {
    
    friend class KernelManager;
    friend class Application;
    friend class ApplicationWorker;

    protected:
        std::string     _kernelName;

    public:

        typedef enum{
            NODE_INACTIVE=0,
            NODE_ACTIVE,
            NODE_BUSY
        } NodeState;

        Node():_priority(1),_nodeState(NODE_ACTIVE)
        {}
        
        virtual ~Node(){}
        
        void start();
        void stop();
        void run();
        
        std::string getKernelName(){ return _kernelName; }

        unsigned int getPriority(){ return _priority; }
        void setPriority( unsigned int priority ){ _priority = priority; }
        
        void enable(){ _nodeState = NODE_ACTIVE; }
        void disable(){ _nodeState = NODE_INACTIVE; }

        NodeState getState(){
            return _nodeState;
        }
        
        virtual void setup()=0;
        virtual void tick( double dTime )=0;
        unsigned int getTickCount(){ return _tickCount; }

		
    private:
        void*           _nodeThread;
        std::string     _nodeName;
        unsigned int    _priority;
        NodeState       _nodeState;
        unsigned int    _tickCount;
    };
}

#define MONADIC_NODE_EXPORT(X, Y) 	extern "C" MONADIC_EXPORT_SYMBOL monadic::Node* createNode() { 	    \
										return new X;		                        \
									}						                        \
									extern "C" MONADIC_EXPORT_SYMBOL void destroyNode(monadic::Node* p) {\
										delete p;				                    \
									}                                               

#endif
