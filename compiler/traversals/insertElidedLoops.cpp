#include "insertElidedLoops.h"
#include "symtab.h"
#include "symscope.h"
#include "symbol.h"
#include "type.h"
#include "expr.h"
#include "stmt.h"
#include "stringutil.h"


InsertElidedIndices::InsertElidedIndices(AList<DefExpr>* init_indices) {
  indices = init_indices;
}


void InsertElidedIndices::preProcessExpr(Expr* expr) {
  Variable* var = dynamic_cast<Variable*>(expr);
  if (var && dynamic_cast<ArrayType*>(var->typeInfo())) {
    AList<Expr>* index_exprs = new AList<Expr>;
    for (DefExpr* tmp = indices->first(); tmp; tmp = indices->next()) {
      index_exprs->insertAtTail(new Variable(tmp->sym));
    }
    ArrayRef* array_ref = new ArrayRef(expr->copy(), index_exprs);
    expr->replace(array_ref);
  }
}


void InsertElidedLoops::postProcessStmt(Stmt* stmt) {
  static int uid = 1;
  if (ExprStmt* expr_stmt = dynamic_cast<ExprStmt*>(stmt)) {
    if (AssignOp* assign = dynamic_cast<AssignOp*>(expr_stmt->expr)) {
      if (ArrayType* array_type = dynamic_cast<ArrayType*>(assign->left->typeInfo())) {
        AList<Symbol>* indices = new AList<Symbol>();
        for (int i = 0; i < array_type->domainType->numdims; i++) {
          char* name = glomstrings(4, "_ind_", intstring(uid), "_", intstring(i));
          indices->insertAtTail(new Symbol(SYMBOL, name));
        }
        uid++;
        ForLoopStmt* loop = Symboltable::startForLoop(true, indices, array_type->domain->copy());
        loop = Symboltable::finishForLoop(loop, stmt->copy());
        stmt->replace(loop);
        TRAVERSE(loop->block, new InsertElidedIndices(loop->indices), true);
      }
    }
  }
}
