#include"lexer.h"

Token::Token(int t): tag(t)
{
}
string Token::toString()const
{
	return string() + (char) tag + "	("+ (char)tag +")";
}

const Word* Word::aand = new Word("&&", Tag::AND);
const Word* Word::oor = new Word("||", Tag::OR);
const Word* Word::eq = new Word("==", Tag::EQ);
const Word* Word::ne = new Word("!=", Tag::NE);
const Word* Word::le = new Word("<=", Tag::LE);
const Word* Word::ge = new Word(">=", Tag::GE);
const Word* Word::minus = new Word("minus", Tag::MINUS);
const Word* Word::True = new Word("true", Tag::TTRUE);
const Word* Word::False = new Word("false", Tag::FFALSE);
const Word* Word::temp = new Word("t", Tag::TEMP);

Word::Word(string s, int tag):Token(tag),lexeme(s)
{
}
string Word::toString() const
{
	if(tag == 256)
	return lexeme + "	(AND)";
	else if(tag == 257)
	return lexeme + "	(BASIC)";
	else if(tag == 258)
	return lexeme + "	(BREAK)";
	else if(tag == 259)
	return lexeme + "	(DO)";
	else if(tag == 260)
	return lexeme + "	(ELSE)";
	else if(tag == 261)
	return lexeme + "	(EQ)";
	else if(tag == 262)
	return lexeme + "	(FALSE)";
	else if(tag == 263)
	return lexeme + "	(GE)";
	else if(tag == 264)
	return lexeme + "	(ID)";
	else if(tag == 265)
	return lexeme + "	(IF)";
	else if(tag == 266)
	return lexeme + "	(INDEX)";
	else if(tag == 267)
	return lexeme + "	(LE)";
	else if(tag == 268)
	return lexeme + "	(MINUS)";
	else if(tag == 269)
	return lexeme + "	(NE)";
	else if(tag == 270)
	return lexeme + "	(NUM)";
	else if(tag == 271)
	return lexeme + "	(OR)";
	else if(tag == 272)
	return lexeme + "	(REAL)";
	else if(tag == 273)
	return lexeme + "	(TEMP)";
	else if(tag == 274)
	return lexeme + "	(TRUE)";
	else if(tag == 275)
	return lexeme + "	(WHILE)";
}
Type::Type(string s,int tag,int w):Word(s,tag),width(w)
{
}

bool Type::numeric(const Type* p)
{
	if(p == Type::Char || p == Type::Int || p == Type::Float)
		return true;
	else
		return false;
}
const Type* Type::max(const Type* p1,const Type* p2)
{
	if(!numeric(p1) || !numeric(p2))
		return NULL;
	else if(p1 == Type::Float || p2 == Type::Float)
		return Type::Float;
	else if(p1 == Type::Int || p1 == Type::Int)
		return Type::Int;
	else
		return Type::Char; 
}

const Type* Type::Int = new Type("int", Tag::BASIC, 4);
const Type* Type::Float = new Type("float", Tag::BASIC, 8);
const Type* Type::Char = new Type("char", Tag::BASIC, 1);
const Type* Type::Bool = new Type("bool", Tag::BASIC, 1);

Num::Num(int v):Token(Tag::NUM),value(v)
{
}
string Num::toString() const
{
	return "" + to_string(value) + "	(NUM)";
}
Real::Real(float v):Token(Tag::REAL),value(v)
{
}
string Real::toString() const
{
	return "" + to_string(value) +"		(REAL)";
}

int Lexer::line = 1;

const void Lexer::reserve(const Word* w)
{
	hashtable[w->lexeme] = w;
}
Lexer::Lexer()
{
	reserve(new Word("if", Tag::IF) );
	reserve(new Word("else", Tag::ELSE) );
	reserve(new Word("while", Tag::WHILE) );
	reserve(new Word("do", Tag::DO) );
	reserve(new Word("break", Tag::BREAK) );
	reserve(Word::True);
	reserve(Word::False);
	reserve(Type::Int);
	reserve(Type::Char);
	reserve(Type::Bool);
	reserve(Type::Float);
}
void Lexer::readch()
{
	int i = cin.get();
	if(i != -1)
		peek = (char) i;
	else
		throw "End of file reached";
}
bool Lexer::readch(char c)
{
	readch();
	if(peek != c)
		return false;
	peek = ' ';
	return true;
}
const Token* Lexer::scan()
{
	for( ; ; readch())
	{
		if(peek == ' ' ||peek == '\t')
			continue;
		else if(peek == '\n')
			line = line + 1;
		else
			break;
	}
	
	switch(peek)
	{
		case '&':
				if(readch('&'))
					return Word::aand;
				else
					return new Token('&');
		case '|':
				if(readch('|'))
					return Word::oor;
				else
					return new Token('|');
		case '=':
				if(readch('='))
					return Word::eq;
				else
					return new Token('=');
		case '!':
				if(readch('='))
					return Word::ne;
				else
					return new Token('!');
		case '<':
				if(readch('='))
					return Word::le;
				else
					return new Token('<');
		case '>':
				if(readch('='))
					return Word::ge;
				else
					return new Token('>');
	}
	if(isdigit(peek))
	{
		int v = 0;
		do
		{
			v = v * 10 + (peek-'0');
			readch();
		}while(isdigit(peek));
		
		if(peek != '.')
			return new Num(v);
		float x = v;
		float d = 10;
		for( ; ; )
		{
			readch();
			if(!(isdigit(peek)))
				break;
			x = x + (peek-'0') / d;
			d = d * 10;
		}
		return new Real(x);
	}
	if(isalpha(peek))
	{
		string b;
		do
		{
			b = b + peek;
			readch();
		}while( (isdigit(peek)|isalpha(peek)) );
		string s = b;
		const Word* w = hashtable[s];
		if(w != NULL)
			return w;
		w = new Word(s, Tag::ID);
		hashtable[s] = w;
		return w;
	}
	Token* tok = new Token(peek);
	peek = ' ';
	return tok;
}
