#ifndef __JSONABLE_HPP__
#define __JSONABLE_HPP__

// JSON
#include "picojson.hpp"

namespace monadic
{
    class JSONable
    {
    public:
        JSONable(){}
        virtual ~JSONable(){}

        virtual picojson::object toJSON()=0;

    };
}

#endif // JSONABLE_HPP
