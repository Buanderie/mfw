#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

// STL
#include <string>
#include <map>
#include <iostream>

// INTERNAL
#include "serializable.hpp"

using namespace std;

namespace monadic
{
  // Base Object class from which every object should derive from
  class Object : public Serializable
  {

    public:
      Object( const std::string& typeName)
          :_typeName(typeName)
      {}

      Object( const Object& other ){ _typeName = other._typeName; }
      virtual ~Object(){}

      //
      std::string getTypeName(){ return _typeName; }
      
      //
      virtual void deserialize( monadic::ObjectBlob* blob )=0;
      virtual monadic::ObjectBlob* serialize()=0;

    private:
      std::string _typeName;
            
    protected:
    
  };
}

#endif
