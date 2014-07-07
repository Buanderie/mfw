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
    
    virtual void deserialize( const std::vector< unsigned char >& dataBuffer )=0;
    virtual std::vector< unsigned char > serialize()=0;
    
  };
}

#endif
