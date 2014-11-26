
// INTERNAL
#include "pin.hpp"

using namespace monadic;

monadic::Pin::Pin( const std::string& name, monadic::Pin::PinMode mode )
    :_name(name), _mode(mode)
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
        return false;
    }
    else if( _mode == Pin::NODE_OUTPUT_PIN )
    {
        for( size_t k = 0; _links.size(); ++k )
        {
            Link* l = _links[k];
            l->write( blob );
        }
        return true;
    }
    else
        return false;
}

// Cannot read from output pin
std::vector< monadic::ObjectBlob * > monadic::Pin::read()
{
    std::vector< ObjectBlob* > res;
    if( _mode == Pin::NODE_INPUT_PIN )
    {
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
        // Error management
    }
    return res;
}
