#include <cassert>
#include <iostream>

#include <cstdlib>

#include <monadic.hpp>

using namespace std;

int main() {

    srand(time(NULL));

    for( int i = 0; i < 10000000; ++i )
    {
        cout << "PUSH " << i << endl;
        size_t N = 100;
        size_t MAXLEN = 1600*1200*3*10;
        monadic::BipBuffer b(MAXLEN, monadic::BipBuffer::BIPBUFFER_OVERWRITE );
        for( int k = 1; k <= N; ++k )
        {
            size_t blobSize = 1600*1200*3;
            unsigned char* data = new unsigned char[blobSize];
            b.push( data, blobSize );
            delete data;
            cout << "blobSize=" << blobSize << " - b.size()=" << b.size() << endl;
        }

        cout << "POP " << i << endl;
        size_t totalSize = 0;
        while( 1 )
        {
            if( b.size() <= 0 )
                break;

            size_t blobSize = b.peekSize();
            totalSize += blobSize;
            cout << "b.size=" << b.size() << " - peekSize=" << blobSize << endl;
            unsigned char* data = new unsigned char[blobSize];
            if( !b.pop(data) )
                cout << "pop xcouille" << endl;
            delete[] data;
        }
        cout << "total=" << totalSize << endl;
    }
    return 0;
}
