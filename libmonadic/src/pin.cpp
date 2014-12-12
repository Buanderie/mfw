
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
    bool ret = false;
    _mtx.lock();
    if( this->_mode == Pin::NODE_INPUT_PIN )
    {
        cout << "ERROR: Cannot write to input pin" << endl;
        ret = false;
    }
    else if( _mode == Pin::NODE_OUTPUT_PIN )
    {
        for( size_t k = 0; k < _links.size(); ++k )
        {
            Link* l = _links[k];
            if( l->freeSpace() > blob->data_size() )
                l->write( blob );
        }
        ret = true;
    }
    else
    {
        ret = false;
    }
    _mtx.unlock();
    return ret;
}

// Cannot read from output pin
std::vector< monadic::ObjectBlob * > monadic::Pin::read()
{
    std::vector< ObjectBlob* > res;
    _mtx.lock();
    if( _mode == Pin::NODE_INPUT_PIN )
    {
        //#pragma omp parallel for
        for( std::size_t k = 0; k < _links.size(); ++k )
        {
            Link* l = _links[k];
            if( l->hasData() )
            {
                ObjectBlob* b = l->read();
                if( b != 0 )
                    res.push_back( b );
            }
        }
    }
    else if( _mode == Pin::NODE_OUTPUT_PIN )
    {
        cout << "ERROR: Cannot read from output pin" << endl;
    }
    _mtx.unlock();
    return res;
}

Node *Pin::getParent()
{
    return _parent;
}

Pin::PinMode Pin::getMode()
{
    return _mode;
}

bool Pin::isConnected()
{
    bool ret = false;
    _mtx.lock();
    if( _links.size() > 0 )
        ret = true;
    _mtx.unlock();
    return ret;
}

void Pin::addLink(Link *l)
{
    _mtx.lock();
    _links.push_back( l );
    _mtx.unlock();
}

void Pin::removeLink(Link *link)
{
    _mtx.lock();
    for( int k = 0; k < _links.size(); ++k )
    {
        if( _links[k] == link )
        {
            //delete link;
            _links.erase( _links.begin() + k );
            break;
        }
    }
    _mtx.unlock();
}
