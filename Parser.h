#ifndef PARSER_H
#define PARSER_H

#include "header.h"

class Token;
class TypeDescriptor;
class IdentifierDescriptor;
class Range;
class Scope;
class Scanner;
class MatrixType;
class Statement;
class Declaration;
class FunctionDeclaration;
class VariableDeclaration;
class DeclarationStatement;
class IfStatement;
class WhileStatement;
class ReturnStatement;
class FunctionCallStatement;
class WriteStatement;
class ReadStatement;
class Assignment;
class Expression;
class SimpleExpression;
class Term;
class Factor;
class Argument;
class Function;
class Variable;
class Constant;
class BlockStatement;

class Parser
{
    public:
        Parser(Scanner& scanner);
        //Parser();
        virtual ~Parser();
        queue<Statement*>* parseProgram(void); // Główna procedura rozbioru
        TypeDescriptor *integerType, *booleanType, *matrixType, *procedureType;

    protected:

    private:
        deque<Token*> *bufferedTokens;
        vector<TokenType> *simpleTypeTokenList;
        vector<TokenType> *assignmentAndLeftParenthesis;
        vector<TokenType> *typeAndIdentifier;
        vector<TokenType> *assignmentAndCommaAndSemicolon;
        vector<TokenType> *MinusAndNaturalNumber;

        Scanner& scanner; // Moduł scanera
        //friend Synchronize;
        //enum { FirstSyntaxErrorWithExpectedToken = 10, FirstSemanticError = 60};
        Token *currentToken; // Ostatnio pobrany token z scanner'a
        //bool can_parse; // Jeśli synchronizacja OK
        // Podzbiory tokenów
        //SymSet ststart, stseq, stiter;
        //SymSet factstart, factiter, mulops;
        //SymSet addops, signs, relops;

        // Desk. pozorne - wykorzystywane w funkcji Search()
        // w przypadku odwołania do niezdefiniowanej nazwy
        void NextToken(); // Następny symbol
        //Token* Peek(unsigned int position);
        void accept(TokenType tokenType);
        void SyntaxErrorWithExpectedToken(TokenType tokenType); // Oczekiwany token
        void SyntaxErrorWithUnexpectedToken(Token *token); // Nieoczekiwany token
        void SyntaxErrorWithExpectedTokens(vector<TokenType> *tokenList);
        void SemanticError(int errorCode, bool displayCurrentTokenPosition);

        // PROCEDURY ROZBIORU
        //void parseFunctionsPart();
        DeclarationStatement* parseDeclarationStatement();
        FunctionDeclaration* parseFunctionDeclaration(TypeDescriptor *typeDescriptorPointer, string identifierName);
        vector<Variable*>* parseArguments();
        Variable* parseArgument();
        BlockStatement* parseBlockStatement(string identifierName, vector<Variable*> *argumentList);
        //TypeDescriptor* ReturnBlock(const IdentifierDescriptor *blockIdentifierDescriptor);
        //void parseVariablesPart();
        vector<VariableDeclaration*>* parseVariableDeclarations(TypeDescriptor* typeDescriptorPointer, string identifierName);
        TypeDescriptor* parseType();
        TypeDescriptor* parseMatrixType();
        TypeDescriptor* parseSimpleType();
        string parseIdentifier();
        //void parseStatementsPart();
        Statement* parseInstructions();
        Statement* parseStatement();
        Statement* parseSimpleStatement();
        Statement* parseIdentifierStatement();
        Statement* parseStructuredStatement();
        FunctionCallStatement* parseFunctionCallStatement(string identifierName);
        vector<Expression*>* parseParameters();
        ReturnStatement*  parseReturnStatement();
        IfStatement* parseIfStatement();
        WhileStatement* parseWhileStatement();
        Assignment* parseAssignment(string identifierName, TypeDescriptor *typeDescriptorPointer);
        ReadStatement* parseReadStatement();
        vector<Variable*>* parseInputVariables();
        WriteStatement* parseWriteStatement();
        vector<Expression*>* parseOutValues();
        //TypeDescriptor* parseConditionExpression();
        Expression* parseExpression();
        SimpleExpression* parseSimpleExpression();
        Term* parseTerm();
        Factor* parseFactor();
        Factor* parseNotFactor();
        Expression* parseParenthesizedExpression();
        bool parseIdentifierFactor(Variable **variablePointer,
            FunctionCallStatement **functionCallStatementPointer);
        Constant* parseConstant();
        Constant* parseIntegerConstant();
        Constant* parseMatrixConstant();
        Variable* parseVariable();
};

#endif // PARSER_H
