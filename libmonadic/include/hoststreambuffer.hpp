#ifndef __HOSTSTREAMBUFFER_HPP__
#define __HOSTSTREAMBUFFER_HPP__



// INCLUDE
#include "streambuffer.hpp"

namespace monadic
{

    class HostStreamBuffer : public StreamBuffer
    {
        public:
            HostStreamBuffer();
            virtual ~HostStreamBuffer();
    
        protected:

        private:

    };

}
#endif
