#include "videoinput.hpp"

#include <cmath>
#include <iostream>
#include <iomanip>

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
	    for( int i = 0; i < 1000; ++i )
		{
		    double k = exp( rand() / rand() ) * log( 2.0 );
		}
        if( _cpt == 5000 )
            disable();

        pol << _cpt << " - " << setprecision(12) << dt << endl;
    }
