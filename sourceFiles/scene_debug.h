//////////////////////////////////////////////////
// デバッグ シーン
// 作成：島袋
//////////////////////////////////////////////////
#pragma once

#include "scene.h"

class DebugScene : public Scene {
private:
	int state = 0; // 状態

public:
	DebugScene() {
		state = 0;
	};

	~DebugScene() {};

	//////////////////////////////////////////////////

	virtual Scene* update() override;

	virtual void draw() const override;
};