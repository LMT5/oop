#ifndef __VECTOR_H__
#define __VECTOR_H__
#include<iostream>
#include<iomanip>
#include"Trace.h"

using namespace std;

template<class T> class Vector
{
		T* v;
		int sz;
		static int count1;
	public:
		Vector();
		Vector(int i) : v(new T[i])
		{
			Trace Int("vector<T>::vector(int)");
			count1++;
			cout<<"  count = "<<count1<<endl;
		}
		~Vector()
		{
			Trace Int("vector<T>::~vector");
			cout<<"  count = "<<count1<<endl;
			count1--;
		}

		
		
		T& elem(int i) { return v[i]; }
		T& operator[](int i) { return v[i]; }

		void swap(Vector&);
};

template<class T> int Vector<T>::count1 = 0;

template<> class Vector<void*>
{
		static int count2;
	public:
		void** p;

		void*& operator[] (int i) { return p[i];}
		Vector();
		Vector(int i) : p(new void*[i])
		{
			Trace Void("vector<void*>::vector(int)");
			count2++;
			cout<<"  count = "<<count2<<endl;
		}
		
		~Vector()
		{
			Trace Void("vector<void*>::~vector");
			cout<<"  count = "<<count2<<endl;
			count2--;
		}
		
		void*& elem(int i) { return p[i]; }
};



template<class T>class Vector<T*> : private Vector<void*>
{
	public:
		typedef Vector<void*> Base;

		Vector() : Base() 
		{
			Trace Tb("vector<T*>::vector()");
		}
		~Vector()
		{
			Trace Tb("vector<T*>::~vector");
		}
		explicit Vector(int i) : Base(i) {
			Trace Tb("vector<T*>::vector(int)");
		}

		T*& elem(int i) {return (T*&)(Base::elem(i)); }
		T*& operator[] (int i) {return (T*&)(Base::operator[] (i) ); }
};


template<class T> void swap(T& x,T& y)
{
	T t;
	x = y;
	y = t;	
}

template<class T> void swap(Vector<T>& a,Vector<T>& b)
{
	a.swap(b);
}

#endif
