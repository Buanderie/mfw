

// INTERNAL
#include "node.hpp"
#include "applicationworker.hpp"

namespace monadic
{
		bool ApplicationWorker::run()
		{
			int i = 0;
			while( 1 )
			{
				Node* n = _app->fetchActiveNode();
				double startTime = _app->getElapsedTime();
				n->tick( startTime );
				_app->releaseNode(n);
			}
			return true;
		}
}
