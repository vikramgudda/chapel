#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include "link.h"
#include "type.h"

class Stmt;

enum varType {
  VAR_NORMAL,
  VAR_CONFIG,
  VAR_STATE
};

class Symbol : public Link {
 public:
  char* name;

  Symbol(char* init_name);

  void print(FILE*);
};


class NullSymbol : public Symbol {
 public:
  NullSymbol(void);

  bool isNull(void) { return true; }
};


class VarSymbol : public Symbol {
 public:
  bool isVar;
  varType varClass;
  Type* type;

  VarSymbol(char* init_name, Type* init_type = dtUnknown);
  
  void setType(Type* newType);
  void setIsVar(bool init_isVar);
  void setVarClass(varType init_varClass);

  void printWithType(FILE*);
};


class TypeSymbol : public Symbol {
 public:
  Type* definition;

  TypeSymbol(char* init_name, Type* init_definition);
};


class FunSymbol : public Symbol {
 public:
  Symbol* formals;
  Type* retType;
  Stmt* body;

  FunSymbol(char* init_name, Symbol* init_formals, Type* init_retType,
	    Stmt* init_body);
};


// BLC: Get rid of this
extern Symbol* pstSumReduce;

#endif
