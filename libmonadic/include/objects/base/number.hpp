#ifndef __NUMBER_HPP__
#define __NUMBER_HPP__

#include "object.hpp"

namespace monadic
{
    class Number : public Object
    {
    public:
        Number();
        Number( const monadic::Number& other );
        virtual ~Number();

        virtual ObjectBlob* serialize();
        virtual void deserialize(ObjectBlob *blob);

    private:
        // Numbers are IEEE-754 double precision floating point numbers
        double _value;

    protected:

    };
}

#endif
