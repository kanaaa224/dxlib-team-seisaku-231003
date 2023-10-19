//////////////////////////////////////////////////
// FPS コントローラー
// 作成：kanaaa224
//////////////////////////////////////////////////
#include "fpsCtrl.h"

int FPSCtrl::frameTime  = 0;
int FPSCtrl::waitTime   = 0;
int FPSCtrl::lastTime   = 0;
int FPSCtrl::nowTime    = 0;
int FPSCtrl::updateTime = 0;
int FPSCtrl::lastUpdate = 0;
float FPSCtrl::count = 0.0f;
float FPSCtrl::fps   = 0.0f;

void FPSCtrl::Limit() {
    nowTime = GetNowCount();
    waitTime = frameTime - (nowTime - lastTime);
    if (waitTime > 0) WaitTimer(waitTime);
    lastTime = GetNowCount();
};

void FPSCtrl::Update() {
    int time = GetNowCount();
    count += 1.0f;
    if (updateTime < (time - lastUpdate)) {
        fps = count / (float)(time - lastUpdate) * 1000.0f;
        lastUpdate = time;
        count = 0.0f;
    };
};