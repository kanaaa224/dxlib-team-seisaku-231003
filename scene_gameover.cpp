#include "main.h"

GameOverScene::GameOverScene(weapon* weapon1, second_weapon* weapon2, Map* map)
{
	// 画像読込
	img_gameover = LoadGraph("resources/images/gameover.png");
	img_ghost = LoadGraph("resources/images/ghost.png");
	img_button_a = LoadGraph("resources/images/button_a01.png");
	img_logo_result = LoadGraph("resources/images/Logo/UI/logo_result.png");

	// 変数の初期化
	ghost_x = 750;
	ghost_y = 150;
	count = 0;

	value = 180;

	// 武器1情報
	result_info[0] = weapon1->GetWeaponType();
	result_info[1] = weapon1->GetWeaponLevel();
	result_info[2] = weapon1->GetTotalDamage();

	// 武器2情報
	result_info[3] = weapon2->GetWeaponType();
	result_info[4] = weapon2->GetWeaponLevel();
	result_info[5] = weapon2->GetTotalDamage();

	// マップ情報
	result_info[6] = map->GetBattleCount();
	result_info[7] = map->GetEventCount();
	result_info[8] = map->GetRestCount();
	result_info[9] = map->GetAnvilCount();
	result_info[10] = map->GetBossCount();
}

GameOverScene::~GameOverScene()
{
	DeleteGraph(img_gameover);
	DeleteGraph(img_ghost);
	DeleteGraph(img_button_a);
	DeleteGraph(img_logo_result);
}

Scene* GameOverScene::update()
{
	SoundManager::PlaySoundBGM("bgm_gameover");

	// ブレンドモードのパラメータ
	if (value > 0)
	{
		value--;
	}
	else
	{
		value = 0;
	}

	if (count < FPS_PERIOD)
	{
		count++;
	}
	else
	{
		count = 0;
	}

	// リザルトへ遷移
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS && value <= 0) {
		SoundManager::PlaySoundSE("se_system_normal_decision");
		return new ResultScene(result_info);
	}

	return this;
}

void GameOverScene::draw() const
{
	// 背景色
	DrawBox(0, 0, 1280, 720, 0xa0a0a0, TRUE);

	// テキスト表示
	SetFontSize(60);
	DrawFormatString(545, 515, 0x000000, "GAME OVER");
	
	// 画像表示
	DrawGraph(0, 0, img_gameover, TRUE);
	// sin( PI*2 / 周期 * Count ) * 振幅
	DrawGraph(ghost_x, ghost_y + sinf(M_PI * 2 / FPS_PERIOD * count) * 40, img_ghost, TRUE);

	if (value <= 10)
	{
		DrawRotaGraph(1130, 685, 0.2f, 0.0f, img_button_a, TRUE);
		DrawRotaGraph(1200, 680, 0.15f, 0.0f, img_logo_result, TRUE);
	}

	//フェードの設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, value);

	//黒で塗りつぶし
	DrawBox(0, 0, 1280, 720, 0x000000, TRUE);

	//デフォルトに戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}