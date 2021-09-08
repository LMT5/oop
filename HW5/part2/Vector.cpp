#include"Vector.h"

using namespace std;

template<class T> void Vector<T>::swap(Vector& a)
{
	swap(v,a.v);
	swap(sz,a.sz);
}

int Vector<void*>::count2 = 0;
