#include <cassert>
#include <iostream>

/*
class Base {
 public:
  virtual size_t id() const = 0;
  virtual const char* name() const = 0;
  virtual ~Base() {}
};

typedef Base* (*CreateFunc)(void);

class SimpleFactory {
 private:
  static const size_t NELEM = 2;
  static size_t id_;
  static CreateFunc creators_[NELEM];

 public:
  static size_t registerFunc(CreateFunc creator) {
    assert(id_ < NELEM);
    assert(creator);
    creators_[id_] = creator;
    return id_++;
  }

  static Base* create(size_t id) { assert(id < NELEM); return (creators_[id])(); }
};

size_t SimpleFactory::id_ = 0;
CreateFunc SimpleFactory::creators_[NELEM];


class D1 : public Base {
 private:
  static Base* create() { return new D1; }
  static const size_t id_;

 public:
  size_t id() const { return id_; }
  const char* name() const { return "D1"; }
};

const size_t D1::id_ = SimpleFactory::registerFunc(&create);

class D2 : public Base {
 private:
  static Base* create() { return new D2; }
  static const size_t id_;

 public:
  size_t id() const { return id_; }
  const char* name() const { return "D2"; }
};

const size_t D2::id_ = SimpleFactory::registerFunc(&create);
*/
int main() {
    /*
  Base* b1 = SimpleFactory::create(0);
  Base* b2 = SimpleFactory::create(1);
  std::cout << "b1 name: " << b1->name() << "\tid: " << b1->id() << "\n";
  std::cout << "b2 name: " << b2->name() << "\tid: " << b2->id() << "\n";
  delete b1;
  delete b2;
  */
  return 0;
}
