#include <windows.h>

unsigned int seed;

int left;
int top;
int width;
int height;

HDC screen;
HDC memoryX;
HDC memoryY;

HBITMAP bitmapX;
HBITMAP bitmapY;

unsigned int random()
{
    seed = seed * 1103515245 + 12345;
    return seed;
}

void tick()
{
    for (int i = 0; i < 100; i++)
    {
        int y = top + random() % (height - 25);
        int move = (random() % 150) + 1;

        if (random() & 1)
            move = -move;

        BitBlt(
            memoryX,
            0, 0,
            width, 25,
            screen,
            left, y,
            SRCCOPY
        );

        if (move > 0)
        {
            BitBlt(
                screen,
                left + move, y,
                width - move, 25,
                memoryX,
                0, 0,
                SRCCOPY
            );
        }
        else
        {
            BitBlt(
                screen,
                left, y,
                width + move, 25,
                memoryX,
                -move, 0,
                SRCCOPY
            );
        }
        int x = left + random() % (width - 25);
        move = (random() % 150) + 1;

        if (random() & 1)
            move = -move;

        BitBlt(
            memoryY,
            0, 0,
            25, height,
            screen,
            x, top,
            SRCCOPY
        );

        if (move > 0)
        {
            BitBlt(
                screen,
                x, top + move,
                25, height - move,
                memoryY,
                0, 0,
                SRCCOPY
            );
        }
        else
        {
            BitBlt(
                screen,
                x, top,
                25, height + move,
                memoryY,
                0, -move,
                SRCCOPY
            );
        }
    }
}

int main()
{
    seed = GetTickCount();

    left   = GetSystemMetrics(SM_XVIRTUALSCREEN);
    top    = GetSystemMetrics(SM_YVIRTUALSCREEN);
    width  = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    height = GetSystemMetrics(SM_CYVIRTUALSCREEN);

    screen = GetDC(NULL);

    memoryX = CreateCompatibleDC(screen);
    memoryY = CreateCompatibleDC(screen);

    bitmapX = CreateCompatibleBitmap(screen, width, 25);
    bitmapY = CreateCompatibleBitmap(screen, 25, height);

    SelectObject(memoryX, bitmapX);
    SelectObject(memoryY, bitmapY);

    while (true)
    {
        tick();
    }

    return 0;
}
