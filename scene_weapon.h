#pragma once
#include"scene.h"

class Weapon_Selection : public Scene
{
private:
	int interval;
	int cursor_num;
	int cursor_x;

public:
	//コンストラクタ
	Weapon_Selection();

	//デストラクタ
	~Weapon_Selection();

	//描画に関すること以外の更新を実装する
	virtual Scene* update()override;

	//描画に関することの更新を実装する
	virtual void draw()const override;
};