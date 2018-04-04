cmake_minimum_required(VERSION 3.9)
project(TICalc C)

set(CMAKE_C_STANDARD 11)

add_library(TICalc src/Library.c src/Library.h src/MathLib.c src/MathLib.h src/IO.c src/IO.h src/Main.c src/Simplifiers.c src/Simplifiers.h)