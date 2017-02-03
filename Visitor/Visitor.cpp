// GoFRefactored.cpp : Defines the entry point for the console application.
//

#include "GoF.h"
#include "Variant1.h"

int main()
{
	{
		VisitorPattern::GoF::ElementA a;
		VisitorPattern::GoF::ElementB b;
		VisitorPattern::GoF::CompositeElement c;
		c.Add(&a);
		c.Add(&b);
		VisitorPattern::GoF::Visitor v;
		c.Accept(v);
		std::cout << std::endl;
	}

	{
		VisitorPattern::Variant1::ElementA a;
		VisitorPattern::Variant1::ElementB b;
		VisitorPattern::Variant1::CompositeElement c;
		c.Add(&a);
		c.Add(&b);
		VisitorPattern::Variant1::Visitor v;
		v.Visit(&c);
		std::cout << std::endl;
	}

	return 0;
}

