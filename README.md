# GoFRefactored
Examples from the GoF book Design Patterns and refactorings to remove dependencies after being analysed with [DeepEnds](https://github.com/zebmason/DeepEnds).

## Visitor
The GoF example has 4 cycles

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/Visitor/Images/gof.png)

which are removed by
* making ElementA and ElementB ignorant of the visitor
* splitting the visitor into an interface and an implementation

![Variant1](https://github.com/zebmason/GoFRefactored/raw/master/Visitor/Images/variant1.png)
