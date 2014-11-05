
// INTERNAL
#include "objects/base/number.hpp"

using namespace monadic;

monadic::Number::Number()
    :Object("Number")
{

}

monadic::ObjectBlob *monadic::Number::serialize()
{
    ObjectBlob* blob = new ObjectBlob(this->getTypeName(),0);
    blob->push<double>(_value);
    return blob;
}

void monadic::Number::deserialize(monadic::ObjectBlob *blob)
{
    _value = blob->pop<double>();
}

monadic::Number::Number(const monadic::Number &other)
    :Object("Number")
{
    _value = other._value;
}

Number::~Number()
{

}
