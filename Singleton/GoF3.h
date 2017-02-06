#pragma once

#include <list>

namespace SingletonPattern::GoF3
{
	class MazeFactory {
	public:
		static MazeFactory* Instance();

		// existing interface goes here 
	protected:
		MazeFactory() {}
	private:
		static MazeFactory* _instance;
	};

	MazeFactory* MazeFactory::_instance = 0;

	class BombedMazeFactory : public MazeFactory {};

	class EnchantedMazeFactory : public MazeFactory {};

	MazeFactory* MazeFactory::Instance() {
		if (_instance == 0) {
			const char* mazeStyle = getenv("MAZESTYLE");

			if (strcmp(mazeStyle, "bombed") == 0) {
				_instance = new BombedMazeFactory;

			}
			else if (strcmp(mazeStyle, "enchanted") == 0) {
				_instance = new EnchantedMazeFactory;

				// ... other possible subclasses 

			}
			else {        // default 
				_instance = new MazeFactory;
			}
		}
		return _instance;
	}
}
