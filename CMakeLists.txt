cmake_minimum_required(VERSION 3.15)
project(ex3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(ex3 commands/Commands.h main.cpp interpreter/Expression.h interpreter/ex1.h interpreter/ex1.cpp
        lexer/Lexer.h lexer/Lexer.cpp commands/Command.cpp commands/OpenServerCommand.cpp commands/ConnectCommand.cpp commands/DefineVarCommand.cpp commands/IfCommand.cpp commands/LoopCommand.cpp commands/SleepCommand.cpp commands/PrintCommand.cpp commands/SetVariableCommand.cpp)