#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "header.h"

class TypeDescriptor;
class SimpleExpression;
class Interpreter;
class Value;

class Expression
{
    public:
        Expression(TypeDescriptor *typeDescriptorPointer, SimpleExpression *leftSimpleExpression,
        SimpleExpression *rightSimpleExpression, TokenType relativeOperator);
        Expression(const Expression& expression);
        virtual ~Expression();

        TypeDescriptor *typeDescriptorPointer;
        Value* evaluate(Interpreter& interpreter);
        void setValue(Value* value);
        Value* getValue();
    protected:

    private:
        SimpleExpression *leftSimpleExpression;
        SimpleExpression *rightSimpleExpression;
        TokenType relativeOperator;
        Value *value;
};

#endif // EXPRESSION_H
