# GoFRefactored
Examples from the GoF book Design Patterns and refactorings to remove dependencies after being analysed with [DeepEnds](https://github.com/zebmason/DeepEnds).
The C++ source code from the Visual Studio solution was parsed with libclang and a report produced via Doxygen.

## Visitor
The GoF example ([source code](https://github.com/zebmason/GoFRefactored/blob/master/Visitor/GoF.h)) has 4 cycles

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/Visitor/Images/gof.png)

which are removed, in variant1 ([source code](https://github.com/zebmason/GoFRefactored/blob/master/Visitor/Variant1.h)), by
* making ElementA and ElementB ignorant of the visitor
* splitting the visitor into an interface and an implementation

![Variant1](https://github.com/zebmason/GoFRefactored/raw/master/Visitor/Images/variant1.png)
