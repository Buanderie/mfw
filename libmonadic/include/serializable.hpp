#ifndef __SERIALIZABLE_HPP__
#define __SERIALIZABLE_HPP__

// STL
#include <vector>

namespace monadic
{
  class Serializable
  {
  public:
  
    public:
    Serializable(){}
    virtual ~Serializable(){}
    
    virtual void deserialize( std::vector< unsigned char >& dataBuffer )=0;
    virtual void serialize( std::vector< unsigned char >& dataBuffer )=0;
    
  };
}

#endif
