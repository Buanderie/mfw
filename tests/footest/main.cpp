// C
#include <dlfcn.h>

// STL
#include <iostream>
#include <vector>

// BOOST
#include <boost/threadpool.hpp>

// Monadic
#include <monadic.hpp>

using namespace monadic;
using namespace std;
using namespace boost::threadpool;

int main ( int argc, char** argv )
{
    Node* n;

    Application app;
    vector< Node* > nodes;
    
    if( ! NodeManager::getInstance()->loadFromDirectory( argv[1] ) )
        return -1;
    
    app.nodes.push_back( NodeManager::getInstance()->create( "VideoInput" ) );
    app.nodes.push_back( NodeManager::getInstance()->create( "VideoInput" ) );
    app.nodes.push_back( NodeManager::getInstance()->create( "VideoInput" ) );
    Node* popo =  NodeManager::getInstance()->create( "Foo" );
    popo->setPriority( 1 );
    app.nodes.push_back( popo );
    
    for( int k = 0; k < app.nodes.size(); ++k )
        app.nodes[k]->setup();
    
    app.start();
    
    return 0;
}
