template
<
  class R,
  R (* f) () 
>
struct il_ptr_fun
<
  R (*) () ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()() const
  { return f(); }
};
template
<
  class R,
   class  A0 ,
  R (* f) ( A0) 
>
struct il_ptr_fun
<
  R (*) ( A0) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()( A0 a0) const
  { return f( a0); }
};
template
<
  class R,
   class  A0 , class  A1 ,
  R (* f) ( A0 , A1) 
>
struct il_ptr_fun
<
  R (*) ( A0 , A1) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()( A0 a0 , A1 a1) const
  { return f( a0 , a1); }
};
template
<
  class R,
   class  A0 , class  A1 , class  A2 ,
  R (* f) ( A0 , A1 , A2) 
>
struct il_ptr_fun
<
  R (*) ( A0 , A1 , A2) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()( A0 a0 , A1 a1 , A2 a2) const
  { return f( a0 , a1 , a2); }
};
template
<
  class R,
   class  A0 , class  A1 , class  A2 , class  A3 ,
  R (* f) ( A0 , A1 , A2 , A3) 
>
struct il_ptr_fun
<
  R (*) ( A0 , A1 , A2 , A3) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3) const
  { return f( a0 , a1 , a2 , a3); }
};
template
<
  class R,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 ,
  R (* f) ( A0 , A1 , A2 , A3 , A4) 
>
struct il_ptr_fun
<
  R (*) ( A0 , A1 , A2 , A3 , A4) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4) const
  { return f( a0 , a1 , a2 , a3 , a4); }
};
template
<
  class R,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 ,
  R (* f) ( A0 , A1 , A2 , A3 , A4 , A5) 
>
struct il_ptr_fun
<
  R (*) ( A0 , A1 , A2 , A3 , A4 , A5) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5) const
  { return f( a0 , a1 , a2 , a3 , a4 , a5); }
};
template
<
  class R,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 ,
  R (* f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6) 
>
struct il_ptr_fun
<
  R (*) ( A0 , A1 , A2 , A3 , A4 , A5 , A6) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6) const
  { return f( a0 , a1 , a2 , a3 , a4 , a5 , a6); }
};
template
<
  class R,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 , class  A7 ,
  R (* f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7) 
>
struct il_ptr_fun
<
  R (*) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7) const
  { return f( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7); }
};
template
<
  class R,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 , class  A7 , class  A8 ,
  R (* f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8) 
>
struct il_ptr_fun
<
  R (*) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8) const
  { return f( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8); }
};
template
<
  class R,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 , class  A7 , class  A8 , class  A9 ,
  R (* f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9) 
>
struct il_ptr_fun
<
  R (*) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8 , A9 a9) const
  { return f( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9); }
};
template
<
  void (* f) () 
>
struct il_ptr_fun
<
  void (*) () ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()() const
  {  f(); }
};
template
<
   class  A0 ,
  void (* f) ( A0) 
>
struct il_ptr_fun
<
  void (*) ( A0) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()( A0 a0) const
  {  f( a0); }
};
template
<
   class  A0 , class  A1 ,
  void (* f) ( A0 , A1) 
>
struct il_ptr_fun
<
  void (*) ( A0 , A1) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()( A0 a0 , A1 a1) const
  {  f( a0 , a1); }
};
template
<
   class  A0 , class  A1 , class  A2 ,
  void (* f) ( A0 , A1 , A2) 
>
struct il_ptr_fun
<
  void (*) ( A0 , A1 , A2) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()( A0 a0 , A1 a1 , A2 a2) const
  {  f( a0 , a1 , a2); }
};
template
<
   class  A0 , class  A1 , class  A2 , class  A3 ,
  void (* f) ( A0 , A1 , A2 , A3) 
>
struct il_ptr_fun
<
  void (*) ( A0 , A1 , A2 , A3) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3) const
  {  f( a0 , a1 , a2 , a3); }
};
template
<
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 ,
  void (* f) ( A0 , A1 , A2 , A3 , A4) 
