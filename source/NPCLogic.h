#ifndef NPC_LOGIC
#define NPC_LOGIC
#include <list>

namespace NPCLogic
{
	struct CardData
	{
		int w, h;
		int num;
		int mark;
		CardData(int w, int h, int num, int mark , float oblivionRate)
		{
			this->w = w;
			this->h = h;
			this->num = num;
			this->mark = mark;
			this->oblivionRate = oblivionRate;
			memoryRetention = 1.0f;
		}
		float oblivionRate;		// ñYãpó¶
		float memoryRetention;	// ãLâØï€éùó¶
	};
	struct Memory
	{
		std::list<CardData> cardData;
		int max;
		int min;
		Memory(int max, int min)
		{
			this->max = max;
			this->min = min;
		}
	};

	void RememberCard(Memory* memory, int w, int h, int num, int mark);
	void Oblivion(Memory* memory, float oblivionRate);
	bool SelectPairCard(Memory* memory, int* w1, int* h1, int* w2, int* h2);
	bool SelectMatchCard(Memory* memory, int num, int mark, int* w, int* h);
}

#endif // NPC_LOGIC