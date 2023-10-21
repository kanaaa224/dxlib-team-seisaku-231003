#include "DxLib.h"
#include "Title.h"

//コンストラクタ
Title::Title()
{
	EnemyImage0 = LoadGraph("resources/images/魔法使い.png");
	EnemyImage1 = LoadGraph("resources/images/スケルトン.png");
	EnemyImage2 = LoadGraph("resources/images/スライム.png");
	EnemyImage3 = LoadGraph("resources/images/ミノタウロス.png");
	EnemyImage4 = LoadGraph("resources/images/まおう.png");
}

//デストラクタ
Title::~Title()
{

}

//更新
Scene*Title::Update()
{
	return this;
}

//描画
void Title::draw() const
{
	DrawGraph(1200, 640, EnemyImage0,FALSE);
}