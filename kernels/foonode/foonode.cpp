#include "foonode.hpp"

#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

#include <objects/base/number.hpp>

using namespace std;

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
        //cout << " TICK TICK TICK " << endl;
        //std::cout << "Foo: " << _cpt << std::endl;
		_cpt++;
		cout << "--start" << endl;
		for( int i = 0; i < 1000000; ++i )
		{
		    double k = exp( pow(limit,3.5) + 0.001 ) * log( 2.0 );
		}
		cout << "--end" << endl;
		cout << "cpt==" << _cpt << "/" << limit << endl;
        if( _cpt == limit )
        {
            disable();
        }

        /*
        monadic::Number n(753.0);
        for( size_t k = 0; k < _pins.size(); ++k )
        {
            _pins[k]->write( n.serialize() );
        }
        */

        //pol << _cpt << endl;
    }
