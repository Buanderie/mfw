
// STL
#include <iostream>

// BOOST
#include <boost/thread.hpp>

// INTERNAL
#include "application.hpp"

using namespace std;

namespace monadic
{
    void Application::init()
    {
        int ncore = boost::thread::hardware_concurrency();
        cout << "pitaing " << ncore << " cores !" << endl;
        _appThreadPool = boost::threadpool::prio_pool( boost::thread::hardware_concurrency() - 1 );
    }
}
