// C
#include <dlfcn.h>
#include <unistd.h>

// STL
#include <iostream>
#include <vector>

// BOOST
//#include <boost/threadpool.hpp>

// Monadic
#include <monadic.hpp>

using namespace monadic;
using namespace std;
//using namespace boost::threadpool;

int main ( int argc, char** argv )
{
    //Image img;
    
    Image* img = reinterpret_cast<Image*>( ObjectFactory::create("Image") );
    img->popo();
    cout << "img - " << img->getTypeName() << endl;
    return 0;
    
    
    Node* n;

    Application app;
    //vector< Node* > nodes;
    
    if( ! NodeManager::getInstance()->loadFromDirectory( argv[1] ) )
        return -1;
    
    //app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    //app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    //app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    //app._nodes.push_back( NodeManager::getInstance()->create( "VideoInput" ) );
    Node* popo =  NodeManager::getInstance()->create( "Foo" );
    popo->setPriority( 1 );
    app._nodes.push_back( popo );
    
    for( int k = 0; k < app._nodes.size(); ++k )
        app._nodes[k]->setup();
    
    app.start();
    while(1)
    {
        cout << "t=" << app.getElapsedTime() << endl;
        for( int k = 0; k < app._nodes.size(); ++k )
        {
            cout    << "NODE " << (unsigned long)app._nodes[k] << " - " 
                    << app._nodes[k]->getTypeName() << " state: " << app._nodes[k]->getState() 
                    << endl;
        }
        cout << endl;
        sleep(1);
    }

    cout << "CHIPS" << endl;
    
    return 0;
}
