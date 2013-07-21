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
        std::cout << "POLBAK !!! " << _cpt << std::endl;
	    _cpt++;
	    //sleep(1);
    }
