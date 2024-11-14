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
        Vector2 tail = bodySnake[bodySnake.size()-1]; 
        Vector2 secondToLast = bodySnake[bodySnake.size()-2]; 

        for(unsigned int i=0; i<bodySnake.size(); i++) 
        {
            float x=bodySnake[i].x;
            float y=bodySnake[i].y;
            Rectangle segment=Rectangle{x*cellSize, y*cellSize, (float)cellSize, (float)cellSize};
            DrawRectangleRounded(segment, 0.5, 6, darkGreen); 
        }

        for(unsigned int i=1; i<bodySnake.size()-1; i++) 
        {
            if(bodySnake[i].x==bodySnake[i-1].x) 
            DrawTexture(bodyVerticalTexture, bodySnake[i].x*cellSize, bodySnake[i].y*cellSize, WHITE);
            
            if(bodySnake[i].y==bodySnake[i-1].y)
            DrawTexture(bodyHorizontalTexture, bodySnake[i].x*cellSize, bodySnake[i].y*cellSize, WHITE);
        }

        if(bodySnake[0].x>bodySnake[1].x) DrawTexture(rightHeadTexture, bodySnake[0].x*cellSize, bodySnake[0].y*cellSize-1, WHITE);
        else if(bodySnake[0].x<bodySnake[1].x) DrawTexture(leftHeadTexture, bodySnake[0].x*cellSize-9, bodySnake[0].y*cellSize-1, WHITE);
        else if(bodySnake[0].y<bodySnake[1].y) DrawTexture(upHeadTexture, bodySnake[0].x*cellSize-1, bodySnake[0].y*cellSize-9, WHITE);  
        else if(bodySnake[0].y>bodySnake[1].y) DrawTexture(downHeadTexture, bodySnake[0].x*cellSize-1, bodySnake[0].y*cellSize, WHITE);
 
 
        if(tail.x==secondToLast.x) 
        {
            if(tail.y<secondToLast.y)
                DrawTexture(upTailTexture, tail.x*cellSize, tail.y*cellSize, WHITE);
            else
                DrawTexture(downTailTexture, tail.x*cellSize, tail.y*cellSize, WHITE);
        }
        if(tail.y==secondToLast.y) 
        {
            if(tail.x<secondToLast.x)
                DrawTexture(leftTailTexture, tail.x*cellSize, tail.y*cellSize, WHITE);
            else
                DrawTexture(rightTailTexture, tail.x*cellSize, tail.y*cellSize, WHITE); 
        }

    }

    void Update()
    {   
        bodySnake.push_front(Vector2Add(bodySnake[0], direction));
        if (addSegment) addSegment = false;
        else bodySnake.pop_back();    
    }
};