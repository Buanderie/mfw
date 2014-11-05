#ifndef __STRING_HPP__
#define __STRING_HPP__

// STL
#include <string>

// INTERNAL
#include "object.hpp"

namespace monadic
{
    class String : public Object
    {
    public:
        String();
        String( const monadic::String& other );
        virtual ~String();

        virtual ObjectBlob * serialize();
        virtual void deserialize(ObjectBlob *blob);

    private:
        std::string _value;

    protected:

    };
}
#endif
