
// C
#include <cstdlib>

// INTERNAL
#include "hostmemoryblock.hpp"

namespace monadic
{
    HostMemoryBlock::HostMemoryBlock( unsigned int size )
    {
        _size = size;
#ifdef __WITH_CUDA__
        cudaMallocHost( (void**)(&_data), _size )
#else
        _data = malloc( _size );
#endif
    }

    HostMemoryBlock::~HostMemoryBlock()
    {
#if __WITH_CUDA__
        cudaFreeHost( _data );
#else
        free( _data );
#endif
    }
}
