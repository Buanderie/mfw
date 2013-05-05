// STL
#include <iostream>

// Monadic
#include <monadic.hpp>

using namespace monadic;
using namespace std;

int main ( int argc, char** argv )
{
    Node* n = new FooNode();
    n->start();

    while(1)
    {
        sleep(1);
    }

    return 0;
}
