#pragma once

#include "scene.h"
#define TITLEINTERVAL 15
#define TITLECURSOR 4

class Title :public Scene
{
private:

	//画像の読込用変数
	int TitleImage;
	int Titlelogo;
	int Titlelogo_white;

	int g_MenuNumber;
	//カーソル画像読み込み用変数
	int cursor;
	int g_MenuY;
	//タイトルカーソル（スティック）制御用の変数
	int TitleInterval;

public:
	//コンストラクタ
	Title();
	~Title();
	//更新
	Scene* update() override;
	//描画
	void draw() const override;

};