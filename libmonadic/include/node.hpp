#ifndef __NODE_HPP__
#define __NODE_HPP__

// BOOST
#include <boost/thread.hpp>

// INTERNAL

namespace monadic
{
    class Node
    {
    friend class NodeManager;
        
    protected:
                    
    public:

        Node():_priority(1)
        {}
        
        virtual ~Node(){}
        
        void start();
        void stop();
        void run();
        std::string getTypeName(){ return _nodeTypeName; }
        unsigned int getPriority(){ return _priority; }
        void setPriority( unsigned int priority ){ _priority = priority; }
        
        virtual void setup()=0;
        virtual void tick( double dTime )=0;

    private:
        boost::thread   _nodeThread;
        std::string     _nodeTypeName;
        std::string     _nodeName;
        unsigned int    _priority;
    };

    // the types of the node factories
    typedef Node* createNode_t();
    typedef void  destroyNode_t(Node*);
    typedef char* getNodeName_t();

}

#define MONADIC_NODE_EXPORT(X, Y) 	extern "C" monadic::Node* createNode() { 	    \
						                return new X;		                        \
					                }						                        \
					                extern "C" void destroyNode(monadic::Node* p) {	\
						                delete p;				                    \
					                }                                               \
                                    extern "C" char* getNodeName(){                 \
                                        return strdup(Y);                           \
                                    }
#endif
