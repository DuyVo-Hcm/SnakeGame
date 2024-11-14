#include <raylib.h>
#include <iostream>
#include <deque>
#include "raymath.h"
#include "button.hpp"
using namespace std;

int cellSize=30;
int cellCount=25;

Color darkGreen={20, 160, 133, 255}; 
Color Green= {20, 0, 0, 255};

double lastUpdateTime=0;
bool ElementInDeque(Vector2 element, deque<Vector2> deque)
{
    for(int i=0; i<deque.size(); i++)
    {
        if(Vector2Equals(deque[i], element))
        {
            return true;
        }
    }
    return false;
}

bool EventTriggered(double interval)
{
    double currentTime=GetTime();
    if(currentTime-lastUpdateTime>=interval)
    {
        lastUpdateTime=currentTime;
        return true;
    }
    return false;
}

class Snake
{
public:
    deque<Vector2> bodySnake = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};
    bool addSegment = false;

    Texture2D rightHeadTexture;
    Texture2D leftHeadTexture;
    Texture2D upHeadTexture;
    Texture2D downHeadTexture;
    Texture2D bodyHorizontalTexture;
    Texture2D bodyVerticalTexture;
    Texture2D rightTailTexture;
    Texture2D leftTailTexture;
    Texture2D upTailTexture;
    Texture2D downTailTexture;

    Snake()
    {
        rightHeadTexture = LoadTexture("ImageSnakegame/RightHead.png");
        leftHeadTexture = LoadTexture("ImageSnakegame/LeftHead.png");
        upHeadTexture = LoadTexture("ImageSnakegame/UpHead.png");
        downHeadTexture = LoadTexture("ImageSnakegame/DownHead.png");
        bodyHorizontalTexture = LoadTexture("ImageSnakegame/body_horizontal.png");
        bodyVerticalTexture = LoadTexture("ImageSnakegame/body_vertical.png");
        rightTailTexture = LoadTexture("ImageSnakegame/RightTail.png");
        leftTailTexture = LoadTexture("ImageSnakegame/LeftTail.png");
        upTailTexture = LoadTexture("ImageSnakegame/UpTail.png");
        downTailTexture = LoadTexture("ImageSnakegame/DownTail.png");

   
    }

    ~Snake()
    {
        UnloadTexture(rightHeadTexture);
        UnloadTexture(leftHeadTexture);
        UnloadTexture(upHeadTexture);
        UnloadTexture(downHeadTexture);
        UnloadTexture(bodyHorizontalTexture);
        UnloadTexture(bodyVerticalTexture);
        UnloadTexture(rightTailTexture);
        UnloadTexture(leftTailTexture);
        UnloadTexture(upTailTexture);
        UnloadTexture(downTailTexture);

    }

    void Draw()
    {
        Vector2 tail = bodySnake[bodySnake.size() - 1]; 
        Vector2 secondToLast = bodySnake[bodySnake.size() - 2]; 

        for (int i = 0; i < bodySnake.size(); i++) {
            float x = bodySnake[i].x;
            float y = bodySnake[i].y;
            Rectangle segment = Rectangle{x * cellSize, y * cellSize, (float)cellSize, (float)cellSize};
            DrawRectangleRounded(segment, 0.5, 6, darkGreen); 
        }

        for (int i = 1; i < bodySnake.size() -  1; i++) {
            if (bodySnake[i].x == bodySnake[i - 1].x) 
            DrawTexture(bodyVerticalTexture, bodySnake[i].x * cellSize, bodySnake[i].y * cellSize, WHITE);
            
            if (bodySnake[i].y == bodySnake[i - 1].y)
            DrawTexture(bodyHorizontalTexture, bodySnake[i].x * cellSize, bodySnake[i].y * cellSize, WHITE);
        }

        if      (bodySnake[0].x > bodySnake[1].x)   DrawTexture(rightHeadTexture, bodySnake[0].x * cellSize, bodySnake[0].y * cellSize - 1, WHITE);
        else if (bodySnake[0].x < bodySnake[1].x)   DrawTexture(leftHeadTexture, bodySnake[0].x * cellSize - 9, bodySnake[0].y * cellSize - 1, WHITE);
        else if (bodySnake[0].y < bodySnake[1].y)   DrawTexture(upHeadTexture, bodySnake[0].x * cellSize - 1, bodySnake[0].y * cellSize - 9, WHITE);  
        else if (bodySnake[0].y > bodySnake[1].y)   DrawTexture(downHeadTexture, bodySnake[0].x * cellSize - 1, bodySnake[0].y * cellSize, WHITE);
 
 
        if (tail.x == secondToLast.x) {
            if(tail.y < secondToLast.y)
                DrawTexture(upTailTexture, tail.x * cellSize , tail.y * cellSize, WHITE);
            else
                DrawTexture(downTailTexture, tail.x * cellSize , tail.y * cellSize, WHITE);
        }
        if (tail.y == secondToLast.y) {
            if(tail.x < secondToLast.x)
                DrawTexture(leftTailTexture, tail.x * cellSize , tail.y * cellSize, WHITE);
            else
                DrawTexture(rightTailTexture, tail.x * cellSize , tail.y * cellSize, WHITE); 
        }

    }
    void Update()
    {   
        bodySnake.push_front(Vector2Add(bodySnake[0], direction));
        if (addSegment) addSegment = false;
        else bodySnake.pop_back();    
    }
};

