
#include "node.hpp"
#include <fstream>

class MSERNode : public monadic::Node
{
        public:
        MSERNode();
        virtual ~MSERNode();
        virtual std::string getKernelName();
        void setup();
        void tick( double dt );

        private:
            void* detector;

};

