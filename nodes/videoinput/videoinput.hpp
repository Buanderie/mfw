
#include "node.hpp"
#include <fstream>

class VideoInputNode : public monadic::Node
{
        public:
        VideoInputNode();
        virtual ~VideoInputNode();

        void setup();
        void tick( double dt );

        private:
        int _cpt;
        std::ofstream pol;
};

