#ifndef __BLOCK__
#define __BLOCK__

class Block
{
public:
    Block();
    ~Block();
    // 色を設定
    void SetColor(char* colorCode);
    // 描画
    void Draw();
private:
    // 色
    char* _colorCode;
};
#endif //__BLOCK__