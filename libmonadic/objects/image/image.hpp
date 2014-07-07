#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__

#include <iostream>

#include "object.hpp"

namespace monadic
{ 
  class Image : public Object
  {
  public:
    Image()
    { 
      std::cout << "monadic::Image constructor\n";
    }
    
    virtual void deserialize( const std::vector< unsigned char >& dataBuffer ){}
    virtual std::vector< unsigned char > serialize(){ std::vector< unsigned char > res; return res; }
    void popo();
  
  private:
      
  };
  
  REGISTER_TYPE(monadic::Image, "Image");
  
}


#endif
