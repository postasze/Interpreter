#include "Parser.h"
#include "Scope.h"
#include "Scanner.h"
#include "Token.h"
#include "IdentifierDescriptor.h"
#include "TypeDescriptor.h"
#include "MatrixType.h"
#include "DeclarationStatement.h"
#include "Statement.h"
#include "FunctionCallStatement.h"
#include "ReadStatement.h"
#include "WriteStatement.h"
#include "IfStatement.h"
#include "WhileStatement.h"
#include "ReturnStatement.h"
#include "BlockStatement.h"
#include "Assignment.h"
#include "Argument.h"
#include "FunctionDeclaration.h"
#include "VariableDeclaration.h"
#include "Expression.h"
#include "SimpleExpression.h"
#include "Term.h"
#include "Factor.h"
#include "Variable.h"
#include "Constant.h"
#include "Function.h"
#include "Value.h"

Parser::Parser(Scanner& scanner) : scanner(scanner)
{
    // Deskryptory typów wbudowanych
    integerType = new TypeDescriptor(Integer);
    booleanType = new TypeDescriptor(Boolean);
    matrixType = new TypeDescriptor(Matrix);
    procedureType = new TypeDescriptor(Procedure);

    bufferedTokens = new deque<Token*>();

    simpleTypeTokenList = new vector<TokenType>();
    simpleTypeTokenList->push_back(IntegerKeyWord);
    simpleTypeTokenList->push_back(BooleanKeyWord);

    assignmentAndLeftParenthesis = new vector<TokenType>();
    assignmentAndLeftParenthesis->push_back(AssignmentOperator);
    assignmentAndLeftParenthesis->push_back(LeftParenthesis);

    typeAndIdentifier = new vector<TokenType>();
    typeAndIdentifier->push_back(IntegerKeyWord);
    typeAndIdentifier->push_back(BooleanKeyWord);
    typeAndIdentifier->push_back(MatrixToken);
    typeAndIdentifier->push_back(Identifier);

    assignmentAndCommaAndSemicolon = new vector<TokenType>();
    assignmentAndCommaAndSemicolon->push_back(AssignmentOperator);
    assignmentAndCommaAndSemicolon->push_back(Comma);
    assignmentAndCommaAndSemicolon->push_back(Semicolon);

    MinusAndNaturalNumber = new vector<TokenType>();
    MinusAndNaturalNumber->push_back(Minus);
    MinusAndNaturalNumber->push_back(NaturalNumberConstant);

    NextToken();
}

//Parser::Parser()
//{
    //ctor
//}

Parser::~Parser()
{
    delete integerType;
    delete booleanType;
    delete matrixType;
    delete procedureType;

    simpleTypeTokenList->clear();
    delete(simpleTypeTokenList);

    assignmentAndLeftParenthesis->clear();
    delete(assignmentAndLeftParenthesis);

    typeAndIdentifier->clear();
    delete(typeAndIdentifier);

    assignmentAndCommaAndSemicolon->clear();
    delete(assignmentAndCommaAndSemicolon);

    MinusAndNaturalNumber->clear();
    delete(MinusAndNaturalNumber);
}

void Parser::accept(TokenType TokenType)
{
    if(currentToken->GetTokenCode() == TokenType)
        NextToken();
    else
        SyntaxErrorWithExpectedToken(TokenType);
}

void Parser::NextToken() // Pobranie następnego tokenu
{
    delete(currentToken); // usuwamy i zwalniamy pamiec poprzedniego tokenu

    if(bufferedTokens->empty())
        currentToken = scanner.GetNextToken();
    else
    {
        currentToken = bufferedTokens->front();
        bufferedTokens->pop_front();
    }
}

/*Token* Parser::Peek(unsigned int position)
{
    Token* tokenPointer;

    while(position > bufferedTokens->size())
    {
        tokenPointer = scanner.GetNextToken();
        if(tokenPointer->GetTokenCode() == EOT)
            exit(0);
        bufferedTokens->push_back(tokenPointer);
    }

    tokenPointer = bufferedTokens->at(position-1);

    return tokenPointer;
}*/

void Parser::SyntaxErrorWithExpectedToken(TokenType TokenType) // Oczekiwany Token
{
    scanner.ScanError(ParsingError, ScanErrors[ParsingError] + " Spodziewany Token: ", TokenStrings[TokenType]);
    exit(1);
}

