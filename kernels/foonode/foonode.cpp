#include "foonode.hpp"

#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

#include <objects/base/number.hpp>

using namespace std;
using namespace monadic;

MONADIC_NODE_EXPORT( FooNode, "Foo" )

    FooNode::FooNode()
    {
        _kernelName = "Foo";
        std::cout << "Foo::CTOR" << std::endl;
        std::cout << "dlfk=" << _kernelName << endl;
        //monadic::Image* img = reinterpret_cast<monadic::Image*>( monadic::ObjectFactory::create("Image") );
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
        monadic::Number n( 1234.0 );
        if( _pins.size() > 0 )
        {
        for( size_t k = 0; k < _pins.size(); ++k )
        {
            ObjectBlob* b = n.serialize();
            _pins[k]->write( b );
            cout << getGuid() << " sent number " << n.getValue() << endl;
            delete b;
        }
        }
        else
        {
            cout << getGuid() << " - NOPE" << endl;
        }
    }
