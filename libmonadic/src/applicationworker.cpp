

// INTERNAL
#include "node.hpp"
#include "applicationworker.hpp"

namespace monadic
{
		bool ApplicationWorker::run()
		{
            //cout << "loulou" << endl;
			while( 1 )
			{
                cout << "Fetching new node" << endl;
                Node* n = _app->fetchActiveNode();
                //  cout << "##### n=" << (unsigned int)(n) << endl;
                //double startTime = _app->getElapsedTime();
                n->tick( 0.0 );
                //sleep(1);

                if( n != NULL )
                {
                    _app->releaseNode(n);
                }




			}
			return true;
		}
}