class Apple
{
public:
    Vector2 position;
    Texture2D texture;

    Apple(deque<Vector2> snakeBody)
    {
        Image image=LoadImage("ImageSnakegame/Apple.png");
        texture=LoadTextureFromImage(image);
        UnloadImage(image);
        position= RandomPos(snakeBody);
    }

    ~Apple()
    {
        UnloadTexture(texture);
    }

    void Draw()
    {
        DrawTexture(texture, position.x *cellSize, position.y *cellSize, WHITE);
    }

    Vector2 RandomPos(deque<Vector2> snakeBody)
    {
        float x=GetRandomValue(0, cellCount - 1);
        float y=GetRandomValue(0, cellCount - 1);
        return Vector2{x, y};
    }

    Vector2 RandomPosNotinSnake(deque<Vector2> snakeBody)
    {
        Vector2 position= RandomPos(snakeBody);
        while(ElementInDeque(position, snakeBody)) position=RandomPos(snakeBody);
        return position;
    }
};

class Game
{
public:
    Snake snake=Snake();
    Apple apple=Apple(snake.bodySnake);
    bool running=true;
    int score=0;

    void Draw()
    {
        snake.Draw();
        apple.Draw();
    }

    void Update()
    {
        if(running)
        {
            snake.Update();
            CheckCollisionWithFood();
            CheckCollisionWithEdges();
            CheckCollisionWithTail();
        }
    }

    void CheckCollisionWithFood()
    {
        if (Vector2Equals(snake.bodySnake[0], apple.position))
        {
            apple.position=apple.RandomPosNotinSnake(snake.bodySnake);
            snake.addSegment=true;
            score++;
        }
        
    }

    void CheckCollisionWithEdges()
    {
        if (snake.bodySnake[0].x==cellCount || snake.bodySnake[0].x==-1) running=false;
        if (snake.bodySnake[0].y==cellCount || snake.bodySnake[0].y==-1) running=false;
    }

    void CheckCollisionWithTail()
    {
        deque<Vector2> headlessBody=snake.bodySnake;
        headlessBody.pop_front();
        if(ElementInDeque(snake.bodySnake[0], headlessBody)) running=false;
    }
};

int main()
{


    InitWindow(cellSize *cellCount, cellSize * cellCount , "SNAKE GAME");
    SetTargetFPS(60);

    Apple apple = Apple();
    Snake snake = Snake();
    Game game = Game();
    Button startButton{{"ImageSnake/buttonplay.jpg"}, {300, 150}};
    Texture2D background = LoadTexture("ImageSnakegame/background.jpg");

    while (!WindowShouldClose())
    {
        DrawTexture(background, 0, 0, WHITE);
        BeginDrawing();
        if (EventTriggered(0.2)) game.Update();

        if(IsKeyPressed(KEY_RIGHT) && game.snake.direction.x!=-1) game.snake.direction={1, 0};

        ClearBackground(darkGreen);
        game.Draw();
        EndDrawing();
    }
    CloseWindow();
}
