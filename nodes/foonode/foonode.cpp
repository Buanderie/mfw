#include "foonode.hpp"

#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;

MONADIC_NODE_EXPORT( FooNode, "Foo" )

    FooNode::FooNode()
    {
        std::cout << "Foo::CTOR" << std::endl;
    }

    FooNode::~FooNode()
    {
        std::cout << "Foo::DTOR" << std::endl;
    }

    void FooNode::setup()
    {
        std::cout << "FooNode::setup()" << std::endl;
        _cpt = 0;
        pol.open("foo.txt");
    }

    void FooNode::tick( double dt )
    {
        //std::cout << "Foo: " << _cpt << std::endl;
		_cpt++;
		for( int i = 0; i < 1000; ++i )
		{
		    double k = exp( rand() / rand() ) * log( 2.0 );
		}
        if( _cpt == 200000 )
        {
            disable();
        }

        pol << _cpt << endl;
    }
