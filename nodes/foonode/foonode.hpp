
#include "node.hpp"

class FooNode : public monadic::Node
{
        public:
        FooNode();
        virtual ~FooNode();

        void setup();
        void tick( double dt );

        private:
        int _cpt;
};