void Parser::SyntaxErrorWithUnexpectedToken(Token *token) // Nieoczekiwany Token
{
    scanner.ScanError(ParsingError, " Nieoczekiwany symbol: ", TokenStrings[token->GetTokenCode()]);
    exit(1);
}

void Parser::SyntaxErrorWithExpectedTokens(vector<TokenType> *tokenList)
{
    cout << "Blad parsowania w linijce: " << currentToken->GetTokenPosition().GetLineNumber()
        << " i w znaku: " << currentToken->GetTokenPosition().GetCharacterNumber() << endl;

    cout << "Nieoczekiwany symbol: " << TokenStrings[currentToken->GetTokenCode()] << endl;
    cout << "Oczekiwane symbole:" << endl;

    for(unsigned int i = 0; i < tokenList->size(); i++)
    cout << TokenStrings[tokenList->at(i)] << endl;

    exit(1);
}

void Parser::SemanticError(int errorCode, bool displayCurrentTokenPosition)
{
    if(displayCurrentTokenPosition)
        cout << "Blad w linijce: " << currentToken->GetTokenPosition().GetLineNumber()
            << " i w znaku: " << currentToken->GetTokenPosition().GetCharacterNumber() << endl;
    cout << "Semantic error: " << SemanticErrors[errorCode] << endl;
    exit(1);
}

queue<Statement*>* Parser::parseProgram(void)
{
    Statement *statementPointer;
    queue<Statement*> *statementList = new queue<Statement*>();

    if(currentToken == nullptr)
    {
        delete(statementList);
        return nullptr; // program pusty
    }
    while(currentToken->GetTokenCode() != EOT &&
          currentToken->GetTokenCode() != Others &&
         (statementPointer = parseStatement()) != nullptr)
        statementList->push(statementPointer);

    if(statementList->empty())
    {
        delete(statementList);
        return nullptr; // blad parsowania programu
    }

    return statementList;
}

FunctionDeclaration* Parser::parseFunctionDeclaration(
    TypeDescriptor *typeDescriptorPointer, string identifierName)
{
    vector<Variable*> *argumentList;
    BlockStatement *blockStatementPointer;
    Function *functionPointer;

    if(currentToken->GetTokenCode() != LeftParenthesis)
        return nullptr;

    accept(LeftParenthesis);

    argumentList = parseArguments(); // jesli nie udalo sie przeparsowac listy argumentow to idziemy dalej (moze nie ma w ogole argumentow)

    accept(RightParenthesis);

    if((blockStatementPointer = parseBlockStatement(identifierName, argumentList)) == nullptr)
        SyntaxErrorWithUnexpectedToken(currentToken);

    functionPointer = new Function(typeDescriptorPointer,
        identifierName, argumentList, blockStatementPointer);

    return new FunctionDeclaration(typeDescriptorPointer, functionPointer);
}

vector<Variable*>* Parser::parseArguments()
{
    vector<Variable*>* argumentList = new vector<Variable*>();
    Variable *argumentPointer;

    if((argumentPointer = parseArgument()) == nullptr)
    {
        delete(argumentList);
        return nullptr;
    }

    argumentList->push_back(argumentPointer);
    while(currentToken->GetTokenCode() == Comma)
    {
        accept(Comma);
        if((argumentPointer = parseArgument()) == nullptr)
            SyntaxErrorWithExpectedTokens(typeAndIdentifier);
        argumentList->push_back(argumentPointer);
    }
    return argumentList;
}

Variable* Parser::parseArgument()
{
    TypeDescriptor *typeDescriptorPointer;
    string identifierName = "";

    if((typeDescriptorPointer = parseType()) == nullptr)
        return nullptr;
    if((identifierName = parseIdentifier()).empty())
        SyntaxErrorWithExpectedToken(Identifier);

    return new Variable(typeDescriptorPointer, identifierName);
}

BlockStatement* Parser::parseBlockStatement(string blockName, vector<Variable*> *argumentList)
{
    queue<Statement*> *statementList = new queue<Statement*>();
    Statement *statementPointer;

    if(currentToken->GetTokenCode() != LeftCurlyBrace)
        return nullptr;

    accept(LeftCurlyBrace);

    while((statementPointer = parseStatement()) != nullptr)
        statementList->push(statementPointer);

    accept(RightCurlyBrace);

    return new BlockStatement(blockName, statementList, argumentList);
}

