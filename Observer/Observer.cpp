// Observer.cpp : Defines the entry point for the console application.
//

#include "GoF.h"
#include "Variant1.h"

int main()
{
	{
		auto timer = new ObserverPattern::GoF::ClockTimer;
		auto analogClock = new ObserverPattern::GoF::AnalogClock(timer);
		auto digitalClock = new ObserverPattern::GoF::DigitalClock(timer);
	}

	{
	}
    return 0;
}

