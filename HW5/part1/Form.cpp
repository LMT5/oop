#include"Form.h"
using namespace std;

Form::Form(int p) : prc(p)
{
	fmt = 0;
	wdt = 0;
}

Form& Form::scientific()
{
	fmt = ios_base::scientific;

	return *this;
}

Form& Form::fixed()
{
	fmt = ios_base::fixed;

	return *this;
}

Form& Form::general()
{
	fmt = 0;

	return *this;
}

Form& Form::precision(int p)
{
	prc = p;

	return *this;
}

Form& Form::width(int w)
{
	wdt = w;
	
	return *this;
}

Bound_form Form::operator() (double d)const
{
	return Bound_form(*this,d);
}

ostream& operator <<(ostream& os,const Bound_form& bf)
{
	ostringstream s;
	s.precision(bf.f.prc);
	s.setf((ios_base::fmtflags)bf.f.fmt,ios_base::floatfield);
	s << bf.val;
	return os<<s.str();
}
