// STL
#include <iostream>
#include <iomanip>
#include <vector>

#ifdef __WINDOWS__

#else
#include <unistd.h>
#endif

// Monadic
#include <monadic.hpp>

using namespace monadic;
using namespace std;
//using namespace boost::threadpool;

int main ( int argc, char** argv )
{
    //Image img;
/*
    Image* img = CREATE_OBJECT(Image);
    img->create( 1600, 1200, 8, 3 );
    //img->popo();
    cout << "img - " << img->getTypeName() << endl;


    int niter = 1000;
    double tot = 0.0;
    for( int k = 0; k < niter; ++k )
    {
        std::vector< unsigned char > data;
        boost::timer t;
        img->serialize( data );
        tot += t.elapsed();
        Image* img2 = CREATE_OBJECT(Image);
        img2->deserialize( data );

        //cout << setprecision(6) << (double)(t.elapsed()*1000.0) << endl;
        delete img2;
    }
    cout << "tot=" << setprecision(6) << tot / (double)niter << endl;

    return 0;
*/

    Node* n;

    Application app( argv[1] );
    //vector< Node* > nodes;
    
    /*
    if( ! NodeManager::getInstance()->loadFromDirectory( argv[1] ) )
        return -1;
    */

    //app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    //app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    //app._nodes.push_back( NodeManager::getInstance()->create( "Foo" ) );
    /*
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
    */
    //app._nodes.push_back( NodeManager::getInstance()->create( "VideoInput" ) );
    //Node* popo =  NodeManager::getInstance()->create( "Foo" );
    //popo->setPriority( 1 );
    //app._nodes.push_back( popo );
    
    /*
    for( int k = 0; k < app._nodes.size(); ++k )
        app._nodes[k]->setup();
    */

    /*
    app.addNode( "VideoInput" );
    app.addNode( "VideoInput" );
    app.addNode( "VideoInput" );
    app.addNode( "VideoInput" );
    app.addNode( "VideoInput" );
    app.addNode( "VideoInput" );
    app.addNode( "VideoInput" );
    app.addNode( "VideoInput" );
    app.addNode( "VideoInput" );
    */
    app.addNode( "Foo" );
    app.addNode( "Foo" );
    app.addNode( "Foo" );
    app.addNode( "Foo" );
    app.addNode( "Foo" );
    app.addNode( "Foo" );
    app.addNode( "Foo" );
    app.addNode( "Foo" );
    app.addNode( "Foo" );
    app.addNode( "Foo" );
    app.addNode( "Foo" );
    app.addNode( "Foo" );
    app.addNode( "Foo" );
    app.addNode( "Foo" );
    app.addNode( "Foo" );
    app.addNode( "Foo" );
    app.addNode( "Foo" );
    app.addNode( "Foo" );

    app.start();
	
    while(1)
    {
        cout << "t=" << app.getElapsedTime() << endl;
        for( int k = 0; k < app._nodes.size(); ++k )
        {
            cout    << "NODE " << (unsigned long)app._nodes[k] << " - " 
                    << app._nodes[k]->getKernelName() << " state: " << app._nodes[k]->getState()
                    << endl;
        }
        cout << endl;
        #ifdef __WINDOWS__
        Sleep(1000);
        #else
        sleep(1);
        #endif
    }

    cout << "CHIPS" << endl;
    
    return 0;
}
