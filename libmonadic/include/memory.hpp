#ifndef __ALLOCATOR_HPP__
#define __ALLOCATOR_HPP__

// C
#include <cstddef>

namespace monadic
{
    class Allocator
    {
        public:
        virtual void* allocate( size_t size, size_t align ) = 0;
        virtual void deallocate( void* p ) = 0 ;
        virtual size_t allocated_size( void* p ) = 0;
    };

    class MallocAllocator;

}

#endif