vector<VariableDeclaration*>* Parser::parseVariableDeclarations(
    TypeDescriptor* typeDescriptorPointer, string identifierName)
{
    vector<VariableDeclaration*>* variableDeclarationList = new vector<VariableDeclaration*>();
    Assignment *assignmentPointer;

    if((assignmentPointer = parseAssignment(identifierName, typeDescriptorPointer)) != nullptr)
        variableDeclarationList->push_back(new VariableDeclaration(assignmentPointer));
    else if(currentToken->GetTokenCode() == Comma ||
            currentToken->GetTokenCode() == Semicolon)
        variableDeclarationList->push_back(new VariableDeclaration(
            new Variable(typeDescriptorPointer, identifierName)));
    else
    {
        delete variableDeclarationList;
        return nullptr;
    }

    while(currentToken->GetTokenCode() == Comma)
    {
        accept(Comma);

        if((identifierName = parseIdentifier()).empty())
            SyntaxErrorWithExpectedToken(Identifier);

        if((assignmentPointer = parseAssignment(identifierName, typeDescriptorPointer)) != nullptr)
            variableDeclarationList->push_back(new VariableDeclaration(assignmentPointer));
        else
            variableDeclarationList->push_back(new VariableDeclaration(
                new Variable(typeDescriptorPointer, identifierName)));
    }
    accept(Semicolon);

    return variableDeclarationList;
}

TypeDescriptor* Parser::parseType()
{
    TypeDescriptor *typeDescriptorPointer;

    if((typeDescriptorPointer = parseMatrixType()) != nullptr)
        return typeDescriptorPointer;
    else if((typeDescriptorPointer = parseSimpleType()) != nullptr)
        return typeDescriptorPointer;
    else
        return nullptr;
}

TypeDescriptor* Parser::parseMatrixType()
{
    TypeDescriptor *elementTypeDescriptorPointer;
    int firstRange, secondRange;

    if(currentToken->GetTokenCode() != MatrixToken)
        return nullptr;

    accept(MatrixToken);
    accept(LeftBracket);

    if(currentToken->GetTokenCode() == NaturalNumberConstant)
        firstRange = currentToken->GetIntValue();
    else
        SyntaxErrorWithExpectedToken(NaturalNumberConstant);

    accept(NaturalNumberConstant);
    accept(RightBracket);
    accept(LeftBracket);

    if(currentToken->GetTokenCode() == NaturalNumberConstant)
        secondRange = currentToken->GetIntValue();
    else
        SyntaxErrorWithExpectedToken(NaturalNumberConstant);

    accept(NaturalNumberConstant);
    accept(RightBracket);
    accept(Of);
    if((elementTypeDescriptorPointer = parseSimpleType()) == nullptr)
        SyntaxErrorWithExpectedTokens(simpleTypeTokenList);

    return new MatrixType(elementTypeDescriptorPointer, firstRange, secondRange);;
}

TypeDescriptor* Parser::parseSimpleType()
{
    if(currentToken->GetTokenCode() == IntegerKeyWord)
    {
        accept(IntegerKeyWord);
        return integerType;
    }
    else if(currentToken->GetTokenCode() == BooleanKeyWord)
    {
        accept(BooleanKeyWord);
        return booleanType;
    }
    else
        return nullptr;
}

Statement* Parser::parseStatement()
{
    DeclarationStatement *declarationStatementPointer;
    Statement *simpleStatementPointer, *structuredStatementPointer;

    if((declarationStatementPointer = parseDeclarationStatement()) != nullptr)
        return declarationStatementPointer;
    else if((simpleStatementPointer = parseSimpleStatement()) != nullptr)
        return simpleStatementPointer;
    else if((structuredStatementPointer = parseStructuredStatement()) != nullptr)
        return structuredStatementPointer;
    else
        return nullptr;
}

