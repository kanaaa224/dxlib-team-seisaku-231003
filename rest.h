#pragma once

class Player;
class GameUI;

class Rest
{
private:
	int cursor_interval;			//カーソルのインターバル
	int scene_interval;				//シーンのインターバル
	int select_interval;			//決定のインターバル
	int cursor_num;					//カーソル番号
	int cursor_x;					//カーソルのｘ座標
	int anim_cnt;					//アニメーションの切り替えカウント
	int bonfire_anim;				//焚火のアニメーション番号

	int cursor_image;				//カーソルの画像
	int bonfire_image[4];			//焚火の画像
	int button_image;				//ボタンの画像

	int logo_dicision_image;		//決定のロゴ画像
	int logo_rest_image;			//休憩するのロゴ画像
	int logo_pray_image;			//祈るのロゴ画像
	int logo_cure_image;			//回復のロゴ画像
	int logo_buf_image;				//バフのロゴ画像

	bool is_select;					//決定した？
	bool rest_buf_flg;				//休憩のバフをかける？

public:
	//コンストラクタ
	Rest();
	//デストラクタ
	~Rest();

	//描画に関すること以外の更新を実装する
	void update(Player* player, int& mode, int& stage, int& restCnt,int& hp);

	//描画に関することの更新を実装する
	void draw()const;

	void Init();

	//rest_buf_flgを取得する
	bool GetRestBufFlg()
	{
		return rest_buf_flg;
	}

	//rest_buf_flgを設定する
	void SetRestBufFlg(const bool flg)
	{
		rest_buf_flg = flg;
	}

};