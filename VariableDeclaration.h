#ifndef VARIABLEDECLARATION_H
#define VARIABLEDECLARATION_H

class Assignment;
class Variable;
class TypeDescriptor;

class VariableDeclaration
{
    public:
        VariableDeclaration();
        VariableDeclaration(Assignment *assignmentPointer);
        VariableDeclaration(Variable *variablePointer);
        VariableDeclaration(const VariableDeclaration& variableDeclaration);
        virtual ~VariableDeclaration();

        TypeDescriptor *typeDescriptorPointer;
        Assignment *assignmentPointer;
        Variable *variablePointer;
    protected:

    private:
};

#endif // VARIABLEDECLARATION_H