>
struct il_ptr_fun
<
  void (*) ( A0 , A1 , A2 , A3 , A4) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4) const
  {  f( a0 , a1 , a2 , a3 , a4); }
};
template
<
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 ,
  void (* f) ( A0 , A1 , A2 , A3 , A4 , A5) 
>
struct il_ptr_fun
<
  void (*) ( A0 , A1 , A2 , A3 , A4 , A5) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5) const
  {  f( a0 , a1 , a2 , a3 , a4 , a5); }
};
template
<
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 ,
  void (* f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6) 
>
struct il_ptr_fun
<
  void (*) ( A0 , A1 , A2 , A3 , A4 , A5 , A6) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6) const
  {  f( a0 , a1 , a2 , a3 , a4 , a5 , a6); }
};
template
<
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 , class  A7 ,
  void (* f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7) 
>
struct il_ptr_fun
<
  void (*) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7) const
  {  f( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7); }
};
template
<
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 , class  A7 , class  A8 ,
  void (* f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8) 
>
struct il_ptr_fun
<
  void (*) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8) const
  {  f( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8); }
};
template
<
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 , class  A7 , class  A8 , class  A9 ,
  void (* f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9) 
>
struct il_ptr_fun
<
  void (*) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8 , A9 a9) const
  {  f( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9); }
};
template
<
  class R,
  R (& f) () 
>
struct il_ptr_fun
<
  R (&) () ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()() const
  { return f(); }
};
template
<
  class R,
   class  A0 ,
  R (& f) ( A0) 
>
struct il_ptr_fun
<
  R (&) ( A0) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()( A0 a0) const
  { return f( a0); }
};
template
<
  class R,
   class  A0 , class  A1 ,
  R (& f) ( A0 , A1) 
>
struct il_ptr_fun
<
  R (&) ( A0 , A1) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()( A0 a0 , A1 a1) const
  { return f( a0 , a1); }
};
template
<
  class R,
   class  A0 , class  A1 , class  A2 ,
  R (& f) ( A0 , A1 , A2) 
>
struct il_ptr_fun
<
  R (&) ( A0 , A1 , A2) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()( A0 a0 , A1 a1 , A2 a2) const
  { return f( a0 , a1 , a2); }
};
template
<
  class R,
   class  A0 , class  A1 , class  A2 , class  A3 ,
  R (& f) ( A0 , A1 , A2 , A3) 
>
struct il_ptr_fun
<
  R (&) ( A0 , A1 , A2 , A3) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3) const
  { return f( a0 , a1 , a2 , a3); }
};
template
<
  class R,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 ,
  R (& f) ( A0 , A1 , A2 , A3 , A4) 
>
struct il_ptr_fun
<
  R (&) ( A0 , A1 , A2 , A3 , A4) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4) const
  { return f( a0 , a1 , a2 , a3 , a4); }
};
template
<
  class R,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 ,
  R (& f) ( A0 , A1 , A2 , A3 , A4 , A5) 
>
struct il_ptr_fun
<
  R (&) ( A0 , A1 , A2 , A3 , A4 , A5) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5) const
  { return f( a0 , a1 , a2 , a3 , a4 , a5); }
};
template
<
  class R,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 ,
  R (& f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6) 
>
struct il_ptr_fun
<
  R (&) ( A0 , A1 , A2 , A3 , A4 , A5 , A6) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6) const
  { return f( a0 , a1 , a2 , a3 , a4 , a5 , a6); }
};
template
<
  class R,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 , class  A7 ,
  R (& f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7) 
>
struct il_ptr_fun
<
  R (&) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7) const
  { return f( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7); }
};
template
<
  class R,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 , class  A7 , class  A8 ,
  R (& f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8) 
>
struct il_ptr_fun
<
  R (&) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8) const
  { return f( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8); }
};
template
<
  class R,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 , class  A7 , class  A8 , class  A9 ,
  R (& f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9) 
