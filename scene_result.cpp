#include "main.h"

ResultScene::ResultScene(int result_info[])
{
	// 画像読込
	img_button_a = LoadGraph("resources/images/button_a01.png");

	// マップアイコン読込用変数
	img_battle = LoadGraph("resources/images/maps/skeleton.png");
	img_event = LoadGraph("resources/images/maps/event.png");
	img_rest = LoadGraph("resources/images/maps/rest.png");
	img_anvil = LoadGraph("resources/images/maps/anvil.png");
	img_boss = LoadGraph("resources/images/maps/boss.png");

	//武器の画像読込
	img_sword = LoadGraph("resources/images/武器/片手剣.png");
	img_dagger = LoadGraph("resources/images/武器/短剣.png");
	img_great_sword = LoadGraph("resources/images/武器/大剣.png");
	img_question_mark = LoadGraph("resources/images/mark_question.png");
	img_spear = LoadGraph("resources/images/武器/槍.png");
	img_frail = LoadGraph("resources/images/武器/フレイル.png");
	img_book = LoadGraph("resources/images/武器/本.png");

	// ロゴ画像読込
	img_logo_result = LoadGraph("resources/images/Logo/UI/logo_result.png");
	img_logo_lv = LoadGraph("resources/images/Logo/UI/logo_lv.png");
	img_logo_title = LoadGraph("resources/images/Logo/UI/logo_title.png");
	img_logo_totaldamage = LoadGraph("resources/images/Logo/UI/logo_totaldamage.png");
	img_logo_dagger = LoadGraph("resources/images/Logo/WeaponName/logo_dagger_black.png");
	img_logo_sword = LoadGraph("resources/images/Logo/WeaponName/logo_sword_black.png");
	img_logo_greatsword = LoadGraph("resources/images/Logo/WeaponName/logo_greatsword_black.png");
	img_logo_spear = LoadGraph("resources/images/Logo/WeaponName/logo_spear_black.png");
	img_logo_frail = LoadGraph("resources/images/Logo/WeaponName/logo_frail_black.png");
	img_logo_book = LoadGraph("resources/images/Logo/WeaponName/logo_book_black.png");

	// 変数の初期化
	value = 180;

	// 武器1
	weapon1_info.type = result_info[0];
	weapon1_info.level = result_info[1];
	weapon1_info.damage = result_info[2];

	// 武器2
	weapon2_info.type = result_info[3];
	weapon2_info.level = result_info[4];
	weapon2_info.damage = result_info[5];

	// マップ情報
	map_info.battle_count = result_info[6];
	map_info.event_count = result_info[7];
	map_info.rest_count = result_info[8];
	map_info.anvil_count = result_info[9];
	map_info.boss_count = result_info[10];
}

ResultScene::~ResultScene()
{

}

Scene* ResultScene::update()
{
	// ブレンドモードのパラメータ
	if (value > 0)
	{
		value--;
	}
	else
	{
		value = 0;
	}

	// タイトルへ遷移
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS && value <= 0)
	{
		SoundManager::StopSoundBGMs();
		SoundManager::SetSoundBGMsPosition(0);
		SoundManager::PlaySoundSE("se_system_normal_decision");
		return new Title;
	}

	return this;
}

