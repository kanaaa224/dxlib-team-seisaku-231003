//////////////////////////////////////////////////
// FPS コントローラー
// 作成：kanaaa224
//////////////////////////////////////////////////
#pragma once

#include "DxLib.h"

// FPSコントローラー クラス
class FPSCtrl {
private:
    static int frameTime;                   // 制限FPSの1フレームの時間（ミリ秒）
    static int waitTime, lastTime, nowTime; // 待ち時間、最後の取得時間、今の時間
    static int updateTime, lastUpdate;      // 更新時間、最後の更新時間
    static float count, fps;                // フレームカウント、FPS

public:
    // 制限するFPSの値を設定
    static void SetLimitRate(float refreshRate) {
        frameTime = (int)(1000.0f / refreshRate); // 1フレームの時間の計算
    };

    // 現在のFPSを計算する間隔を設定
    static void SetUpdateInterval(int updateInterval) {
        updateTime = updateInterval;
    };

    // 事前に指定したFPSに制限
    static void Limit();

    // 事前に指定した間隔で現在のFPSを計算
    static void Update();

    // FPSを取得（注意：float型）
    static float Get() {
        return fps;
    };
};