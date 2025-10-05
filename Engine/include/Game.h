#ifndef _GAME_H_
#define _GAME_H_

#include <memory>


class Graphics;
class Object;
class Game
{
public:
	Game(std::shared_ptr<Graphics>& gfx);
	~Game();

	void BeginPlay();

	void Update(float dt);
	void Render();

	void Run();

private:
	std::shared_ptr<Graphics> gfx;

	bool isRunning = true;

};

#endif