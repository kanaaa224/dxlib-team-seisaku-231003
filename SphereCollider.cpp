#include "SphereCollider.h"
#include <math.h>
#include <stdio.h>
#include "Common.h"


SphereCollider::SphereCollider()
{
    diff.x = 0;//ここにプレイヤーの移動量を入れる
    diff.y = 0;
}

int SphereCollider::CheckCollision(SphereCollider sphereCollider)
{
    //三平方の定理を使う
    float a = (location.x + diff.x) - (sphereCollider.location.x + sphereCollider.diff.x);
    float b = (location.y + diff.y) - (sphereCollider.location.y + sphereCollider.diff.y);
    float c = sqrtf(a * a + b * b);

    //それぞれの半径の合計と2点間の距離を比べる
    if (c <= radius + sphereCollider.radius) {
        return COLLISION;
    }
    return NO_COLLISION;
}