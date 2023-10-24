#pragma once

#define APP_NAME    "タイトル未設定"
#define APP_VERSION "v0.0.0"

#define SCREEN_WIDTH  1280 // 画面サイズ（幅）
#define SCREEN_HEIGHT 720  // 画面サイズ（高さ）
#define SCREEN_FPS    60   // 起動時の最大FPS

////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <math.h>

#include <time.h>   // 日付時刻関連
#include <iostream> // 入出力関連
#include <fstream>  // ファイル操作関連
#include <string>   // 文字列操作関連
#include <map>      // 連想配列
#include <vector>   // 動的配列（要素を追加したり削除したり）
#include <sstream>  // 文字列ストリーム操作（文字列から数値への変換や数値から文字列への変換）

#define _USE_MATH_DEFINES
using std::string;
using std::to_string;

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "sceneManager.h"
#include "inputCtrl.h"
#include "fpsCtrl.h"

#include "DxLib.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

// ゲームメイン処理のヘッダーファイル
class GameScene;
//#include "game_collider.h"
//#include "game_characterBase.h"
//#include "game_bullet.h"
//#include "game_bulletSpawner.h"
//#include "game_nwaySpawner.h"
//#include "game_player.h"
#include "game_ui.h"
//#include "game_main.h"

// 各シーンのヘッダーファイル
#include "scene_debug.h"
//#include "scene_title.h"
#include "scene_game.h"
//#include "scene_result.h"
#include "kitamura_test.h"