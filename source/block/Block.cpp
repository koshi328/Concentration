#include "Block.h"
#include <cstdio>
#include <cstdlib>

Block::Block()
{
}

Block::~Block()
{
}

/*
* �F��ݒ�
*/
void Block::SetColor(char* colorCode)
{
    _colorCode = colorCode;
}

/*
* �`��
*/
void Block::Draw()
{
    if (_colorCode != nullptr)
    {
        printf(_colorCode);
        printf("��");
        printf("\x1b[31m");
    }
    else
    {
        printf("��");
    }
}
