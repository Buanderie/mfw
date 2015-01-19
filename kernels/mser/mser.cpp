#include "mser.hpp"

#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>

#include "monadic.hpp"
#include "objects/image/image.hpp"

using namespace std;
using namespace monadic;

MONADIC_NODE_EXPORT( MSERNode, "MSER" )

    MSERNode::MSERNode()
    {
        detector = (void*)( new cv::MSER(25, (int)(0.00002*640.0*480.0), (int)(0.005*640.0*480.0), 1, 0.7));
        std::cout << "Sobel::CTOR" << std::endl;
        this->addPin( "out", monadic::Pin::NODE_OUTPUT_PIN );
        this->addPin( "in", monadic::Pin::NODE_INPUT_PIN );
    }

    MSERNode::~MSERNode()
    {
        std::cout << "Sobel::DTOR" << std::endl;
    }

    std::string MSERNode::getKernelName()
    {
        return "MSER";
    }

    void MSERNode::setup()
    {

    }

    void MSERNode::tick( double dt )
    {
        Timer t;
        t.start();
        Pin* outPin = findPinFromLabel("out");
        Pin* inPin = findPinFromLabel("in");

        if( !inPin->isConnected() )
            waitForConnection();

        if( !outPin->isConnected() )
            waitForConnection();

        if( outPin->isConnected() && inPin->isConnected() )
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
                        res = m.clone();

                        cv::cvtColor( m, m, CV_RGB2GRAY );

                        vector< vector< cv::Point > > ret;
                        cv::MSER* det = (cv::MSER*)(detector);
                        (*det)(m, ret);

                        for( size_t i = 0; i < ret.size(); ++i )
                        {
                            //cv::circle( res, kps[i].pt, 3, CV_RGB(255,0,0) );
                            cv::Rect r = cv::boundingRect(ret[i]);
                            cv::rectangle( res, r, CV_RGB(255,0,0), 3 );
                        }

                        monadic::Image imgout;
                        imgout.create( res.cols, res.rows, 8, res.channels() );
                        size_t bufferSize = res.cols * res.rows * res.channels();
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
