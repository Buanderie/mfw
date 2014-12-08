#include "videodisplay.hpp"

#include "monadic.hpp"
#include "objects/image/image.hpp"

#include <opencv2/highgui/highgui.hpp>

#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

#include <SDL/SDL.h>

using namespace std;
using namespace monadic;

MONADIC_NODE_EXPORT( VideoDisplayNode, "VideoDisplay" )

    VideoDisplayNode::VideoDisplayNode()
    {
        std::cout << "VideoDisplay::CTOR" << std::endl;
        _kernelName = "VideoDisplay";
        this->addPin( "in", Pin::NODE_INPUT_PIN );
    }

    VideoDisplayNode::~VideoDisplayNode()
    {
        std::cout << "VideoDisplay::DTOR" << std::endl;
    }

    void VideoDisplayNode::setup()
    {
        // Initialize the SDL
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            cerr << "SDL_Init() Failed: " << SDL_GetError() << endl;
            exit(1);
        }

        // Set the video mode

         display = SDL_SetVideoMode(1280, 768, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE );
         if (display == NULL)
         {
          cerr << "SDL_SetVideoMode() Failed: " << SDL_GetError() << endl;
          exit(1);
         }

         // Set the title bar
         SDL_WM_SetCaption("SDL Tutorial", "SDL Tutorial");

    }

    void VideoDisplayNode::tick( double dt )
    {
        Timer t;
        t.start();
        SDL_Event event;
        // Check for messages
        if (SDL_PollEvent(&event))
        {
            // Check for the quit message
            if (event.type == SDL_QUIT)
            {
                // Quit the program
                return;
            }
            
            cout << "event.type=" << (int)(event.type) << endl;
        }

        Pin* p = this->findPinFromLabel("in");
        vector<ObjectBlob*> b = p->read();
        if( b.size() > 0 )
        {
            if( b[0]->getTypeName() == "Image" )
            {
                monadic::Image img;
                img.deserialize(b[0]);
                cv::Mat m( img.getHeight(), img.getWidth(), CV_8UC3, img.ptr() );
                cout << dec <<  img.getHeight() << " - " << img.getWidth() << " - " << endl;
                //cv::imshow("pute", m);
                //cv::waitKey(5);
                //cv::imwrite("po.png", m);
                int pitch = img.getChannels()*img.getWidth();
                    printf("Depth %d, nChannels %d, pitch %d\n", img.getDepth(),
                                    img.getChannels(), pitch);
                    SDL_Surface *surface = SDL_CreateRGBSurfaceFrom((void*)img.ptr(),
                                    img.getWidth(),
                                    img.getHeight(),
                                    img.getDepth()*img.getChannels(),
                                    pitch,
                                    0x0000ff, 0x00ff00, 0xff0000, 0
                                    );

                    if (SDL_BlitSurface(surface, NULL, display, NULL) != 0)
                    {
                     cerr << "SDL_BlitSurface() Failed: " << SDL_GetError() << endl;
                     exit(1);
                    }

                    //Update the display
                    SDL_Flip(display);

                    delete surface;

            }
        }
        for( int i = 0; i < b.size(); ++i )
        {
            delete b[i];
        }
        t.stop();
        cout << "DISPLAY - t=" << t.getElapsedTimeInSec() << " - fps=" << 1.0 / t.getElapsedTimeInSec() << endl;
        //usleep(33000);
    }
