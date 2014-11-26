
// INTERNAL
#include "link.hpp"

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
}

monadic::Link::~Link()
{
    if( _buffer )
        delete _buffer;
}

void monadic::Link::write(monadic::ObjectBlob *blob)
{
    _linkMtx.lock();

    bool ret = _buffer->push( blob->data(), blob->data_size() );

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
        unsigned char* blobTmp = new unsigned char[ blobSize ];
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