>
struct il_ptr_fun
<
  R (&) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8 , A9 a9) const
  { return f( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9); }
};
template
<
  void (& f) () 
>
struct il_ptr_fun
<
  void (&) () ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()() const
  {  f(); }
};
template
<
   class  A0 ,
  void (& f) ( A0) 
>
struct il_ptr_fun
<
  void (&) ( A0) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()( A0 a0) const
  {  f( a0); }
};
template
<
   class  A0 , class  A1 ,
  void (& f) ( A0 , A1) 
>
struct il_ptr_fun
<
  void (&) ( A0 , A1) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()( A0 a0 , A1 a1) const
  {  f( a0 , a1); }
};
template
<
   class  A0 , class  A1 , class  A2 ,
  void (& f) ( A0 , A1 , A2) 
>
struct il_ptr_fun
<
  void (&) ( A0 , A1 , A2) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()( A0 a0 , A1 a1 , A2 a2) const
  {  f( a0 , a1 , a2); }
};
template
<
   class  A0 , class  A1 , class  A2 , class  A3 ,
  void (& f) ( A0 , A1 , A2 , A3) 
>
struct il_ptr_fun
<
  void (&) ( A0 , A1 , A2 , A3) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3) const
  {  f( a0 , a1 , a2 , a3); }
};
template
<
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 ,
  void (& f) ( A0 , A1 , A2 , A3 , A4) 
>
struct il_ptr_fun
<
  void (&) ( A0 , A1 , A2 , A3 , A4) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4) const
  {  f( a0 , a1 , a2 , a3 , a4); }
};
template
<
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 ,
  void (& f) ( A0 , A1 , A2 , A3 , A4 , A5) 
>
struct il_ptr_fun
<
  void (&) ( A0 , A1 , A2 , A3 , A4 , A5) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5) const
  {  f( a0 , a1 , a2 , a3 , a4 , a5); }
};
template
<
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 ,
  void (& f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6) 
>
struct il_ptr_fun
<
  void (&) ( A0 , A1 , A2 , A3 , A4 , A5 , A6) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6) const
  {  f( a0 , a1 , a2 , a3 , a4 , a5 , a6); }
};
template
<
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 , class  A7 ,
  void (& f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7) 
>
struct il_ptr_fun
<
  void (&) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7) const
  {  f( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7); }
};
template
<
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 , class  A7 , class  A8 ,
  void (& f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8) 
>
struct il_ptr_fun
<
  void (&) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8) const
  {  f( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8); }
};
template
<
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 , class  A7 , class  A8 , class  A9 ,
  void (& f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9) 
>
struct il_ptr_fun
<
  void (&) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8 , A9 a9) const
  {  f( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9); }
};
template
<
  class R,
  class X,
  R (X::* f) () 
>
struct il_ptr_fun
<
  R (X::*) () ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()(X *p  ) const
  { return (p->*f)(); }
  R
  operator()(X &x  ) const
  { return (p.*f)(); }
};
template
<
  class R,
  class X,
   class  A0 ,
  R (X::* f) ( A0) 
>
struct il_ptr_fun
<
  R (X::*) ( A0) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()(X *p ,  A0 a0) const
  { return (p->*f)( a0); }
  R
  operator()(X &x ,  A0 a0) const
  { return (p.*f)( a0); }
};
template
<
  class R,
  class X,
   class  A0 , class  A1 ,
  R (X::* f) ( A0 , A1) 
>
struct il_ptr_fun
<
  R (X::*) ( A0 , A1) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()(X *p ,  A0 a0 , A1 a1) const
  { return (p->*f)( a0 , a1); }
  R
  operator()(X &x ,  A0 a0 , A1 a1) const
  { return (p.*f)( a0 , a1); }
};
template
<
  class R,
  class X,
   class  A0 , class  A1 , class  A2 ,
  R (X::* f) ( A0 , A1 , A2) 
