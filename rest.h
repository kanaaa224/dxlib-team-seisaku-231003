#pragma once

class Player;
class GameUI;

class Rest
{
private:
	int cursor_interval;
	int interval;
	int cursor_num;
	int cursor_x;

	int cursor_image;
	int bonfire_image;
	int button_image;

	int logo_dicision_image;
	int logo_rest_image;
	int logo_pray_image;

	bool is_select;
	bool is_ok;
	bool rest_buf_flg;			//休憩のバフをかける？

public:
	//コンストラクタ
	Rest();
	//デストラクタ
	~Rest();

	//描画に関すること以外の更新を実装する
	void update(Player* player, int& mode, int& stage, int& restCnt);

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