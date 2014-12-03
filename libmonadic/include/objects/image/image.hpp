#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__

#include <iostream>

#include "object.hpp"

namespace monadic
{ 
  class Image : public Object
  {
  public:
    Image();
    virtual ~Image();

    int create(unsigned int width = 0, unsigned int height = 0, unsigned int depth = 0, unsigned int channels = 0 );
    void copyFrom( char* data, size_t size );
    char* ptr();

    unsigned int getWidth(){ return _width; }
    unsigned int getHeight(){ return _height; }
    unsigned int getDepth(){ return _depth; }
    unsigned int getChannels(){ return _channels; }

    virtual void deserialize( monadic::ObjectBlob* blob );
    virtual monadic::ObjectBlob* serialize();
  
  private:
    unsigned char*_rawBuffer;
    unsigned int  _width;
    unsigned int  _height;
    unsigned int  _depth;
    unsigned int  _channels;
    
  };  
}


#endif
