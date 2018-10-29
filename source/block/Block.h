#ifndef __BLOCK__
#define __BLOCK__

class Block
{
public:
    Block();
    ~Block();
    // F‚ğİ’è
    void SetColor(char* colorCode);
    // •`‰æ
    void Draw();
private:
    // F
    char* _colorCode;
};
#endif //__BLOCK__