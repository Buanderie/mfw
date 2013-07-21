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

    Application app;
    vector< Node* > nodes;
    
    if( ! NodeManager::getInstance()->loadFromDirectory( argv[1] ) )
        return -1;
    
    app.nodes.push_back( NodeManager::getInstance()->create( "VideoInput" ) );
    //app.nodes.push_back( NodeManager::getInstance()->create( "VideoInput" ) );
    //app.nodes.push_back( NodeManager::getInstance()->create( "VideoInput" ) );
    Node* popo =  NodeManager::getInstance()->create( "Foo" );
    popo->setPriority( 25 );
    app.nodes.push_back( popo );
    
    
/*
    for( int k = 0; k < nodes.size(); ++k )
        nodes[k]->setup();
*/

/*
    for( int k = 0; k < nodes.size(); ++k )
        nodes[k]->start();

    fifo_pool tp(4); // tp is handle to the pool
    
    while(1)
    {
        
        for( int k = 0; k < nodes.size(); ++k )
        {
            tp.schedule( boost::bind( &Node::tick, nodes[k], 0.0 ) );
        }
        boost::xtime t;
        tp.wait();
    }
*/

    app.start();
    
    return 0;
}
