#include "Game.h"

Game::Game()
{
    SpriteRenderer::Initizialize();
    pad_1 = new Pad( { -2.75,0.0f }, { 0.15f,1.0f }, { 5.0f,2.0f }, { 1.0f,0.0f,0.0f,1.0f });
    pad_2 = new Pad( {  2.60,0.0f }, { 0.15f,1.0f }, { 5.0f,2.0f }, { 1.0f,0.0f,0.0f,1.0f });

    ball = new Ball( {  2.60f - 0.2f, 0.0f }, 0.2f, {-1.60,0.7}, { 0.0f,1.0f,0.0f,1.0f });

    game_over_texture = new Texture2D("game_over2.jpg");

}

Game::~Game()
{
    SpriteRenderer::ShutDown();

    delete game_over_texture;

    delete pad_1;
    delete pad_2;
    delete ball;
}

void Game::OnUpdate()
{
    if (game_state == GAME_ON) {
        SpriteRenderer::DrawSprite(*pad_1);
        SpriteRenderer::DrawSprite(*pad_2);
        SpriteRenderer::DrawSprite(*ball);

        OnPaddleBoundsCollision(pad_1);
        OnPaddleBoundsCollision(pad_2);
        MoveBall(ball);

    }
    else if(game_state == GAME_OVER)
    {
        OnGameOver();
    }
    std::cout << game_state<<std::endl;
}

void Game::OnGameOver()
{
    {
        SpriteRenderer::DrawQuadRaw(*game_over_texture);
        
    }
}

void Game::MoveBall(Gameobject* object)
{
    Ball* b = (Ball*)object;

    object->position += object->velocity * 0.0016f;

    object->OnUpdate(0.2f);

    OnBallPaddleCollision(object);
    OnBallBoundsCollision(object);
}

void Game::OnKeyPressed(GLFWwindow* window, int key, int action, int mod)
{
    float move_factor = 0.25f;
    if(game_state == GAME_ON)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }
        if (key == GLFW_KEY_W && action == GLFW_PRESS)
        {
            pad_1->position.y += move_factor;

        }
        if (key == GLFW_KEY_S && action == GLFW_PRESS)
        {
            pad_1->position.y -= move_factor;
        }
        if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        {
            pad_2->position.y += move_factor;
        }
        if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        {
            pad_2->position.y -= move_factor;
        }
    }
    else if (game_state == GAME_OVER)
    {
        if (key == GLFW_KEY_E && action == GLFW_PRESS)
        {
            game_state == GAME_ON;
        }
    }
    
}

bool Game::OnPaddleBoundsCollision(Gameobject* object)
{
    {
        if (object->position.y + object->size.y >= TOP_BOUND)
        {
            object->position.y = 1.1;
            return true;
        }
        if (object->position.y <= BOTTOM_BOUND)
        {
            object->position.y = -2.1;
            return true;
        }
    }
    return false;
}


void Game::OnBallPaddleCollision(Gameobject* object)
{
    auto obj = (Ball*)object;
    switch (player_turn)
    {
    case PLAYER_L:
    {
        if ((obj->center.y >= pad_1->position.y) && obj->center.y <= pad_1->position.y + pad_1->size.y)
        {
            if ((obj->center.x - obj->diameter / 2) <= pad_1->position.x + pad_1->size.x)
            {

                /*float pad_center_x = pad_1->position.x + (pad_1->size.y / 2.0f) + pad_1->size.x;
                float center_offset = (obj->center.x + (obj->diameter / 2)) - pad_center_x;
                float normalized_offset = center_offset / (pad_1->size.y / 2.0f);

                object->velocity.x *= normalized_offset * 2.0f;
                object->velocity.y = -1;

                object->velocity *= 1.05f;*/

                object->velocity.x *= -1;

                player_turn = PLAYER_R;
                std::cout << "Player L has hit\n";
            }
        }
        break;
    }
        
    case PLAYER_R:
    {
        if ((obj->center.y >= pad_2->position.y) && obj->center.y <= pad_2->position.y + pad_2->size.y)
        {
            if ((obj->center.x + obj->diameter / 2) >= pad_2->position.x)
            {

               /*float pad_center_x = pad_2->position.x + (pad_2->size.y / 2.0f);
                float center_offset = (obj->center.x + (obj->diameter / 2)) - pad_center_x;
                float normalized_offset = center_offset / (pad_2->size.y / 2.0f);

                object->velocity.x *= normalized_offset ;
                object->velocity.y -= 1;*/

                object->velocity.x *= -1;

                player_turn = PLAYER_L;
                std::cout << "Player R has hit\n";
            }
        }
        break;
    }
    default:
        break;
    }
    
}




void Game::OnBallBoundsCollision(Gameobject* object)
{
    auto& obj = *(Ball*)object;

    {
        if ((obj.center.x + obj.diameter / 2) >= RIGHT_BOUND)
        {
            std::cout << "Hit the right boundary\n";
            game_state = GAME_OVER;
        }

        if ((obj.center.x - obj.diameter / 2) <= LEFT_BOUND)
        {
            std::cout << "Hit the left boundary\n";
            game_state = GAME_OVER;
        }
    }

    {

        if ((obj.center.y + obj.diameter / 2) <= BOTTOM_BOUND + 0.1f)
        {
            object->velocity.y *= -1.0f;
        }
        if ((obj.center.y + obj.diameter / 2) >= TOP_BOUND)
        {
            object->velocity.y *= -1.0f;
        }
    }

}


