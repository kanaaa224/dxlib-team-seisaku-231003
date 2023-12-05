#include "main.h"

ResultScene::ResultScene(int result_info[11])
{
	// 画像読込
	img_button_a = LoadGraph("resources/images/button_a01.png");

	// マップアイコン読込用変数
	img_battle = LoadGraph("resources/images/skeleton.png");
	img_event = LoadGraph("resources/images/event.png");
	img_rest = LoadGraph("resources/images/rest.png");
	img_anvil = LoadGraph("resources/images/anvil.png");
	img_boss = LoadGraph("resources/images/boss.png");

	//武器の画像読込
	img_sword = LoadGraph("resources/images/武器/片手剣.png");
	img_dagger = LoadGraph("resources/images/武器/短剣.png");
	img_great_sword = LoadGraph("resources/images/武器/大剣.png");
	img_question_mark = LoadGraph("resources/images/mark_question.png");
	img_spear = LoadGraph("resources/images/武器/槍.png");
	img_frail = LoadGraph("resources/images/武器/フレイル.png");
	img_book = LoadGraph("resources/images/武器/本.png");

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
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
	{
		SoundManager::StopSoundBGMs();
		return new Title;
	}

	return this;
}

void ResultScene::draw() const
{
	// 背景色
	DrawBox(0, 0, 1280, 720, 0xa0a0a0, TRUE);

	// 画像表示
	DrawRotaGraph(1150, 690, 0.2f, 0.0f, img_button_a, TRUE);

	// テキスト表示
	SetFontSize(60);
	DrawFormatString(550, 10, 0x000000, "RESULT");
	SetFontSize(20);
	DrawFormatString(1180, 680, 0x000000, "TITLE");

	DrawFormatString(10, 50, 0x000000, "縮小マップ");

	// マップ情報
	DrawRotaGraph(150, 150, 1.0f, 0.0f, img_battle, TRUE);
	DrawRotaGraph(150, 250, 1.0f, 0.0f, img_event, TRUE);
	DrawRotaGraph(150, 350, 1.0f, 0.0f, img_rest, TRUE);
	DrawRotaGraph(150, 450, 1.0f, 0.0f, img_anvil, TRUE);
	DrawRotaGraph(150, 550, 1.0f, 0.0f, img_boss, TRUE);

	SetFontSize(30);
	DrawFormatString(200, 135, 0x000000, "× %d",map_info.battle_count);
	DrawFormatString(200, 235, 0x000000, "× %d",map_info.event_count);
	DrawFormatString(200, 335, 0x000000, "× %d",map_info.event_count);
	DrawFormatString(200, 435, 0x000000, "× %d",map_info.anvil_count);
	DrawFormatString(200, 535, 0x000000, "× %d",map_info.boss_count);

	// 武器1情報表示
	DrawFormatString(850, 200, 0x000000, "Lv．               %d", weapon1_info.level);
	DrawFormatString(850, 250, 0x000000, "総ダメージ    %7d", weapon1_info.damage);

	// 武器2情報表示
	DrawFormatString(850, 450, 0x000000, "Lv．               %d", weapon2_info.level);
	DrawFormatString(850, 500, 0x000000, "総ダメージ    %7d", weapon2_info.damage);

	switch (weapon1_info.type)
	{
	case 0:			// 片手剣
		DrawRotaGraph(750, 215, 0.2f, 0.0f, img_sword, TRUE);
		DrawFormatString(850, 150, 0x000000, "片手剣");
		break;
	case 1:		// 短剣
		DrawRotaGraph(750, 215, 0.2f, 0.0f, img_dagger, TRUE);
		DrawFormatString(850, 150, 0x000000, "短剣");
		break;
	case 2:	// 大剣
		DrawRotaGraph(750, 215, 0.2f, 0.0f, img_great_sword, TRUE);
		DrawFormatString(850, 150, 0x000000, "大剣");
		break;
	default:
		DrawRotaGraph(750, 215, 0.15f, 0.0f, img_question_mark, TRUE);
		DrawFormatString(850, 150, 0x000000, "武器がありません");
		break;
	}

	// 武器2の画像
	switch (weapon2_info.type)
	{
	case 0:			// 槍
		DrawRotaGraph(750, 470, 0.2f, 0.0f, img_spear, TRUE);
		DrawFormatString(850, 400, 0x000000, "槍");
		break;
	case 1:			// フレイル
		DrawRotaGraph(750, 470, 0.2f, 0.0f, img_frail, TRUE);
		DrawFormatString(850, 400, 0x000000, "フレイル");
		break;
	case 2:			// 魔導書
		DrawRotaGraph(750, 470, 0.2f, 0.0f, img_book, TRUE);
		DrawFormatString(850, 400, 0x000000, "魔導書");
		break;
	default:
		DrawRotaGraph(750, 470, 0.15f, 0.0f, img_question_mark, TRUE);
		DrawFormatString(850, 400, 0x000000, "武器がありません");
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