>
struct il_ptr_fun
<
  R (X::*) ( A0 , A1 , A2) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()(X *p ,  A0 a0 , A1 a1 , A2 a2) const
  { return (p->*f)( a0 , a1 , a2); }
  R
  operator()(X &x ,  A0 a0 , A1 a1 , A2 a2) const
  { return (p.*f)( a0 , a1 , a2); }
};
template
<
  class R,
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 ,
  R (X::* f) ( A0 , A1 , A2 , A3) 
>
struct il_ptr_fun
<
  R (X::*) ( A0 , A1 , A2 , A3) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()(X *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3) const
  { return (p->*f)( a0 , a1 , a2 , a3); }
  R
  operator()(X &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3) const
  { return (p.*f)( a0 , a1 , a2 , a3); }
};
template
<
  class R,
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 ,
  R (X::* f) ( A0 , A1 , A2 , A3 , A4) 
>
struct il_ptr_fun
<
  R (X::*) ( A0 , A1 , A2 , A3 , A4) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()(X *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4) const
  { return (p->*f)( a0 , a1 , a2 , a3 , a4); }
  R
  operator()(X &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4) const
  { return (p.*f)( a0 , a1 , a2 , a3 , a4); }
};
template
<
  class R,
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 ,
  R (X::* f) ( A0 , A1 , A2 , A3 , A4 , A5) 
>
struct il_ptr_fun
<
  R (X::*) ( A0 , A1 , A2 , A3 , A4 , A5) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()(X *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5) const
  { return (p->*f)( a0 , a1 , a2 , a3 , a4 , a5); }
  R
  operator()(X &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5) const
  { return (p.*f)( a0 , a1 , a2 , a3 , a4 , a5); }
};
template
<
  class R,
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 ,
  R (X::* f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6) 
>
struct il_ptr_fun
<
  R (X::*) ( A0 , A1 , A2 , A3 , A4 , A5 , A6) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()(X *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6) const
  { return (p->*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6); }
  R
  operator()(X &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6) const
  { return (p.*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6); }
};
template
<
  class R,
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 , class  A7 ,
  R (X::* f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7) 
>
struct il_ptr_fun
<
  R (X::*) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()(X *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7) const
  { return (p->*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7); }
  R
  operator()(X &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7) const
  { return (p.*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7); }
};
template
<
  class R,
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 , class  A7 , class  A8 ,
  R (X::* f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8) 
>
struct il_ptr_fun
<
  R (X::*) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()(X *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8) const
  { return (p->*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8); }
  R
  operator()(X &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8) const
  { return (p.*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8); }
};
template
<
  class R,
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 , class  A7 , class  A8 , class  A9 ,
  R (X::* f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9) 
>
struct il_ptr_fun
<
  R (X::*) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()(X *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8 , A9 a9) const
  { return (p->*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9); }
  R
  operator()(X &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8 , A9 a9) const
  { return (p.*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9); }
};
template
<
  class X,
  void (X::* f) () 
>
struct il_ptr_fun
<
  void (X::*) () ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()(X *p  ) const
  {  (p->*f)(); }
  void
  operator()(X &x  ) const
  {  (p.*f)(); }
};
template
<
  class X,
   class  A0 ,
  void (X::* f) ( A0) 
>
struct il_ptr_fun
<
  void (X::*) ( A0) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()(X *p ,  A0 a0) const
  {  (p->*f)( a0); }
  void
  operator()(X &x ,  A0 a0) const
  {  (p.*f)( a0); }
};
template
<
  class X,
   class  A0 , class  A1 ,
  void (X::* f) ( A0 , A1) 
>
struct il_ptr_fun
<
  void (X::*) ( A0 , A1) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()(X *p ,  A0 a0 , A1 a1) const
  {  (p->*f)( a0 , a1); }
  void
  operator()(X &x ,  A0 a0 , A1 a1) const
  {  (p.*f)( a0 , a1); }
};
template
<
  class X,
   class  A0 , class  A1 , class  A2 ,
  void (X::* f) ( A0 , A1 , A2) 
