#include "il_ptr_fun.hpp"

#include <iostream>
#include <functional>

#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

class C
{
public:
  void set(int n){ n_ = n; }
  int get() const{ return n_; }
private:
  int n_;
};

inline int square(int n){ return n * n; }

template<class F>
inline
void print_ptr_fun(F f, int n)
{
  std::cout << f(n) << std::endl;
}

template<class T, class F>
inline
void my_mem_fun1(F f, T *p, int n)
{
  f(p, n);
}

template<class T, class F>
inline
void print_mem_fun(F f, T const *p)
{ std::cout << f(p) << std::endl; }

int main()
{
  using namespace cry;
  using namespace std;
  using namespace boost::lambda;

                                                                   // inlined? (@VC++7.1 with /Ox)
  print_ptr_fun(&square, 1);                                       // yes
  print_ptr_fun(ptr_fun(&square), 2);                              // no
  print_ptr_fun(bind(&square, _1), 3);                             // no
  print_ptr_fun(il_ptr_fun<int (*)(int), &square>(), 4);           // yes
  print_ptr_fun(bind(il_ptr_fun<int (*)(int), &square>(), _1), 5); // yes
  print_ptr_fun(CRY_AS_FUNCTOR(&square), 6);                       // yes
  print_ptr_fun(CRY_AS_FUNCTOR(&square), 7);                       // yes

  C c;                                                           // inlined? (@VC++7.1 with /Ox)
  my_mem_fun1(mem_fun(&C::set), &c, 1);                         // no
  print_mem_fun(mem_fun(&C::get), &c);                           // no
  my_mem_fun1(il_ptr_fun<void (C::*)(int), &C::set>(), &c, 2);   // yes
  print_mem_fun(il_ptr_fun<int (C::*)() const, &C::get>(), &c);  // yes
  my_mem_fun1(CRY_AS_FUNCTOR(&C::set), &c, 3);                   // yes
  print_mem_fun(CRY_AS_FUNCTOR(&C::get), &c);                    // yes
}
