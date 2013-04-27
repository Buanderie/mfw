#ifndef __MEMORYCHUNK_HPP__
#define __MEMORYCHUNK_HPP__

namespace monadic
{
    class MemoryChunk
    {
    public:
        void* ptr(){ return _data; };
        unsigned int size(){ return _size; };

        virtual ~MemoryChunk();
    
    protected:
        void *          _data;
        unsigned int    _size;
    };
}

#endif
