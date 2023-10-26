#include"scene_weapon.h"
#include"inputCtrl.h"
#include"weapon.h"

Weapon_Selection::Weapon_Selection()
{
	interval = 0;
	cursor_num = 0;
	select_num = 0;
	cursor_x = 0;

	dagger_image = LoadGraph("resources/images/sword_shortsword_brown.png");
	sword_image = LoadGraph("resources/images/sword_longsword_brown.png");
	great_sword_image = LoadGraph("resources/images/tsurugi_bronze_blue.png");

	cursor_image = LoadGraph("resources/images/computer_cursor_finger_black.png");

	is_selecting = false;
	was_selected = false;
}

Weapon_Selection::~Weapon_Selection()
{

}

void Weapon_Selection::update(weapon* _weapon, bool &is_weapon_select)
{
	//１５ｆのインターバルを設ける
	if (interval < INTERVAL)
	{
		interval++;
	}

	if (is_selecting != true)
	{
		cursor_x = cursor_num * 300;
	}
	else
	{
		cursor_x = cursor_num * 400;
	}

	//左スティックを右に
	if (InputCtrl::GetStickRatio(L).x > 0.8 && interval >= 15)
	{
		cursor_num++;
		interval = 0;
		//武器を選択していないなら３つまで
		if (is_selecting != true)
		{
			if (cursor_num >= SELECT_WEAPON)
			{
				cursor_num = 0;
			}
		}
		//武器を選択したなら２つまで
		else
		{
			if (cursor_num > 1)
			{
				cursor_num = 0;
			}
		}
	}

	//左スティックを左に
	if (InputCtrl::GetStickRatio(L).x < -0.8 && interval >= 15)
	{
		cursor_num--;
		interval = 0;
		//武器を選択していないなら３つまで
		if (is_selecting != true)
		{
			if (cursor_num < 0)
			{
				cursor_num = SELECT_WEAPON - 1;
			}
		}
		//武器を選択したなら２つまで
		else
		{
			if (cursor_num < 0)
			{
				cursor_num = 1;
			}
		}
	}

	//武器を選択していないなら
	if (is_selecting != true)
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) || InputCtrl::GetKeyState(KEY_INPUT_SPACE) == PRESS)
	{
		if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
		{
			//まだ武器を選択したことがないなら
			if (was_selected != true)
			{
				if (cursor_num == 0)
				{
					_weapon->SetWeaponType(dagger);
					select_num = 0;
				}
				else if (cursor_num == 1)
				{
					_weapon->SetWeaponType(sword);
					select_num = 1;
				}
				else
				{
					_weapon->SetWeaponType(greatSword);
					select_num = 2;
				}
			}
			//武器を選択したことがあるなら
			else
			{
				if (cursor_num == 0)
				{
					//_weapon->SetWeaponType();
					select_num = 0;
				}
				else if (cursor_num == 1)
				{
					//_weapon->SetWeaponType();
					select_num = 1;
				}
				else
				{
					//_weapon->SetWeaponType();
					select_num = 2;
				}
			}
			//武器を選択した状態にする
			is_selecting = true;
			//カーソルを「はい」の位置にする
			cursor_num = 0;
		}
	}
	//武器を選択したなら
	else
	{
		if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
		{
			//はい
			if (cursor_num == 0)
			{
				is_weapon_select = true;
			}
			//いいえ
			else
			{
				is_selecting = false;
			}
		}
	}
}

void Weapon_Selection::draw() const
{
	//武器を選択していないなら
	if (is_selecting != true)
	{		
		if (was_selected != true)
		{
			SetFontSize(32);
			DrawString(430, 10, "最初の武器を選んでください\n",0xffffff);
			SetFontSize(16);

			DrawRotaGraph(350, 300, .45f, .0625f, dagger_image, TRUE);
			DrawRotaGraph(650, 300, .45f, .0625f, sword_image, TRUE);
			DrawRotaGraph(950, 300, .45f, .0625f, great_sword_image, TRUE);

		}
		else
		{
			SetFontSize(32);
			DrawString(430, 10, "２つ目の武器を選んでください\n", 0xffffff);
			SetFontSize(16);

			DrawRotaGraph(350, 300, .45f, .0625f, dagger_image, TRUE);
			DrawRotaGraph(650, 300, .45f, .0625f, sword_image, TRUE);
			DrawRotaGraph(950, 300, .45f, .0625f, great_sword_image, TRUE);
		}
		DrawRotaGraph(400 + cursor_x, 600, .5f, 0, cursor_image, TRUE);
	}
	//武器を選択したなら
	else
	{		
		SetFontSize(32);
		DrawString(430, 10, "この武器を選びますか？\n", 0xffffff);
		SetFontSize(16);

		if (was_selected != true)
		{
			if (select_num == 0)
			{
				DrawRotaGraph(350, 300, .45f, .0625f, dagger_image, TRUE);
			}
			else if (select_num == 1)
			{
				DrawRotaGraph(350, 300, .45f, .0625f, sword_image, TRUE);
			}
			else
			{
				DrawRotaGraph(350, 300, .45f, .0625f, great_sword_image, TRUE);
			}
		}
		else
		{
			if (select_num == 0)
			{
				DrawRotaGraph(350, 300, .45f, .0625f, sword_image, TRUE);
			}
			else if (select_num == 1)
			{
				DrawRotaGraph(350, 300, .45f, .0625f, sword_image, TRUE);
			}
			else
			{
				DrawRotaGraph(350, 300, .45f, .0625f, sword_image, TRUE);
			}
		}

		SetFontSize(64);

		DrawString(400, 600, "はい", 0xffffff);
		DrawString(800, 600, "いいえ", 0xffffff);

		SetFontSize(16);

		DrawRotaGraph(320 + cursor_x, 640, .5f, 1.6f, cursor_image, TRUE);
	}
}
