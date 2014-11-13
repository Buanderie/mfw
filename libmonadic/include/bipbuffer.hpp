#ifndef __CIRCULARBUFFER_HPP__
#define __CIRCULARBUFFER_HPP__

// C
#include <cstddef>

// STL
#include <vector>

namespace monadic
{
    class BipBuffer
    {
    public:
        BipBuffer(size_t capacity = 0 );
        virtual ~BipBuffer();
        void resize( size_t size );
        size_t size();

        bool push(const void *data, size_t length );
        size_t peekSize();
        bool pop( const void* dst );

    private:
        size_t                          _capacity;
        size_t                          _size;
        size_t                          _beg_index;
        size_t                          _end_index;

        unsigned char *                 _data;
        std::vector< size_t >           _blobs;

        size_t write( const unsigned char * data, size_t bytes );
        size_t read( const unsigned char * data, size_t bytes );

    protected:

    };
}

#endif
