#ifndef __KERNEL_HPP__
#define __KERNEL_HPP__

// INTERNAL
#include "node.hpp"

namespace monadic
{

    // the types of the node factories
    typedef Node* createNode_t();
    typedef void  destroyNode_t(Node*);
    typedef char* getNodeName_t();

    class Kernel
    {
    public:
        Kernel( createNode_t* nodeCreator = 0, destroyNode_t*  nodeDestructor = 0 )
            :_nodeCreator(nodeCreator), _nodeDestructor(nodeDestructor)
        {

        }

        Kernel( const monadic::Kernel& other )
        {
            _nodeCreator = other._nodeCreator;
            _nodeDestructor = other._nodeDestructor;
        }

        virtual ~Kernel(){}

        createNode_t* getCreator(){ return _nodeCreator; }
        destroyNode_t* getDestructor(){ return _nodeDestructor; }
        monadic::Node* create(){ return _nodeCreator(); }
        void destroy( monadic::Node* n ){ return _nodeDestructor(n); }

    private:
        createNode_t*   _nodeCreator;
        destroyNode_t*  _nodeDestructor;

    protected:

    };
}

#endif
