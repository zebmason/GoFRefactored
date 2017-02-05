// Decorator.cpp : Defines the entry point for the console application.
//

#include "GoF.h"
#include "Variant1.h"

int main()
{
	{
		auto window = new DecoratorPattern::GoF::Window;
		auto textView = new DecoratorPattern::GoF::TextView;

		window->SetContents(textView);

		window->SetContents(
			new DecoratorPattern::GoF::BorderDecorator(
				new DecoratorPattern::GoF::ScrollDecorator(textView), 1
			)
		);
	}

	{
	}

    return 0;
}

