#include <iostream>
#include <stdarg.h>
#include <vector>
#include <exception>
#include <memory>
#include <functional>
using namespace std;

class StopIteration: public exception {
  public:
    virtual const char* what() const throw() {
      return "StopIteration";
    }
};


#define BEGIN_YIELD switch(first) { \
  case 0: \
      first =1;\

#define END_YIELD  first = 0; \
    break;\
    }

#define YIELD(a) return (a); \
  case 1:

int yield_list(int x) {
  static int a = 0;
  static int first = 0;

  while(a < x) {
    BEGIN_YIELD
    printf("inside function %d\n", a);
    YIELD(a)
    a += 1;
    END_YIELD
  }

  throw StopIteration();
}



template<class ItemType>
class List {
  public:
    List(int num_item, ... ) {
      at = 0;
      if ( num_item == 0 ) {
        return ;
      }
      va_list ap;
      va_start(ap, num_item);
    
      int i = 0;
      for(; i < num_item; i ++ ) {
        ItemType item = va_arg(ap, ItemType);
        content.push_back(item);
      }
    }


    bool has_next() {
      return !(at == content.size());
    }

    ItemType next() {
      return content[at++];
    }

  private:
    vector<ItemType> content;
    int at;
};

int func(shared_ptr< List<int> > iter) {
  for(; iter->has_next(); ){
    return iter->next() + 10;
  }
  throw StopIteration();
}


template< class IterType, class BaseType> // IterType should be a smart pointer
class Generator {
  public:
    Generator(function< BaseType (IterType)> func, IterType iter) {
      this->iter = iter;
      this->func = func;
    }

    BaseType next() {
      return this->func(this->iter);
    }

  private:
    IterType iter;
    function<BaseType (IterType)> func;
};


template<class FuncType, class BaseType, class ArgType>
class GeneratorFromFunction {
  public:
    GeneratorFromFunction(FuncType func, ArgType arg) {
      this->func = func;
      this->arg = arg;
    }

    BaseType next() {
      return func(arg);
    }

  private:
    FuncType func;
    ArgType arg;
};


int main() {
  auto list = make_shared< List<int> >(3, 10, 20, 30);

  /*
  for(; list->has_next(); )
    cout << list->next() << endl;
  */

  /*
  auto x = make_shared< Generator< shared_ptr< List<int> >,  int > >(func, list);
  for(; 1; ) {
    cout << x->next() << endl;
  }
  */

  /*
  auto x = make_shared< GeneratorFromFunction<function< int (int) >, int, int> > (yield_list, 10);
  for(; 1; ) {
    cout << x->next() << endl;
  }
  */


  cout << yield_list(10) << endl;
  cout << yield_list(10) << endl;
  cout << yield_list(10) << endl;
  cout << yield_list(10) << endl;
  cout << yield_list(10) << endl;
  cout << yield_list(10) << endl;
}