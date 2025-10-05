#include "Game.h"

Game::Game(std::shared_ptr<Graphics>& gfx) : gfx(gfx) {}

Game::~Game()
{
	gfx.reset();
}

void Game::BeginPlay()
{
}

void Game::Update(float dt)
{
}

void Game::Render()
{
}

void Game::Run()
{
	//TODO: Handle delta timing
	Update(0);
	Render();
}
