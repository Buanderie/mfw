#ifndef __MEMORYBLOCK_HPP__
#define __MEMORYBLOCK_HPP__

namespace monadic
{
    class MemoryBlock
    {
    public:
        void* ptr(){ return _data; };
        unsigned int size(){ return _size; };

        virtual ~MemoryBlock();
    
    protected:
        void *          _data;
        unsigned int    _size;
    };
}

#endif
