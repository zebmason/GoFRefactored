# Dependencies in the Gang of Four examples

## Abstract
The example C++ code from the GoF (Gang of Four) book Design Patterns has had its dependencies analysed with [DeepEnds](https://github.com/zebmason/DeepEnds). 
Certain examples have been refactored to remove circular dependencies enabled by forward declaration of classes. These cycles in the graph serve to reduce
the ability to subsequently modify the code with ease.

## Introduction
[DeepEnds](https://github.com/zebmason/deepends)
 is distributed as both a [Visual Studio extension](https://visualstudiogallery.msdn.microsoft.com/4c9c5d41-46d2-409d-8c83-9d6d4d9e86bc?redir=0)
 and as a 
[NuGet package](https://www.nuget.org/packages/DeepEnds.Console/).
It creates a set of nested graphs from source code and calculates various statistics on the individual graphs.
These graphs and statistics are then saved in various formats, in this case
the C++ source code from the Visual Studio solution was parsed with libclang and a report produced via Doxygen.

DeepEnds takes an agnostic view as to how the dependencies originate. The libclang based parser does not differentiate 
between constructing classes by inheritance as opposed to composition, it also picks up usage within the contents of methods.
So it is also agnostic as to whether the code is object orientated, in fact the original C++ parser just parses the source 
files for include statements and nests the resulting nodes according to the corresponding Visual Studio filter. The include 
statement based parser is thus similar to the physical cycle based analysis of Bloomberg's waf verify tool. In fact if
the levelization technique of John Lakos has been applied to the code then the libclang based parser will execute more swiftly.

The source of the C++ example code has been extracted from the Gang of Four book and inserted into a Visual Studio project
for each Design Pattern. The code has been altered to ensure that it compiles and then all template definitions have been
transformed into normal classes to overcome a limitation of the parser. The output report has had various of its images
of the graphs taken for this article and, where it warns of a cycle in the graph, the corresponding example has been analysed
and potentially refactored. Cycles are observed in the graphs for

* Creational Patterns : [Singleton](./README.md#singleton)
* Structural Patterns : [Composite](./README.md#composite), [Facade](./README.md#facade)
* Behavioural Patterns : [Interpreter](./README.md#interpreter), [Mediator](./README.md#mediator), [Observer](./README.md#observer), [State](./README.md#state), [Visitor](./README.md#visitor)

## Creational Patterns

### AbstractFactory
The GoF example ([source code](https://github.com/zebmason/GoFRefactored/blob/master/AbstractFactory/GoF.h))
contains no cycles but is rather busy. To digress, a typical refactoring would create a Bombed namespace and place BombedMazeFactory,
BombedWall and RoomWithABomb into it. The resulting graph would then have those 3 classes replaced by one node representing
the namespace.

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/AbstractFactory/Images/GoF.png)

### Builder
The GoF example ([source code](https://github.com/zebmason/GoFRefactored/blob/master/Builder/GoF.h))

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/Builder/Images/GoF.png)

### FactoryMethod
The GoF example ([source code](https://github.com/zebmason/GoFRefactored/blob/master/FactoryMethod/GoF.h))

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/FactoryMethod/Images/GoF.png)

### Prototype
The GoF example ([source code](https://github.com/zebmason/GoFRefactored/blob/master/Prototype/GoF.h))

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/Prototype/Images/GoF.png)

### Singleton
The GoF examples ([first source code](https://github.com/zebmason/GoFRefactored/blob/master/Singleton/GoF.h),
[second](https://github.com/zebmason/GoFRefactored/blob/master/Singleton/GoF2.h),
[third](https://github.com/zebmason/GoFRefactored/blob/master/Singleton/GoF3.h))

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/Singleton/Images/GoF.png)

![GoF2](https://github.com/zebmason/GoFRefactored/raw/master/Singleton/Images/GoF2.png)

![GoF3](https://github.com/zebmason/GoFRefactored/raw/master/Singleton/Images/GoF3.png)

the cycle in the last graph may be removed by inserting an interface as shown in variant1 
([source code](https://github.com/zebmason/GoFRefactored/blob/master/Singleton/Variant1.h))

![Variant1](https://github.com/zebmason/GoFRefactored/raw/master/Singleton/Images/Variant1.png)

## Structural Patterns

### Adapter
The GoF example ([source code](https://github.com/zebmason/GoFRefactored/blob/master/Adapter/GoF.h))

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/Adapter/Images/GoF.png)

### Bridge
The GoF example ([source code](https://github.com/zebmason/GoFRefactored/blob/master/Bridge/GoF.h))

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/Bridge/Images/GoF.png)

### Composite
The GoF examples ([first source code](https://github.com/zebmason/GoFRefactored/blob/master/Composite/GoF.h),
[second](https://github.com/zebmason/GoFRefactored/blob/master/Composite/GoF2.h))

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/Composite/Images/GoF.png)

![GoF2](https://github.com/zebmason/GoFRefactored/raw/master/Composite/Images/GoF2.png)

the cycle in the first graph may be removed, in variant1
([source code](https://github.com/zebmason/GoFRefactored/blob/master/Composite/Variant1.h)),
by changing the GetComposite() command, which returns a Composite, to IsComposite() which returns a bool.

![Variant1](https://github.com/zebmason/GoFRefactored/raw/master/Composite/Images/Variant1.png)

### Decorator
The GoF example ([source code](https://github.com/zebmason/GoFRefactored/blob/master/Decorator/GoF.h))

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/Decorator/Images/GoF.png)

### Facade
The GoF example ([source code](https://github.com/zebmason/GoFRefactored/blob/master/Facade/GoF.h))

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/Facade/Images/GoF.png)

the cycle in the graph may be removed, in variant1
([source code](https://github.com/zebmason/GoFRefactored/blob/master/Facade/Variant1.h)),
because it only exists due to the use of the Visitor pattern.

![Variant1](https://github.com/zebmason/GoFRefactored/raw/master/Facade/Images/Variant1.png)

### Flyweight
The GoF example ([source code](https://github.com/zebmason/GoFRefactored/blob/master/Flyweight/GoF.h))

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/Flyweight/Images/GoF.png)

### Proxy
The GoF examples ([first source code](https://github.com/zebmason/GoFRefactored/blob/master/Proxy/GoF.h),
[second](https://github.com/zebmason/GoFRefactored/blob/master/Proxy/GoF2.h))

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/Proxy/Images/GoF.png)

![GoF2](https://github.com/zebmason/GoFRefactored/raw/master/Proxy/Images/GoF2.png)


## Behavioural Patterns

### ChainOfResponsibility
The GoF examples ([source code](https://github.com/zebmason/GoFRefactored/blob/master/ChainOfResponsibility/GoF.h),
[second](https://github.com/zebmason/GoFRefactored/blob/master/ChainOfResponsibility/GoF2.h))

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/ChainOfResponsibility/Images/GoF.png)

![GoF2](https://github.com/zebmason/GoFRefactored/raw/master/ChainOfResponsibility/Images/GoF2.png)

### Command
The GoF example ([source code](https://github.com/zebmason/GoFRefactored/blob/master/Command/GoF.h))

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/Command/Images/GoF.png)

### Interpreter
The GoF example ([source code](https://github.com/zebmason/GoFRefactored/blob/master/Interpreter/GoF.h))
contains one cycle

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/Interpreter/Images/GoF.png)

which is removed, in variant1 ([source code](https://github.com/zebmason/GoFRefactored/blob/master/Interpreter/Variant1.h)), by
defining an interface for the Context class.

![Variant1](https://github.com/zebmason/GoFRefactored/raw/master/Interpreter/Images/Variant1.png)

### Iterator
The GoF example ([source code](https://github.com/zebmason/GoFRefactored/blob/master/Iterator/GoF.h))

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/Iterator/Images/GoF.png)

### Mediator
The GoF example ([source code](https://github.com/zebmason/GoFRefactored/blob/master/Mediator/GoF.h))
contains one cycle

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/Mediator/Images/GoF.png)

which is removed, in variant1 ([source code](https://github.com/zebmason/GoFRefactored/blob/master/Mediator/Variant1.h)), by
defining an interface for the Widget class.

![Variant1](https://github.com/zebmason/GoFRefactored/raw/master/Mediator/Images/Variant1.png)

### Memento
The GoF examples ([first source code](https://github.com/zebmason/GoFRefactored/blob/master/Memento/GoF.h),
[second](https://github.com/zebmason/GoFRefactored/blob/master/Memento/GoF2.h))

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/Memento/Images/GoF.png)

![GoF2](https://github.com/zebmason/GoFRefactored/raw/master/Memento/Images/GoF2.png)

### Observer
The GoF example ([source code](https://github.com/zebmason/GoFRefactored/blob/master/Observer/GoF.h))
contains one cycle

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/Observer/Images/GoF.png)

which is removed, in variant1 ([source code](https://github.com/zebmason/GoFRefactored/blob/master/Observer/Variant1.h)), by
splitting the Subject class into two so that the data, which is subject to change, is accessible from the Observer.

![Variant1](https://github.com/zebmason/GoFRefactored/raw/master/Observer/Images/Variant1.png)

### State
The GoF example ([source code](https://github.com/zebmason/GoFRefactored/blob/master/State/GoF.h))
contains several cycles

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/State/Images/GoF.png)

which are removed, in variant1 ([source code](https://github.com/zebmason/GoFRefactored/blob/master/State/Variant1.h)), by defining
* an enumerant for the state
* a state holder which contains the objects representing the states and knows the current state

![Variant1](https://github.com/zebmason/GoFRefactored/raw/master/State/Images/Variant1.png)

### Strategy
The GoF example ([source code](https://github.com/zebmason/GoFRefactored/blob/master/Strategy/GoF.h))

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/Strategy/Images/GoF.png)

### TemplateMethod
The GoF example ([source code](https://github.com/zebmason/GoFRefactored/blob/master/TemplateMethod/GoF.h))

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/TemplateMethod/Images/GoF.png)

### Visitor
The GoF example ([source code](https://github.com/zebmason/GoFRefactored/blob/master/Visitor/GoF.h)) has 4 cycles

![GoF](https://github.com/zebmason/GoFRefactored/raw/master/Visitor/Images/gof.png)

which are removed, in variant1 ([source code](https://github.com/zebmason/GoFRefactored/blob/master/Visitor/Variant1.h)), by
* making ElementA and ElementB ignorant of the visitor
* splitting the visitor into an interface and an implementation

![Variant1](https://github.com/zebmason/GoFRefactored/raw/master/Visitor/Images/variant1.png)
