#include<iostream>
#include<cstdlib>
#include<sstream>
using namespace std;

class Bound_form;

class Form
{
		friend	ostream& operator<<(ostream&,const Bound_form&);
		int prc;
		int wdt;
		int fmt;
	public:
		explicit Form(int p = 6);
		
		Bound_form operator() (double d)const;

		Form& scientific();
		Form& fixed();
		Form& general();

		Form& uppercase();
		Form& lowercase();
		Form& precision(int p);

		Form& width(int w);
		Form& fill(char);

		Form& plus(bool b = true);
		Form& trailing_zeros(bool b = true);
};

ostream& operator<<(ostream&,const Bound_form&);

struct Bound_form
{
	const Form& f;
	double val;
	
	Bound_form(const Form& ff,double v) : f(ff), val(v) { }
};