>
struct il_ptr_fun
<
  void (X::*) ( A0 , A1 , A2) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()(X *p ,  A0 a0 , A1 a1 , A2 a2) const
  {  (p->*f)( a0 , a1 , a2); }
  void
  operator()(X &x ,  A0 a0 , A1 a1 , A2 a2) const
  {  (p.*f)( a0 , a1 , a2); }
};
template
<
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 ,
  void (X::* f) ( A0 , A1 , A2 , A3) 
>
struct il_ptr_fun
<
  void (X::*) ( A0 , A1 , A2 , A3) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()(X *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3) const
  {  (p->*f)( a0 , a1 , a2 , a3); }
  void
  operator()(X &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3) const
  {  (p.*f)( a0 , a1 , a2 , a3); }
};
template
<
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 ,
  void (X::* f) ( A0 , A1 , A2 , A3 , A4) 
>
struct il_ptr_fun
<
  void (X::*) ( A0 , A1 , A2 , A3 , A4) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()(X *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4) const
  {  (p->*f)( a0 , a1 , a2 , a3 , a4); }
  void
  operator()(X &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4) const
  {  (p.*f)( a0 , a1 , a2 , a3 , a4); }
};
template
<
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 ,
  void (X::* f) ( A0 , A1 , A2 , A3 , A4 , A5) 
>
struct il_ptr_fun
<
  void (X::*) ( A0 , A1 , A2 , A3 , A4 , A5) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()(X *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5) const
  {  (p->*f)( a0 , a1 , a2 , a3 , a4 , a5); }
  void
  operator()(X &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5) const
  {  (p.*f)( a0 , a1 , a2 , a3 , a4 , a5); }
};
template
<
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 ,
  void (X::* f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6) 
>
struct il_ptr_fun
<
  void (X::*) ( A0 , A1 , A2 , A3 , A4 , A5 , A6) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()(X *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6) const
  {  (p->*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6); }
  void
  operator()(X &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6) const
  {  (p.*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6); }
};
template
<
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 , class  A7 ,
  void (X::* f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7) 
>
struct il_ptr_fun
<
  void (X::*) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()(X *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7) const
  {  (p->*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7); }
  void
  operator()(X &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7) const
  {  (p.*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7); }
};
template
<
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 , class  A7 , class  A8 ,
  void (X::* f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8) 
>
struct il_ptr_fun
<
  void (X::*) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()(X *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8) const
  {  (p->*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8); }
  void
  operator()(X &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8) const
  {  (p.*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8); }
};
template
<
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 , class  A7 , class  A8 , class  A9 ,
  void (X::* f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9) 
>
struct il_ptr_fun
<
  void (X::*) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9) ,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()(X *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8 , A9 a9) const
  {  (p->*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9); }
  void
  operator()(X &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8 , A9 a9) const
  {  (p.*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9); }
};
template
<
  class R,
  class X,
  R (X::* f) () const
>
struct il_ptr_fun
<
  R (X::*) () const,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()(X const *p  ) const
  { return (p->*f)(); }
  R
  operator()(X const &x  ) const
  { return (p.*f)(); }
};
template
<
  class R,
  class X,
   class  A0 ,
  R (X::* f) ( A0) const
>
struct il_ptr_fun
<
  R (X::*) ( A0) const,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()(X const *p ,  A0 a0) const
  { return (p->*f)( a0); }
  R
  operator()(X const &x ,  A0 a0) const
  { return (p.*f)( a0); }
};
template
<
  class R,
  class X,
   class  A0 , class  A1 ,
  R (X::* f) ( A0 , A1) const
