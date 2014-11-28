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

    Node* n1 = app.addNode( "Foo" );
    Node* n5 = app.addNode( "Foo" );
    Node* n2 = app.addNode( "Bar" );
    Node* n3 = app.addNode( "Bar" );
    Node* n4 = app.addNode( "Bar" );
    Pin* p1  = n1->addPin( "bite", Pin::NODE_OUTPUT_PIN );
    Pin* p5  = n5->addPin( "bite", Pin::NODE_OUTPUT_PIN );
    Pin* p2 = n2->addPin( "cul", Pin::NODE_INPUT_PIN );
    Pin* p3 = n3->addPin( "cul", Pin::NODE_INPUT_PIN );
    Pin* p4 = n4->addPin( "cul", Pin::NODE_INPUT_PIN );
    app.addLink( p1, p2, 100000000, Link::NODE_LINK_BLOCKING );
    app.addLink( p1, p3, 100000000, Link::NODE_LINK_BLOCKING );
    app.addLink( p5, p4, 100000000, Link::NODE_LINK_BLOCKING );
    /*
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
    */

    app.enableAllNodes();
    //app.start();
    app.start();
    while(1)
    {
        cout << "t=" << app.getElapsedTime() << endl;

        vector< monadic::Node* > nodes = app.getNodes();
        for( int k = 0; k < nodes.size(); ++k )
        {

            cout    << "NODE " << nodes[k]->getGuid() << " - "
                    << nodes[k]->getKernelName() << " state: " << nodes[k]->getState()
                    << endl;

        }

        cout << endl;
        #ifdef __WINDOWS__
        Sleep(1000);
        #else
        usleep(1000000);
        #endif


    }

    cout << "CHIPS" << endl;
    
    return 0;
}
