#include "foonode.hpp"

#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

#include <objects/base/number.hpp>
#include <objects/image/image.hpp>


using namespace std;
using namespace monadic;

MONADIC_NODE_EXPORT( FooNode, "Foo" )

    FooNode::FooNode()
    {
        std::cout << "Foo::CTOR" << std::endl;
        //monadic::Image* img = reinterpret_cast<monadic::Image*>( monadic::ObjectFactory::create("Image") );
        this->addPin( "bite", Pin::NODE_OUTPUT_PIN );
        cout << "KALBOP " << this->_pins.size() << endl;
    }

    FooNode::~FooNode()
    {
        std::cout << "Foo::DTOR" << std::endl;
    }

    void FooNode::setup()
    {
        //cout << " SETUP SETUP SETUP " << endl;
        std::cout << "FooNode::setup()" << std::endl;
        _cpt = 0;
        //pol.open("foo.txt");
        srand( time(NULL) );
        //sleep(1);
        limit = 100;
        cout << "limit=" << limit << endl;
    }

    void FooNode::tick( double dt )
    {
        if( _pins.size() > 0 )
        {
            monadic::Image n;
            n.create( 800, 600, 8, 3 );
            for( size_t k = 0; k < _pins.size(); ++k )
            {
                ObjectBlob* b = n.serialize();
                _pins[k]->write( b );
                //cout << getGuid() << " sent number " << n.getValue() << endl;
                delete b;
            }
        }
        else
        {
            //cout << getGuid() << " - NOPE" << endl;
        }
    }

    string FooNode::getKernelName()
    {
        return "Foo";
    }
