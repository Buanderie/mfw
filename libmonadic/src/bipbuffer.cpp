
// C
#include <cstdlib>

// INTERNAL
#include "bipbuffer.hpp"

monadic::BipBuffer::BipBuffer(size_t bufferSize)
    :_bufferSize(bufferSize), _start(0), _end(0)
{
    _data = 0;
    if( _bufferSize )
        _data = (unsigned char*)(malloc(_bufferSize));
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
    return _blobs.size();
}

bool monadic::BipBuffer::push(void *data, size_t length)
{

	// Check if we have any fucking blobs in here
	if( !_blobs.size() )
	{
	
	}

    // check if we have enough space left at the end
    
    if( _end + length > _bufferSize )
    {
        // not enough space
        // what should we do ? :'(
    }
    else
    {
        // enough space at the end
        
    }
}

size_t monadic::BipBuffer::peekSize()
{
    if( size() )
    {
        //return *(_blobSizes.end());
    }
    else
        return 0;
}

bool monadic::BipBuffer::pop(void *dst)
{
    if( size() )
    {
        //memcpy the shit out of the last blob
        return true;
    }
    else
    {
        //do nothing and get over it
        return false;
    }
}
