#ifndef RPN_TYPES_H_SENTRY
#define RPN_TYPES_H_SENTRY

#include "rpn.hpp"

class RPNConst : public RPNElem
{
public:
	virtual RPNConst* Clone() const = 0;
	void Evaluate(RPNItem **stack,
						RPNItem **cur_cmd) const;
	virtual void set(string& str) = 0;
	virtual ~RPNConst() {}
	RPNElem* Convert2RPNElem(lexeme *c_l) const;
};

class RPNStringLiteral	: public RPNConst	
{
	string value;
public:
	RPNStringLiteral(char *a = 0) : value(a) {  }
	RPNStringLiteral(const string &str) { value = str; }
	void set(string& str) { value = str; }
	virtual ~RPNStringLiteral() {}
	virtual RPNConst* Clone() const 
		{ return new RPNStringLiteral(value); }
	string& Get() { return value; }
	void print() const { value.print(); }
};

class RPNDouble	: public RPNConst	/* Maybe real like in Pascal */
{
	double value;
public:
	RPNDouble(double a = 0) { value = a; }
	void set(string& number);
	virtual ~RPNDouble() {}
	virtual RPNConst* Clone() const 
		{ return new RPNDouble(value); }
	double Get() const { return value; }
	void print() const { printf("[%2.2fl]", value); }
};


class RPNLabel: public RPNConst	/* Maybe real like in Pascal */
{
	RPNItem *value;
public:
	RPNLabel(RPNItem *a = 0) { value = a; }
	void set(string& number) {};
	virtual ~RPNLabel() {}
	virtual RPNConst* Clone() const 
		{ return new RPNLabel(value); }
	RPNItem *Get() const { return value; }
	void print() const { printf("Label");}
};



#endif