void ResultScene::draw() const
{
	// 背景色
	DrawBox(0, 0, 1280, 720, 0xa0a0a0, TRUE);

	DrawRotaGraph(640, 50, 0.45f, 0.0f, img_logo_result, TRUE);

	SetFontSize(35);
	DrawFormatString(10, 50, 0x000000, "到達したステージ");

	if (value <= 10)
	{
		DrawRotaGraph(1130, 685, 0.2f, 0.0f, img_button_a, TRUE);
		DrawRotaGraph(1200, 680, 0.15f, 0.0f, img_logo_title, TRUE);
	}

	// マップアイコン画像表示
	DrawRotaGraph(150, 150, 1.0f, 0.0f, img_battle, TRUE);
	DrawRotaGraph(150, 250, 1.0f, 0.0f, img_event, TRUE);
	DrawRotaGraph(150, 350, 1.0f, 0.0f, img_rest, TRUE);
	DrawRotaGraph(150, 450, 1.0f, 0.0f, img_anvil, TRUE);
	DrawRotaGraph(150, 550, 1.0f, 0.0f, img_boss, TRUE);
	
	// マップ情報
	SetFontSize(30);
	DrawFormatString(200, 135, 0x000000, "× %d",map_info.battle_count);
	DrawFormatString(200, 235, 0x000000, "× %d",map_info.event_count);
	DrawFormatString(200, 335, 0x000000, "× %d",map_info.event_count);
	DrawFormatString(200, 435, 0x000000, "× %d",map_info.anvil_count);
	DrawFormatString(200, 535, 0x000000, "× %d",map_info.boss_count);

	// 武器1情報表示
	DrawRotaGraph(860, 250, 0.2f, 0.0f, img_logo_lv, TRUE);
	DrawRotaGraph(915, 300, 0.2f, 0.0f, img_logo_totaldamage, TRUE);
	DrawFormatString(1050, 240, 0x000000, "%7d", weapon1_info.level);
	DrawFormatString(1050, 290, 0x000000, "%7d", weapon1_info.damage);

	// 武器2情報表示
	DrawRotaGraph(860, 500, 0.2f, 0.0f, img_logo_lv, TRUE);
	DrawRotaGraph(915, 550, 0.2f, 0.0f, img_logo_totaldamage, TRUE);
	DrawFormatString(1050, 490, 0x000000, "%7d", weapon2_info.level);
	DrawFormatString(1050, 540, 0x000000, "%7d", weapon2_info.damage);

	switch (weapon1_info.type)
	{
	case 0:			// 片手剣
		DrawRotaGraph(720, 240, 0.2f, 0.0f, img_sword, TRUE);
		DrawRotaGraph(885, 180, 0.25f, 0.0f, img_logo_sword, TRUE);
		break;
	case 1:		// 短剣
		DrawRotaGraph(720, 240, 0.17f, 0.0f, img_dagger, TRUE);
		DrawRotaGraph(870, 180, 0.25f, 0.0f, img_logo_dagger, TRUE);
		break;
	case 2:	// 大剣
		DrawRotaGraph(720, 240, 0.25f, 0.0f, img_great_sword, TRUE);
		DrawRotaGraph(870, 180, 0.25f, 0.0f, img_logo_greatsword, TRUE);
		break;
	default:
		DrawRotaGraph(720, 260, 0.15f, 0.0f, img_question_mark, TRUE);
		DrawFormatString(840, 200, 0x000000, "武器がありません");
		break;
	}

	// 武器2の画像
	switch (weapon2_info.type)
	{
	case 0:			// 槍
		DrawRotaGraph(720, 500, 0.25f, 0.0f, img_spear, TRUE);
		DrawRotaGraph(860, 430, 0.25f, 0.0f, img_logo_spear, TRUE);
		break;
	case 1:			// フレイル
		DrawRotaGraph(700, 500, 0.25f, 0.0f, img_frail, TRUE);
		DrawRotaGraph(900, 430, 0.25f, 0.0f, img_logo_frail, TRUE);
		break;
	case 2:			// 魔導書
		DrawRotaGraph(720, 500, 0.17f, 0.0f, img_book, TRUE);
		DrawRotaGraph(910, 430, 0.25f, 0.0f, img_logo_book, TRUE);
		break;
	default:
		DrawRotaGraph(720, 520, 0.15f, 0.0f, img_question_mark, TRUE);
		DrawFormatString(840, 450, 0x000000, "武器がありません");
		break;
	}

	//フェードの設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, value);

	//黒で塗りつぶし
	DrawBox(0, 0, 1280, 720, 0x000000, TRUE);

	//デフォルトに戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "カーソル位置: %d - %d", InputCtrl::GetMouseCursor().x, InputCtrl::GetMouseCursor().y);
#endif
}