>
struct il_ptr_fun
<
  R (X::*) ( A0 , A1) const,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()(X const *p ,  A0 a0 , A1 a1) const
  { return (p->*f)( a0 , a1); }
  R
  operator()(X const &x ,  A0 a0 , A1 a1) const
  { return (p.*f)( a0 , a1); }
};
template
<
  class R,
  class X,
   class  A0 , class  A1 , class  A2 ,
  R (X::* f) ( A0 , A1 , A2) const
>
struct il_ptr_fun
<
  R (X::*) ( A0 , A1 , A2) const,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()(X const *p ,  A0 a0 , A1 a1 , A2 a2) const
  { return (p->*f)( a0 , a1 , a2); }
  R
  operator()(X const &x ,  A0 a0 , A1 a1 , A2 a2) const
  { return (p.*f)( a0 , a1 , a2); }
};
template
<
  class R,
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 ,
  R (X::* f) ( A0 , A1 , A2 , A3) const
>
struct il_ptr_fun
<
  R (X::*) ( A0 , A1 , A2 , A3) const,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()(X const *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3) const
  { return (p->*f)( a0 , a1 , a2 , a3); }
  R
  operator()(X const &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3) const
  { return (p.*f)( a0 , a1 , a2 , a3); }
};
template
<
  class R,
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 ,
  R (X::* f) ( A0 , A1 , A2 , A3 , A4) const
>
struct il_ptr_fun
<
  R (X::*) ( A0 , A1 , A2 , A3 , A4) const,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()(X const *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4) const
  { return (p->*f)( a0 , a1 , a2 , a3 , a4); }
  R
  operator()(X const &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4) const
  { return (p.*f)( a0 , a1 , a2 , a3 , a4); }
};
template
<
  class R,
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 ,
  R (X::* f) ( A0 , A1 , A2 , A3 , A4 , A5) const
>
struct il_ptr_fun
<
  R (X::*) ( A0 , A1 , A2 , A3 , A4 , A5) const,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()(X const *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5) const
  { return (p->*f)( a0 , a1 , a2 , a3 , a4 , a5); }
  R
  operator()(X const &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5) const
  { return (p.*f)( a0 , a1 , a2 , a3 , a4 , a5); }
};
template
<
  class R,
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 ,
  R (X::* f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6) const
>
struct il_ptr_fun
<
  R (X::*) ( A0 , A1 , A2 , A3 , A4 , A5 , A6) const,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()(X const *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6) const
  { return (p->*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6); }
  R
  operator()(X const &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6) const
  { return (p.*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6); }
};
template
<
  class R,
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 , class  A7 ,
  R (X::* f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7) const
>
struct il_ptr_fun
<
  R (X::*) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7) const,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()(X const *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7) const
  { return (p->*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7); }
  R
  operator()(X const &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7) const
  { return (p.*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7); }
};
template
<
  class R,
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 , class  A7 , class  A8 ,
  R (X::* f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8) const
>
struct il_ptr_fun
<
  R (X::*) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8) const,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()(X const *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8) const
  { return (p->*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8); }
  R
  operator()(X const &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8) const
  { return (p.*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8); }
};
template
<
  class R,
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 , class  A7 , class  A8 , class  A9 ,
  R (X::* f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9) const
>
struct il_ptr_fun
<
  R (X::*) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9) const,
  f
>
{
  template<class Args>
  struct sig
  { typedef R type; };
  R
  operator()(X const *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8 , A9 a9) const
  { return (p->*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9); }
  R
  operator()(X const &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8 , A9 a9) const
  { return (p.*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9); }
};
template
<
  class X,
  void (X::* f) () const
>
struct il_ptr_fun
<
  void (X::*) () const,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()(X const *p  ) const
  {  (p->*f)(); }
  void
  operator()(X const &x  ) const
  {  (p.*f)(); }
};
template
<
  class X,
   class  A0 ,
  void (X::* f) ( A0) const
