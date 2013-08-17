
#include "node.hpp"
#include <fstream>

class FooNode : public monadic::Node
{
        public:
        FooNode();
        virtual ~FooNode();

        void setup();
        void tick( double dt );

        private:
        int _cpt;
        std::ofstream pol;
};

