//////////////////////////////////////////////////
// 入力 コントローラー
// 作成：kanaaa224
//////////////////////////////////////////////////
#pragma once

#include <math.h>
#include "DxLib.h"

#define PAD_BUTTONS   16  // ゲームコントローラー全ボタン数
#define KEYBOARD_KEYS 256 // キーボード全キー数
#define STICK_MAX 32767.f // スティック最大値

#define PRESS   1 // 押された瞬間
#define PRESSED 2 // 押されている間
#define RELEASE 3 // 離した瞬間

#define L 0
#define R 1

// スティック 構造体
struct PadStick {
	float x = 0, // 横軸値
		  y = 0; // 縦軸値
};

// マウスカーソル 構造体
struct MousePoint {
	int x = 0, // 横軸値
		y = 0; // 縦軸値
};

// 入力コントローラー クラス（ゲームコントローラー / キーボード・マウス）
class InputCtrl {
private:
	static char nowBtn[PAD_BUTTONS];  // 今回のボタン入力
	static char oldBtn[PAD_BUTTONS];  // 前回のボタン入力

	static XINPUT_STATE padInput;     // ゲームコントローラー入力状態

	static PadStick padLStick;       // 左スティック
	static PadStick padRStick;       // 右スティック

	static int nowKey[KEYBOARD_KEYS]; // 今回のキーボードキー入力

	static MousePoint mousePoint;     // マウスカーソルの位置
	static int nowMouseClick[2];      // 今回のマウスクリック入力
	static int oldMouseClick[2];      // 前回のマウスクリック入力

private:
	// コンストラクタ
	InputCtrl() = default;

public:
	// 入力状況の更新
	static void Update() {
		GetJoypadXInputState(DX_INPUT_KEY_PAD1, &padInput);
		for (int i = 0; i < PAD_BUTTONS; i++) {
			oldBtn[i] = nowBtn[i];
			nowBtn[i] = padInput.Buttons[i];
		};

		padLStick.x = padInput.ThumbLX;
		padLStick.y = padInput.ThumbLY;

		padRStick.x = padInput.ThumbRX;
		padRStick.y = padInput.ThumbRY;

		for (int i = 0; i < KEYBOARD_KEYS; i++) {
			if (nowKey[i] <= -1) nowKey[i] = 0;
		};
		GetHitKeyStateAllEx(nowKey);

		GetMousePoint(&mousePoint.x, &mousePoint.y);

		for (int i = 0; i < 2; i++) {
			oldMouseClick[i] = nowMouseClick[i];
			if ((GetMouseInput() & (i + 1)) != 0) nowMouseClick[i] = 1;
			else nowMouseClick[i] = 0;
		};
	};

	//////////////////////////////////////////////////
	// ゲームコントローラーの入力
	//////////////////////////////////////////////////

	// ボタンの状態を取得
	static int GetButtonState(int button) {
		if (nowBtn[button] == 1 && oldBtn[button] == 0)      return 1;
		else if (nowBtn[button] == 1)                        return 2;
		else if (nowBtn[button] == 0 && oldBtn[button] == 1) return 3;
		return 0;
	};

	// スティックの状態を取得（構造体）
	static PadStick GetStickState(int stickType) {
		if (stickType) return padRStick;
		return padLStick;
	};

	// スティックの傾き割合を取得（構造体）
	static PadStick GetStickRatio(int stickType) {
		PadStick stickRatio;
		stickRatio.x = padLStick.x / STICK_MAX;
		stickRatio.y = padLStick.y / STICK_MAX;
		if (stickType) {
			stickRatio.x = padRStick.x / STICK_MAX;
			stickRatio.y = padRStick.y / STICK_MAX;
		};
		stickRatio.x = round(stickRatio.x * 10.0f) / 10.0f;
		stickRatio.y = round(stickRatio.y * 10.0f) / 10.0f;
		return stickRatio;
	};

	//////////////////////////////////////////////////
	// キーボード・マウスの入力
	//////////////////////////////////////////////////

	// キーの状態を取得
	static int GetKeyState(int key) {
		if (nowKey[key] == 1)       return 1;
		else if (nowKey[key] >= 1)  return 2;
		else if (nowKey[key] <= -1) return 3;
		return 0;
	};

	// マウスの状態を取得
	static int GetMouseState(int button) {
		if (nowMouseClick[button] == 1 && oldMouseClick[button] == 0)      return 1;
		else if (nowMouseClick[button] == 1)                               return 2;
		else if (nowMouseClick[button] == 0 && oldMouseClick[button] == 1) return 3;
		return 0;
	};

	// マウスカーソル位置を取得（構造体）
	static MousePoint GetMouseCursor() {
		return mousePoint;
	};
};