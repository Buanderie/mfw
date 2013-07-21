#include "videoinput.hpp"

#include <iostream>

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
    }

    void VideoInputNode::tick( double dt )
    {
        std::cout << "VideoNode: " << _cpt << std::endl;
	    _cpt++;
	    		for( int i = 0; i < 1000; ++i )
		{
		    double k = exp( rand() / rand() ) * log( 2.0 );
		}
    }
