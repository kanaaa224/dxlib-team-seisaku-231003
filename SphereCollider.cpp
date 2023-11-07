#include "SphereCollider.h"
#include <math.h>
#include <stdio.h>
#include "Common.h"
#include "Player.h"




SphereCollider::SphereCollider()
{
    diff.x = 0;//ここにプレイヤーの移動量を入れる
    diff.y = 0;

    caleVector.x = 0;
    caleVector.y = 0;
}

int SphereCollider::CheckCollision(SphereCollider sphereCollider,Player* player)
{
    SetPlayerAmountOfTravel_X(player->Player_MoveX());
    SetPlayerAmountOfTravel_Y(player->Player_MoveY());

    //三平方の定理を使う
    float a = (location.x + diff.x) - (sphereCollider.location.x + sphereCollider.diff.x);
    float b = (location.y + diff.y) - (sphereCollider.location.y + sphereCollider.diff.y);
    float c = sqrtf(pow(a, 2) + pow(b, 2));

    //それぞれの半径の合計と2点間の距離を比べる
    if (c <= radius + sphereCollider.radius) {
        return HIT;
    }
    else {
        return NO_COLLISION;
    }
}

void SphereCollider::HitVectorCale(SphereCollider sphereCollider, Player* player)
{
    SetPlayerAmountOfTravel_X(player->Player_MoveX());
    SetPlayerAmountOfTravel_Y(player->Player_MoveY());

    //三平方の定理を使う
    float x = (location.x + diff.x) - (sphereCollider.location.x + sphereCollider.diff.x);
    float y = (location.y + diff.y) - (sphereCollider.location.y + sphereCollider.diff.y);
    float xy = sqrtf(pow(x, 2) + pow(y, 2));
    float r;
    //それぞれ の半径の合計と2点間の距離を比べる
    if (xy <= radius + sphereCollider.radius) {
        r = (xy - (radius + sphereCollider.radius)) / 2;

        float a = (location.x - sphereCollider.location.x) * -1;
        float b = (location.y - sphereCollider.location.y) * -1;

        caleVector.x = (a * r) * 0.1f;
        caleVector.y = (b * r) * 0.1f;
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
