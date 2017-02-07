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

	class MapSite {
	public:
		virtual void Enter() = 0;
	};

	class Door;

	class Wall : public MapSite {
	public:
		Wall() {}
		virtual void Enter() {}
		Wall* Clone() { return this; }
	};

	class Room : public MapSite {
	public:
		Room() {}
		Room(int roomNo) {}
		MapSite* GetSide(Direction) const { return nullptr; }
		void SetSide(Direction, MapSite*) {}
		virtual void Enter() {}
	private:
		MapSite* _sides[4];
		int _roomNumber;
	};

	class Door : public MapSite {
	public:
		Door(Room* = 0, Room* = 0) {}
		Door(const Door&);
		virtual void Enter() {}
		Room* OtherSideFrom(Room*) {}
		virtual void Initialize(Room*, Room*);
		virtual Door* Clone() const;
	private:
		Room* _room1;
		Room* _room2;
		bool _isOpen;
	};

	class Maze {
	public:
		Maze() {}
		void AddRoom(Room*) {}
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
