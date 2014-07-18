

// C

// STL
#include <vector>

// MSGPACK
#include <msgpack.hpp>

// INTERNAL
#include "object.hpp"

using namespace std;

void monadic::Object::deserialize( std::vector< unsigned char >& dataBuffer )
{
    // Object retrieves its type
    msgpack::unpacker pac;

    // feeds the buffer.
    pac.reserve_buffer(dataBuffer.size());
    memcpy(pac.buffer(), &(dataBuffer[0]), dataBuffer.size());
    pac.buffer_consumed(dataBuffer.size());

    msgpack::unpacked result;

    unsigned int origSize = pac.message_size();

    pac.next(&result);
    std::string strres;
    msgpack::object obj = result.get();
    //cout << obj << endl;
    obj.convert( &strres );
    _typeName = strres;

    unsigned finalSize = pac.message_size();
    unsigned extractedSize = origSize - finalSize;
    cout << "finalSize=" << finalSize << endl;
    dataBuffer.erase( dataBuffer.begin(), dataBuffer.begin() + extractedSize );
}

void monadic::Object::serialize( std::vector< unsigned char >& dataBuffer )
{
    msgpack::sbuffer sbuf;
    msgpack::pack( sbuf, _typeName );
    for( int k = 0; k < sbuf.size(); ++k )
    {
        dataBuffer.push_back( (unsigned char)(sbuf.data()[k]));
    }
}
