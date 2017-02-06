#pragma once

namespace FactoryMethodPattern::GoF
{
	enum Direction
	{
		North,
		South,
		East,
		West
	};
	class Door;
	class Wall {};
	class Room {
	public:
		Room(int n) {}
		void SetSide(Direction, Wall*) {}
		void SetSide(Direction, Door*) {}
	};
	class Maze {
	public:
		Maze() {}
		void AddRoom(Room*) {}
	};
	class Door {
	public:
		Door(Room* r1, Room* r2) {}
	};

	class MazeGame {
	public:
		Maze* CreateMaze();

		// factory methods: 

		virtual Maze* MakeMaze() const
		{
			return new Maze;
		}
		virtual Room* MakeRoom(int n) const
		{
			return new Room(n);
		}
		virtual Wall* MakeWall() const
		{
			return new Wall;
		}
		virtual Door* MakeDoor(Room* r1, Room* r2) const
		{
			return new Door(r1, r2);
		}
	};

	Maze* MazeGame::CreateMaze() {
		Maze* aMaze = MakeMaze();

		Room* r1 = MakeRoom(1);
		Room* r2 = MakeRoom(2);
		Door* theDoor = MakeDoor(r1, r2);

		aMaze->AddRoom(r1);
		aMaze->AddRoom(r2);

		r1->SetSide(North, MakeWall());
		r1->SetSide(East, theDoor);
		r1->SetSide(South, MakeWall());
		r1->SetSide(West, MakeWall());

		r2->SetSide(North, MakeWall());
		r2->SetSide(East, MakeWall());
		r2->SetSide(South, MakeWall());
		r2->SetSide(West, theDoor);

		return aMaze;
	}

	class BombedWall : public Wall
	{};

	class RoomWithABomb : public Room
	{
	public:
		RoomWithABomb(int n) : Room(n) {}
	};

	class BombedMazeGame : public MazeGame {
	public:
		BombedMazeGame() {}

		virtual Wall* MakeWall() const
		{
			return new BombedWall;
		}

		virtual Room* MakeRoom(int n) const
		{
			return new RoomWithABomb(n);
		}
	};

	class Spell;

	class EnchantedRoom : public Room
	{
	public:
		EnchantedRoom(int n, Spell*)
			: Room(n) {}
	};

	class DoorNeedingSpell : public Door
	{
	public:
		DoorNeedingSpell(Room* r1, Room* r2)
			: Door(r1, r2) {}
	};

	class EnchantedMazeGame : public MazeGame {
	public:
		EnchantedMazeGame() {}

		virtual Room* MakeRoom(int n) const
		{
			return new EnchantedRoom(n, CastSpell());
		}

		virtual Door* MakeDoor(Room* r1, Room* r2) const
		{
			return new DoorNeedingSpell(r1, r2);
		}
	protected:
		Spell* CastSpell() const { return nullptr; };
	};
}
