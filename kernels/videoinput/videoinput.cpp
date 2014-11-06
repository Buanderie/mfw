#include "videoinput.hpp"

#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
//#include <unistd.h>

using namespace std;

MONADIC_NODE_EXPORT( VideoInputNode, "VideoInput" )

    VideoInputNode::VideoInputNode()
    {
        std::cout << "VideoNode::CTOR" << std::endl;
    }

    VideoInputNode::~VideoInputNode()
    {
        std::cout << "VideoNode::DTOR" << std::endl;
    }

    void VideoInputNode::setup()
    {
        _cpt = 0;
        pol.open("video.txt");
    }

    void VideoInputNode::tick( double dt )
    {
        std::cout << "VideoNode: " << dt << std::endl;
	    _cpt++;
        for( int i = 0; i < 10000; ++i )
		{
            double k = pow( 0.8, exp( rand() / rand() ) * log( 2.0 ) * exp( 10.0 ) );
		}
        //if( _cpt == 5000 )
        //    disable();
        //sleep(1);
        pol << _cpt << " - " << setprecision(12) << dt << endl;
    }
