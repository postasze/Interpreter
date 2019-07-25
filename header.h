#ifndef HEADER_H
#define HEADER_H

#include <utility>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <climits>
#include <iomanip>
#include <map>
#include <queue>
#include <deque>
#include <vector>
#include <math.h>

#define TOKENS_QUANTIY 56
#define KEYWORDS_QUANTITY 14
#define MAX_CHARACTERS_IN_LINE 128
#define MAX_IDENTIFIER_LENGTH 64
#define TYPE_KINDS_QUANTITY 4
#define SHOWIDS 1

using namespace std;

class TypeDescriptor;
class IdentifierDescriptor;

/*class CompilationError
{
public:
    ErrorCode errorCode; // kod erroru
    string message; // przechowuje wiadomosc dotyczaca erroru
};*/

enum TokenType // Tokeny leksykalne, kody tokenów zgodne ze specyfikacją
{
    LeftParenthesis, RightParenthesis, LeftBracket, RightBracket, LeftCurlyBrace, RightCurlyBrace,
    Read, Write,
    While,
    If, Then, Else,
    NotOperator, AndOperator, OrOperator,
    Plus, Minus, Multiplication, Division, Exponentiation,
    DivOperator, ModOperator,
    MatrixToken, Of,
    Identifier,
    NaturalNumberConstant, LiteralConstant, MatrixConstant,
    LesserThanOperator, LesserOrEqualOperator, GreaterThanOperator, GreaterOrEqualOperator, InequityOperator, EquationOperator,
    AssignmentOperator,
    Semicolon, Colon,
    Period, Comma,
    At, Dollar, Percent, ExclamationMark, BackSlash, QuotationMark,
    Tabulation, NewLine, Space,
    OneLineComment, MultiLinesCommentStart, MultiLinesCommentEnd,
    BooleanKeyWord, IntegerKeyWord,
    ReturnKeyWord,
    EOT,
    Others,
};

enum TokenCategory
{
    TypeToken,
    AdditiveOperatorToken,
    MultiplicativeOperatorToken,
    RelativeOperatorToken,
    PunctuationToken,
    StatementToken,
    OtherToken,
};

enum ScanErrorCodes
{
    NaturalNumberTooBig,
    WrongNaturalNumber,
    WrongLiteralConstant,
    WrongMatrixConstant,
    WrongIdentifier,
    WrongComment,
    SyntacticError,
    ParsingError
};

enum SemanticErrorCodes
{
    HomonymDefinition,
    WrongMatrixRanges,
    NoIdentifierDefinition,
    IncompatibleTypesForExpressionAndVariable,
    IncompatibleTypesForOperands,
    WrongIdentifierKind,
    MainFunctionNotDefined,
    ExpressionResultNotBoolean,
    WrongTypesForFunctionAndReturnValue,
    VariableNotInitialized,
    NoReturnValue,
    WrongNumberOfFunctionParameters,
    WrongTypeForFunctionParameter,
};

enum TypeKind
{
    Integer,
    Boolean,
    Matrix,
    Procedure,
};

enum IdentifierKind // Rodzaje ident.(do łączenia operatorem |)
{
    VariableIdentifier = 1,
    ConstantIdentifier = 2,
    TypeIdentifier = 4,
    ProcedureIdentifier = 8,
    ProgramIdentifier = 16
};

extern string TokenStrings[TOKENS_QUANTIY];

extern string ScanErrors[];

extern string SemanticErrors[];

extern map<int, pair<TokenType, string>> KeyWordsMap;

extern string TypeKindStrings[TYPE_KINDS_QUANTITY];

unsigned int hashFunction(string word); // Funkcja mieszająca dla KeyWordsMap

int Compatible(TypeDescriptor *t1, TypeDescriptor *t2);

ostream& operator<<(ostream& os, const IdentifierDescriptor &identifierDescriptor);

#endif // HEADER_H