DeclarationStatement* Parser::parseDeclarationStatement()
{
    TypeDescriptor *typeDescriptorPointer;
    string identifierName;
    FunctionDeclaration *functionDeclarationPointer;
    vector<VariableDeclaration*> *variableDeclarationList;
    int statementPosition = currentToken->GetTokenPosition().GetLineNumber();

    if((typeDescriptorPointer = parseType()) == nullptr)
        return nullptr;

    if((identifierName = parseIdentifier()).empty())
        SyntaxErrorWithExpectedToken(Identifier);

    if((functionDeclarationPointer = parseFunctionDeclaration(typeDescriptorPointer, identifierName)) != nullptr)
        return new DeclarationStatement(functionDeclarationPointer, statementPosition);
    else if((variableDeclarationList = parseVariableDeclarations(typeDescriptorPointer, identifierName)) != nullptr)
        return new DeclarationStatement(variableDeclarationList, statementPosition);
    else
        SyntaxErrorWithUnexpectedToken(currentToken);

    return nullptr;
}


Statement* Parser::parseSimpleStatement()
{
    Statement *statementPointer;

    if((statementPointer = (Statement*) parseWriteStatement()) != nullptr)
        accept(Semicolon);
    else if((statementPointer = (Statement*) parseReadStatement()) != nullptr)
        accept(Semicolon);
    else if((statementPointer = (Statement*) parseReturnStatement()) != nullptr)
        accept(Semicolon);
    else if((statementPointer = (Statement*) parseIdentifierStatement()) != nullptr)
        accept(Semicolon);
    else
        return nullptr;

    return statementPointer;
}

Statement* Parser::parseIdentifierStatement()
{
    string identifierName;
    Statement *statementPointer;

    if((identifierName = parseIdentifier()).empty())
        return nullptr;

    if((statementPointer = (Statement*) parseAssignment(identifierName, nullptr)) != nullptr)
        return statementPointer;
    else if((statementPointer = (Statement*) parseFunctionCallStatement(identifierName)) != nullptr)
        return statementPointer;
    else
        SyntaxErrorWithExpectedTokens(assignmentAndLeftParenthesis);

    return nullptr;
}

Statement* Parser::parseStructuredStatement()
{
    Statement *statementPointer;

    if((statementPointer = (Statement*) parseWhileStatement()) != nullptr)
        return statementPointer;
    else if((statementPointer = (Statement*) parseIfStatement()) != nullptr)
        return statementPointer;
    else if((statementPointer = (Statement*) parseBlockStatement("", nullptr)) != nullptr)
        return statementPointer;
    else
        return nullptr;
}

FunctionCallStatement* Parser::parseFunctionCallStatement(string identifierName)
{
    vector<Expression*>* parameterList;
    int statementPosition = currentToken->GetTokenPosition().GetLineNumber();

    if(currentToken->GetTokenCode() != LeftParenthesis)
        return nullptr;

    accept(LeftParenthesis);

    parameterList = parseParameters(); // jesli nie udalo sie przeparsowac listy parametrow to idziemy dalej (moze nie ma w ogole parametrow)

    accept(RightParenthesis);

    return new FunctionCallStatement(identifierName, parameterList, statementPosition);
}

vector<Expression*>* Parser::parseParameters()
{
    vector<Expression*>* parameterList = new vector<Expression*>();
    Expression *expressionPointer;

    if((expressionPointer = parseExpression()) == nullptr)
    {
        delete(parameterList);
        return nullptr;
    }

    parameterList->push_back(expressionPointer);
    while(currentToken->GetTokenCode() == Comma)
    {
        accept(Comma);
        if((expressionPointer = parseExpression()) == nullptr)
            SyntaxErrorWithUnexpectedToken(currentToken);
        parameterList->push_back(expressionPointer);
    }

    return parameterList;
}

ReturnStatement* Parser::parseReturnStatement()
{
    Expression *expressionPointer;
    int statementPosition = currentToken->GetTokenPosition().GetLineNumber();

    if(currentToken->GetTokenCode() != ReturnKeyWord)
        return nullptr;

    accept(ReturnKeyWord);
    if((expressionPointer = parseExpression()) == nullptr)
        SyntaxErrorWithUnexpectedToken(currentToken);

    return new ReturnStatement(expressionPointer, statementPosition);
}

