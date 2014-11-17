
// C
#include <cstdlib>
#include <cstring>

// STL
#include <iostream>

// INTERNAL
#include "bipbuffer.hpp"

using namespace std;

monadic::BipBuffer::BipBuffer(size_t capacity, BipBufferStrategy strategy)
    :_capacity(capacity)
    ,_size(0)
    ,_beg_index(0)
    ,_end_index(0)
    ,_strategy(strategy)
{
    _data = 0;
    if( _capacity )
        _data = (unsigned char*)(malloc(_capacity));
}

monadic::BipBuffer::~BipBuffer()
{
    if( _data )
        free((void*)_data);
}

void monadic::BipBuffer::resize(size_t size)
{
    // realloc somehow... careful about that
}

size_t monadic::BipBuffer::size()
{
    return _size;
}

size_t monadic::BipBuffer::blobs()
{
    return _blobs.size();
}

bool monadic::BipBuffer::push( const void *data, size_t length)
{
    if( length >= _capacity )
        return false;

    // This code assumes read and write are working
    if( length >= ( _capacity - _size ) )
    {
        switch( _strategy )
        {
            case BIPBUFFER_OVERWRITE:
            {
                //cout << "fuck it's full" << endl;
                while( (_capacity - _size) < length )
                {
                    read(NULL, peekSize(), false);
                    _blobs.erase( _blobs.begin() + 0 );
                }
                write( (const unsigned char*)data, length );
                _blobs.push_back( length );
                break;
            }

            case BIPBUFFER_SKIP:
            {
                return false;
                break;
            }

        default:
            break;
        }

        return false;
    }
    else
    {
        _blobs.push_back( length );
        write( (const unsigned char*)data, length );
        return true;
    }

    return false;

}

size_t monadic::BipBuffer::peekSize()
{
    if( size() != 0 )
    {
        return _blobs[ 0 ];
    }
    else
        return 0;
}

bool monadic::BipBuffer::pop( const void *dst )
{
    // If there is a blob in the buffer
    if( size() != 0 )
    {
        size_t blobSize = peekSize();
        read( (const unsigned char*)dst, blobSize, true );
        _blobs.erase( _blobs.begin() + 0 );
        return true;
    }
    else
    {
        //do nothing and get over it
        return false;
    }
}

size_t monadic::BipBuffer::write(const unsigned char *data, size_t bytes)
{
    if( !_data )
        return 0;

    size_t capacity = _capacity;
    size_t bytes_to_write = std::min(bytes, capacity - _size );

    // Write in single step
    if( bytes_to_write <= capacity - _end_index )
    {
        memcpy( _data + _end_index, data, bytes_to_write );
        _end_index += bytes_to_write;
        if( _end_index == _capacity )
            _end_index = 0;
    }
    // Write in two steps
    else
    {
        size_t size_1 = _capacity - _end_index;
        memcpy( _data + _end_index, data, size_1 );
        size_t size_2 = bytes_to_write - size_1;
        memcpy( _data, data+size_1, size_2 );
        _end_index = size_2;
    }

    _size += bytes_to_write;

    return bytes_to_write;
}

size_t monadic::BipBuffer::read(const unsigned char *data, size_t bytes, bool executeOperation )
{
    if( executeOperation && !_data )
        return 0;

    size_t capacity = _capacity;
    size_t bytes_to_read = std::min(bytes, _size);

    // Read in a single step
    if( bytes_to_read <= capacity - _beg_index )
    {
        if( executeOperation )
            memcpy( (void*)data, (const void*)(_data + _beg_index), bytes_to_read );
        _beg_index += bytes_to_read;
        if( _beg_index == _capacity )
            _beg_index = 0;
    }
    // Read in two steps
    else
    {
        size_t size_1 = capacity - _beg_index;
        if( executeOperation )
            memcpy( (void*)data, (const void*)(_data + _beg_index), size_1 );
        size_t size_2 = bytes_to_read - size_1;
        if( executeOperation )
            memcpy( (void*)(data + size_1), (const void*)_data, size_2 );
        _beg_index = size_2;
    }

    _size -= bytes_to_read;
    return bytes_to_read;
}
