#include <cstdio>
#include <cstdlib>
#include "BlockController.h"

using namespace std;
int main()
{
    // ��ʂ̃��Z�b�g
    system("cls");
    // �u���b�N�̊Ǘ��N���X
    BlockController blockCon;
    // �������i�����A���j
    blockCon.Initialize(6, 16);
    // �`��
    blockCon.DrawBlocks();

    // Enter�������܂őҋ@
    getchar();
    return 0;
}