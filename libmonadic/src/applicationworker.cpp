

// INTERNAL
#include "node.hpp"
#include "applicationworker.hpp"

namespace monadic
{
		bool ApplicationWorker::run()
		{
			int i = 0;
			while( ! mustStop() )
			{
				Node* n = _app->fetchActiveNode();
				n->tick( _app->getElapsedTime() );
				_app->releaseNode(n);
			}
			return true;
		}
}