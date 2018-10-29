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
* ������
*/
void BlockController::Initialize(int height, int width)
{
    _width = width;
    _height = height;
    // �z��̏�����
    blocks = new Block*[_height];
    for (int i = 0; i < _height; ++i)
    {
        blocks[i] = new Block[_width];
        // �F��ݒ�
        char* color = colors[i % colorKind];
        for (int j = 0; j < _width; ++j)
        {
            blocks[i][j].SetColor(color);
        }
    }
}

/*
* �ꊇ�`��
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
* �j��
*/
void BlockController::Dispose()
{
    // �z��̉��
    for (int i = 0; i < _height; ++i)
    {
        delete[] blocks[i];
    }
}