>
struct il_ptr_fun
<
  void (X::*) ( A0) const,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()(X const *p ,  A0 a0) const
  {  (p->*f)( a0); }
  void
  operator()(X const &x ,  A0 a0) const
  {  (p.*f)( a0); }
};
template
<
  class X,
   class  A0 , class  A1 ,
  void (X::* f) ( A0 , A1) const
>
struct il_ptr_fun
<
  void (X::*) ( A0 , A1) const,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()(X const *p ,  A0 a0 , A1 a1) const
  {  (p->*f)( a0 , a1); }
  void
  operator()(X const &x ,  A0 a0 , A1 a1) const
  {  (p.*f)( a0 , a1); }
};
template
<
  class X,
   class  A0 , class  A1 , class  A2 ,
  void (X::* f) ( A0 , A1 , A2) const
>
struct il_ptr_fun
<
  void (X::*) ( A0 , A1 , A2) const,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()(X const *p ,  A0 a0 , A1 a1 , A2 a2) const
  {  (p->*f)( a0 , a1 , a2); }
  void
  operator()(X const &x ,  A0 a0 , A1 a1 , A2 a2) const
  {  (p.*f)( a0 , a1 , a2); }
};
template
<
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 ,
  void (X::* f) ( A0 , A1 , A2 , A3) const
>
struct il_ptr_fun
<
  void (X::*) ( A0 , A1 , A2 , A3) const,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()(X const *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3) const
  {  (p->*f)( a0 , a1 , a2 , a3); }
  void
  operator()(X const &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3) const
  {  (p.*f)( a0 , a1 , a2 , a3); }
};
template
<
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 ,
  void (X::* f) ( A0 , A1 , A2 , A3 , A4) const
>
struct il_ptr_fun
<
  void (X::*) ( A0 , A1 , A2 , A3 , A4) const,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()(X const *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4) const
  {  (p->*f)( a0 , a1 , a2 , a3 , a4); }
  void
  operator()(X const &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4) const
  {  (p.*f)( a0 , a1 , a2 , a3 , a4); }
};
template
<
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 ,
  void (X::* f) ( A0 , A1 , A2 , A3 , A4 , A5) const
>
struct il_ptr_fun
<
  void (X::*) ( A0 , A1 , A2 , A3 , A4 , A5) const,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()(X const *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5) const
  {  (p->*f)( a0 , a1 , a2 , a3 , a4 , a5); }
  void
  operator()(X const &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5) const
  {  (p.*f)( a0 , a1 , a2 , a3 , a4 , a5); }
};
template
<
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 ,
  void (X::* f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6) const
>
struct il_ptr_fun
<
  void (X::*) ( A0 , A1 , A2 , A3 , A4 , A5 , A6) const,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()(X const *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6) const
  {  (p->*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6); }
  void
  operator()(X const &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6) const
  {  (p.*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6); }
};
template
<
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 , class  A7 ,
  void (X::* f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7) const
>
struct il_ptr_fun
<
  void (X::*) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7) const,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()(X const *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7) const
  {  (p->*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7); }
  void
  operator()(X const &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7) const
  {  (p.*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7); }
};
template
<
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 , class  A7 , class  A8 ,
  void (X::* f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8) const
>
struct il_ptr_fun
<
  void (X::*) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8) const,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()(X const *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8) const
  {  (p->*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8); }
  void
  operator()(X const &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8) const
  {  (p.*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8); }
};
template
<
  class X,
   class  A0 , class  A1 , class  A2 , class  A3 , class  A4 , class  A5 , class  A6 , class  A7 , class  A8 , class  A9 ,
  void (X::* f) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9) const
>
struct il_ptr_fun
<
  void (X::*) ( A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9) const,
  f
>
{
  template<class Args>
  struct sig
  { typedef void type; };
  void
  operator()(X const *p ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8 , A9 a9) const
  {  (p->*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9); }
  void
  operator()(X const &x ,  A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8 , A9 a9) const
  {  (p.*f)( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9); }
};
