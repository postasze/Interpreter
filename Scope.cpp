#include "Scope.h"
#include "Parser.h"
#include "IdentifierDescriptor.h"
#include "TypeDescriptor.h"
#include "Interpreter.h"

Scope::~Scope()
{
    if(root)
    {
        if(SHOWIDS)
        {
            cout << "======== Nazwy zdefiniowane w zakresie: " << scopeName << '\n';
            root->Print();
            cout << "========\n";
        }
        delete root;
    }
}

/*Scope::Scope()
{
    //ctor
}

Scope::~Scope()
{
    //dtor
}
*/

// Instaluje identyfikator name z podanymi atrybutami
IdentifierDescriptor* Scope::Install(string name, unsigned typeKind, TypeDescriptor *identifierType)
{
    int equationResult, leftSubTree;
    IdentifierDescriptor *identifierDescriptorPointer, *lastIdentifierDescriptorPointer;
    IdentifierDescriptor *newIdentifierDescriptorPointer = new IdentifierDescriptor(name, typeKind, identifierType);

    if(root == NULL)
        return root = newIdentifierDescriptorPointer;
    identifierDescriptorPointer = root;

    while(identifierDescriptorPointer != NULL)
    {
        lastIdentifierDescriptorPointer = identifierDescriptorPointer;
        equationResult = name.compare(identifierDescriptorPointer->name);// A...Z != a...z

        if(equationResult < 0)
        {
            identifierDescriptorPointer = identifierDescriptorPointer->leftSubTree;
            leftSubTree = 1;
        }
        else if(equationResult > 0)
        {
            identifierDescriptorPointer = identifierDescriptorPointer->rightSubTree;
            leftSubTree = 0;
        }
        else
        {
            interpreter.SemanticError(HomonymDefinition, true); // Definicja homonimu
            identifierDescriptorPointer = identifierDescriptorPointer->rightSubTree;
            leftSubTree = 0; // Instaluj jednak
        }
    }
    return leftSubTree?(lastIdentifierDescriptorPointer->leftSubTree = newIdentifierDescriptorPointer)
        : (lastIdentifierDescriptorPointer->rightSubTree = newIdentifierDescriptorPointer);
}

// Szukanie nazwy 'name' w tabelach poczynając od
// bieżącego zasięgu. Parametr 'expectedTypeKinds' określa
// dopuszczalne rodzaje identyfikatorów spośród
// {VarId, ConstId, TypId, ProcId}. Znalezienie nazwy
// niezgodnego rodzaju albo brak nazwy powodują
// komunikat błędu; w przypadku braku nazwy, oprócz
// wysłania komunikatu, instaluje się tę nazwę z
// najbardziej prawdopodobnym rodzajem (p. kolejność w
// zbiorze IdKind).
// Jeżeli nazwę znaleziono, ale ma ona błędny rodzaj,
// to zwracane jest wskazanie na pseudo-deskryptor
// ...Dummy. Pozwala to korzystać z funkcji Search()
// jednorodnie, niezależnie od wyniku szukania.
IdentifierDescriptor* Scope::Search(string name, unsigned expectedTypeKinds)
{
    int ok = 1, equationResult, best;
    IdentifierDescriptor *IdentifierDescriptorPointer;
    Scope *currentScope = this; // Zasięg aktualny
    // best = "najważnejszy" rodzaj
    for(best = 1; (expectedTypeKinds & best) == 0; best <<= 1) ;
    do
    {
        IdentifierDescriptorPointer = currentScope->root;
        while(IdentifierDescriptorPointer != NULL)
        {
            equationResult = name.compare(IdentifierDescriptorPointer->name);// A...Z == a...z
            if(equationResult<0)
                IdentifierDescriptorPointer = IdentifierDescriptorPointer->leftSubTree;
            else if(equationResult>0)
                IdentifierDescriptorPointer = IdentifierDescriptorPointer->rightSubTree;
            else
            {
                ok = expectedTypeKinds & IdentifierDescriptorPointer->typeKind;
                if(ok)
                    return IdentifierDescriptorPointer; // Znaleziony
                IdentifierDescriptorPointer = IdentifierDescriptorPointer->rightSubTree;
            }
        }
        if(!ok)
        {
            interpreter.SemanticError(WrongIdentifierKind, true); // Zły rodzaj identyfikatora
            // Zwróć wskazanie na deskryptor "pozorny"
            switch(best)
            {
                case 1: return interpreter.VariableDummy;
                case 2: return interpreter.ConstantDummy;
                case 4: return interpreter.TypeDummy;
                case 8: return interpreter.ProcedureDummy;
                default:// Nie powinno się zdarzyć
                    break;
            }
        }
        currentScope = currentScope->exteriorScope; // Przejdź do zasięgu zewnętrznego
    } while(currentScope != NULL);
    if(name == "main")
        interpreter.SemanticError(MainFunctionNotDefined, false);
    else
        interpreter.SemanticError(NoIdentifierDefinition, true); // Brak definicji identyfikatora
    return Install(name, best, NULL);
}

void Scope::PrintTree(IdentifierDescriptor *identifierDescriptorPointer, int currentDepth)
{
    if(identifierDescriptorPointer == nullptr)
        return ;
    for(int i = 0; i < currentDepth; i++)
        cout << "-";
    cout << identifierDescriptorPointer->name << endl;
    PrintTree(identifierDescriptorPointer->leftSubTree, currentDepth+1);
    PrintTree(identifierDescriptorPointer->rightSubTree, currentDepth+1);
}
