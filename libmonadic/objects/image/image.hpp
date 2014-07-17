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
    
    virtual void deserialize( std::vector< unsigned char >& dataBuffer );
    virtual void serialize( std::vector< unsigned char >& dataBuffer );
  
  private:
    unsigned char*_rawBuffer;
    unsigned int  _width;
    unsigned int  _height;
    unsigned int  _depth;
    unsigned int  _channels;
    
  };
  
  REGISTER_TYPE(monadic::Image, "Image");
  
}


#endif
