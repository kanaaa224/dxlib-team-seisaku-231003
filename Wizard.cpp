#include "Wizard.h"
#include "Common.h"
#include <math.h>
#include "inputCtrl.h"
#include"Stage.h"

Wizard::Wizard(int arrayNum, int WizardMaxNum)
{
	//画像読込
	img = LoadGraph("resources/images/enemy_tmp_images/wizard_sato.png");
	//変数の初期化
	hp = WIZARD_HP_MAX;
	damage = WIZARD_ATTAK_DAMAGE;
	location.x = 0;
	location.y = 0;
	vector.x = 0;
	vector.y = 0;

	respawnTimeCnt = 0;
	respawnTime = SetRespawnTime(arrayNum, WizardMaxNum);

	//リスポーンポイント決め
	SetRespawnPoint();
}

void Wizard::Update(int arrayNum, Player* player, weapon* w, Stage stage)
{

}

void Wizard::Draw(int arrayNum)
{

}

void Wizard::X()
{

}

void Wizard::Y()
{

}

float Wizard::GetWizardDamage()
{
	return damage;
}

