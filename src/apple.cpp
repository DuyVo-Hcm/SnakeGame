#include "apple.hpp"

Apple::Apple(deque<Vector2> snakeBody)
{
    Image image=LoadImage("ImageSnakegame/Apple.png");
    texture=LoadTextureFromImage(image);
    position=RandomPosNotinSnake(snakeBody);
}

Apple::~Apple()
{
    UnloadTexture(texture);
}

void Apple::Draw()
{
    DrawTexture(texture, position.x*cellSize, position.y*cellSize, WHITE);
}

Vector2 Apple::RandomPos()
{
    float x=GetRandomValue(0, cellCount-1);
    float y=GetRandomValue(0, cellCount-1);
    return Vector2{x, y};
}

Vector2 Apple::RandomPosNotinSnake(deque<Vector2> snakeBody)
{
    Vector2 position=RandomPos();
    while(ElementInDeque(position, snakeBody)) position=RandomPos();
    return position;
}