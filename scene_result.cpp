#include "main.h"

ResultScene::ResultScene(int result_info[])
{
	// 画像読込
	img_button_a = LoadGraph("resources/images/button_a01.png");

	// マップアイコン読込用変数
	img_battle = LoadGraph("resources/images/maps/battle.png");
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

	// 武器名ロゴ画像
	img_logo_dagger = LoadGraph("resources/images/Logo/WeaponName/logo_dagger_black.png");
	img_logo_sword = LoadGraph("resources/images/Logo/WeaponName/logo_sword_black.png");
	img_logo_greatsword = LoadGraph("resources/images/Logo/WeaponName/logo_greatsword_black.png");
	img_logo_spear = LoadGraph("resources/images/Logo/WeaponName/logo_spear_black.png");
	img_logo_frail = LoadGraph("resources/images/Logo/WeaponName/logo_frail_black.png");
	img_logo_book = LoadGraph("resources/images/Logo/WeaponName/logo_book_black.png");
	
	// レベル7の武器名ロゴ画像
	img_logo_assasinsdagger = LoadGraph("resources/images/Logo/WeaponName/logo_assasin'sdagger.png");;
	img_logo_legendsword = LoadGraph("resources/images/Logo/WeaponName/logo_legendsword.png");
	img_logo_windslash = LoadGraph("resources/images/Logo/WeaponName/logo_windslash.png");
	img_logo_royallance = LoadGraph("resources/images/Logo/WeaponName/logo_royallance.png");
	img_logo_threechain =  LoadGraph("resources/images/Logo/WeaponName/logo_threechain.png");
	img_logo_blessing = LoadGraph("resources/images/Logo/WeaponName/logo_blessing.png");

	// レベル8の武器名ロゴ画像
	img_logo_throwingknife = LoadGraph("resources/images/Logo/WeaponName/logo_throwingknife.png");;
	img_logo_magicsword = LoadGraph("resources/images/Logo/WeaponName/logo_magicsword.png");
	img_logo_dustsword = LoadGraph("resources/images/Logo/WeaponName/logo_dustsword.png");
	img_logo_gungnir = LoadGraph("resources/images/Logo/WeaponName/logo_gungnir.png");
	img_logo_earthcrusher = LoadGraph("resources/images/Logo/WeaponName/logo_earthcrusher.png");
	img_logo_bullet = LoadGraph("resources/images/Logo/WeaponName/logo_bullet.png");

	img_width = 40;

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
	DeleteGraph(img_button_a);
	
	DeleteGraph(img_battle);
	DeleteGraph(img_event);
	DeleteGraph(img_rest);
	DeleteGraph(img_anvil);
	DeleteGraph(img_boss);

	DeleteGraph(img_sword);
	DeleteGraph(img_dagger);
	DeleteGraph(img_great_sword);
	DeleteGraph(img_question_mark);
	DeleteGraph(img_spear);
	DeleteGraph(img_frail);
	DeleteGraph(img_book);

	DeleteGraph(img_logo_sword);
	DeleteGraph(img_logo_dagger);
	DeleteGraph(img_logo_greatsword);
	DeleteGraph(img_logo_spear);
	DeleteGraph(img_logo_frail);
	DeleteGraph(img_logo_book);

	DeleteGraph(img_logo_assasinsdagger);
	DeleteGraph(img_logo_legendsword);
	DeleteGraph(img_logo_windslash);
	DeleteGraph(img_logo_royallance);
	DeleteGraph(img_logo_threechain);
	DeleteGraph(img_logo_blessing);

	DeleteGraph(img_logo_throwingknife);
	DeleteGraph(img_logo_magicsword);
	DeleteGraph(img_logo_dustsword);
	DeleteGraph(img_logo_gungnir);
	DeleteGraph(img_logo_earthcrusher);
	DeleteGraph(img_logo_bullet);
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

	SetFontSize(25);
	DrawFormatString(50, 120, 0x000000, "制覇したステージ");

	if (value <= 10)
	{
		DrawRotaGraph(1130, 685, 0.2f, 0.0f, img_button_a, TRUE);
		DrawRotaGraph(1200, 680, 0.15f, 0.0f, img_logo_title, TRUE);
	}

	// マップアイコン画像表示
	DrawRotaGraph(150, 200, 1.2f, 0.0f, img_battle, TRUE);
	DrawRotaGraph(150, 300, 1.2f, 0.0f, img_event, TRUE);
	DrawRotaGraph(150, 400, 1.2f, 0.0f, img_rest, TRUE);
	DrawRotaGraph(150, 500, 1.2f, 0.0f, img_anvil, TRUE);
	DrawRotaGraph(150, 600, 1.2f, 0.0f, img_boss, TRUE);
	
	// マップ情報
	SetFontSize(30);
	DrawFormatString(230, 190, 0x000000, "× %d",map_info.battle_count);
	DrawFormatString(230, 290, 0x000000, "× %d",map_info.event_count);
	DrawFormatString(230, 390, 0x000000, "× %d",map_info.event_count);
	DrawFormatString(230, 490, 0x000000, "× %d",map_info.anvil_count);
	DrawFormatString(230, 590, 0x000000, "× %d",map_info.boss_count);


	//for (int i = 0; i < map_info.battle_count; i++)
	//{
	//	DrawRotaGraph(250 + (img_width * i), 200, 0.7f, 0.0f, img_battle, TRUE);
	//}



	// 武器1情報表示
	DrawRotaGraph(840, 250, 0.2f, 0.0f, img_logo_lv, TRUE);
	DrawRotaGraph(895, 300, 0.2f, 0.0f, img_logo_totaldamage, TRUE);
	DrawFormatString(1030, 240, 0x000000, "%7d", weapon1_info.level);
	DrawFormatString(1030, 290, 0x000000, "%7d", weapon1_info.damage);

	// 武器2情報表示
	DrawRotaGraph(840, 500, 0.2f, 0.0f, img_logo_lv, TRUE);
	DrawRotaGraph(895, 550, 0.2f, 0.0f, img_logo_totaldamage, TRUE);
	DrawFormatString(1030, 490, 0x000000, "%7d", weapon2_info.level);
	DrawFormatString(1030, 540, 0x000000, "%7d", weapon2_info.damage);

	switch (weapon1_info.type)
	{
	case 0:			// 片手剣
		DrawRotaGraph(700, 240, 0.2f, 0.0f, img_sword, TRUE);
		DrawRotaGraph(865, 180, 0.25f, 0.0f, img_logo_sword, TRUE);
		if (weapon1_info.level == 7)
		{
			DrawFormatString(930, 175, 0x000000, "-");
			DrawRotaGraph(1030, 180, 0.25f, 0.0f, img_logo_legendsword, TRUE);
		}
		else if (weapon1_info.level == 8)
		{
			DrawFormatString(930, 175, 0x000000, "-");
			DrawRotaGraph(1000, 180, 0.25f, 0.0f, img_logo_magicsword, TRUE);
		}
		break;
	case 1:		// 短剣
		DrawRotaGraph(700, 240, 0.17f, 0.0f, img_dagger, TRUE);
		DrawRotaGraph(850, 180, 0.25f, 0.0f, img_logo_dagger, TRUE);
		if (weapon1_info.level == 7)
		{
			DrawFormatString(900, 175, 0x000000, "-");
			DrawRotaGraph(1030, 180, 0.25f, 0.0f, img_logo_assasinsdagger, TRUE);
		}
		else if (weapon1_info.level == 8)
		{
			DrawFormatString(900, 175, 0x000000, "-");
			DrawRotaGraph(1000, 180, 0.25f, 0.0f, img_logo_throwingknife, TRUE);
		}
		break;
	case 2:	// 大剣
		DrawRotaGraph(700, 240, 0.25f, 0.0f, img_great_sword, TRUE);
		DrawRotaGraph(850, 180, 0.25f, 0.0f, img_logo_greatsword, TRUE);
		if (weapon1_info.level == 7)
		{
			DrawFormatString(900, 175, 0x000000, "-");
			DrawRotaGraph(980, 180, 0.25f, 0.0f, img_logo_windslash, TRUE);
		}
		else if (weapon1_info.level == 8)
		{
			DrawFormatString(900, 175, 0x000000, "-");
			DrawRotaGraph(1020, 180, 0.25f, 0.0f, img_logo_dustsword, TRUE);
		}
		break;
	default:
		DrawRotaGraph(700, 260, 0.15f, 0.0f, img_question_mark, TRUE);
		DrawFormatString(820, 200, 0x000000, "武器がありません");
		break;
	}

	// 武器2の画像
	switch (weapon2_info.type)
	{
	case 0:			// 槍
		DrawRotaGraph(700, 500, 0.25f, 0.0f, img_spear, TRUE);
		DrawRotaGraph(840, 430, 0.25f, 0.0f, img_logo_spear, TRUE);
		if (weapon2_info.level == 7)
		{
			DrawFormatString(870, 425, 0x000000, "-");
			DrawRotaGraph(1020, 425, 0.3f, 0.0f, img_logo_royallance, TRUE);
		}
		else if (weapon2_info.level == 8)
		{
			DrawFormatString(870, 425, 0x000000, "-");
			DrawRotaGraph(980, 425, 0.3f, 0.0f, img_logo_gungnir, TRUE);
		}
		break;
	case 1:			// フレイル
		DrawRotaGraph(680, 500, 0.25f, 0.0f, img_frail, TRUE);
		DrawRotaGraph(880, 430, 0.25f, 0.0f, img_logo_frail, TRUE);
		if (weapon2_info.level == 7)
		{
			DrawFormatString(965, 425, 0x000000, "-");
			DrawRotaGraph(1080, 425, 0.3f, 0.0f, img_logo_threechain, TRUE);
		}
		else if (weapon2_info.level == 8)
		{
			DrawFormatString(965, 425, 0x000000, "-");
			DrawRotaGraph(1120, 420, 0.35f, 0.0f, img_logo_earthcrusher, TRUE);
		}
		break;
	case 2:			// 魔導書
		DrawRotaGraph(700, 500, 0.17f, 0.0f, img_book, TRUE);
		DrawRotaGraph(890, 430, 0.25f, 0.0f, img_logo_book, TRUE);
		if (weapon2_info.level == 7)
		{
			DrawFormatString(950, 425, 0x000000, "-");
			DrawRotaGraph(1060, 425, 0.3f, 0.0f, img_logo_blessing, TRUE);
		}
		else if (weapon2_info.level == 8)
		{
			DrawFormatString(950, 425, 0x000000, "-");
			DrawRotaGraph(1110, 410, 0.4f, 0.0f, img_logo_bullet, TRUE);
		}
		break;
	default:
		DrawRotaGraph(700, 520, 0.15f, 0.0f, img_question_mark, TRUE);
		DrawFormatString(820, 450, 0x000000, "武器がありません");
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