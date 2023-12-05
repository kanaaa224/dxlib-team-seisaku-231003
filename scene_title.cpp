#include "main.h"

//コンストラクタ
Title::Title()
{
	//TitleImage = LoadGraph("resources/images/Title.png");
	//Titlelogo = LoadGraph("resources/images/Title/logo/戦塔ロゴ.png");
	Titlelogo_white = LoadGraph("resources/images/Title/logo/戦塔ロゴ-白.png");
	g_MenuNumber = 0;
	TitleInterval = 0;
	cursor = LoadGraph("resources/images/cursor.png");

	if (Title_Background_Img[0] = LoadGraph("resources/images/Title/Title_background_tree tower_1280.png")) {}
	if (Title_Background_Img[1] = LoadGraph("resources/images/Title/Title_background_tree.png")) {}
	if (Title_SkyStar_Img = LoadGraph("resources/images/Title/Star2.png")) {}

	if (Title_Start_Img = LoadGraph("resources/images/Title/title_logo_start.png")) {}
	if (Title_Help_Img = LoadGraph("resources/images/Title/title_logo_help.png")) {}
	if (Title_Credit_Img = LoadGraph("resources/images/Title/title_logo_credit.png")) {}
	if (Title_End_Img = LoadGraph("resources/images/Title/title_logo_end.png")) {}

	if (Title_Cosol_sword_Img = LoadGraph("resources/images/Title/片手剣50・50.png")) {}
	if (Title_Cosol_greatsword_Img = LoadGraph("resources/images/武器/大剣50・50.png")) {}
	if (Title_Cosol_shortsword_Img = LoadGraph("resources/images/武器/短剣50・50.png")) {}

	Title_Select_magnification = 0.0;

	//座標系
	logo_white_x = 640.0f;
	logo_white_y = -70.0f;
	logo_move_x = 0.0f;
	logo_move_y = 0.0f;

	for (int i = 0; i < 8; i++) {
		Title_Star_x[i] = 0;
		Title_Star_y[i] = 0;
	}

	//デバッグ用マウスポインタlocation
	Title_Debug_Mousepoint_x = 0;
	Title_Debug_Mousepoint_y = 0;

	//fps系
	Title_Animation_fps = 0;

	//乱数
	Title_Star_rand = 0;

	//カウンタ
	Star_Anim_Count = 0;
	Title_Star_rand_Count = 0;

	//フラグ系
	logo_location_y_flg = false;
	Title_Select_mg_flg = false;
	Title_Anim_flg = true;
	Title_FadeOut_flg = false;
	Title_FadeIn_flg = false;
	Title_select_flg = false;

	//色
	Title_Star_Anim_Color_red = 255;
	Title_Star_Anim_Color_green = 255;
	Title_Star_Anim_Color_blue = 255;
}

//更新
Scene* Title::update()
{
	Title_Animation_fps++;

	Title_Debug_Mousepoint_x = InputCtrl::GetMouseCursor().x;
	Title_Debug_Mousepoint_y = InputCtrl::GetMouseCursor().y;

	//スティックの制御
	if (TitleInterval < TITLEINTERVAL)
	{
		TitleInterval++;
	}
	//カーソル上下
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_DPAD_UP) == PRESS || InputCtrl::GetStickRatio(L).y > 0.8 && TitleInterval >= 15 || InputCtrl::GetKeyState(KEY_INPUT_UP) == PRESS)
	{
		//スティック移動の初期化
		TitleInterval = 0;
		//タイトルカーソルの移動
		if (--g_MenuNumber > TITLECURSOR);
		//タイトルカーソルの移動量の制御
		if (g_MenuNumber < 0) g_MenuNumber = 3;
	}
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_DPAD_DOWN) == PRESS || InputCtrl::GetStickRatio(L).y < -0.8 && TitleInterval >= 15 || InputCtrl::GetKeyState(KEY_INPUT_DOWN) == PRESS)
	{
		//スティック移動の初期化
		TitleInterval = 0;
		//タイトルカーソルの移動
		if (++g_MenuNumber < -TITLECURSOR);
		//タイトルカーソルの移動量の制御
		if (g_MenuNumber > 3)g_MenuNumber = 0;
	}
	g_MenuY = g_MenuNumber * 52;
	//Aボタンでメニュー決定・画面遷移
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS || InputCtrl::GetKeyState(KEY_INPUT_A) == PRESS)
	{
		if (g_MenuNumber == 0) {
			return new GameScene;
		}
		if (g_MenuNumber == 1) {
			return new Help;
		}
		if (g_MenuNumber == 2) {
			return new Credit;
		}
		if (g_MenuNumber == 3) {
			return new End;
		}
	}

	if (Title_Anim_flg == true) {

		//星の座標を rands_x:25～500  rands_y:25～250 rands1_x:775～1260 rands1_y:25～250の範囲内で取得する
		//Title_Star_Rands(499, 249, 1259, 249);
		Title_Star_Rands(499, 249, 1259, 249);
	}
	else if (Title_FadeOut_flg == true) {

		//星のフェードアウト関数
		Title_Star_FadeOut();
	}
	else if (Title_FadeIn_flg == true) {

		//星のフェードイン関数
		Title_Star_FadeIn();
	}

	//タイトルロゴアニメーション
	Title_logo_Animation();

	logo_white_y = logo_white_y + logo_move_y;

	//if (logo_location_y_flg == true && Title_Select_mg_flg == false) {
	//	//タイトルのセレクトアニメーション
	//	Title_Select_Anim();
	//}
	
	if (Title_Animation_fps > 59) {
		// 1秒
		Title_Animation_fps = 0;
		Star_Anim_Count++;
		if (Star_Anim_Count > 2) {
			Star_Anim_Count = 0;
		}
	}

	return this;
}

