#include "add.hpp"

#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

#include <objects/base/number.hpp>
#include <objects/image/image.hpp>


using namespace std;
using namespace monadic;

MONADIC_NODE_EXPORT( AddNode, "Add" )

    AddNode::AddNode()
    {
        _kernelName = "Add";
        this->addPin( "in1", Pin::NODE_INPUT_PIN );
        this->addPin( "in2", Pin::NODE_INPUT_PIN );
        this->addPin( "out", Pin::NODE_OUTPUT_PIN );
    }

    AddNode::~AddNode()
    {
        //std::cout << "Number::DTOR" << std::endl;
    }

    void AddNode::setup()
    {
        //cout << " SETUP SETUP SETUP " << endl;
        //std::cout << "FooNode::setup()" << std::endl;
        //_cpt = 0;
        //pol.open("foo.txt");
        //srand( time(NULL) );
        //sleep(1);
        //limit = 100;
        //cout << "limit=" << limit << endl;
    }

    void AddNode::tick( double dt )
    {
        Timer t;
        t.start();
        std::vector<ObjectBlob*> b;
        for( int k = 0; k < _pins.size(); ++k )
        {

        	if( _pins[k]->getLabel() == "in1" )
        	{
        		b = _pins[k]->read();
        		if( b.size() > 0 && b[0]->getTypeName() == "Number" )
        			n1.deserialize( b[0] );
        		for( int i = 0; i < b.size(); ++i )
        		{
        			delete b[i];
        		}
        	}
        	else if( _pins[k]->getLabel() == "in2" )
        	{
        		b = _pins[k]->read();
        		if( b.size() > 0 && b[0]->getTypeName() == "Number" )
        			n2.deserialize( b[0] );
        		for( int i = 0; i < b.size(); ++i )
        		{
        			delete b[i];
        		}
        	}
        	else if( _pins[k]->getLabel() == "out" )
        	{
        		out = monadic::Number( n1.getValue() + n2.getValue() );
        		ObjectBlob* blob = out.serialize();
        		_pins[k]->write( blob );
        		cout << out.getValue() << endl;
        		delete blob;
        	}

        }
        t.stop();
        //cout << "t=" << t.getElapsedTimeInSec() << " - fps=" << 1.0 / t.getElapsedTimeInSec() << endl;
    }
