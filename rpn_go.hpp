class RPNOp : public RPNElem
{
public: 
	virtual RPNOp* Clone() const = 0;
	RPNElem* Convert2RPNElem(lexeme *c_l) const;
};

class RPNOpGo : public RPNOp
{
	void Evaluate(RPNItem** stack, 
								RPNItem  **cur_cmd) const {}
public:
	virtual RPNOpGo* Clone() const 
		{ return new RPNOpGo(); }
	virtual ~RPNOpGo() {};
	virtual void print() const { printf("OpGo"); }
};

class RPNOpGoFalse: public RPNOp
{
	void Evaluate(RPNItem** stack, 
								RPNItem  **cur_cmd) const {}
public:
	virtual ~RPNOpGoFalse() {};
	virtual RPNOpGoFalse* Clone() const 
		{ return new RPNOpGoFalse(); }
	virtual void print() const { printf("OpGoFalse"); }

};

class RPNNoop : public RPNOp
{
	
	virtual void Evaluate(RPNItem **stack,
						RPNItem **cur_cmd) const {}
public:
	virtual ~RPNNoop(){};
	virtual RPNNoop* Clone() const 
		{ return new RPNNoop(); }

	void print() const { printf("Noop"); }
};



