#include "Pch.h"
#include "Window.h"
#include "Game.h"
#include "AssetManager.h"
#include "MainMenu.h"
#include "InstructionsScreen.h"

// ==== CONTROL DEFINES ====

//#define USE_WINMAIN // Uncomment to build as Windows Desktop Application
#define ESC_TO_CLOSE true // Window will close with escape key -> Good for Debugging

// =========================

#ifdef USE_WINMAIN
#include <windows.h>
#endif

namespace Application
{
    extern GameState nextState = GameState::Game; // TODO - Change to Main Menu // States Enum in Structs.h
}

#ifdef USE_WINMAIN
int WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
#else
int main(int argc, char* argv[])
#endif
{
    srand(time(NULL));
    GameState currentState = Application::nextState;

    AssetManager::Load();
    sf::Clock deltaTime;


    while (Window::GetIsOpen())
    {
        //START
        switch (currentState)
        {
        case GameState::MainMenu:
            MainMenu::Start();
            break;
        case GameState::Game:
            Game::Start();
            break;
        case GameState::Instructions:
            InstructionsScreen::Start();
            break;
        }

        deltaTime.restart();
        while (Window::GetIsOpen() && currentState == Application::nextState)
        {
            xe::InputSystem::Update(Window::UnWrap(), deltaTime.getElapsedTime().asSeconds(), ESC_TO_CLOSE);

            //UPDATE
            switch (currentState)
            {
            case GameState::MainMenu:
                MainMenu::Update(deltaTime.restart().asSeconds());
                break;
            case GameState::Game:
                Game::Update(deltaTime.restart().asSeconds());
                break;
            case GameState::Instructions:
                InstructionsScreen::Update(deltaTime.restart().asSeconds());
                break;
            }

            //DRAW
            Window::Clear();
            switch (currentState)
            {
            case GameState::MainMenu:
                MainMenu::Draw();
                break;
            case GameState::Game:
                Game::Draw();
                break;
            case GameState::Instructions:
                InstructionsScreen::Draw();
                break;
            }
            Window::Display();
        }

        //ON_DESTROY
        switch (currentState)
        {
        case GameState::MainMenu:
            MainMenu::OnDestroy();
            break;
        case GameState::Game:
            Game::OnDestroy();
            break;
        case GameState::Instructions:
            InstructionsScreen::OnDestroy();
            break;
        }
        currentState = Application::nextState;
    }
	return 0;
}