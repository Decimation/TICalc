cmake_minimum_required(VERSION 3.9)
project(TICalc C)

set(CMAKE_C_STANDARD 11)

add_library(TICalc src/Library.c src/Library.h src/MathLib.c src/MathLib.h src/IO.c src/IO.h src/Main.c src/Simplifiers.c src/Simplifiers.h src/Menu.c src/Menu.h src/Test.c src/Test.h src/Main.h src/Trigonometry.c src/Trigonometry.h src/Solvers.c src/Solvers.h src/Shapes.h src/Shapes.c src/Sequences.c src/Sequences.h src/RightTrig.c src/RightTrig.h src/Slope.c src/Slope.h src/TrigMath.c src/TrigMath.h src/GraphicsExt.c src/GraphicsExt.h src/Area.c src/Area.h src/SurfaceArea.c src/SurfaceArea.h src/Volume.c src/Volume.h src/Formulas.h src/Formulas.c)