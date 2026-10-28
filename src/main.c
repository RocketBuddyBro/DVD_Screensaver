#include "raylib.h"

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 600;

    // The invisible rectangle used for movement and collision detection.
    const float logoWidth = 170.0f;
    const float logoHeight = 86.0f;

    // Position is measured from the top-left corner of the window.
    float x = 120.0f;
    float y = 100.0f;

    // Velocity is measured in pixels per second.
    float velocityX = 300.0f;
    float velocityY = 210.0f;

    const Color logoColors[] = {
        RED, ORANGE, GOLD, GREEN, SKYBLUE, BLUE, PURPLE, PINK
    };
    const int colorCount = (int)(sizeof(logoColors) / sizeof(logoColors[0]));
    int colorIndex = 0;

    InitWindow(screenWidth, screenHeight, "DVD Screensaver - raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // GetFrameTime() makes movement consistent across different frame rates.
        float deltaTime = GetFrameTime();
        x += velocityX * deltaTime;
        y += velocityY * deltaTime;

        int bounced = 0;

        // Left and right walls.
        if (x < 0.0f)
        {
            x = 0.0f;
            velocityX = -velocityX;
            bounced = 1;
        }
        else if (x + logoWidth > (float)screenWidth)
        {
            x = (float)screenWidth - logoWidth;
            velocityX = -velocityX;
            bounced = 1;
        }

        // Top and bottom walls.
        if (y < 0.0f)
        {
            y = 0.0f;
            velocityY = -velocityY;
            bounced = 1;
        }
        else if (y + logoHeight > (float)screenHeight)
        {
            y = (float)screenHeight - logoHeight;
            velocityY = -velocityY;
            bounced = 1;
        }

        // Change the logo's colour whenever it hits a wall.
        if (bounced)
        {
            colorIndex = (colorIndex + 1) % colorCount;
        }

        Color logoColor = logoColors[colorIndex];

        BeginDrawing();
        ClearBackground((Color){ 8, 10, 20, 255 });

        // Draw a DVD-style wordmark using raylib's built-in font.
        DrawEllipseLines((int)(x + logoWidth / 2.0f),
                         (int)(y + logoHeight / 2.0f),
                         82.0f, 35.0f, logoColor);
        DrawText("DVD", (int)x + 32, (int)y + 5, 46, logoColor);
        DrawText("VIDEO", (int)x + 58, (int)y + 52, 15, logoColor);

        
        DrawText("Close the window or press ESC to exit", 20,
                 screenHeight - 32, 16, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
