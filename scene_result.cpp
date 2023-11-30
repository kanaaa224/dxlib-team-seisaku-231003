#include "scene_result.h"

ResultScene::ResultScene()
{
	// 画像読込
	img_button_a = LoadGraph("resources/images/button_a01.png");

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

	// テスト
	fp = NULL;
	for (int i = 0; i < 2; i++)
	{
		sample[i] = { 0 };
	}
	is_fopen = false;

}

ResultScene::~ResultScene()
{

}

Scene* ResultScene::update()
{
	// テスト
	// ファイル読み込み
	fopen_s(&fp, "resources/dat/test.txt", "r");

	if (fp)
	{
		is_fopen = true;
		for (int i = 0; i < 2; i++)
		{
			int dammy = fscanf_s(fp, "%1d %1d %07d", &sample[i].type, &sample[i].level, &sample[i].damage);
		}
		//ファイルクローズ
		fclose(fp);
	}

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

	//DrawFormatString(700, 200, 0x000000, "武器UI１");
	//DrawFormatString(850, 150, 0x000000, "武器名１");
	//DrawFormatString(850, 200, 0x000000, "Lv.              0");
	//DrawFormatString(850, 250, 0x000000, "総ダメージ数      100000");

	//DrawFormatString(700, 450, 0x000000, "武器UI２");
	//DrawFormatString(850, 400, 0x000000, "武器名２");
	//DrawFormatString(850, 450, 0x000000, "Lv.              0");
	//DrawFormatString(850, 500, 0x000000, "総ダメージ数      100000");

	if (is_fopen == false)
	{
		DrawFormatString(600, 50, 0xff0000, "error");

	}
	else
	{
		/*DrawFormatString(700, 200, 0x000000, "武器UI１  %d", sample[0].type);
		DrawFormatString(850, 150, 0x000000, "武器名１  %d", sample[0].type);*/
		SetFontSize(25);
		DrawFormatString(850, 200, 0x000000, "Lv.              %d", sample[0].level);
		DrawFormatString(850, 250, 0x000000, "総ダメージ数      %7d", sample[0].damage);

		/*DrawFormatString(700, 450, 0x000000, "武器UI２  %d", sample[1].type);
		DrawFormatString(850, 400, 0x000000, "武器名２  %d", sample[1].type);*/
		SetFontSize(25);
		DrawFormatString(850, 450, 0x000000, "Lv.              %d", sample[1].level);
		DrawFormatString(850, 500, 0x000000, "総ダメージ数      %7d", sample[1].damage);
	}

	switch (sample[0].type)
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
	switch (sample[1].type)
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
