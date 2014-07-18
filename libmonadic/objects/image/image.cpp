// C

// STL
#include <iostream>

// MSGPACK
#include <msgpack.hpp>

// INTERNAL
#include "image.hpp"

using namespace std;

monadic::Image::Image()
{
    _width = 0;
    _height = 0;
    _depth = 0;
    _channels = 0;
    _rawBuffer = 0;
}

monadic::Image::~Image()
{
    if( _rawBuffer )
        delete[] _rawBuffer;
}

void monadic::Image::deserialize( std::vector< unsigned char >& dataBuffer )
{
    monadic::Object::deserialize( dataBuffer );

    // Object retrieves its type
    msgpack::unpacker pac;

    // feeds the buffer.
    pac.reserve_buffer(dataBuffer.size());
    memcpy(pac.buffer(), &(dataBuffer[0]), dataBuffer.size());
    pac.buffer_consumed(dataBuffer.size());

    msgpack::unpacked result;
    while(pac.next(&result))
    {
        std::cout << result.get() << std::endl;
    }
}

void monadic::Image::serialize( std::vector< unsigned char >& dataBuffer )
{
    monadic::Object::serialize( dataBuffer );
    msgpack::sbuffer sbuf;
    msgpack::packer<msgpack::sbuffer> packer(&sbuf);
    packer.pack( _width );
    packer.pack( _height );
    packer.pack( _depth );
    packer.pack( _channels );
    const unsigned int rawBufferSize = _width * _height * _channels * (_depth/8);
    packer.pack_raw( rawBufferSize );
    packer.pack_raw_body( (const char*)_rawBuffer, rawBufferSize );

    // memcpy at the end of dataBuffer
    int oldSize = dataBuffer.size();
    dataBuffer.resize( oldSize + rawBufferSize );
    memcpy( &(dataBuffer[0 + oldSize]), sbuf.data(), rawBufferSize );
}

int monadic::Image::create(unsigned int width, unsigned int height, unsigned int depth, unsigned int channels)
{
    _width = width;
    _height = height;
    _depth = depth;
    _channels = channels;
    const unsigned int memsz = _width * _height * (_depth/8) * _channels;
    _rawBuffer = new unsigned char[ memsz ];
    return 0;
}

