#include "header.h"
#include "TypeDescriptor.h"
#include "MatrixType.h"
#include "IdentifierDescriptor.h"

string TokenStrings[TOKENS_QUANTIY] =
{
    "(", ")", "[", "]", "{", "}",
    "Read", "Write",
    "While",
    "If", "Then", "Else",
    "not", "and", "or",
    "+", "-", "*", "/", "^",
    "Div", "Mod",
    "Matrix", "Of",
    "Identifier",
    "NaturalNumber", "Literal constant", "Matrix constant",
    "<", "<=", ">", ">=", "!=", "==",
    "=",
    ";", ":",
    ".", ",",
    "@", "$", "%", "!", "\\", "\"",
    "Tabulation", "New line", "Space",
    "One line comment", "Multi lines comment start", "Multi lines comment end",
    "BooleanKeyWord", "IntegerKeyWord",
    "ReturnKeyWord",
    "End of text",
    "Others",
};

string ScanErrors[] =
{
    "Przekroczony zakres stalej liczbowej",
    "Bledna stała liczbowa",
    "Bledna stała literalna",
    "Bledna stała macierzowa",
    "Bledny identyfikator",
    "Bledny komentarz",
    "Blad syntaktyczny",
    "Blad parsowania",
};

string SemanticErrors[] =
{
    "Identyfikator o podanej nazwie juz istnieje",
    "Bledny zakres indeksow macierzy",
    "Brak definicji identyfikatora",
    "Niezgodnosc typow zmiennej i wyrazenia",
    "Niezgodnosc typow operandow",
    "Niewlasciwy typ identyfikatora",
    "Brak definicji funkcji main",
    "Wartosc zwrocona przez wyrazenie nie jest typu boolean",
    "Niezgodnosc typow funkcji i wartosci zwracanej przez funkcje",
    "Zmienna nie zostala zainicjalizowana",
    "Brak wartosci zwracanej",
    "Niewlasiciwa liczba parametrow funkcji",
    "Niewlasciwy typ parametru funkcji",
};

string TypeKindStrings[TYPE_KINDS_QUANTITY] =
{
    "Integer",
    "Boolean",
    "Matrix",
    "Procedure",
};

unsigned int hashFunction(string word)
{
    switch(word.length())
    {
    case 1:
        return word[0];
    case 2:
        return (word[0] << 8) + word[1];
    case 3:
        return (word[0] << 16) + (word[1] << 8) + word[2];
    default:
        return (word[0] << 24) + (word[1] << 16) + (word[2] << 8) + word[3];
    }
}

map<int, pair<TokenType, string>> KeyWordsMap {
    { hashFunction("read"), { Read, "read" } },
    { hashFunction("write"), { Write, "write" } },
    { hashFunction("while"), { While, "while" } },
    { hashFunction("if"), { If, "if" } },
    { hashFunction("then"), { Then, "then" } },
    { hashFunction("else"), { Else, "else" } } ,
    { hashFunction("not"), { NotOperator, "not" } },
    { hashFunction("and"), { AndOperator ,"and" } },
    { hashFunction("or"), { OrOperator, "or" } },
    { hashFunction("div"), { DivOperator, "div" } },
    { hashFunction("mod"), { ModOperator, "mod" } },
    { hashFunction("matrix"), { MatrixToken, "matrix" } },
    { hashFunction("of"), { Of, "of" } },
    { hashFunction("integer"), { IntegerKeyWord, "integer" } },
    { hashFunction("boolean"), { BooleanKeyWord, "boolean" } },
    { hashFunction("return"), { ReturnKeyWord, "return" } },
};

int Compatible(TypeDescriptor *t1, TypeDescriptor *t2)
{
    if(t1 == t2 || t1 == NULL || t2 == NULL)
        return 1;
    if(t1->typeKind == Matrix && t2->typeKind == Matrix)
        return (((MatrixType*)t1)->firstRange == ((MatrixType*)t2)->firstRange) &&
            (((MatrixType*)t1)->secondRange == ((MatrixType*)t2)->secondRange) &&
            Compatible(((MatrixType*)t1)->elementType,((MatrixType*)t2)->elementType);
    else
        return 0;
}

ostream& operator<<(ostream& os, const IdentifierDescriptor &identifierDescriptor)
{
    os << setw(10) << identifierDescriptor.name << ": ";
    if(identifierDescriptor.identifierType)
        identifierDescriptor.identifierType->Print();
    else
        cout<<"NULL";
    return os << '\n';
}
