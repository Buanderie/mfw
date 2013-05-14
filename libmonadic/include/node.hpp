#ifndef __NODE_HPP__
#define __NODE_HPP__

// BOOST
#include <boost/thread.hpp>

// INTERNAL

namespace monadic
{
    class Node
    {
    public:
        Node(){}
        virtual ~Node(){}

        void start();
        void stop();
        void run();

        virtual void setup()=0;
        virtual void tick( double dTime )=0;

    private:
        boost::thread   _nodeThread;

    };

    // the types of the node factories
    typedef Node* createNode_t();
    typedef void destroyNode_t(Node*);

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
