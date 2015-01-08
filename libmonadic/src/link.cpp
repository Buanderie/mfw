
// STL
#include <sstream>

// INTERNAL
#include "link.hpp"
#include "pin.hpp"
#include "node.hpp"

using namespace std;
using namespace monadic;

monadic::Link::Link(Pin *pin1, Pin *pin2, std::size_t bandwidth, monadic::Link::LinkMode mode )
    :_p1(pin1)
    ,_p2(pin2)
    ,_bandwidth(bandwidth)
    ,_mode(mode)
    ,_buffer(0)
{
    monadic::BipBuffer::BipBufferStrategy strategy;
    switch( _mode )
    {
    case Link::NODE_LINK_BLOCKING:
        strategy = BipBuffer::BIPBUFFER_SKIP;
        break;

    case Link::NODE_LINK_NONBLOCKING:
        strategy = BipBuffer::BIPBUFFER_OVERWRITE;
        break;

    default:
        strategy = BipBuffer::BIPBUFFER_OVERWRITE;
        break;
    }
    _buffer = new monadic::BipBuffer( _bandwidth, strategy );
    _p1->addLink( this );
    _p2->addLink( this );

}

monadic::Link::~Link()
{
    // disconnect from pins
    if( _p1 )
        _p1->removeLink( this );

    if( _p2 )
        _p2->removeLink( this );

    if( _buffer )
        delete _buffer;
}

void monadic::Link::write(monadic::ObjectBlob *blob)
{
    _linkMtx.lock();
    //cout << "before pushing" << endl;
    bool ret = _buffer->push( blob->data(), blob->data_size() );
    //cout << "ret=" << ret << endl;
    if( _mode == Link::NODE_LINK_BLOCKING )
    {
        while( ret == false )
        {
            _linkWriteCnd.wait( _linkMtx );
            ret = _buffer->push( blob->data(), blob->data_size() );
        }

        {
            _linkReadCnd.signal();
        }
    }
    _linkMtx.unlock();
}

monadic::ObjectBlob *monadic::Link::read()
{
    ObjectBlob* blob = 0;
    _linkMtx.lock();
    switch( _mode )
    {
    case Link::NODE_LINK_BLOCKING:
    {
        while( _buffer->blobs() == 0 )
        {
            _linkReadCnd.wait( _linkMtx );
        }
        size_t blobSize = _buffer->peekSize();
        unsigned char* blobTmp = new unsigned char[ blobSize + 1 ];
        _buffer->pop( blobTmp );
        blob = new ObjectBlob( blobTmp, blobSize );
        delete[] blobTmp;
        _linkWriteCnd.signal();
        break;
    }

    case Link::NODE_LINK_NONBLOCKING:
    {
        if( _buffer->blobs() == 0 )
            break;
        else
        {
            // Extract blob data
            size_t blobSize = _buffer->peekSize();
            unsigned char* blobTmp = new unsigned char[ blobSize ];
            _buffer->pop( blobTmp );
            blob = new ObjectBlob( blobTmp, blobSize );
            delete[] blobTmp;
        }
        break;
    }
    }
    _linkMtx.unlock();
    return blob;
}

size_t Link::occupation()
{
    size_t ret = 0;
    _linkMtx.lock();
    ret = _buffer->size();
    _linkMtx.unlock();
    return ret;
}

bool Link::hasData()
{
    bool ret = false;
    _linkMtx.lock();
    ret = (_buffer->size() != 0 );
    _linkMtx.unlock();
    return ret;
}

size_t Link::freeSpace()
{
    size_t ret = 0;
    _linkMtx.lock();
    ret = ( _buffer->capacity() - _buffer->size() );
    _linkMtx.unlock();
    return ret;
}

picojson::object Link::toJSON()
{
    picojson::object ret;

    ret["guid"] = picojson::value( this->getGuid().toString() );
    ret["mode"] = picojson::value( (float)(this->_mode) );
    ret["bandwidth"] = picojson::value( (float)this->_bandwidth );

    ret["startnode"] = picojson::value( this->_p1->getParent()->getGuid().toString() );
    ret["endnode"] = picojson::value( this->_p2->getParent()->getGuid().toString() );

    ret["startpin"] = picojson::value( this->_p1->getLabel() );
    ret["endpin"] = picojson::value( this->_p2->getLabel() );

    return ret;
}
