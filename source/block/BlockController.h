#ifndef __BLOCK_CONTROLLER__
#define __BLOCK_CONTROLLER__

#include "Block.h"

class BlockController
{
public:
    BlockController();
    ~BlockController();

    // 初期化
    void Initialize(int height, int width);
    // 一括描画
    void DrawBlocks();
    // 破棄
    void Dispose();
private:
    int _width;
    int _height;
    Block** blocks;

    // 色定義
    static const int colorKind = 3;
    // [色の数][文字数]
    // 文字数はカラーコードの文字以上
    char colors[colorKind][10] =
    {
        "\x1b[32m",
        "\x1b[33m",
        "\x1b[34m"
    };
};
#endif //__BLOCK_CONTROLLER__