//描画
void Title::draw() const
{	
	SetDrawBright(255, 255, 255);
	//木と塔
	DrawGraph(0, 0, Title_Background_Img[0], TRUE);

	//　中心線
	DrawLine(0, 360, 1280, 360, GetColor(255, 0, 0), TRUE);
	DrawLine(640, 0, 640, 720, GetColor(255, 0, 0), TRUE);

	//タイトルロゴ
	//DrawRotaGraph(logo_white_x, logo_white_y, 0.4, 0.0, Titlelogo_white, TRUE);
	DrawRotaGraph(logo_white_x, logo_white_y, 0.58, 0.0, Titlelogo_white, TRUE);

	//星をランダムに出現させる範囲
	DrawBox(25, 25, 500, 250, GetColor(255, 0, 0), FALSE);
	DrawBox(775, 25, 1260, 250, GetColor(255, 0, 0), FALSE);

	DrawFormatString(0, 300, GetColor(255, 0, 0), "Mouse x %d", Title_Debug_Mousepoint_x);
	DrawFormatString(0, 320, GetColor(255, 0, 0), "Mouse y %d", Title_Debug_Mousepoint_y);
	/*DrawFormatString(0, 360, GetColor(255, 0, 0), "青	%d", Title_Star_Anim_Color_blue);
	DrawFormatString(0, 380, GetColor(255, 0, 0), "カウンタ %d", Title_Star_rand_Count);
	DrawFormatString(0, 400, GetColor(255, 0, 0), "星の座標 x1  %d", Title_Star_x[1]);
	DrawFormatString(0, 420, GetColor(255, 0, 0), "星の座標 y1  %d", Title_Star_y[1]);
	DrawFormatString(0, 440, GetColor(255, 0, 0), "星の座標 x2  %d", Title_Star_x[2]);
	DrawFormatString(0, 460, GetColor(255, 0, 0), "星の座標 y2  %d", Title_Star_y[2]);*/
	
	if (Title_select_flg == true/* && Title_Select_mg_flg == false*/) {

		//タイトルカーソルの描画
		DrawGraph(470, 290 + g_MenuY, cursor, TRUE);

		// 90ずつ足している	倍率は0.32
		DrawRotaGraph(659, 300, 0.32, 0.0, Title_Start_Img, TRUE);
		DrawRotaGraph(659, 390, 0.32, 0.0, Title_Help_Img, TRUE);
		DrawRotaGraph(659, 480, 0.32, 0.0, Title_Credit_Img, TRUE);
		DrawRotaGraph(659, 570, 0.32, 0.0, Title_End_Img, TRUE);
	}

	//星のフェードアウト
	SetDrawBright(Title_Star_Anim_Color_red, Title_Star_Anim_Color_green, Title_Star_Anim_Color_blue);

	for (int i = 0; i < 8; i++) {
		//星
		DrawRotaGraph(Title_Star_x[i], Title_Star_y[i], 0.05, 0.0, Title_SkyStar_Img, TRUE);
	}

	SetDrawBright(255, 255, 255);
}

