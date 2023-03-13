#include "Pch.h"
#include "Game.h"

#include "AssetManager.h"
#include "Window.h"

namespace Application
{
	extern GameState nextState; // Defined in CoreBuilder.cpp
}

Game& Game::Get()
{
	static Game instance;
	return instance;
}

Game::Game()
{
}

Game::~Game()
{
}

void Game::Start()
{
	//Escape to Go to Main Menu -v
	xe::InputSystem::Subscribe(xe::Key::Escape, xe::Pressed,
		std::bind(&Game::QuitToMain, &Get()), static_cast<void*>(&Get()));
	Get().fps.setCharacterSize(12);
	Get().fps.setFont(*AssetManager::GetFont("default"));
	Get().fps.setFillColor(sf::Color::White);


}

void Game::Update(const float& deltaTime)
{




	if (Get().showFPS)
	{
		std::string fpsStr = (deltaTime == 0) ? std::to_string(0) : std::to_string(static_cast<int>((1 / deltaTime) + 0.5f));
		Get().fps.setString(fpsStr);
	}
}

void Game::Draw()
{




	if (Get().showFPS)
	{
		Get().fps.setPosition({ Window::GetResolution().x - Get().fps.getLocalBounds().width, 0.f });
		Window::UnWrap()->draw(Get().fps);
	}
}

void Game::OnDestroy()
{


	xe::InputSystem::Unsubscribe(xe::Key::Escape, xe::Pressed, static_cast<void*>(&Get()));
	Window::SetCameraPosition({ 0.f, 0.f });
}

void Game::QuitToMain()
{
	Application::nextState = GameState::MainMenu;
}
