#ifndef MATRIXTYPE_H
#define MATRIXTYPE_H

#include "header.h"
#include "TypeDescriptor.h"

class MatrixType : public TypeDescriptor
{
    public:
        //MatrixType();
        MatrixType(TypeDescriptor *elementType, int firstRange, int secondRange):
        TypeDescriptor(Matrix), firstRange(firstRange), secondRange(secondRange), elementType(elementType)
        {
            if(elementType)
                elementType->Link();
        }
        ~MatrixType()
        {
            if(elementType && elementType->Delink() == 0)
                delete elementType;
        }
        TypeDescriptor* GetElementType() const
        {
            return elementType;
        }
        void Print()
        {
            TypeDescriptor::Print();
            cout << "[" << firstRange << "][" << secondRange << "] of ";
            if(elementType)
                elementType->Print();
            else
                cout << "NULL";
        }
        friend int Compatible(TypeDescriptor *t1, TypeDescriptor *t2);

        int firstRange; // Zakres pierwszego indeksu
        int secondRange; // Zakres drugiego indeksu
    protected:

    private:
        TypeDescriptor *elementType; // Typ elementu
};

#endif // MATRIXTYPE_H
