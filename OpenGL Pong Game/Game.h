#pragma once
#include "Pad.h"
#include "Ball.h"
#include "SpriteRenderer.h"
#include <GLFW/glfw3.h>


enum GAME_STATE
{
	GAME_ON,
	GAME_OVER,
};

enum PlayerTurn
{
	PLAYER_L,
	PLAYER_R
};

class Game
{
public:
	Game();
	~Game();

	void OnUpdate();
	void OnGameOver();

	void MoveBall(Gameobject* object);
	void OnKeyPressed(GLFWwindow* window, int key, int action, int mod);
	bool OnPaddleBoundsCollision(Gameobject* object);

	void OnBallPaddleCollision(Gameobject* object);
	void OnBallBoundsCollision(Gameobject* object);

public:
	Gameobject* pad_1;
	Gameobject* pad_2;
	Gameobject* ball;

	GAME_STATE game_state = GAME_ON;
	PlayerTurn player_turn = PLAYER_L;

private:
	Texture2D* game_over_texture;

	const float LEFT_BOUND = -2.75f;
	const float RIGHT_BOUND = 2.60f + 0.15f;
	const float TOP_BOUND = 2.1f;
	const float BOTTOM_BOUND = -2.0f;
};

