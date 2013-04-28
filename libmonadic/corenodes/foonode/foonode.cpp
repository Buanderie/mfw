// STL
#include <iostream>

// NODE INTERNAL
#include "foonode.hpp"

using namespace std;

namespace monadic
{
    FooNode::FooNode()
    {

    }

    FooNode::~FooNode()
    {

    }

    void FooNode::setup()
    {
        _cpt = 0;
    }

    void FooNode::tick( double dt )
    {
        cout << "FooNode: " << _cpt << endl;
    }
}
