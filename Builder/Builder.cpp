// Builder.cpp : Defines the entry point for the console application.
//

#include "GoF.h"
#include "Variant1.h"

#include <iostream>

int main()
{
	{
		BuilderPattern::GoF::Maze* maze;
		BuilderPattern::GoF::MazeGame game;
		BuilderPattern::GoF::StandardMazeBuilder builder;

		game.CreateMaze(builder);
		maze = builder.GetMaze();
	}

	{
		int rooms, doors;
		BuilderPattern::GoF::MazeGame game;
		BuilderPattern::GoF::CountingMazeBuilder builder;

		game.CreateMaze(builder);
		builder.GetCounts(rooms, doors);

		std::cout << "The maze has "
			<< rooms << " rooms and "
			<< doors << " doors" << std::endl;
	}
    return 0;
}

