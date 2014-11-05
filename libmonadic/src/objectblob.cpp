
// C
#include <cstdlib>
#include <cstring>

// INTERNAL
#include "objectblob.hpp"

monadic::ObjectBlob::ObjectBlob(const std::string &typeName, const size_t blobSize)
    :_typeName(typeName), _blobSize(blobSize)
{
    _data = 0;
    reserve( _blobSize );
    markObjectName();
    _pushedSize = 0;
    _poppedSize = 0;
}

monadic::ObjectBlob::~ObjectBlob()
{
    free(_data);
}

void *monadic::ObjectBlob::data()
{
    //return (void*)(_data + monadic::ObjectBlob::OBJECT_BLOB_NAME_LENGTH);
    return (void*)(_data);
}


void monadic::ObjectBlob::reserve(const size_t size)
{
    _data = (unsigned char*)realloc( (void*)_data, monadic::ObjectBlob::OBJECT_BLOB_NAME_LENGTH + size );
    _blobSize = size;
}

void monadic::ObjectBlob::pushArray(void *ptr, size_t size)
{
    if( size + _pushedSize >= _blobSize )
        reserve( size + _blobSize );

    unsigned char* dPtr = (_data + OBJECT_BLOB_NAME_LENGTH + _pushedSize );
    memcpy( dPtr, ptr, size );
}

void monadic::ObjectBlob::popArray(void *ptr, size_t size )
{
    unsigned char* dPtr = (_data + OBJECT_BLOB_NAME_LENGTH + _poppedSize );
    memcpy( dPtr, ptr, size );
}


void monadic::ObjectBlob::markObjectName()
{
    _data[0] = _typeName.size();
    memcpy( _data + 1, (void*)(_typeName.c_str()), _typeName.size() );
}
