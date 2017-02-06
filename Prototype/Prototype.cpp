// Prototype.cpp : Defines the entry point for the console application.
//

#include "GoF.h"
#include "Variant1.h"

int main()
{
	{
		PrototypePattern::GoF::MazeGame game;
		PrototypePattern::GoF::MazePrototypeFactory simpleMazeFactory(
			new PrototypePattern::GoF::Maze, new PrototypePattern::GoF::Wall, new PrototypePattern::GoF::Room, new PrototypePattern::GoF::Door
		);

		PrototypePattern::GoF::Maze* maze = game.CreateMaze(simpleMazeFactory);
	}

	{
	}
    return 0;
}

