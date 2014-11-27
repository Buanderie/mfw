#ifndef __OBJECTBLOB_HPP__
#define __OBJECTBLOB_HPP__

// STL
#include <string>

namespace monadic
{
    class ObjectBlob
    {
        const static int OBJECT_BLOB_NAME_LENGTH = 256;

    public:
        ObjectBlob( const std::string& typeName, const size_t blobSize = 0 );
        ObjectBlob( void* ptr, std::size_t size );

        virtual ~ObjectBlob();
        void* data();
        std::size_t data_size();
        void reserve( const size_t size );

        template<class T> void push( const T& elem )
        {
            if( sizeof(T) + _pushedSize >= _blobSize )
                reserve( sizeof(T) + _blobSize );
            T* tPtr = (T*)(_data + OBJECT_BLOB_NAME_LENGTH + _pushedSize );
            tPtr[0] = elem;
            _pushedSize += sizeof(T);
        }

        template<class T> T pop()
        {
            T* tPtr = (T*)(_data + OBJECT_BLOB_NAME_LENGTH + _poppedSize );
            T ret = tPtr[0];
            _poppedSize += sizeof(T);
            return ret;
        }

        void pushArray( void* ptr, size_t size );
        void popArray(void* ptr, size_t size);

        std::string getTypeName();

    private:
        std::string     _typeName;
        size_t          _blobSize;
        unsigned char*  _data;
        size_t          _pushedSize;
        size_t          _poppedSize;

        void markObjectName();

    protected:

    };
}

#endif // OBJECTBLOB_HPP
