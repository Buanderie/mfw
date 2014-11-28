#include <cassert>
#include <iostream>

#include <cstdlib>

#include <monadic.hpp>
#include <objects/base/number.hpp>
#include <objects/base/string.hpp>
#include <objects/image/image.hpp>

#include <boost/thread.hpp>


using namespace std;

monadic::Link* lnk;
monadic::Pin* p1;
monadic::Pin* p2;

void producer()
{
  int i = 0;
  for (;;)
  {
      monadic::Number n(12345.0);
      monadic::ObjectBlob* blob = n.serialize();
      p1->write(blob);
      delete blob;
  }
}

void consumer()
{
  for (;;)
  {
    //sleep(1);
    Timer t;
    t.start();
    vector< monadic::ObjectBlob* > blob2 = p2->read();
    if( blob2.size() != 0 )
    {
        monadic::Number n2;
        n2.deserialize( blob2[0] );
        for( int i = 0; i < blob2.size(); ++i )
            delete blob2[0];
        cout << "Number received : " << n2.getValue() << endl;
    }
    t.stop();
    double tt = t.getElapsedTimeInSec();
    cout << 1.0 / tt << " fps" << endl;
  }
}

int main() {


    srand(time(NULL));

    p1 = new monadic::Pin( "output", monadic::Pin::NODE_OUTPUT_PIN );
    p2 = new monadic::Pin( "input", monadic::Pin::NODE_INPUT_PIN );
    lnk = new monadic::Link( p1, p2, 1000457280, monadic::Link::NODE_LINK_NONBLOCKING );
    boost::thread t(producer);
    boost::thread t2(consumer);

    for(;;)
    {
        sleep(1);
        cout << "occupation: " << lnk->occupation() << endl;
    }

    return 0;
}
