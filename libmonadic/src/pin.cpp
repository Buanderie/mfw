
// OPENMP
#include <omp.h>

// INTERNAL
#include "pin.hpp"

using namespace monadic;

monadic::Pin::Pin(Node *parentNode, const std::string& name, monadic::Pin::PinMode mode )
    :_name(name), _mode(mode), _parent(parentNode)
{

}

monadic::Pin::~Pin()
{

}

// Cannot write to input pin
bool monadic::Pin::write(monadic::ObjectBlob *blob)
{
    if( this->_mode == Pin::NODE_INPUT_PIN )
    {
        cout << "ERROR: Cannot write to input pin" << endl;
        return false;
    }
    else if( _mode == Pin::NODE_OUTPUT_PIN )
    {
//#pragma omp parallel for
        for( size_t k = 0; k < _links.size(); ++k )
        {
            Link* l = _links[k];
            l->write( blob );
        }
        return true;
    }
    else
    {
        return false;
    }
}

// Cannot read from output pin
std::vector< monadic::ObjectBlob * > monadic::Pin::read()
{
    std::vector< ObjectBlob* > res;
    if( _mode == Pin::NODE_INPUT_PIN )
    {
//#pragma omp parallel for
        for( std::size_t k = 0; k < _links.size(); ++k )
        {
            Link* l = _links[k];
            ObjectBlob* b = l->read();
            if( b != 0 )
                res.push_back( b );
        }
    }
    else if( _mode == Pin::NODE_OUTPUT_PIN )
    {
        cout << "ERROR: Cannot read from output pin" << endl;
    }
    return res;
}

Node *Pin::getParent()
{
    return _parent;
}

void Pin::addLink(Link *l)
{
    _links.push_back( l );
}
