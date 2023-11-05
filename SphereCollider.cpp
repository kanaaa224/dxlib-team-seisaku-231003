#include "SphereCollider.h"
#include <math.h>
#include <stdio.h>
#include "Common.h"
#include "Player.h"




SphereCollider::SphereCollider()
{
    diff.x = 0;//ここにプレイヤーの移動量を入れる
    diff.y = 0;
}

int SphereCollider::CheckCollision(SphereCollider sphereCollider,Player* player)
{
    SetPlayerAmountOfTravel_X(player->Player_MoveX());
    SetPlayerAmountOfTravel_Y(player->Player_MoveY());

    //三平方の定理を使う
    float a = (location.x + diff.x) - (sphereCollider.location.x + sphereCollider.diff.x);
    float b = (location.y + diff.y) - (sphereCollider.location.y + sphereCollider.diff.y);
    float c = sqrtf(a * a + b * b);

    //それぞれの半径の合計と2点間の距離を比べる
    if (c <= radius + sphereCollider.radius) {
        return HIT;
    }
    else {
        return NO_COLLISION;
    }
}

void SphereCollider::SetPlayerAmountOfTravel_X(float x)
{
    diff.x = x;
}

void SphereCollider::SetPlayerAmountOfTravel_Y(float y)
{
    diff.y = y;
}

float SphereCollider::GetEnemyRadius()
{
    return radius;
}
