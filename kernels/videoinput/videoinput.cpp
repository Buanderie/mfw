#include "videoinput.hpp"

#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "monadic.hpp"
#include "objects/image/image.hpp"

using namespace std;
using namespace monadic;

MONADIC_NODE_EXPORT( VideoInputNode, "VideoInput" )

    VideoInputNode::VideoInputNode()
    {
        _cap = 0;
        std::cout << "VideoNode::CTOR" << std::endl;
        this->addPin( "out", monadic::Pin::NODE_OUTPUT_PIN );
    }

    VideoInputNode::~VideoInputNode()
    {
        std::cout << "VideoNode::DTOR" << std::endl;
    }

    std::string VideoInputNode::getKernelName()
    {
        return "VideoInput";
    }

    void VideoInputNode::setup()
    {
        //cv::VideoCapture* cap = new cv::VideoCapture("C:\\Users\\imagedpt\\dev\\outputVideo.avi");
        //cv::VideoCapture* cap = new cv::VideoCapture(0);
        cv::VideoCapture* cap = new cv::VideoCapture("/home/said/videos/valls.mp4");
        _cap = (void*)cap;
    }

    void VideoInputNode::tick( double dt )
    {
        Timer t;
        t.start();
        cv::Mat frame;
        cv::VideoCapture* cap = (cv::VideoCapture*)_cap;
        Pin* outPin = findPinFromLabel("out");

        if( !outPin->isConnected() )
            waitForConnection();

        if( outPin->isConnected() )
        {
            if( cap->grab() )
            {
                cap->retrieve(frame);
                //cv::resize( frame, frame, cv::Size( frame.cols * 2, frame.rows * 2 ) );
                cv::cvtColor( frame, frame, CV_BGR2RGB );
                //cout << "shit retreived" << endl;
                monadic::Image img;
                img.create( frame.cols, frame.rows, 8, frame.channels() );

                size_t bufferSize = frame.cols * frame.rows * frame.channels();
                img.copyFrom( (char*)frame.data, bufferSize );

                ObjectBlob* b = img.serialize();

                outPin->write( b );
                /*
            cv::imshow("pol.png", frame);
            cv::waitKey(5);
            */
                delete b;

            }
            else
            {
                this->disable();
            }
        }
        t.stop();
        //cout << "PLAYER - t=" << t.getElapsedTimeInSec() << " - fps=" << 1.0 / t.getElapsedTimeInSec() << endl;
        //cout << "###### TICK TOCK ######" << endl;
    }
