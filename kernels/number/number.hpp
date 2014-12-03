
#include "monadic.hpp"
#include <fstream>

class NumberNode : public monadic::Node
{
        public:
        NumberNode();
        virtual ~NumberNode();

        void setup();
        void tick( double dt );

        private:

};

