#include "map.h"

Map::Map() {
	// マップデータ初期化処理
	for (int i = 0; i <= DATA_MAX; i++)
	{
		Mapdata[i] = 0;
		randnum[i] = 0;
	}

	// マップ生成(0:戦闘、1:ランダムイベント、2:休憩、3:鍛冶屋、4:ボス)
	Mapdata[8] = 1;


	randnum[0] = GetRand(1) + 1;
	for (int i = 0; i < randnum[0]; i++) {
		int r = GetRand(3) + 3;
		if (Mapdata[r] == 0) {
			Mapdata[r] = 2;
		}else continue;
	}

	randnum[1] = GetRand(2) + 2;
	for (int i = 0; i < randnum[1]; i++) {
		int r = GetRand(10) + 9;
		if (Mapdata[r] == 0) {
			Mapdata[r] = 2;
		}
		else continue;
	}
	Mapdata[20] = 2;


	randnum[2] = GetRand(1) + 1;
	for (int i = 0; i < randnum[2]; i++) {
		int r = GetRand(10) + 9;
		if (Mapdata[r] == 0) {
			Mapdata[r] = 3;
		}
		else continue;
	}


	Mapdata[21] = 4;
}
Map::~Map() {

}

Scene* Map::update() {

	return this;
};

void Map::draw() const {

	for (int i = 0; i <= DATA_MAX; i++)
	{
		DrawFormatString(10 * i + 10, 10, 0xffffff, "%d", i);
		DrawFormatString(10 * i + 10, 40, 0xffffff, "%d", Mapdata[i]);
		DrawFormatString(10 * i + 10, 60, 0xffffff, "%d", randnum[i]);
	}
	
}