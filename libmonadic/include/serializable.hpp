#ifndef __SERIALIZABLE_HPP__
#define __SERIALIZABLE_HPP__

// STL
#include <vector>

// INTERNAL
#include "objectblob.hpp"

namespace monadic
{
  class Serializable
  {
  public:
  
    public:
    Serializable(){}
    virtual ~Serializable(){}
    
    virtual void deserialize( monadic::ObjectBlob* blob )=0;
    virtual monadic::ObjectBlob* serialize()=0;
    
  };
}

#endif
