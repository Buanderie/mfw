#include <cassert>
#include <iostream>

#include <cstdlib>

#include <monadic.hpp>
#include <objects/base/number.hpp>
#include <objects/base/string.hpp>

#include <boost/thread.hpp>

using namespace std;

monadic::Link* lnk;

void producer()
{
  int i = 0;
  for (;;)
  {
      //sleep(1);
      //std::cout << "producer" << std::endl;
      monadic::String n("i++");
      monadic::ObjectBlob* blob = n.serialize();
      lnk->write(blob);
      delete blob;
  }
}

void consumer()
{
  for (;;)
  {
    //sleep(1);
    //std::cout << "consumer" << std::endl;
    monadic::String n2;
    monadic::ObjectBlob* blob2 = lnk->read();
    if( blob2 != 0 )
    {
    n2.deserialize( blob2 );
    cout << n2.getTypeName() << " " << n2.getValue() << endl;
    delete blob2;
    }
  }
}

int main() {

    /*
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
    */

    lnk = new monadic::Link( 0, 0, 1024, monadic::Link::NODE_LINK_BLOCKING );



    boost::thread t(producer);
    boost::thread t2(consumer);

    t.join();

    return 0;
}
