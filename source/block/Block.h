#ifndef __BLOCK__
#define __BLOCK__

class Block
{
public:
    Block();
    ~Block();
    // �F��ݒ�
    void SetColor(char* colorCode);
    // �`��
    void Draw();
private:
    // �F
    char* _colorCode;
};
#endif //__BLOCK__