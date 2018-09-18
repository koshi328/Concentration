#include <stdlib.h>
#include "NPCLogic.h"
#include "GameLogic.h"

/*
* カードの位置と番号を記憶する
*/
void NPCLogic::RememberCard(Memory* memory, int w, int h, int num, int mark)
{
	if (memory->cardData.size() > memory->max)
	{
		memory->cardData.pop_back();
	}

	memory->cardData.push_front(CardData(w, h, num, mark , 0.9f));
}

/*
* 忘却率によって覚えたカードデータを忘れる
*/
void NPCLogic::Oblivion(Memory* memory, float threshold)
{	
	for (std::list<CardData>::iterator it = memory->cardData.begin();
		it != memory->cardData.end();)
	{
		if (memory->cardData.size() > memory->min)
		{
			it->memoryRetention *= it->oblivionRate;
		}

		if (it->memoryRetention < threshold ||
			GameLogic::GetCard(GameLogic::ConvertIndex(it->w, it->h))->owner != -1)
		{
			it = memory->cardData.erase(it);
			continue;
		}
		++it;
	}
}

/*
* ペアで覚えているカードを選択
*/
bool NPCLogic::SelectPairCard(Memory* memory, int* w1, int* h1, int* w2, int* h2)
{
	for (std::list<CardData>::iterator it1 = memory->cardData.begin();
		it1 != memory->cardData.end(); ++it1)
	{
		for (std::list<CardData>::iterator it2 = memory->cardData.begin();
			it2 != memory->cardData.end(); ++it2)
		{
			if (it1->num == it2->num && it1->mark != it2->mark)
			{
				*w1 = it1->w;
				*h1 = it1->h;
				*w2 = it2->w;
				*h2 = it2->h;
				it1->memoryRetention *= 0.0f;
				it2->memoryRetention *= 0.0f;
				return true;
			}
		}
	}

	return false;
}


/*
* 覚えているカードデータ等からカードを選択する
*/
bool NPCLogic::SelectMatchCard(Memory* memory, int num, int mark, int* w, int* h)
{
	for (std::list<CardData>::iterator it = memory->cardData.begin();
		it != memory->cardData.end(); ++it)
	{
		if (it->num == num && it->mark != mark)
		{
			*w = it->w;
			*h = it->h;
			it->memoryRetention = 1.0f;
			return true;
		}
	}

	return false;
}
