// C

// STL
#include <iostream>

// INTERNAL
#include "objects/image/image.hpp"

using namespace std;
using namespace monadic;

monadic::Image::Image()
    :Object("Image")
{
    _width = 0;
    _height = 0;
    _depth = 0;
    _channels = 0;
    _rawBuffer = 0;
}

monadic::Image::~Image()
{
    if( _rawBuffer )
        delete[] _rawBuffer;
}

void monadic::Image::deserialize( monadic::ObjectBlob* blob )
{

    _width = blob->pop<unsigned int>();
    _height = blob->pop<unsigned int>();
    _depth = blob->pop<unsigned int>();
    _channels = blob->pop<unsigned int>();
    const unsigned int memsz = _width * _height * (_depth/8) * _channels;
    if( _rawBuffer )
        delete[] _rawBuffer;
    _rawBuffer = new unsigned char[ memsz ];
    blob->popArray( (void*)_rawBuffer, memsz );
    cout << "width=" << _width << " - height=" << _height << endl;
}

monadic::ObjectBlob* monadic::Image::serialize()
{
    const unsigned int memsz = _width * _height * (_depth/8) * _channels;
    ObjectBlob* obj = new ObjectBlob(this->getTypeName());
    obj->push<unsigned int>( _width );
    obj->push<unsigned int>( _height );
    obj->push<unsigned int>( _depth );
    obj->push<unsigned int>( _channels );
    obj->pushArray( _rawBuffer, memsz );
    return obj;
}

int monadic::Image::create(unsigned int width, unsigned int height, unsigned int depth, unsigned int channels)
{
    _width = width;
    _height = height;
    _depth = depth;
    _channels = channels;
    const unsigned int memsz = _width * _height * (_depth/8) * _channels;
    _rawBuffer = new unsigned char[ memsz ];
    return 0;
}

