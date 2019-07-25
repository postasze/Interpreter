TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    Argument.cpp \
    Assignment.cpp \
    BlockStatement.cpp \
    Constant.cpp \
    DeclarationStatement.cpp \
    Expression.cpp \
    Factor.cpp \
    Function.cpp \
    FunctionCallStatement.cpp \
    FunctionDeclaration.cpp \
    header.cpp \
    IdentifierDescriptor.cpp \
    IfStatement.cpp \
    Interpreter.cpp \
    Main.cpp \
    MatrixType.cpp \
    Parameter.cpp \
    Parser.cpp \
    ReadStatement.cpp \
    ReturnStatement.cpp \
    Scanner.cpp \
    Scope.cpp \
    SimpleExpression.cpp \
    Source.cpp \
    Statement.cpp \
    Term.cpp \
    TextPosition.cpp \
    Token.cpp \
    TypeDescriptor.cpp \
    Value.cpp \
    Variable.cpp \
    VariableDeclaration.cpp \
    WhileStatement.cpp \
    WriteStatement.cpp

HEADERS += \
    Argument.h \
    Assignment.h \
    BlockStatement.h \
    Constant.h \
    DeclarationStatement.h \
    Expression.h \
    Factor.h \
    Function.h \
    FunctionCallStatement.h \
    FunctionDeclaration.h \
    header.h \
    IdentifierDescriptor.h \
    IfStatement.h \
    Interpreter.h \
    MatrixType.h \
    Parameter.h \
    Parser.h \
    ReadStatement.h \
    ReturnStatement.h \
    Scanner.h \
    Scope.h \
    SimpleExpression.h \
    Source.h \
    Statement.h \
    Term.h \
    TextPosition.h \
    Token.h \
    TypeDescriptor.h \
    Value.h \
    Variable.h \
    VariableDeclaration.h \
    WhileStatement.h \
    WriteStatement.h
