#include "IdentifierDescriptor.h"
#include "TypeDescriptor.h"

IdentifierDescriptor::IdentifierDescriptor()
{
    //ctor
}

IdentifierDescriptor::~IdentifierDescriptor()
{
    //dtor
}

void IdentifierDescriptor::Print()
{
    if(leftSubTree) leftSubTree->Print();
    cout << *this;
    if(rightSubTree) rightSubTree->Print();
}
