#include <cstdio>
#include <cstdlib>
#include "BlockController.h"

using namespace std;
int main()
{
    // 画面のリセット
    system("cls");
    // ブロックの管理クラス
    BlockController blockCon;
    // 初期化（高さ、幅）
    blockCon.Initialize(6, 16);
    // 描画
    blockCon.DrawBlocks();

    // Enterを押すまで待機
    getchar();
    return 0;
}