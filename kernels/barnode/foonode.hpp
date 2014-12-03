
#include "monadic.hpp"
#include <fstream>

class BarNode : public monadic::Node
{
        public:
        BarNode();
        virtual ~BarNode();

        void setup();
        void tick( double dt );

        private:
        int _cpt;
        int limit;
        std::ofstream pol;
};

