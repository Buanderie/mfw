#include "foonode.hpp"

#include <iostream>

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
    }

    void FooNode::tick( double dt )
    {
        std::cout << "Foo: " << _cpt << std::endl;
		_cpt++;
		for( int i = 0; i < 1000; ++i )
		{
		    double k = exp( rand() / rand() ) * log( 2.0 );
		}
    }
