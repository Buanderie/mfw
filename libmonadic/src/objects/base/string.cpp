
// INTERNAL
#include "objects/base/string.hpp"


using namespace monadic;

monadic::String::String(const string &rawString)
    :Object("String")
{
    _value = rawString;
}

monadic::String::String(const monadic::String &other)
    :Object("String")
{
    _value = other._value;
}

monadic::String::~String()
{
}

monadic::ObjectBlob *monadic::String::serialize()
{
    ObjectBlob* blob = new ObjectBlob( _typeName );
    blob->push<size_t>( _value.size() );
    blob->pushArray( (void*)(_value.c_str()), _value.size() + 1 );
    return blob;
}

void monadic::String::deserialize(monadic::ObjectBlob *blob)
{
    size_t strSize = blob->pop<size_t>();
    cout << "strSize=" << strSize << endl;
    char tmpStr[ strSize + 1 ];
    blob->popArray( tmpStr, strSize + 1 );
    cout << "tmpStr=#" << tmpStr << "#" << endl;
    _value = tmpStr;
}
