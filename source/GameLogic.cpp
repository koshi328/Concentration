#include <stdio.h>
#include <stdlib.h>
#include "GameLogic.h"

using namespace GameLogic;
/*
* グローバル変数(クラス化する際にメンバ変数に変更)
*/
int MaxCardNum;	// カードの最大数
Card* card;		// カード一覧
int width, height;

/*
* Gameシステムの初期化処理
*/
bool GameLogic::Initialize(int useMark, int useNum, int w)
{
	MaxCardNum = useMark * useNum;
	width = w;
	height = MaxCardNum / width + 1;
	// ゲームが成立しない引数なら処理しない
	if (MaxCardNum <= 0 || useNum >= 14 || useMark >= 5)
	{
		printf("ゲームが成立しないカード枚数です");
		return false;
	}

	card = new Card[MaxCardNum];
	for (int i = 0; i < useMark; i++)
	{
		for (int j = 0; j < useNum; j++)
		{
			int index = (i * useNum) + j;
			card[index].mark = i;
			card[index].num = j + 1;
			card[index].isOpen = false;
			card[index].owner = -1;
		}
	}

	return true;
}

/*
* カード配列の中身をランダムに入れ替える
*/
void GameLogic::Shuffle(int seed)
{
	// 乱数の設定
	srand(seed);

	// スワップ処理
	for (int i = 0; i < MaxCardNum; i++)
	{
		int changeIndex = rand() % MaxCardNum;
		if (changeIndex == i)
		{
			continue;
		}
		Card tmp = card[i];
		card[i] = card[changeIndex];
		card[changeIndex] = tmp;
	}
}
/*
* 指定番号のカードを取得
*/
Card* GameLogic::GetCard(int index)
{
	if (index < 0 || index > MaxCardNum)
	{
		return nullptr;
	}
	return &card[index];
}

/*
* 指定番号のカードを開く
*/
bool GameLogic::Open(int index)
{
	Card* c = GetCard(index);
	if (c == nullptr || c->owner != -1)
	{
		printf("指定番号のカードは存在しません。\n");
		return false;
	}
	if (c->isOpen == true)
	{
		printf("指定番号のカードは既に開かれています。\n");
		return false;
	}

	c->isOpen = true;
	return true;
}

/*
* すべてのカードを閉じる
*/
void GameLogic::Close()
{
	for (int i = 0; i < MaxCardNum; i++)
	{
		card[i].isOpen = false;
	}
}

/*
* 開かれたカードが一致するか確認し、一致する場合は所有者を確定する
*/
bool GameLogic::ConfirmMatchAndBind(int owner)
{
	bool isMatch = false;
	// 開かれているカード一覧を取得
	std::list<int> openIndexes;
	for (int i = 0; i < MaxCardNum; i++)
	{
		// チェック対象外
		if (!card[i].isOpen || card[i].owner != -1)
		{
			continue;
		}
		openIndexes.push_back(i);
	}

	// TODO: 最適化したい
	// 一致を探してバインドする
	for (int i : openIndexes)
	{
		for (int j : openIndexes)
		{
			if (i == j ||				// 同一カード
				card[i].owner != -1 ||	// Bindされた
				card[j].owner != -1)	// Bindされた
			{
				continue;
			}
			if (card[i].num == card[j].num)
			{
				Bind(i, j, owner);
				isMatch = true;
			}
		}
	}
	return isMatch;
}

/*
* 所有者を確定する
*/
void GameLogic::Bind(int index1, int index2, int owner)
{
	Card* c1 = GetCard(index1);
	Card* c2 = GetCard(index2);

	if (c1 == nullptr || c2 == nullptr)
	{
		return;
	}

	c1->owner = owner;
	c2->owner = owner;
}

/*
* 現在のカード状態を表示する
*/
void GameLogic::Show(int playerID)
{
	system("cls");
	for (int i = 0; i < height; i++)
	{
		printf("\x1b[31m");// 文字色変更
		printf("--");
		for (int j = 0; j < width; j++)
		{
			printf("-%02d-", j);
		}
		printf("\n%02d", i);
		printf("\x1b[37m");
		for (int j = 0; j < width; j++)
		{
			int index = ConvertIndex(j, i);
			if (index >= MaxCardNum)
			{
				printf("    ");
				continue;
			}
			char markIcon;
			switch (card[index].mark)
			{
			case 0:markIcon = 'H'; break;
			case 1:markIcon = 'S'; break;
			case 2:markIcon = 'C'; break;
			case 3:markIcon = 'D'; break;
			}
			if (card[index].isOpen)
			{
				printf("\x1b[33m");
				printf("|%c%d|", markIcon, card[index].num);
				printf("\x1b[37m");
			}
			else if(card[index].owner != -1)
			{
				printf("|  |");
			}
			else
			{
				printf("|□|");
			}
		}
		printf("\n");
		printf("\x1b[31m");
		for (int j = 0; j < width; j++)
		{
			printf("----");
		}
		printf("--");
		printf("\x1b[37m");
		printf("\n");
	}

	printf("現在は%d番のプレイヤーの番です\n",playerID);
}

/*
* ゲームが終了したかを判定
* <return> true : 終了
*/
bool GameLogic::CheckGameEnd()
{
	for (int i = 0; i < MaxCardNum; i++)
	{
		if (card[i].owner == -1)
		{
			return false;
		}
	}
	return true;
}

/*
* 終了処理
*/
void GameLogic::Finalize()
{
	delete[] card;
}


/*
* WidthとHeightをIndexに変換
*/
int GameLogic::ConvertIndex(int w, int h)
{
	return (h * width) + w;
}

/*
* IndexをWidthHeightに変換
*/
void GameLogic::ConvertWidthHeight(int index, int* w, int* h)
{
	*h = index / width;
	*w = index % width;
}

void GameLogic::CanOpenIndexes(std::list<int>* indexes)
{
	for (int i = 0; i < MaxCardNum; i++)
	{
		if (!card[i].isOpen && card[i].owner == -1)
		{
			indexes->push_back(i);
		}
	}
}

int GameLogic::GetRandomCardIndex()
{
	static int offset = 0;
	std::list<int> indexes;
	for (int i = 0; i < MaxCardNum; i++)
	{
		if (!card[i].isOpen && card[i].owner == -1)
		{
			indexes.push_back(i);
		}
	}
	++offset;
	return *std::next(indexes.begin(), (rand() + offset) % indexes.size());
}