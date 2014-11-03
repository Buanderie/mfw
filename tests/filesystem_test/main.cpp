// STL
#include <iostream>
#include <iomanip>
#include <vector>

// Monadic
#include <monadic.hpp>

using namespace monadic;
using namespace monadic::filesystem;
using namespace std;

int main ( int argc, char** argv )
{
    monadic::filesystem::Path p(argv[1]);
    std::vector< Path > f = p.getChildren(true);
    for( int k = 0; k < f.size(); ++k )
    {
        if( !f[k].isDirectory() )
            cout << f[k].str() << endl;
            cout << f[k].extension() << endl;
    }

    return 0;
}
