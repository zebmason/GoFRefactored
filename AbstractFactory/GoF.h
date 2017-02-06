#pragma once

namespace AbstractFactoryPattern::GoF
{
	enum CompassPoint
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
		void SetSide(CompassPoint, Wall*) {}
		void SetSide(CompassPoint, Door*) {}
	};
	class Maze {
	public:
		void AddRoom(Room*) {}
	};
	class Door {
	public:
		Door(Room* r1, Room* r2) {}
	};

	class MazeFactory {
	public:
		MazeFactory() {}

		virtual Maze* MakeMaze() const
		{
			return new Maze;
		}
		virtual Wall* MakeWall() const
		{
			return new Wall;
		}
		virtual Room* MakeRoom(int n) const
		{
			return new Room(n);
		}
		virtual Door* MakeDoor(Room* r1, Room* r2) const
		{
			return new Door(r1, r2);
		}
	};

	class MazeGame
	{
	public:
		Maze* CreateMaze(MazeFactory& factory);
	};

	Maze* MazeGame::CreateMaze(MazeFactory& factory) {
		Maze* aMaze = factory.MakeMaze();
		Room* r1 = factory.MakeRoom(1);
		Room* r2 = factory.MakeRoom(2);
		Door* aDoor = factory.MakeDoor(r1, r2);

		aMaze->AddRoom(r1);
		aMaze->AddRoom(r2);

		r1->SetSide(North, factory.MakeWall());
		r1->SetSide(East, aDoor);
		r1->SetSide(South, factory.MakeWall());
		r1->SetSide(West, factory.MakeWall());

		r2->SetSide(North, factory.MakeWall());
		r2->SetSide(East, factory.MakeWall());
		r2->SetSide(South, factory.MakeWall());
		r2->SetSide(West, aDoor);

		return aMaze;
	}

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

	class EnchantedMazeFactory : public MazeFactory {
	public:
		EnchantedMazeFactory() {}

		virtual Room* MakeRoom(int n)  const
		{
			return new EnchantedRoom(n, CastSpell());
		}

		virtual Door* MakeDoor(Room* r1, Room* r2)  const
		{
			return new DoorNeedingSpell(r1, r2);
		}

	protected:
		Spell* CastSpell() const { return nullptr; }
	};

	class BombedMazeFactory : public MazeFactory {
	public:
		BombedMazeFactory() {}

		Wall* MakeWall() const;

		Room* MakeRoom(int n) const;
	};

	class BombedWall : public Wall
	{};

	class RoomWithABomb : public Room
	{
	public:
		RoomWithABomb(int n) : Room(n) {}
	};

	Wall* BombedMazeFactory::MakeWall() const {
		return new BombedWall;
	}

	Room* BombedMazeFactory::MakeRoom(int n) const {
		return new RoomWithABomb(n);
	}

}
