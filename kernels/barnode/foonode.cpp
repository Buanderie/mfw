#include "foonode.hpp"

#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

#include <objects/base/number.hpp>
#include <objects/image/image.hpp>

using namespace std;
using namespace monadic;

MONADIC_NODE_EXPORT( BarNode, "Bar" )

    BarNode::BarNode()
    {
        _kernelName = "Bar";
        std::cout << "Bar::CTOR" << std::endl;
        this->addPin( "cul", Pin::NODE_INPUT_PIN );
        cout << "POLOP " << this->_pins.size() << endl;
    }

    BarNode::~BarNode()
    {
        std::cout << "Foo::DTOR" << std::endl;
    }

    void BarNode::setup()
    {
        //cout << " SETUP SETUP SETUP " << endl;
        std::cout << "BarNode::setup()" << std::endl;
        _cpt = 0;
        //pol.open("foo.txt");
        srand( time(NULL) );
        //sleep(1);
        limit = 100;
        cout << "limit=" << limit << endl;
    }

    void BarNode::tick( double dt )
    {
        Timer t;
        t.start();
        if( _pins.size() > 0 )
        {
            for( size_t k = 0; k < _pins.size(); ++k )
            {
                //cout << getGuid() << " READING from " << _pins[k]->getLabel() << endl;
                vector< ObjectBlob* > blobs = _pins[k]->read();
                //cout << "BLOBS.size()=" << blobs.size() << endl;
                for( int i = 0; i < blobs.size(); ++i )
                {
                    ObjectBlob* b = blobs[i];
                    cout << b->getTypeName() << endl;
                    if( b->getTypeName() == "Image" )
                    {
                        //cout << getGuid() << " received blob image " << endl;
                        Image n;
                        n.deserialize(b);
                        //cout << getGuid() << " received image " << endl;
                    }
                    delete blobs[i];
                }
            }
            t.stop();
            cout << getGuid() << " t=" << t.getElapsedTimeInSec() << " - fps=" << 1.0 / t.getElapsedTimeInSec() << endl;
        }
        //usleep(33333);
    }
