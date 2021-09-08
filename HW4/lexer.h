#include<iostream>
#include<clocale>
#include<map>
using namespace std;

class Tag
{
	public:
		static const int AND = 256;
		static const int BASIC = 257;
		static const int BREAK = 258;
		static const int DO = 259;
		static const int ELSE = 260;
		static const int EQ = 261;
		static const int FFALSE = 262;
		static const int GE = 263;
		static const int ID = 264;
		static const int IF = 265;
		static const int INDEX = 266;
		static const int LE = 267;
		static const int MINUS = 268;
		static const int NE = 269;
		static const int NUM = 270;
		static const int OR = 271;
		static const int REAL = 272;
		static const int TEMP = 273;
		static const int TTRUE = 274;
		static const int WHILE = 275;
};

class Token
{
	public:
		const int tag;
		Token(int t);
		virtual string toString()const;
};
class Word : public Token
{
	public:
		string lexeme = "";
		Word(string s,int tag);
		virtual string toString() const;
		static const Word* aand;
		static const Word* oor;
		static const Word* eq;
		static const Word* ne;
		static const Word* le;
		static const Word* ge;
		static const Word* minus;
		static const Word* True;
		static const Word* False;
		static const Word* temp;
};

class Type : public Word
{
	public:
		int width = 0;
		Type(string s,int tag,int w);
		static const Type* Int;
		static const Type* Float;
		static const Type* Char;
		static const Type* Bool;
		static bool numeric(const Type* p);
		static const Type* max(const Type* p1,const Type* p2);
};

class Num : public Token
{
	public:
		const int value;
		Num(int v);
		virtual string toString() const;
};
class Real : public Token
{
	public:
		const float value;
		Real(float v);
		virtual string toString() const;
};
class Lexer
{
	public:
		static int line;
		char peek = ' ';
		map<string,const Word*> hashtable;//Hashtable words = new Hashtable()
		const void reserve(const Word* w);
		Lexer();
		void readch();
		bool readch(char c);
		const Token* scan();
};
