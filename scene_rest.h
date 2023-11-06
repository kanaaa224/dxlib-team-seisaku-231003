#pragma once

class Player;

class Rest
{
private:
	int interval;
	int cursor_num;


	int cursor_image;
	int bonfire_image;

public:
	//コンストラクタ
	Rest();
	//デストラクタ
	~Rest();

	//描画に関すること以外の更新を実装する
	void update(Player* player, bool& flg);

	//描画に関することの更新を実装する
	void draw()const;

};