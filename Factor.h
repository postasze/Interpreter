#ifndef FACTOR_H
#define FACTOR_H

class TypeDescriptor;
class Variable;
class Constant;
class Expression;
class Factor;
class FunctionCallStatement;
class Interpreter;
class Value;

class Factor
{
    public:
        Factor(TypeDescriptor *typeDescriptorPointer = nullptr, Variable *variablePointer = nullptr,
        Constant *constantPointer = nullptr, Expression *expressionPointer = nullptr,
        Factor *notFactorPointer = nullptr,
        FunctionCallStatement *functionCallStatementPointer = nullptr);

        Factor(Variable *variablePointer);
        Factor(Constant *constantPointer);
        Factor(Expression *expressionPointer);
        Factor(Factor *notFactorPointer);
        Factor(FunctionCallStatement *functionCallStatementPointer);
        Factor(const Factor& factor);
        virtual ~Factor();

        TypeDescriptor *typeDescriptorPointer;
        Value* evaluate(Interpreter& interpreter);
        void setValue(Value* value);
        Value* getValue();
    protected:

    private:
        Variable *variablePointer;
        Constant *constantPointer;
        Expression *expressionPointer;
        Factor *notFactorPointer;
        FunctionCallStatement *functionCallStatementPointer;
        Value *value;
};

#endif // FACTOR_H