Title::~Title()
{
	DeleteGraph(TitleImage);
}

void Title::Title_logo_Animation() {

	if (logo_white_y < /*75*/ 110 && logo_location_y_flg == true) {
		logo_move_y = 0.0f;
		Title_select_flg = true;
	}
	else {

		if (logo_white_y > 200.0f) {

			logo_location_y_flg = true;
			logo_move_y = logo_move_y + TITLE_MOVE_DOWN;
		}
		else {

			logo_move_y = logo_move_y + TITLE_MOVE_UP;
		}
	}
}

void Title::Title_Star_Rands(int rands_x, int rands_y, int rands1_x, int rands1_y) {

	for (int i = 0; i < 4;) {
		//星の座標を x:25～500  y:25～250 の範囲内で取得する
		Title_Star_x[i] = GetRand(rands_x) + 5;
		Title_Star_y[i] = GetRand(rands_y) + 50;

		//星の座標範囲と画像が被らないようにするため
		if (Title_Star_x[i] > 25 && Title_Star_y[i] > 25 && Title_Star_x[i] != Title_Star_x[i - 1] && Title_Star_y[i] != Title_Star_y[i - 1]) {

			i++;
		}
	}

	for (int j = 4; j < 8;) {
		//星の座標を x:25～500  y:25～250 の範囲内で取得する
		Title_Star_x[j] = GetRand(rands1_x) - 5;
		Title_Star_y[j] = GetRand(rands1_y) + 50;

		//星の座標範囲と画像が被らないようにするため
		if (Title_Star_x[j] > 775 && Title_Star_y[j] > 25 && Title_Star_x[j] != Title_Star_x[j - 1] && Title_Star_y[j] != Title_Star_y[j - 1]) {
				
			j++;

			if (j >= 8) {

				if (Title_Anim_flg == true && Title_Star_rand_Count == 0) {

					Title_Star_rand_Count++;
					Title_Anim_flg = false;
					Title_FadeOut_flg = true;
				}
				else if (Title_Anim_flg == true && Title_Star_rand_Count == 1) {

					Title_Anim_flg = false;
					Title_FadeIn_flg = true;

					Title_Star_rand_Count = 0;
				}
			}
		}
	}
}

void Title::Title_Star_FadeOut() {

	Title_Star_Anim_Color_red = Title_Star_Anim_Color_red + TITLE_STAR_BRIGHT_COLOR1;
	Title_Star_Anim_Color_green = Title_Star_Anim_Color_green + TITLE_STAR_BRIGHT_COLOR1;
	Title_Star_Anim_Color_blue = Title_Star_Anim_Color_blue + TITLE_STAR_BRIGHT_COLOR1;

	if (Title_Star_Anim_Color_red <= 0 && Title_Star_Anim_Color_green <= 0 && Title_Star_Anim_Color_blue <= 0) {

		//フェードアウト関数
		Title_FadeOut_flg = false;

		//色を黒にセット
		Title_Star_Anim_Color_red = 0;
		Title_Star_Anim_Color_green = 0;
		Title_Star_Anim_Color_blue = 0;

		Title_Anim_flg = true;
	}
}

void Title::Title_Star_FadeIn() {

	Title_Star_Anim_Color_red = Title_Star_Anim_Color_red + TITLE_STAR_BRIGHT_COLOR2;
	Title_Star_Anim_Color_green = Title_Star_Anim_Color_green + TITLE_STAR_BRIGHT_COLOR2;
	Title_Star_Anim_Color_blue = Title_Star_Anim_Color_blue + TITLE_STAR_BRIGHT_COLOR2;

	if (Title_Star_Anim_Color_red >= 255 && Title_Star_Anim_Color_green >= 255 && Title_Star_Anim_Color_blue >= 255) {

		Title_Star_Anim_Color_red = 255;
		Title_Star_Anim_Color_green = 255;
		Title_Star_Anim_Color_blue = 255;

		Title_FadeIn_flg = false;

		Title_FadeOut_flg = true;
	}
}

void Title::Title_Select_Anim() {

	if (Title_Select_mg_flg == true) {

		Title_Select_magnification = 0.32;
	}
	else {

		if (Title_Select_magnification > 0.32) {

			Title_Select_mg_flg = true;
		}

		Title_Select_magnification = Title_Select_magnification + TITLE_SELECT_MG;
	}
}