#pragma once

#define APP_NAME    "戦塔"
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
#include "SoundManager.h"
#include "inputCtrl.h"
#include "fpsCtrl.h"

#include "DxLib.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

// ゲームメイン処理系
class GameScene;
#include "game_ui.h"
#include "Player.h"
#include "weapon.h"
#include "second_weapon.h"
#include "Stage.h"
#include "Slime.h"
#include "Skeleton.h"
#include "Wizard.h"
#include "EnemyBullet.h"
#include "Minotaur.h"
#include "Devil_king.h"
#include "BigEnemyBullet.h"
#include "Common.h"

// ゲームメインシーン内のシーン（シーンを継承していない）
#include "map.h"
#include "weaponSelect.h"
#include "weaponLevelup.h"
#include "blacksmith.h"
#include "rest.h"

// シーン
#include "scene_title.h"
#include "scene_help.h"
#include "scene_game.h"
#include "scene_gameclear.h"
#include "scene_gameover.h"
#include "scene_result.h"
#include "scene_end.h"
#include "scene_credit.h"
#include "scene_load.h"

// デバッグ用
#include "scene_debug.h"
#include "kitamura_test.h"
#include "map_temp.h"