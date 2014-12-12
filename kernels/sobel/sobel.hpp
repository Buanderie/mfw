
#include "node.hpp"
#include <fstream>

class SobelNode : public monadic::Node
{
        public:
        SobelNode();
        virtual ~SobelNode();
        virtual std::string getKernelName();
        void setup();
        void tick( double dt );

        private:

};