IfStatement* Parser::parseIfStatement()
{
    Expression *expressionPointer;
    Statement *thenStatement, *elseStatement = nullptr;
    int statementPosition = currentToken->GetTokenPosition().GetLineNumber();

    if(currentToken->GetTokenCode() != If)
        return nullptr;

    accept(If);
    accept(LeftParenthesis);

    if((expressionPointer = parseExpression()) == nullptr)
        SyntaxErrorWithUnexpectedToken(currentToken);

    if(!Compatible(expressionPointer->typeDescriptorPointer, booleanType))
        SemanticError(ExpressionResultNotBoolean, true);

    accept(RightParenthesis);
    accept(Then);

    if((thenStatement = parseInstructions()) == nullptr)
        SyntaxErrorWithUnexpectedToken(currentToken);

    if(currentToken->GetTokenCode() == Else)
    {
        accept(Else);
        if((elseStatement = parseInstructions()) == nullptr)
            SyntaxErrorWithUnexpectedToken(currentToken);
    }
    return new IfStatement(expressionPointer, thenStatement, elseStatement, statementPosition);
}

WhileStatement* Parser::parseWhileStatement()
{
    Expression *expressionPointer;
    Statement *statementPointer;
    int statementPosition = currentToken->GetTokenPosition().GetLineNumber();

    if(currentToken->GetTokenCode() != While)
        return nullptr;

    accept(While);
    accept(LeftParenthesis);

    if((expressionPointer = parseExpression()) == nullptr)
        SyntaxErrorWithUnexpectedToken(currentToken);

    if(!Compatible(expressionPointer->typeDescriptorPointer, booleanType))
        SemanticError(ExpressionResultNotBoolean, true);

    accept(RightParenthesis);

    if((statementPointer = parseInstructions()) == nullptr)
        SyntaxErrorWithUnexpectedToken(currentToken);

    return new WhileStatement(expressionPointer, statementPointer, statementPosition);
}

Statement* Parser::parseInstructions()
{
    Statement *statementPointer;

    if((statementPointer = parseBlockStatement("", nullptr)) != nullptr)
        return statementPointer;
    else if((statementPointer = parseStatement()) != nullptr)
        return statementPointer;
    else
        return nullptr;
}

Assignment* Parser::parseAssignment(string identifierName, TypeDescriptor *typeDescriptorPointer)
{
    Expression *expressionPointer;
    int statementPosition = currentToken->GetTokenPosition().GetLineNumber();

    if(currentToken->GetTokenCode() != AssignmentOperator)
        return nullptr;

    accept(AssignmentOperator);

    if((expressionPointer = parseExpression()) == nullptr)
        SyntaxErrorWithUnexpectedToken(currentToken);

    if(typeDescriptorPointer != nullptr)
        return new Assignment(new Variable(typeDescriptorPointer, identifierName), expressionPointer);
    else
        return new Assignment(identifierName, expressionPointer, statementPosition);
}

ReadStatement* Parser::parseReadStatement()
{
    vector<Variable*> *variableList;
    int statementPosition = currentToken->GetTokenPosition().GetLineNumber();

    if(currentToken->GetTokenCode() != Read)
        return nullptr;

    accept(Read);

    accept(LeftParenthesis);

    variableList = parseInputVariables(); // jesli nie udalo sie przeparsowac listy zmiennych to idziemy dalej (moze nie ma w ogole zmiennych)

    accept(RightParenthesis);

    return new ReadStatement(variableList, statementPosition);
}

vector<Variable*>* Parser::parseInputVariables()
{
    vector<Variable*>* variableList = new vector<Variable*>();
    Variable *variablePointer;

    if((variablePointer = parseVariable()) == nullptr)
    {
        delete(variableList);
        return nullptr;
    }

    variableList->push_back(variablePointer);
    while(currentToken->GetTokenCode() == Comma)
    {
        accept(Comma);
        if((variablePointer = parseVariable()) == nullptr)
            SyntaxErrorWithExpectedToken(Identifier);
        variableList->push_back(variablePointer);
    }
    return variableList;
}

WriteStatement* Parser::parseWriteStatement()
{
    vector<Expression*> *expressionList;
    int statementPosition = currentToken->GetTokenPosition().GetLineNumber();

    if(currentToken->GetTokenCode() != Write)
        return nullptr;

    accept(Write);

    accept(LeftParenthesis);

    expressionList = parseOutValues(); // jesli nie udalo sie przeparsowac listy wyrazen to idziemy dalej (moze nie ma w ogole wyrazen)

    accept(RightParenthesis);

    return new WriteStatement(expressionList, statementPosition);
}

