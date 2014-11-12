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
        typedef struct
        {
            size_t start;
            size_t stop;
            size_t size;
        } BipBufferElem;

    public:
        BipBuffer( size_t bufferSize = 0 );
        virtual ~BipBuffer();
        void resize( size_t size );
        size_t size();

        bool push( void* data, size_t length );
        size_t peekSize();
        bool pop( void* dst );

    private:
        size_t                          _bufferSize;
        unsigned char *                 _data;
        std::vector< BipBufferElem >    _blobs;

    protected:

    };
}

#endif
