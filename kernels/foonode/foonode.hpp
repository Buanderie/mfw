
#include "monadic.hpp"
#include <fstream>

class FooNode : public monadic::Node
{
        public:
        FooNode();
        virtual ~FooNode();

        void setup();
        void tick( double dt );
        virtual std::string getKernelName();

        private:
        int _cpt;
        int limit;
        std::ofstream pol;
};

