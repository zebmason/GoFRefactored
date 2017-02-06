// Strategy.cpp : Defines the entry point for the console application.
//

#include "GoF.h"
#include "Variant1.h"

int main()
{
	{
		auto quick = new StrategyPattern::GoF::Composition(new StrategyPattern::GoF::SimpleCompositor);
		auto slick = new StrategyPattern::GoF::Composition(new StrategyPattern::GoF::TeXCompositor);
		auto iconic = new StrategyPattern::GoF::Composition(new StrategyPattern::GoF::ArrayCompositor(100));
	}

	{
	}
    return 0;
}

