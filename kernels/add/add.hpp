
#include "monadic.hpp"
#include "objects/base/number.hpp"

#include <fstream>

class AddNode : public monadic::Node
{
        public:
        AddNode();
        virtual ~AddNode();

        void setup();
        void tick( double dt );

        private:
        	monadic::Number n1;
        	monadic::Number n2;
        	monadic::Number out;

};

