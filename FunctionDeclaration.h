#ifndef FUNCTIONDECLARATION_H
#define FUNCTIONDECLARATION_H

class TypeDescriptor;
class Function;

class FunctionDeclaration
{
    public:
        FunctionDeclaration(TypeDescriptor *typeDescriptorPointer, Function *functionPointer);
        virtual ~FunctionDeclaration();

        TypeDescriptor *typeDescriptorPointer;
        Function *functionPointer;
    protected:

    private:
};

#endif // FUNCTIONDECLARATION_H
