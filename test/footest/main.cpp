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


    //Node* n1 = app.addNode("Number");
    //Node* n2 = app.addNode("Number");
    //Node* n3 = app.addNode("Add");

	Node* n4 = app.addNode("VideoInput");
	Node* n6 = app.addNode("VideoDisplay");
	Node* n7 = app.addNode("Blur");
	Node* n8 = app.addNode("Sobel");
    Node* n9 = app.addNode("FastDetector");
    //Node* n10 = app.addNode("VideoDisplay");

    //Pin* p1 = n1->findPinFromLabel("out");
    //Pin* p2 = n2->findPinFromLabel("out");
    //Pin* p3 = n3->findPinFromLabel("in1");
    //Pin* p4 = n3->findPinFromLabel("in2");

	Pin* p5 = n4->findPinFromLabel("out");
	Pin* p6 = n6->findPinFromLabel("in");
	Pin* p7 = n7->findPinFromLabel("out");
	Pin* p8 = n7->findPinFromLabel("in");

    //app.addLink(p1, p3, 1500000, Link::NODE_LINK_NONBLOCKING);
    //app.addLink(p2, p4, 1500000, Link::NODE_LINK_NONBLOCKING);
    app.addLink(p5, p6, 6500000, Link::NODE_LINK_BLOCKING);
    //app.addLink( p7, p6, 6500000, Link::NODE_LINK_NONBLOCKING );

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
    //

    app.save("popo.app");
    //app.load("popo.app");
    //app.enableAllNodes();
    //app.save("popo.app");

    app.start();
    //return 0;

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
		cout << "nian nian" << endl;

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
