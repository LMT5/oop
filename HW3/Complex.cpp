#include"Complex.h"
#include<cmath>

Complex::Complex(const double re, const double im)
{
	real = re;
	imag = im;
}
Complex::Complex(const Complex& c)
{
	real = c.real;
	imag = c.imag;
}
Complex& Complex::operator=(const Complex& c)
{
	real = c.real;
	imag = c.imag;
	return (*this);
}
Complex Complex::Polar(const double leng, const double arg)
{
	this->real = leng*cos(arg);
	this->imag = leng*sin(arg);
	return Complex(leng*cos(arg),leng*sin(arg));
}
double Complex::Real()
{
	return real;
}
double Complex::Imag()
{
	return imag;
}
double Complex::Norm()
{
	return (pow(real,2) + pow(imag,2));
} 
double Complex::Abs()
{
	return (sqrt(pow(real,2) + pow(imag,2)));
}
double Complex::Arg()
{
	return acos(real / sqrt(pow(real,2) + pow(imag,2)));
}
Complex Complex::operator++()
{
	(this->real)+=1;
	(this->imag)+=1;
	return (*this);
}
Complex Complex::operator++(int)
{
	Complex pre(*this);
	(this->real)+=1;
	(this->imag)+=1;
	return pre;
} 
Complex Complex::operator--()
{
	(this->real)-=1;
	(this->imag)-=1;
	return (*this);
}
Complex Complex::operator--(int)
{
	Complex pre(*this);
	(this->real)-=1;
	(this->imag)-=1;
	return (*this);
} 
Complex::Complex()
{
	real = 0;
	imag = 0;
}
Complex Polar(const double leng, const double arg)
{
	return Complex(leng*cos(arg),leng*sin(arg));
}
double Norm(const Complex& x)
{
	return (pow(x.real,2) + pow(x.imag,2));
} 
double Abs(const Complex& x)
{
	return ( sqrt( ( pow(x.real,2) + pow(x.imag,2) ) ) );
}
double Arg(const Complex& x)
{
	return acos(x.real / sqrt(pow(x.real,2) + pow(x.imag,2)));
}
Complex operator+(const Complex& x, const Complex& y)
{
	return Complex((x.real+y.real),(x.imag+y.imag));
}
Complex operator-(const Complex& x, const Complex& y)
{
	return Complex((x.real-y.real),(x.imag-y.imag));
}
Complex operator*(const Complex& x, const Complex& y)
{
	double allreal = x.real * y.real - x.imag * y.imag;
	double allimag = x.real * y.imag + x.imag * y.real;
	return Complex(allreal,allimag);
}
Complex operator/(const Complex& x, const Complex& y)
{
	double allreal = (x.real * y.real + y.imag * x.imag) / (pow(y.real,2) + pow(y.imag,2));
	double allimag = (x.imag * y.real - x.real * y.imag) / (pow(y.real,2) + pow(y.imag,2));
	return Complex(allreal,allimag);
}
Complex operator+=(Complex& x, const Complex& y)
{
	x = x + y;
	return x;	
}
Complex operator-=(Complex& x, const Complex& y)
{
	x = x - y;
	return x;	
}
Complex operator*=(Complex& x, const Complex& y)
{
	x = x * y;
	return x;	
}
Complex operator/=(Complex& x, const Complex& y)
{
	x = x / y;
	return x;	
}
bool operator==(const Complex& x, const Complex& y)
{
	if(x.real == y.real && x.imag == y.imag)
	return true;
	else
	return false;
}
bool operator!=(const Complex& x, const Complex& y)
{
	if(x.real == y.real && x.imag == y.imag)
	return false;
	else
	return true;
}
ostream& operator<<(ostream& o, const Complex& x)
{
	o<<"("<<x.real<<","<<x.imag<<")";
	return o;
}