vector<Expression*>* Parser::parseOutValues()
{
    vector<Expression*>* expressionList = new vector<Expression*>();
    Expression *expressionPointer;

    if((expressionPointer = parseExpression()) == nullptr)
    {
        delete(expressionList);
        return nullptr;
    }

    expressionList->push_back(expressionPointer);
    while(currentToken->GetTokenCode() == Comma)
    {
        accept(Comma);
        if((expressionPointer = parseExpression()) == nullptr)
            SyntaxErrorWithUnexpectedToken(currentToken);
        expressionList->push_back(expressionPointer);
    }

    return expressionList;
}

/*TypeDescriptor* Parser::parseConditionExpression()
{

}*/

Expression* Parser::parseExpression()
{
    TokenType relativeOperator;
    SimpleExpression *leftSimpleExpression, *rightSimpleExpression;

    if((leftSimpleExpression = parseSimpleExpression()) == nullptr)
        return nullptr;

    if(currentToken->GetTokenCategoryCode() == RelativeOperatorToken)
    {
        relativeOperator = currentToken->GetTokenCode();
        NextToken();

        if((rightSimpleExpression = parseSimpleExpression()) == nullptr)
            SyntaxErrorWithUnexpectedToken(currentToken);

        return new Expression(booleanType, leftSimpleExpression, rightSimpleExpression, relativeOperator);
    }
    else
        return new Expression(nullptr, leftSimpleExpression, nullptr, (TokenType) -1);
}

SimpleExpression* Parser::parseSimpleExpression()
{
    vector<Term*> *termList = new vector<Term*>();
    vector<TokenType> *additiveOperatorList = new vector<TokenType>();
    bool isNegative = false;
    Term *termPointer;

    if(currentToken->GetTokenCode() == Plus)
    {
        NextToken();
        if((termPointer = parseTerm()) == nullptr)
            SyntaxErrorWithUnexpectedToken(currentToken);
    }
    else if(currentToken->GetTokenCode() == Minus)
    {
        isNegative = true;
        NextToken();
        if((termPointer = parseTerm()) == nullptr)
            SyntaxErrorWithUnexpectedToken(currentToken);
    }
    else if((termPointer = parseTerm()) == nullptr)
    {
        delete termList;
        delete additiveOperatorList;
        return nullptr;
    }

    termList->push_back(termPointer);

    while(currentToken->GetTokenCategoryCode() == AdditiveOperatorToken)
    {
        additiveOperatorList->push_back(currentToken->GetTokenCode());
        NextToken();

        if((termPointer = parseTerm()) == nullptr)
            SyntaxErrorWithUnexpectedToken(currentToken);

        termList->push_back(termPointer);
    }
    return new SimpleExpression(nullptr, termList, additiveOperatorList, isNegative);
}

Term* Parser::parseTerm()
{
    vector<Factor*> *factorList = new vector<Factor*>();
    vector<TokenType> *multiplicativeOperatorList = new vector<TokenType>();
    Factor *factorPointer;

    if((factorPointer = parseFactor()) == nullptr)
    {
        delete factorList;
        delete multiplicativeOperatorList;
        return nullptr;
    }

    factorList->push_back(factorPointer);

    while(currentToken->GetTokenCategoryCode() == MultiplicativeOperatorToken)
    {
        multiplicativeOperatorList->push_back(currentToken->GetTokenCode());
        NextToken();

        if((factorPointer = parseFactor()) == nullptr)
            SyntaxErrorWithUnexpectedToken(currentToken);

        factorList->push_back(factorPointer);
    }
    return new Term(nullptr, factorList, multiplicativeOperatorList);
}

Factor* Parser::parseFactor()
{
    Expression *expressionPointer;
    Constant *constantPointer;
    Factor *factorPointer;
    Variable *variablePointer =  nullptr;
    FunctionCallStatement *functionCallStatementPointer = nullptr;

    if((constantPointer = parseConstant()) != nullptr)
        return new Factor(constantPointer);
    else if((expressionPointer = parseParenthesizedExpression()) != nullptr)
        return new Factor(expressionPointer);
    else if((factorPointer = parseNotFactor()) != nullptr)
        return new Factor(factorPointer);
    else if(parseIdentifierFactor(&variablePointer, &functionCallStatementPointer) != false)
    {
        if(variablePointer != nullptr)
            return new Factor(variablePointer);
        else
            return new Factor(functionCallStatementPointer);
    }
    else
        return nullptr;
}

