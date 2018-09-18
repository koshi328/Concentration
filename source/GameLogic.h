#ifndef GAME_LOGIC
#define GAME_LOGIC

#include <list>
namespace GameLogic
{
	/*
	* \‘¢‘Ì’è‹`
	*/
	struct Card
	{
		int mark;
		int num;
		bool isOpen;
		int owner;
	};

	// ŠÖ”éŒ¾
	bool Initialize(int useMark, int useNum, int w);
	void Shuffle(int seed);
	Card* GetCard(int index);
	bool Open(int index);
	void Close();
	bool ConfirmMatchAndBind(int owner);
	void Bind(int index1, int index2, int owner);
	void Show(int playerID);
	bool CheckGameEnd();
	void Finalize();
	int ConvertIndex(int w, int h);
	void ConvertWidthHeight(int index, int* w, int* h);
	void CanOpenIndexes(std::list<int>* indexes);
	int GetRandomCardIndex();
}
#endif // GAME_LOGIC