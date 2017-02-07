#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
#include <set>
#include <deque>
using namespace std;

#define N 1000000
#define P  400000

class less_than_4000
{ 
public: bool operator()( int i ){ return i<P; }
};

int main( int argc, char* argv[] )
{
vector< int > vec;
list< int > lst;
set< int > st;
deque< int > qu;	

clock_t c0 = clock();
for( int i=N; i>=0; --i ){ vec.push_back( i ); } clock_t c1 = clock();
for( int i=N; i>=0; --i ){ lst.push_back( i ); } clock_t c2 = clock();
for( int i=N; i>=0; --i ){ st.insert( i ); }	 clock_t c3 = clock();
for( int i=N; i>=0; --i ){ qu.push_back( i ); }	 clock_t c4 = clock();


clock_t s0 = clock();
lst.sort();                    clock_t s1 = clock();
sort( vec.begin(), vec.end() );clock_t s2 = clock();
sort( qu.begin(), qu.end() );  clock_t s3 = clock();

clock_t f0 = clock();
{
	for( int j=0; j<1000; ++j )
	vector< int >::iterator it = find( vec.begin(), vec.end(), 8888+j );
}
clock_t f1 = clock();
{
for( int j=0; j<1000; ++j )
	list< int >::iterator it = find( lst.begin(), lst.end(), 8888+j );
}
clock_t f2 = clock();
{
	for( int j=0; j<1000; ++j )
	deque< int >::iterator it = find( qu.begin(), qu.end(), 8888+j );
}
clock_t f3 = clock();

clock_t fe0 = clock();
{
	for( int j=0; j<1000; ++j ){
	vector< int >::iterator it = find( vec.begin(), vec.end(), 8888+j );
	vec.erase( it );
	}
}
clock_t fe1 = clock();
{
	for( int j=0; j<1000; ++j ){
	list< int >::iterator it = find( lst.begin(), lst.end(), 8888+j );
	lst.erase( it );
	}
}
clock_t fe2 = clock();
{
	for( int j=0; j<1000; ++j ){
	deque< int >::iterator it = find( qu.begin(), qu.end(), 8888+j );
	qu.erase( it );
	}
}
clock_t fe3 = clock();
{
	for( int j=0; j<1000; ++j ){
	set< int >::iterator it = st.find( 8888+j );
	st.erase( it );
	}
}
clock_t fe4 = clock();
clock_t i0 = clock();
{
	vector< int >::iterator it = find( vec.begin(), vec.end(), 8888 );
	for( int j=0; j<1000; ++j ){
	vec.insert( it, j );
	}
}
clock_t i1 = clock();
{
	list< int >::iterator it = find( lst.begin(), lst.end(), 8888 );
	for( int j=0; j<1000; ++j ){
	lst.insert( it, j );
	}
}
clock_t i2 = clock();
{
	deque< int >::iterator it = find( qu.begin(), qu.end(), 8888 );
	for( int j=0; j<1000; ++j ){
	qu.insert( it, j );
	}
}
clock_t i3 = clock();
{
	set< int >::iterator it = st.find( 8888 );
	for( int j=0; j<1000; ++j ){
	st.insert( it, j );
	}
}
clock_t i4 = clock();

clock_t t0 = clock();
{
	for( int j=0; j<1000; ++j )
	  vector< int >::iterator it = lower_bound( vec.begin(), vec.end(), 8888 );
}
clock_t t1 = clock();
{
	for( int j=0; j<1000; ++j )
	list< int >::iterator it = lower_bound( lst.begin(), lst.end(), 8888 );
}
clock_t t2 = clock();
{
	for( int j=0; j<1000; ++j )
	set< int >::iterator it = st.find( 8888 );
}
clock_t t3 = clock();
{
	for( int j=0; j<1000; ++j )
	deque< int >::iterator it = find( qu.begin(), qu.end(), 8888 );
}
clock_t t4 = clock();
clock_t r0 = clock();
vec.erase( remove_if( vec.begin(), vec.end(), less_than_4000() ), vec.end() ); 
clock_t r1 = clock();
lst.remove_if( less_than_4000() );                     clock_t r2 = clock();
qu.erase( remove_if( qu.begin(), qu.end(), less_than_4000() ), qu.end() );   
clock_t r3 = clock();

const float cps = static_cast< const float >( CLOCKS_PER_SEC );
cout << N << " elems." << endl <<endl;
cout << "setup vector:  " << (c1-c0)/cps << endl;
cout << "setup list:    " << (c2-c1)/cps << endl;
cout << "setup set:     " << (c3-c2)/cps << endl;
cout << "setup deque:   " << (c4-c3)/cps << endl;
cout << endl;

cout << "sort vector:   " << (s1-s0)/cps << endl;
cout << "sort list:     " << (s2-s1)/cps << endl;
cout << "sort deque:    " << (s3-s2)/cps << endl;
cout << endl;

cout << "1000 times find() vector: " << (f1-f0)/cps << endl;
cout << "1000 times find() list    " << (f2-f1)/cps << endl;
cout << "1000 times find set       " << (t3-t2)/cps << endl;
cout << "1000 times find deque     " << (t4-t3)/cps << endl;
cout << endl;

cout << "1000 times {find() and erase()} vector: " << (fe1-fe0)/cps << endl;
cout << "1000 times {find() and erase()} list    " << (fe2-fe1)/cps << endl;
cout << "1000 times {find() and erase()} set   " << (fe4-fe3)/cps << endl;
cout << "1000 times {find() and erase()} deque   " << (fe3-fe2)/cps << endl;
cout << endl;

cout << "1000 times insert() vector: " << (i1-i0)/cps << endl;
cout << "1000 times insert() list    " << (i2-i1)/cps << endl;
cout << "1000 times insert() set     " << (i4-i3)/cps << endl;
cout << "1000 times insert() deque   " << (i3-i2)/cps << endl;
cout << endl;

cout << "1000 times lower_bound() vector: " << (t1-t0)/cps << endl;
cout << "1000 times lower_bound() list    " << (t2-t1)/cps << endl;
cout << "1000 times lower_bound() deque    " << (t4-t3)/cps << endl;
cout << endl;

cout << "remove if<"<<P<<" vector:   " << (r1-r0)/cps << endl;
cout << "remove if<"<<P<<" list:     " << (r2-r1)/cps << endl;
cout << "remove if<"<<P<<" deque:    " << (r3-r2)/cps << endl;
cout << endl;

{
	vector< int > vec;
	set< int > st;
	for( int i=0; i<N; ++i ){
		vec.push_back( i );
		st.insert( i );
	}// i
	clock_t ri0 = clock();
	vec.erase( remove_if( vec.begin(), vec.end(), less_than_4000() ), vec.end() );
	clock_t ri1 = clock();
	for( int i=0; i<P; ++i ){
		set< int >::iterator it = st.find( i );
		if( it!= st.end() )
			st.erase( it );
	}// i
	clock_t ri2 = clock();
	cout<< st.size() <<" "<< vec.size()<<endl;
	cout << "remove if<"<<P<<" vector:    " << (ri1-ri0)/cps << endl;
	cout << "find <"<<P<<" and erase set: " << (ri2-ri1)/cps << endl;
}
return 0;
}
