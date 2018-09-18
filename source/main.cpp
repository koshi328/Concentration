#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 神経衰弱のソース
#include "GameLogic.h"
#include "NPCLogic.h"

enum PlayMode
{
	Manual,
	Auto
};

struct Player
{
	PlayMode mode;
	int playerID;
	NPCLogic::Memory* memory;
	Player(PlayMode m, int id, NPCLogic::Memory* mem)
	{
		mode = m;
		playerID = id;
		memory = mem;
	}
};

// 前方宣言
void CardSelectWithManual(Player* player);
void CardSelectWithAuto(Player* player);

int main(void)
{
	// --------------------------------
	// 初期設定
	// --------------------------------
	GameLogic::Initialize(4, 6, 6);
	// シャッフル結果を固定ランダムにしたい場合は引数を任意の値にする
	GameLogic::Shuffle((unsigned)time(NULL));
	
	// Shuffleのシード値を定数にした場合に以降の処理のランダム性を高めるため
	srand((unsigned)time(NULL));

	// --------------------------------
	// Player系の処理は継承を使ってClass化する
	// --------------------------------
	int playerNum = 2;
	Player player1(PlayMode::Auto, 0, new NPCLogic::Memory(10, 5));
	Player player2(PlayMode::Auto, 0, new NPCLogic::Memory(10, 5));

	Player* entrant[2];
	entrant[0] = &player1;
	entrant[1] = &player2;
	int nowPlayerIndex = 0;
	// --------------------------------
	// ゲームループ
	// --------------------------------
	while (!GameLogic::CheckGameEnd())
	{
		// Playerを選択
		Player* player = entrant[nowPlayerIndex];

		do
		{
			if (player->mode == PlayMode::Manual)
			{
				CardSelectWithManual(player);
			}
			else if (player->mode == PlayMode::Auto)
			{
				CardSelectWithAuto(player);
			}
			// カードを確認して継続or終了
		} while (GameLogic::ConfirmMatchAndBind(1));

		// カードを閉じる
		GameLogic::Close();

		// プレイヤーを切り替える
		nowPlayerIndex = (nowPlayerIndex + 1) % playerNum;
	}

	system("pause");
	return 0;
}

/*
* 手動でのカード選択
*/
void CardSelectWithManual(Player* player)
{
	int w = 0, h = 0;
	// カードを閉じる
	GameLogic::Close();
	GameLogic::Show(player->playerID);
	// カードを選択
	do
	{
		printf("行を選択してください:");
		scanf_s("%d", &h);
		printf("\n列を選択してください:");
		scanf_s("%d", &w);
		printf("\n");
		system("pause>nul");
	} while (!GameLogic::Open(GameLogic::ConvertIndex(w, h)));
	GameLogic::Show(player->playerID);
	do
	{
		printf("行を選択してください:");
		scanf_s("%d", &h);
		printf("\n列を選択してください:");
		scanf_s("%d", &w);
		printf("\n");
	} while (!GameLogic::Open(GameLogic::ConvertIndex(w, h)));
	GameLogic::Show(player->playerID);
	system("pause");
}

/*
* 自動でのカード選択
*/
void CardSelectWithAuto(Player* player)
{
	// カード情報の記憶を忘れる
	NPCLogic::Oblivion(player->memory, 0.3f);
	// カードを閉じる
	GameLogic::Close();
	GameLogic::Show(player->playerID);
	// カードを選択
	int w1 = 0, h1 = 0, w2 = 0, h2 = 0;
	bool isSuccess = false;
	// 記憶したデータでマッチさせられた場合
	if (NPCLogic::SelectPairCard(player->memory, &w1, &h1, &w2, &h2))
	{
		isSuccess = true;
		isSuccess &= GameLogic::Open(GameLogic::ConvertIndex(w1, h1));
		isSuccess &= GameLogic::Open(GameLogic::ConvertIndex(w2, h2));
		// カード情報の記憶を忘れる
		NPCLogic::Oblivion(player->memory, 0.3f);
	}

	if(isSuccess == false)
	{
		GameLogic::Close();
		// ランダムで一枚目を決定
		int index = 0;
		GameLogic::Card* c;
		do
		{
			index = GameLogic::GetRandomCardIndex();
			 c = GameLogic::GetCard(index);
			// カードを開く
		} while (!GameLogic::Open(index));
		// カードを記憶
		GameLogic::ConvertWidthHeight(index, &w1, &h1);
		NPCLogic::RememberCard(player->memory, w1, h1, c->num, c->mark);
		do
		{
			// 開いたカードとマッチするカードを探す
			if (NPCLogic::SelectMatchCard(player->memory, c->num, c->mark, &w2, &h2))
			{
				index = GameLogic::ConvertIndex(w2, h2);
			}
			else
			{
				// 見つからなかった場合
				index = GameLogic::GetRandomCardIndex();
				GameLogic::ConvertWidthHeight(index, &w2, &h2);
			}
			c = GameLogic::GetCard(index);
			// カードを開く
		} while (!GameLogic::Open(index));

		// カードを記憶
		NPCLogic::RememberCard(player->memory, w2, h2, c->num, c->mark);
	}
	GameLogic::Show(player->playerID);
	system("pause");
}