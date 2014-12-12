
#include "node.hpp"
#include <fstream>

class BlurNode : public monadic::Node
{
        public:
        BlurNode();
        virtual ~BlurNode();
        virtual std::string getKernelName();
        void setup();
        void tick( double dt );

        private:

};

