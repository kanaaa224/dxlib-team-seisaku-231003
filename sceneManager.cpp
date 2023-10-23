//////////////////////////////////////////////////
// シーンマネージャー
// 作成：島袋
//////////////////////////////////////////////////
#include "main.h"

Scene* SceneManager::update() {
	Scene* nextScene = nowScene->update();
	/* Scene* nextScene;
	try {
		nextScene = nowScene->update();
	}
	catch (const char* err) {
		TextFile::Write(1, 1, "Log.txt", err);
		return nullptr;
	}; */
	if (nextScene != nowScene) {
		delete nowScene;
		nowScene = nextScene;
	};
	return nextScene;
};

void SceneManager::draw() const {
	nowScene->draw();
};