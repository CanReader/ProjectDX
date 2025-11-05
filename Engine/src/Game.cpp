#include "Game.h"
#include "Graphics.h"
#include "Object.h"
#include "Mesh.h"

Game::Game(std::shared_ptr<Graphics>& gfx) : gfx(gfx) {}

Game::~Game()
{
	gfx.reset();
}

void Game::BeginPlay()
{
	gfx->RegisterObject(std::make_shared<Object>("Triangle", new Mesh({
		{0.0f, 0.5f, 0.0f},
		{0.45f, -0.5f, 0.0f},
		{-0.45f, -0.5f, 0.0f}
	   }
	  )));
}

void Game::Update(float dt)
{
}
