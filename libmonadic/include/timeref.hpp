#ifndef __TIMEREF_HPP__
#define __TIMEREF_HPP__

namespace monadic
{
  class TimeRef
  {
    public:
      TimeRef( double timeReference=0.0 )
      :_timeRef(timeReference)
      {}
      
      double getTime();
      
    private:
      double _timeRef;
  };
}

#endif
