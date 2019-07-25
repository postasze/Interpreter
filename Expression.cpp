#include "Expression.h"
#include "SimpleExpression.h"
#include "Interpreter.h"
#include "Value.h"

Expression::Expression(TypeDescriptor *typeDescriptorPointer, SimpleExpression *leftSimpleExpression,
        SimpleExpression *rightSimpleExpression, TokenType relativeOperator)
{
    this->typeDescriptorPointer = typeDescriptorPointer;
    this->leftSimpleExpression = leftSimpleExpression;
    this->rightSimpleExpression = rightSimpleExpression;
    this->relativeOperator = relativeOperator;
    this->value = nullptr;
}

Expression::Expression(const Expression& expression)
{
    this->typeDescriptorPointer = expression.typeDescriptorPointer;
    this->leftSimpleExpression = new SimpleExpression(*expression.leftSimpleExpression);
    if(expression.rightSimpleExpression != nullptr)
        this->rightSimpleExpression = new SimpleExpression(*expression.rightSimpleExpression);
    else
        this->rightSimpleExpression = nullptr;
    this->relativeOperator = expression.relativeOperator;
    this->value = nullptr;
}

Expression::~Expression()
{
    if(this->value != nullptr)
        delete this->value;
    if(this->leftSimpleExpression != nullptr)
        delete leftSimpleExpression;
    if(this->rightSimpleExpression != nullptr)
        delete rightSimpleExpression;
}

Value* Expression::evaluate(Interpreter& interpreter)
{
    Value *leftValue, *rightValue;

    if(this->value != nullptr)
        delete this->value;

    if(rightSimpleExpression == nullptr)
    {
        this->value = new Value(*leftSimpleExpression->evaluate(interpreter));
        this->typeDescriptorPointer = leftSimpleExpression->typeDescriptorPointer;
    }
    else
    {
        this->value = new Value();
        leftValue = leftSimpleExpression->evaluate(interpreter);
        rightValue = rightSimpleExpression->evaluate(interpreter);

        // tylko integery moga byc powiazane operatorem relacyjnym
        if(!(Compatible(leftSimpleExpression->typeDescriptorPointer, interpreter.integerType) &&
             Compatible(rightSimpleExpression->typeDescriptorPointer, interpreter.integerType)))
            interpreter.SemanticError(IncompatibleTypesForOperands, true);

        switch(relativeOperator)
        {
        case EquationOperator:
            this->value->SetBoolValue(leftValue->GetIntValue() == rightValue->GetIntValue());
            break;
        case InequityOperator:
            this->value->SetBoolValue(leftValue->GetIntValue() != rightValue->GetIntValue());
            break;
        case LesserThanOperator:
            this->value->SetBoolValue(leftValue->GetIntValue() < rightValue->GetIntValue());
            break;
        case LesserOrEqualOperator:
            this->value->SetBoolValue(leftValue->GetIntValue() <= rightValue->GetIntValue());
            break;
        case GreaterThanOperator:
            this->value->SetBoolValue(leftValue->GetIntValue() > rightValue->GetIntValue());
            break;
        case GreaterOrEqualOperator:
            this->value->SetBoolValue(leftValue->GetIntValue() >= rightValue->GetIntValue());
            break;
        default:
            break;
        }
        this->typeDescriptorPointer = interpreter.booleanType;
    }
    return this->value;
}

void Expression::setValue(Value* value)
{
    if(this->value == nullptr)
        this->value = new Value();

    this->value->SetBoolValue(value->GetBoolValue());
    this->value->SetIntValue(value->GetIntValue());
    this->value->SetMatrixValue(value->GetMatrixValue());
}

Value* Expression::getValue()
{
    return this->value;
}
