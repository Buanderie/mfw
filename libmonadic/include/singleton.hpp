#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

/////////////////////////////////////////////////////////////////////////////
//
// Singleton - modèle Singleton applicable à n'importe quelle classe.
//
/////////////////////////////////////////////////////////////////////////////

template <typename T>
class Singleton
{
protected:
  // Constructeur/destructeur
  Singleton () { }
  ~Singleton () { /*std::cout << "destroying singleton." << std::endl;*/ }

public:
  // Interface publique
  static T *getInstance ()
  {
    if (0 == _singleton)
      {
        //std::cout << "creating singleton." << std::endl;
        _singleton = new T;
      }
    else
      {
        //std::cout << "singleton already created!" << std::endl;
      }

    return (static_cast<T*> (_singleton));
  }

  static void kill ()
  {
    if (0 != _singleton)
      {
        delete _singleton;
        _singleton = 0;
      }
  }

private:
  // Unique instance
  static T *_singleton;
};

template <typename T>
T *Singleton<T>::_singleton = 0;


#endif
