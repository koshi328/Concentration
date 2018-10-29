#include "BlockController.h"
#include <cstdio>

BlockController::BlockController()
{
}

BlockController::~BlockController()
{
    Dispose();
}
/*
* ‰Šú‰»
*/
void BlockController::Initialize(int height, int width)
{
    _width = width;
    _height = height;
    // ”z—ñ‚Ì‰Šú‰»
    blocks = new Block*[_height];
    for (int i = 0; i < _height; ++i)
    {
        blocks[i] = new Block[_width];
        // F‚ğİ’è
        char* color = colors[i % colorKind];
        for (int j = 0; j < _width; ++j)
        {
            blocks[i][j].SetColor(color);
        }
    }
}

/*
* ˆêŠ‡•`‰æ
*/
void BlockController::DrawBlocks()
{
    for (int i = 0; i < _height; ++i)
    {
        for (int j = 0; j < _width; ++j)
        {
            blocks[i][j].Draw();
        }
        printf("\n");
    }
}

/*
* ”jŠü
*/
void BlockController::Dispose()
{
    // ”z—ñ‚Ì‰ğ•ú
    for (int i = 0; i < _height; ++i)
    {
        delete[] blocks[i];
    }
}
