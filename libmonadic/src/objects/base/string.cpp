
// INTERNAL
#include "objects/base/string.hpp"




monadic::String::String()
    :Object("String")
{
}

monadic::String::String(const monadic::String &other)
    :Object("String")
{
}

monadic::String::~String()
{
}

monadic::ObjectBlob *monadic::String::serialize()
{
}

void monadic::String::deserialize(monadic::ObjectBlob *blob)
{

}
