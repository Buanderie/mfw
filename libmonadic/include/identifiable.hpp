#ifndef __IDENTIFIABLE_HPP__
#define __IDENTIFIABLE_HPP__

#include "guid.hpp"

namespace monadic
{
	class Identifiable
	{
		public:
			Identifiable(){}
			virtual ~Identifiable(){}
			
			monadic::Guid getGuid()
			{
				return _guid;
			}

			void resetGuid()
			{
				monadic::GuidGenerator gen;
				_guid = gen.newGuid();
			}

		protected:
			monadic::Guid _guid;
			
	};
}

#endif
