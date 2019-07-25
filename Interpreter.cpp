#include "Interpreter.h"
#include "IdentifierDescriptor.h"
#include "TypeDescriptor.h"
#include "Scope.h"
#include "Statement.h"
#include "Parser.h"
#include "Function.h"
#include "BlockStatement.h"

Interpreter::Interpreter(Parser& parser) : parser(parser)
{

}

Interpreter::~Interpreter()
{
    CloseScope(); // Zamknij zakres globalny "GLOBAL"
    delete VariableDummy;
    delete ConstantDummy;
    delete TypeDummy;
    delete ProcedureDummy;

    delete integerType;
    delete booleanType;
    delete matrixType;
    delete procedureType;

    while (!statementList->empty())
    {
        statementList->pop();
    }
    delete statementList;
}

void Interpreter::NextStatement()
{
    currentStatement = statementList->front();
    statementList->pop();
    currentStatement->execute(*this);
}

void Interpreter::OpenScope(string scopeName, BlockStatement *block)
{
    currentScope = new Scope(scopeName, *this, currentScope, block);
}

void Interpreter::CloseScope()
{
    Scope *oldScope = currentScope;
    currentScope = currentScope->exteriorScope; // Przelacz na zasieg otaczajacy
    delete oldScope; // Uzun zawartosc starego zakresu
}

void Interpreter::SemanticError(int errorCode, bool displayStatementPosition)
{
    if(displayStatementPosition)
    {
        if(currentScope->scopeName == "GLOBAL")
            cout << "Blad w instrukcji zaczynajacej sie w linijce: " <<
                currentStatement->GetStatementPosition() << endl;
        else
            cout << "Blad w instrukcji zaczynajacej sie w linijce: " <<
                currentScope->block->currentStatement->GetStatementPosition() << endl;
    }
    cout << "Semantic error: " << SemanticErrors[errorCode] << endl;
    exit(1);
}

void Interpreter::Run()
{
    IdentifierDescriptor *identifierDescriptorPointer;
    // Utworz deskryptory pozorne dla Scope::Search()
    VariableDummy = new IdentifierDescriptor("@@VARIABLEDUMMY", VariableIdentifier, 0);
    ConstantDummy = new IdentifierDescriptor("@@CONSTANTDUMMY", ConstantIdentifier,0);
    TypeDummy = new IdentifierDescriptor("@@TYPEDUMMY", TypeIdentifier, 0);
    ProcedureDummy = new IdentifierDescriptor("@@PROCEDUREDUMMY", ProcedureIdentifier, 0);

    // Utworz zasieg globalny
    OpenScope("GLOBAL", nullptr);

    // Deskryptory typow wbudowanych
    integerType = parser.integerType;
    booleanType = parser.booleanType;
    matrixType = parser.matrixType;
    procedureType = parser.procedureType;

    // Instaluj nazwy predefiniowane
    currentScope->Install("integer", TypeIdentifier, integerType);
    currentScope->Install("boolean", TypeIdentifier, booleanType);
    currentScope->Install("false", ConstantIdentifier, booleanType);
    currentScope->Install("true", ConstantIdentifier, booleanType);

    if((statementList = parser.parseProgram()) == nullptr)
        cout << "Blad kompilacji, nie udalo sie przeparsowac pliku" << endl;

    while(!statementList->empty())
        NextStatement();

    // sprawdzamy czy zostala zdefiniowana funkcja main
    identifierDescriptorPointer = currentScope->Search("main", ProcedureIdentifier);
    // jesli funkcja main istnieje to wykonujemy jej zawartosc
    identifierDescriptorPointer->functionPointer->blockStatement->execute(*this);
}
