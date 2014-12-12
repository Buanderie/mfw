#ifndef __CIRCULARBUFFER_HPP__
#define __CIRCULARBUFFER_HPP__

/*
 * http://www.asawicki.info/news_1468_circular_buffer_of_raw_binary_data_in_c.html
 */

// C
#include <cstddef>

// STL
#include <vector>

namespace monadic
{
    class BipBuffer
    {
    public:
        typedef enum
        {
            BIPBUFFER_SKIP=0,
            BIPBUFFER_OVERWRITE
        } BipBufferStrategy;

    public:
        BipBuffer(size_t capacity = 0, BipBufferStrategy strategy = BIPBUFFER_OVERWRITE );
        virtual ~BipBuffer();
        void resize( size_t size );
        size_t size();
        size_t capacity();
        size_t blobs();

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
        BipBufferStrategy               _strategy;

        size_t write( const unsigned char * data, size_t bytes );
        size_t read(const unsigned char * data, size_t bytes , bool executeOperation = true );

    protected:

    };
}

#endif
