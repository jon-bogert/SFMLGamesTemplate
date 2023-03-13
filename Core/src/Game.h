#pragma once

class Game
{
	sf::Text fps;
	bool showFPS = true;



	static Game& Get();
	Game();

public:
	virtual ~Game();
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;

	static void Start();
	static void Update(const float& deltaTime);
	static void Draw();
	static void OnDestroy();

private:
	void QuitToMain();
};

