
#include "node.hpp"
#include <fstream>

/*
 *http://dranger.com/ffmpeg/tutorial05.html
 *
 */
class VideoInputNode : public monadic::Node
{
        public:
        VideoInputNode();
        virtual ~VideoInputNode();
        virtual getKernelName();
        void setup();
        void tick( double dt );

        private:
        void* _cap;
};

