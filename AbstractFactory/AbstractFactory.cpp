// AbstractFactory.cpp : Defines the entry point for the console application.
//

#include "GoF.h"
#include "Variant1.h"

int main()
{
	{
		AbstractFactoryPattern::GoF::MazeGame game;
		AbstractFactoryPattern::GoF::BombedMazeFactory factory;
		game.CreateMaze(factory);
	}

	{
	}

    return 0;
}

