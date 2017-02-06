#pragma once

namespace PrototypePattern::GoF
{
	enum Direction
	{
		North,
		South,
		East,
		West
	};
	class Door;
	class Wall {
	public:
		Wall* Clone() { return this; }
	};
	class Room {
	public:
		Room() {}
		Room(int n) {}
		void SetSide(Direction, Wall*) {}
		void SetSide(Direction, Door*) {}
	};
	class Maze {
	public:
		Maze() {}
		void AddRoom(Room*) {}
	};

	class MapSite {};

	class Door : public MapSite {
	public:
		Door() {}
		Door(const Door&);

		virtual void Initialize(Room*, Room*);
		virtual Door* Clone() const;

		virtual void Enter() {}
		Room* OtherSideFrom(Room*) { return nullptr; }
	private:
		Room* _room1;
		Room* _room2;
	};

	Door::Door(const Door& other) {
		_room1 = other._room1;
		_room2 = other._room2;
	}

	void Door::Initialize(Room* r1, Room* r2) {
		_room1 = r1;
		_room2 = r2;
	}

	Door* Door::Clone() const {
		return new Door(*this);
	}

	class BombedWall : public Wall {
	public:
		BombedWall() {}
		BombedWall(const BombedWall&);

		virtual Wall* Clone() const;
		bool HasBomb() {}
	private:
		bool _bomb;
	};

	BombedWall::BombedWall(const BombedWall& other) : Wall(other) {
		_bomb = other._bomb;
	}

	Wall* BombedWall::Clone() const {
		return new BombedWall(*this);
	}

	class MazeFactory {};

	class MazePrototypeFactory : public MazeFactory {
	public:
		MazePrototypeFactory(Maze*, Wall*, Room*, Door*);

		virtual Maze* MakeMaze() const { return nullptr; }
		virtual Room* MakeRoom(int) const { return nullptr; }
		virtual Wall* MakeWall() const;
		virtual Door* MakeDoor(Room*, Room*) const;

	private:
		Maze* _prototypeMaze;
		Room* _prototypeRoom;
		Wall* _prototypeWall;
		Door* _prototypeDoor;
	};

	MazePrototypeFactory::MazePrototypeFactory(
		Maze* m, Wall* w, Room* r, Door* d
	) {
		_prototypeMaze = m;
		_prototypeWall = w;
		_prototypeRoom = r;
		_prototypeDoor = d;
	}

	Wall* MazePrototypeFactory::MakeWall() const {
		return _prototypeWall->Clone();
	}

	Door* MazePrototypeFactory::MakeDoor(Room* r1, Room *r2) const {
		Door* door = _prototypeDoor->Clone();
		door->Initialize(r1, r2);
		return door;
	}

	class MazeGame
	{
	public:
		Maze* CreateMaze(MazeFactory& factory) { return nullptr; }
	};

}
