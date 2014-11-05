// STL
#include <iostream>
#include <iomanip>
#include <vector>

// Monadic
#include <monadic.hpp>
#include <objects/image/image.hpp>

using namespace monadic;
using namespace monadic::filesystem;
using namespace std;

int main ( int argc, char** argv )
{
    /*
    ObjectBlob blob("pol");
    for( int i = 0; i < 10; ++i )
        blob.push<double>(i);

    for( int i = 0; i < 10; ++i )
        cout << blob.pop<double>() << endl;
    */


    Image* img1 = new Image();
    img1->create( 1600, 1200, 8, 3 );
    unsigned int N = 10000;
    Timer t;
    t.start();
    for( int k = 0; k < N; ++k )
    {
        Image* img2 = new Image();
        ObjectBlob* blob = img1->serialize();
        img2->deserialize(blob);
        delete img2;
        delete blob;
    }
    t.stop();
    double tt = t.getElapsedTimeInSec() / (double)N;
    cout << t.getElapsedTimeInMilliSec() << endl;
    cout << (double)(1600 * 1200 * 3)/(tt) << "B/s" << endl;

    return 0;
}
