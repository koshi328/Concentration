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
* êFÇê›íË
*/
void Block::SetColor(char* colorCode)
{
    _colorCode = colorCode;
}

/*
* ï`âÊ
*/
void Block::Draw()
{
    if (_colorCode != nullptr)
    {
        printf(_colorCode);
        printf("Å†");
        printf("\x1b[31m");
    }
    else
    {
        printf("Å†");
    }
}
