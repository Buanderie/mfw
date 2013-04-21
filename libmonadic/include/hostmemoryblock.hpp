#ifndef __HOSTMEMORYBLOCK_HPP__
#define __HOSTMEMORYBLOCK_HPP__

#include "memoryblock.hpp"

namespace monadic
{
    class HostMemoryBlock : public MemoryBlock
    {
    public:
        HostMemoryBlock( unsigned int size = 1024);
        virtual ~HostMemoryBlock();
    };
}

#endif
