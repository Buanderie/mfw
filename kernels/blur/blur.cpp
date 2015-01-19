#include "blur.hpp"

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

MONADIC_NODE_EXPORT( BlurNode, "Blur" )

    BlurNode::BlurNode()
    {
        std::cout << "Sobel::CTOR" << std::endl;
        this->addPin( "out", monadic::Pin::NODE_OUTPUT_PIN );
        this->addPin( "in", monadic::Pin::NODE_INPUT_PIN );
    }

    BlurNode::~BlurNode()
    {
        std::cout << "Sobel::DTOR" << std::endl;
    }

    std::string BlurNode::getKernelName()
    {
        return "Blur";
    }

    void BlurNode::setup()
    {

    }

    void BlurNode::tick( double dt )
    {
        Timer t;
        t.start();
        Pin* outPin = findPinFromLabel("out");
        Pin* inPin = findPinFromLabel("in");

        if( !outPin->isConnected() )
            waitForConnection();

        if( !inPin->isConnected() )
            waitForConnection();

        if( inPin->isConnected() && outPin->isConnected() )
        {
            vector<ObjectBlob*> b = inPin->read();
            if( b.size() > 0 )
            {
                for( int k = 0; k < b.size(); ++k )
                {
                    if( b[k]->getTypeName() == "Image" )
                    {
                        monadic::Image img;
                        img.deserialize(b[k]);
                        cv::Mat m( img.getHeight(), img.getWidth(), CV_8UC3, img.ptr() );
                        cv::Mat res( img.getHeight(), img.getWidth(), CV_8UC3 );

                        cv::blur( m, res, cv::Size(10,10) );

                        monadic::Image imgout;
                        imgout.create( m.cols, m.rows, 8, m.channels() );
                        size_t bufferSize = m.cols * m.rows * m.channels();
                        imgout.copyFrom( (char*)res.data, bufferSize );
                        ObjectBlob* bout = imgout.serialize();
                        outPin->write( bout );
                        delete bout;
                    }
                    delete b[k];
                }
            }
        }
        t.stop();
    }
