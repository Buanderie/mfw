
#include "node.hpp"
#include <fstream>

#include <SDL/SDL.h>

/*
 *http://dranger.com/ffmpeg/tutorial05.html
 *
 */
class VideoDisplayNode : public monadic::Node
{
        public:
        VideoDisplayNode();
        virtual ~VideoDisplayNode();

        void setup();
        void tick( double dt );
        virtual std::string getKernelName();
        private:
        int _cpt;
        std::ofstream pol;
        SDL_Surface* display;
};

