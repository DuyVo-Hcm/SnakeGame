#include "snake.hpp"

Snake::Snake()
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
    topleftBodyTexture = LoadTexture("ImageSnakegame/body_topleft.png");
    toprightBodyTexture = LoadTexture("ImageSnakegame/body_topright.png");
    bottomleftBodyTexture = LoadTexture("ImageSnakegame/body_bottomleft.png");
    bottomrightBodyTexture = LoadTexture("ImageSnakegame/body_bottomright.png");
}

Snake::~Snake()
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
    UnloadTexture(topleftBodyTexture);
    UnloadTexture(toprightBodyTexture);
    UnloadTexture(bottomleftBodyTexture);
    UnloadTexture(bottomrightBodyTexture);
}

void Snake::Draw()
{
    Vector2 tail = bodySnake[bodySnake.size()-1]; 
    Vector2 secondToLast = bodySnake[bodySnake.size()-2]; 

    for(unsigned int i=0; i<bodySnake.size(); i++) 
    {
        float x=bodySnake[i].x;
        float y=bodySnake[i].y;
        Rectangle segment=Rectangle{offset + x*cellSize, offset + y*cellSize, (float)cellSize, (float)cellSize};
        DrawRectangleRounded(segment, 0.5, 6, darkGreen); 
    }

    for(unsigned int i=1; i<bodySnake.size()-1; i++) 
    {
        if(bodySnake[i-1].x==bodySnake[i+1].x)
        {
            DrawTexture(bodyVerticalTexture,offset +  bodySnake[i].x*cellSize, offset + bodySnake[i].y*cellSize, WHITE);
            continue;
        }
        if(bodySnake[i-1].y==bodySnake[i+1].y)
        {
            DrawTexture(bodyHorizontalTexture, offset + bodySnake[i].x*cellSize,offset + bodySnake[i].y*cellSize, WHITE);
            continue;
        }
        Vector2 a=bodySnake[i-1], b=bodySnake[i+1];
        if(a.x>b.x) std::swap(a, b);
        int control=a.x-b.x+a.y-b.y;
        if(control!=0)
        {
            if(a.x==bodySnake[i].x) DrawTexture(toprightBodyTexture,offset +  bodySnake[i].x*cellSize,offset +  bodySnake[i].y*cellSize, WHITE);
            else DrawTexture(bottomleftBodyTexture,offset +  bodySnake[i].x*cellSize,offset +  bodySnake[i].y*cellSize, WHITE);
        }
        else
        {
            if(a.x==bodySnake[i].x) DrawTexture(bottomrightBodyTexture,offset +  bodySnake[i].x*cellSize,offset +  bodySnake[i].y*cellSize, WHITE);
            else DrawTexture(topleftBodyTexture,offset +  bodySnake[i].x*cellSize,offset +  bodySnake[i].y*cellSize, WHITE);
        }
    }

    if(bodySnake[0].x>bodySnake[1].x) DrawTexture(rightHeadTexture,offset +  bodySnake[0].x*cellSize,offset +  bodySnake[0].y*cellSize, WHITE);
    else if(bodySnake[0].x<bodySnake[1].x) DrawTexture(leftHeadTexture,offset +  bodySnake[0].x*cellSize,offset +  bodySnake[0].y*cellSize, WHITE);
    else if(bodySnake[0].y<bodySnake[1].y) DrawTexture(upHeadTexture,offset +  bodySnake[0].x*cellSize,offset +  bodySnake[0].y*cellSize, WHITE);  
    else if(bodySnake[0].y>bodySnake[1].y) DrawTexture(downHeadTexture,offset +  bodySnake[0].x*cellSize,offset +  bodySnake[0].y*cellSize, WHITE);


    if(tail.x==secondToLast.x) 
    {
        if(tail.y<secondToLast.y)
            DrawTexture(upTailTexture, offset + tail.x*cellSize, offset + tail.y*cellSize, WHITE);
        else
            DrawTexture(downTailTexture,offset +  tail.x*cellSize, offset + tail.y*cellSize, WHITE);
    }
    if(tail.y==secondToLast.y) 
    {
        if(tail.x<secondToLast.x)
            DrawTexture(leftTailTexture,offset +  tail.x*cellSize,offset +  tail.y*cellSize, WHITE);
        else
            DrawTexture(rightTailTexture, offset + tail.x*cellSize,offset + tail.y*cellSize, WHITE); 
    }

}

void Snake::Update()
{   
    bodySnake.push_front(Vector2Add(bodySnake[0], direction));
    if (addSegment) addSegment = false;
    else bodySnake.pop_back();    
}

std::deque<Vector2> Snake::getbodySnake() {return bodySnake;}

void Snake::setAddSegment() {addSegment=true;}

Vector2 Snake::getDirection() {return direction;}

void Snake::setDirection(Vector2 direct) 
{
    this->direction=direct;
}