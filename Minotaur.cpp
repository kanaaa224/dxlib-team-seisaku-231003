#include "Minotaur.h"
#include "Common.h"

Minotaur::Minotaur()
{
	img = LoadGraph("resources/images/enemy_tmp_images/usi.png");
	location.x = _SCREEN_WIDHT_ / 2;
	location.y = 0;
	radius = 100;
}

void Minotaur::Update()
{

}

void Minotaur::Draw() const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1, 0, img, TRUE);
}

void Minotaur::Tackle()
{

}

void Minotaur::Roar()
{

}