Factor* Parser::parseNotFactor()
{
    Factor *factorPointer;

    if(currentToken->GetTokenCode() != NotOperator)
        return nullptr;

    accept(NotOperator);

    if((factorPointer = parseFactor()) == nullptr)
        SyntaxErrorWithUnexpectedToken(currentToken);

    return factorPointer;
}

Expression* Parser::parseParenthesizedExpression()
{
    Expression *expressionPointer;

    if(currentToken->GetTokenCode() != LeftParenthesis)
        return nullptr;

    accept(LeftParenthesis);

    if((expressionPointer = parseExpression()) == nullptr)
        SyntaxErrorWithUnexpectedToken(currentToken);

    accept(RightParenthesis);

    return expressionPointer;
}

bool Parser::parseIdentifierFactor(Variable **variablePointer,
    FunctionCallStatement **functionCallStatementPointer)
{
    string identifierName = "";
    if((identifierName = parseIdentifier()).empty())
        return false;

    if((*functionCallStatementPointer = parseFunctionCallStatement(identifierName)) != nullptr)
        return true;
    else
    {
        *variablePointer = new Variable(nullptr, identifierName);
        return true;
    }
}

Constant* Parser::parseConstant()
{
    Constant *constantPointer;
    if((constantPointer = parseMatrixConstant()) != nullptr)
        return constantPointer;
    else if((constantPointer = parseIntegerConstant()) != nullptr)
        return constantPointer;
    else
        return nullptr;
}

Constant* Parser::parseIntegerConstant()
{
    int integerConstant = 1;
    if(currentToken->GetTokenCode() == Minus)
    {
        integerConstant *= (-1);
        accept(Minus);

        if(currentToken->GetTokenCode() == NaturalNumberConstant)
        {
            integerConstant *= currentToken->GetIntValue();
            accept(NaturalNumberConstant);
            return new Constant(integerType, integerConstant);
        }
        else
            SyntaxErrorWithExpectedToken(NaturalNumberConstant);
    }
    else if(currentToken->GetTokenCode() == NaturalNumberConstant)
    {
        integerConstant *= currentToken->GetIntValue();
        accept(NaturalNumberConstant);
        return new Constant(integerType, integerConstant);
    }
    return nullptr;
}

Constant* Parser::parseMatrixConstant()
{
    int firstRange = 0, secondRange = 0, previousSecondRange = 0;
    bool firstTime = true;
    vector<int>* matrixValue = new vector<int>();
    Constant *constantPointer;

    if(currentToken->GetTokenCode() != LeftBracket)
    {
        delete matrixValue;
        return nullptr;
    }

    accept(LeftBracket);
    while(currentToken->GetTokenCode() == LeftBracket)
    {
        firstRange++;
        secondRange = 0;
        accept(LeftBracket);

        while(currentToken->GetTokenCode() == Minus ||
              currentToken->GetTokenCode() == NaturalNumberConstant)
        {
            secondRange++;
            if((constantPointer = parseIntegerConstant()) == nullptr)
                SyntaxErrorWithExpectedTokens(MinusAndNaturalNumber);
            matrixValue->push_back(constantPointer->getValue()->GetIntValue());
            delete constantPointer;
        }
        if((!firstTime) && (previousSecondRange != secondRange))
            SemanticError(WrongMatrixRanges, currentToken);

        previousSecondRange = secondRange;

        accept(RightBracket);
        if(firstTime)
            firstTime = false;
    }
    accept(RightBracket);

    return new Constant(new MatrixType(integerType, firstRange, secondRange), matrixValue);
}

Variable* Parser::parseVariable()
{
    string identifierName = "";

    if((identifierName = parseIdentifier()).empty())
        return nullptr;

    return new Variable(nullptr, identifierName);
}

string Parser::parseIdentifier()
{
    string identifierName;

    if(currentToken->GetTokenCode() != Identifier)
        return "";

    identifierName = currentToken->GetStringValue();
    accept(Identifier);

    return identifierName;
}
