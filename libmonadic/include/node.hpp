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
#include "identifiable.hpp"
#include "jsonable.hpp"
#include "thread.hpp"
#include "pin.hpp"


namespace monadic
{
    class Application;
    class Node : public Identifiable, JSONable
    {
    
    friend class KernelManager;
    friend class Application;
    friend class ApplicationWorker;

    protected:
        std::string     _kernelName;

        // Pins
        std::vector< monadic::Pin * > _pins;

    public:

        typedef enum{
            NODE_INACTIVE=0,
            NODE_ACTIVE,
            NODE_BUSY,
            NODE_REQUESTING_ACTIVATION,
            NODE_REQUESTING_DEACTIVATION
        } NodeState;

        Node():_priority(1),_nodeState(NODE_ACTIVE)
        {

        }
        
        virtual ~Node(){}
        
        void start();
        void stop();
        void run();
        
        std::string getKernelName(){ return _kernelName; }

        unsigned int getPriority(){ return _priority; }
        void setPriority( unsigned int priority ){ _priority = priority; }
        
        void enable();
        void disable();

        NodeState getState(){
            NodeState ret;
            _nodeMtx.lock();
            ret = _nodeState;
            _nodeMtx.unlock();
            return ret;
        }

        void setState( Node::NodeState state )
        {
            _nodeMtx.lock();
            _nodeState = state;
            _nodeMtx.unlock();
        }
        
        virtual void setup()=0;
        virtual void tick( double dTime )=0;
        unsigned int getTickCount(){ return _tickCount; }

        monadic::Pin* addPin( const std::string& pinLabel, monadic::Pin::PinMode mode );
        monadic::Pin* findPinFromLabel( const std::string& pinLabel );

        virtual picojson::object toJSON();

    private:
        monadic::Application*   _parentApp;
        std::string             _nodeName;
        unsigned int            _priority;
        NodeState               _nodeState;
        unsigned int            _tickCount;
        monadic::Mutex          _nodeMtx;

    };
}

#define MONADIC_NODE_EXPORT(X, Y) 	extern "C" MONADIC_EXPORT_SYMBOL monadic::Node* createNode() { 	    \
										return new X;		                        \
									}						                        \
									extern "C" MONADIC_EXPORT_SYMBOL void destroyNode(monadic::Node* p) {\
										delete p;				                    \
									}                                               

#endif
