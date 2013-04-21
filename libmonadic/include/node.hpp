#ifndef __NODE_HPP__
#define __NODE_HPP__

// BOOST
#include <boost/thread.hpp>

// INTERNAL

namespace monadic
{
    class Node
    {
    public:
        void start();
        void stop();
        void run();

        virtual void setup()=0;
        virtual void tick( double dTime )=0;

    private:
        boost::thread   _nodeThread;

    };
}
#endif
