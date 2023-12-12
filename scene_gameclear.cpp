#include "main.h"

GameClearScene::GameClearScene(weapon* weapon1, second_weapon* weapon2, Map* map)
{
	// 画像読込
	img_gameclear = LoadGraph("resources/images/GameClear/gameclear.png");
	img_crown = LoadGraph("resources/images/GameClear/crown_01_gold_red.png");
	img_grail = LoadGraph("resources/images/GameClear/seihai_gold.png");
	img_player = LoadGraph("resources/images/player_images/Player_right50・50.png");
	img_button_a = LoadGraph("resources/images/button_a01.png");
	img_background = LoadGraph("resources/images/stageimage2.png");
	img_logo_result = LoadGraph("resources/images/Logo/UI/logo_result.png");

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

GameClearScene::~GameClearScene()
{

}

Scene* GameClearScene::update()
{
	SoundManager::PlaySoundBGM("bgm_gameclear");

	// ブレンドモードのパラメータ
	if (value > 0)
	{
		value--;
	}
	else
	{
		value = 0;
	}

	// リザルトへ遷移
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS && value <= 0) {
		SoundManager::PlaySoundSE("se_system_normal_decision");
		return new ResultScene(result_info);
	}

	return this;
}

void GameClearScene::draw() const
{
	// 背景色
	DrawBox(0, 0, 1280, 720, 0xa0a0a0, TRUE);
	//DrawBox(0, 0, 1280, 720, 0x68030c, TRUE);
	//DrawGraph(0, 0, img_background, TRUE);

	// テキスト表示
	SetFontSize(60);
	DrawFormatString(530, 515, 0x000000, "GAME CLEAR");

	// 画像表示
	//DrawGraph(0, 0, img_gameclear, TRUE);
	DrawRotaGraph(650, 350, 3.0f, 0.0f, img_player, TRUE);
	DrawRotaGraph(640, 180, 0.15f, 0.0f, img_crown, TRUE);
	DrawRotaGraph(480, 545, 0.1f, 0.0f, img_grail, TRUE);

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

#ifdef _DEBUG
//	DrawFormatString(0, 0, 0xffffff, "カーソル位置: %d - %d", InputCtrl::GetMouseCursor().x, InputCtrl::GetMouseCursor().y);
#endif
}
