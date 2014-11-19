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
        String( const std::string& rawString = "" );
        String( const monadic::String& other );
        virtual ~String();

        std::string getValue(){ return _value; }

        virtual ObjectBlob * serialize();
        virtual void deserialize(ObjectBlob *blob);

    private:
        std::string _value;

    protected:

    };
}
#endif
