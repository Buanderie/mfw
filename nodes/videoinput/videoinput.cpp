#include "videoinput.hpp"

#include <iostream>

MONADIC_NODE_EXPORT( VideoInputNode, "VideoInput" )

    VideoInputNode::VideoInputNode()
    {

    }

    VideoInputNode::~VideoInputNode()
    {

    }

    void VideoInputNode::setup()
    {
        _cpt = 0;
    }

    void VideoInputNode::tick( double dt )
    {
        std::cout << "VideoNode: " << _cpt << std::endl;
	_cpt++;
    }
