#pragma once

namespace SingletonPattern::Variant1
{
	class IMazeFactory {};

	class MazeFactory : public IMazeFactory {
	public:
		static IMazeFactory* Instance();

		// existing interface goes here 
	protected:
		MazeFactory() {}
	private:
		static IMazeFactory* _instance;
	};

	IMazeFactory* MazeFactory::_instance = 0;

	class BombedMazeFactory : public IMazeFactory {};

	class EnchantedMazeFactory : public IMazeFactory {};

	IMazeFactory* MazeFactory::Instance() {
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
