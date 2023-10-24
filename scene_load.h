//////////////////////////////////////////////////
// ロード シーン
// 作成：島袋
//////////////////////////////////////////////////
#pragma once

#include "scene.h"

class LoadScene : public Scene {
private:
	int state, frameCounter;

	float progress;     // 読み込み進捗
	float opacity;      // 不透明度

	int img_background; // 背景
	int img_cat;        // キャラクター

public:
	LoadScene();

	~LoadScene();

	virtual Scene* update() override;

	virtual void draw() const override;
};