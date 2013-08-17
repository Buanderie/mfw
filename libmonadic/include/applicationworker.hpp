#ifndef __APPLICATIONWORKER_HPP__
#define __APPLICATIONWORKER_HPP__

// INTERNAL
#include "application.hpp"
#include "thread.hpp"

// STL
#include <iostream>

using namespace std;

namespace monadic
{
	class ApplicationWorker : public monadic::Thread
	{
	public:
		ApplicationWorker( monadic::Application* app )
		:_app(app)
		{

		}

		virtual bool run();

	private:
		Application* _app;

	};
}

#endif//__APPLICATIONWORKER_HPP__