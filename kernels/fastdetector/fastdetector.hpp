
#include "node.hpp"
#include <fstream>

class FastDetectorNode : public monadic::Node
{
        public:
        FastDetectorNode();
        virtual ~FastDetectorNode();
        virtual std::string getKernelName();
        void setup();
        void tick( double dt );

        private:
            void* detector;

};

