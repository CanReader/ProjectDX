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
    gfx->RegisterObject(std::make_shared<Object>("Rectangle", new Mesh(
        {
            {-0.5f, 0.5f, 0.0f}, // Top left
            {0.5f, 0.5f, 0.0f}, // Top right
            {0.5f, -0.5f, 0.0f}, // Bottom right
            {-0.5f, -0.5f, 0.0f} // Bottom left
        },
        {
            0, 1, 2, // First triangle
            0, 2, 3 //Second triangle
        }
    )));
}

void Game::Update(float dt)
{
}
