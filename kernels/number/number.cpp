#include "number.hpp"

#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

#include <objects/base/number.hpp>
#include <objects/image/image.hpp>


using namespace std;
using namespace monadic;

MONADIC_NODE_EXPORT( NumberNode, "Number" )

    NumberNode::NumberNode()
    {
        this->addPin( "out", Pin::NODE_OUTPUT_PIN );
    }

    NumberNode::~NumberNode()
    {
        //std::cout << "Number::DTOR" << std::endl;
    }

    void NumberNode::setup()
    {
        //cout << " SETUP SETUP SETUP " << endl;
        //std::cout << "FooNode::setup()" << std::endl;
        //_cpt = 0;
        //pol.open("foo.txt");
        //srand( time(NULL) );
        //sleep(1);
        //limit = 100;
        //cout << "limit=" << limit << endl;
    }

    void NumberNode::tick( double dt )
    {
        if( _pins.size() > 0 )
        {
        		
            for( size_t k = 0; k < _pins.size(); ++k )
            {
                //monadic::Number n( sin( 3.14159 * ((double)rand() / (double)RAND_MAX) ) );
                monadic::Number n( 77 );
                ObjectBlob* b = n.serialize();
                _pins[k]->write( b );
                delete b;
            }
        }
    }

    string NumberNode::getKernelName()
    {
        return "Number";
    }
