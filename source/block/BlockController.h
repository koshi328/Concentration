#ifndef __BLOCK_CONTROLLER__
#define __BLOCK_CONTROLLER__

#include "Block.h"

class BlockController
{
public:
    BlockController();
    ~BlockController();

    // ������
    void Initialize(int height, int width);
    // �ꊇ�`��
    void DrawBlocks();
    // �j��
    void Dispose();
private:
    int _width;
    int _height;
    Block** blocks;

    // �F��`
    static const int colorKind = 3;
    // [�F�̐�][������]
    // �������̓J���[�R�[�h�̕����ȏ�
    char colors[colorKind][10] =
    {
        "\x1b[32m",
        "\x1b[33m",
        "\x1b[34m"
    };
};
#endif //__BLOCK_CONTROLLER__