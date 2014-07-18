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
    friend class ObjectFactory;
    
    public:
      Object(){}
      Object( const Object& other ){ _typeName = other._typeName; }
      virtual ~Object(){}

      //
      std::string getTypeName(){ return _typeName; }
      
      //
      virtual void deserialize( std::vector< unsigned char >& dataBuffer )=0;
      virtual void serialize( std::vector< unsigned char >& dataBuffer )=0;

    private:
      std::string _typeName;
            
    protected:
    
  };
  
  class ObjectFactory
  {
  
  public:
    static Object* create(const std::string& id)
    { 
      // creates an object from a string
      const Creators_t::const_iterator iter = static_creators().find(id);
      Object* ret = (iter == static_creators().end() ? 0 : (*iter->second)()); // if found, execute the creator function pointer
      if( ret != 0 )
      {
        ret->_typeName = id;
      }
      return ret;
    }

  private:
    typedef Object* Creator_t(); // function pointer to create Object
    typedef std::map<std::string, Creator_t*> Creators_t; // map from id to creator
    static Creators_t& static_creators()
    {
      static Creators_t s_creators; return s_creators;
    } // static instance of map
    
    template<class T = int> class Register
    {
      static Object* create() { Object* o = new T(); return o; };
      static Creator_t* init_creator(const std::string& id) { return static_creators()[id] = create; }
      static Creator_t* creator;
    };
    
  };

#define REGISTER_TYPE(T, STR) template<> monadic::ObjectFactory::Creator_t* monadic::ObjectFactory::Register<T>::creator = monadic::ObjectFactory::Register<T>::init_creator(STR)
#define CREATE_OBJECT(x) reinterpret_cast<x*>( ObjectFactory::create(#x) )

}

#endif
