#ifndef __FOONODE_HPP__
#define __FOONODE_HPP__

// INTERNAL
#include "node.hpp"

namespace monadic
{
    class FooNode : public Node
    {
        public:
        FooNode();
        virtual ~FooNode();

        void setup();
        void tick( double dt );

        private:
        int _cpt;
    };
}

#endif
