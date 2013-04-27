#ifndef __HOSTMEMORYCHUNK_HPP__
#define __HOSTMEMORYCHUNK_HPP__

#include "memorychunk.hpp"

namespace monadic
{
    class HostMemoryChunk : public MemoryChunk
    {
    public:
        HostMemoryChunk( unsigned int size = 1024);
        virtual ~HostMemoryChunk();
    };
}

#endif
