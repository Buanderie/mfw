// C
#include <dlfcn.h>

// STL
#include <iostream>

// Monadic
#include <monadic.hpp>

using namespace monadic;
using namespace std;

int main ( int argc, char** argv )
{
    Node* n;

//
// load the triangle library
    void* triangle = dlopen( argv[1], RTLD_LAZY);
    if (!triangle) {
        cerr << "Cannot load library: " << dlerror() << '\n';
        return 1;
    }

    // load the symbols
    createNode_t* create_triangle = (createNode_t*) dlsym(triangle, "createNode");
    destroyNode_t* destroy_triangle = (destroyNode_t*) dlsym(triangle, "destroyNode");
    if (!create_triangle || !destroy_triangle) {
        cerr << "Cannot load symbols: " << dlerror() << '\n';
        return 1;
    }

    // create an instance of the class
    n = create_triangle();
    n->start();
    // destroy the class

    while(1)
    {
        sleep(1);
    }

	    // unload the triangle library
        //destroy_triangle(n);
    //dlclose(triangle);

    return 0;
}
