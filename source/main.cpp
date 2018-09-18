#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// �_�o����̃\�[�X
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

// �O���錾
void CardSelectWithManual(Player* player);
void CardSelectWithAuto(Player* player);

int main(void)
{
	// --------------------------------
	// �����ݒ�
	// --------------------------------
	GameLogic::Initialize(4, 6, 6);
	// �V���b�t�����ʂ��Œ胉���_���ɂ������ꍇ�͈�����C�ӂ̒l�ɂ���
	GameLogic::Shuffle((unsigned)time(NULL));
	
	// Shuffle�̃V�[�h�l��萔�ɂ����ꍇ�Ɉȍ~�̏����̃����_���������߂邽��
	srand((unsigned)time(NULL));

	// --------------------------------
	// Player�n�̏����͌p�����g����Class������
	// --------------------------------
	int playerNum = 2;
	Player player1(PlayMode::Auto, 0, new NPCLogic::Memory(10, 5));
	Player player2(PlayMode::Auto, 0, new NPCLogic::Memory(10, 5));

	Player* entrant[2];
	entrant[0] = &player1;
	entrant[1] = &player2;
	int nowPlayerIndex = 0;
	// --------------------------------
	// �Q�[�����[�v
	// --------------------------------
	while (!GameLogic::CheckGameEnd())
	{
		// Player��I��
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
			// �J�[�h���m�F���Čp��or�I��
		} while (GameLogic::ConfirmMatchAndBind(1));

		// �J�[�h�����
		GameLogic::Close();

		// �v���C���[��؂�ւ���
		nowPlayerIndex = (nowPlayerIndex + 1) % playerNum;
	}

	system("pause");
	return 0;
}

/*
* �蓮�ł̃J�[�h�I��
*/
void CardSelectWithManual(Player* player)
{
	int w = 0, h = 0;
	// �J�[�h�����
	GameLogic::Close();
	GameLogic::Show(player->playerID);
	// �J�[�h��I��
	do
	{
		printf("�s��I�����Ă�������:");
		scanf_s("%d", &h);
		printf("\n���I�����Ă�������:");
		scanf_s("%d", &w);
		printf("\n");
		system("pause>nul");
	} while (!GameLogic::Open(GameLogic::ConvertIndex(w, h)));
	GameLogic::Show(player->playerID);
	do
	{
		printf("�s��I�����Ă�������:");
		scanf_s("%d", &h);
		printf("\n���I�����Ă�������:");
		scanf_s("%d", &w);
		printf("\n");
	} while (!GameLogic::Open(GameLogic::ConvertIndex(w, h)));
	GameLogic::Show(player->playerID);
	system("pause");
}

/*
* �����ł̃J�[�h�I��
*/
void CardSelectWithAuto(Player* player)
{
	// �J�[�h���̋L����Y���
	NPCLogic::Oblivion(player->memory, 0.3f);
	// �J�[�h�����
	GameLogic::Close();
	GameLogic::Show(player->playerID);
	// �J�[�h��I��
	int w1 = 0, h1 = 0, w2 = 0, h2 = 0;
	bool isSuccess = false;
	// �L�������f�[�^�Ń}�b�`������ꂽ�ꍇ
	if (NPCLogic::SelectPairCard(player->memory, &w1, &h1, &w2, &h2))
	{
		isSuccess = true;
		isSuccess &= GameLogic::Open(GameLogic::ConvertIndex(w1, h1));
		isSuccess &= GameLogic::Open(GameLogic::ConvertIndex(w2, h2));
		// �J�[�h���̋L����Y���
		NPCLogic::Oblivion(player->memory, 0.3f);
	}

	if(isSuccess == false)
	{
		GameLogic::Close();
		// �����_���ňꖇ�ڂ�����
		int index = 0;
		GameLogic::Card* c;
		do
		{
			index = GameLogic::GetRandomCardIndex();
			 c = GameLogic::GetCard(index);
			// �J�[�h���J��
		} while (!GameLogic::Open(index));
		// �J�[�h���L��
		GameLogic::ConvertWidthHeight(index, &w1, &h1);
		NPCLogic::RememberCard(player->memory, w1, h1, c->num, c->mark);
		do
		{
			// �J�����J�[�h�ƃ}�b�`����J�[�h��T��
			if (NPCLogic::SelectMatchCard(player->memory, c->num, c->mark, &w2, &h2))
			{
				index = GameLogic::ConvertIndex(w2, h2);
			}
			else
			{
				// ������Ȃ������ꍇ
				index = GameLogic::GetRandomCardIndex();
				GameLogic::ConvertWidthHeight(index, &w2, &h2);
			}
			c = GameLogic::GetCard(index);
			// �J�[�h���J��
		} while (!GameLogic::Open(index));

		// �J�[�h���L��
		NPCLogic::RememberCard(player->memory, w2, h2, c->num, c->mark);
	}
	GameLogic::Show(player->playerID);
	system("pause");
}