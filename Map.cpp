#include "Map.h"

Map::Map() {
	// マップデータ初期化処理
	for (size_t i = 0; i <= DATA_MAX; i++)
	{
		Mapdata[i] = 0;
	}
}
