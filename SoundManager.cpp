#include"main.h"

SoundManager* SoundManager::manager = nullptr;

void SoundManager::CreateSoundManager()
{
	//オブジェクトが作成されていないならオブジェクトを作成する
	if (manager == nullptr)
	{
		manager = new SoundManager();
	}

	//BGMの設定
	SetBGM("bgm_title");
	SetBGM("bgm_map");
	SetBGM("bgm_weaponselection");
	SetBGM("bgm_normal");
	SetBGM("bgm_middleboss");
	SetBGM("bgm_middleboss_end");
	SetBGM("bgm_boss");
	SetBGM("bgm_smith");
	SetBGM("bgm_breakstage");
	SetBGM("bgm_breaktime");
	SetBGM("bgm_gameover");
	SetBGM("bgm_gameclear");

	//SEの設定
	SetSE("se_system_Title_decision_sound");	//タイトルのカーソル決定音
	SetSE("se_system_normal_decision");			//タイトル以外のカーソル決定音
	SetSE("se_system_select_syu");				//カーソル移動音
	SetSE("se_system_healing");					//回復の音
	SetSE("se_system_blessing");				//祝福の音
	SetSE("se_system_hammer");
	SetSE("se_system_cancel");
	SetSE("se_system_ng");
	SetSE("se_player_move");
	SetSE("se_player_avoidance");
	SetSE("se_enemy_damage");
	SetSE("se_enemy_shout");
	SetSE("se_enemy_tackle");
	SetSE("se_enemy_barrierdamage");
	SetSE("se_enemy_bossbullet");
	SetSE("se_weapon_sword_swing");
	SetSE("se_weapon_sword_Lv8");
	SetSE("se_weapon_sword_Lv7");
	SetSE("se_weapon_dagger_swing");
	SetSE("se_weapon_dagger_Lv8");
	SetSE("se_weapon_dagger_Lv7");
	SetSE("se_weapon_greatsword_swing");
	SetSE("se_weapon_greatsword_Lv8");
	SetSE("se_weapon_spear_swing");
	SetSE("se_weapon_spear_Lv8");
	SetSE("se_weapon_frail_swig");
	SetSE("se_weapon_frail_Lv8");
	SetSE("se_weapon_frail");
	SetSE("se_weapon_book_swing");
	SetSE("se_weapon_book_Lv7");
	SetSE("se_weapon_book_Lv8");

	//音量の調整
	SetVolumeBGMs(30);
	SetVolumeSEs(65);
	SetVolumeBGM("bgm_title", 35);
	SetVolumeBGM("bgm_weaponselection", 45);
	SetVolumeBGM("bgm_normal", 30);
	SetVolumeBGM("bgm_middleboss", 45);
	SetVolumeBGM("bgm_boss", 55);
	SetVolumeBGM("bgm_gameover", 50);
	SetVolumeBGM("bgm_gameclear", 30);
	SetVolumeSE("se_system_normal_decision", 70);
	SetVolumeSE("se_system_ng", 60);
	SetVolumeSE("se_system_cancel", 60);
	SetVolumeSE("se_enemy_damage", 30);
	SetVolumeSE("se_enemy_barrierdamage", 40);
	SetVolumeSE("se_enemy_shout", 65);
	SetVolumeSE("se_enemy_tackle", 65);
	SetVolumeSE("se_enemy_bossbullet", 30);
	SetVolumeSE("se_weapon_dagger_swing", 50);
	SetVolumeSE("se_weapon_sword_swing", 50);
	SetVolumeSE("se_weapon_greatsword_swing", 70);

	//再生位置の調整
	SetSoundSEPosition(100, "se_system_normal_decision");

	//ループ位置の調整
	SetLoopPosSoundMem(4798, GetBGMHandle("bgm_map"));
	SetLoopPosSoundMem(56400, GetBGMHandle("bgm_weaponselection"));
	SetLoopPosSoundMem(470, GetBGMHandle("bgm_normal"));
	SetLoopPosSoundMem(45900, GetBGMHandle("bgm_middleboss"));
	SetLoopPosSoundMem(22720, GetBGMHandle("bgm_boss"));
	SetLoopPosSoundMem(5100, GetBGMHandle("bgm_smith"));
}

void SoundManager::DeleteSoundManager()
{
	InitSoundMem();
	delete manager;
	manager = nullptr;
}

void SoundManager::SetBGM(const char* fileName)
{
	//ローカル変数iteratorにfileNameキーの検索結果を代入
	auto iterator = manager->bgm.find(string(fileName));

	//設定されていない場合
	if (iterator == manager->bgm.end())
	{
		//ファイルのパス
		string filePath;
		filePath = "resources/sounds/BGM/" + string(fileName) + ".wav";

		//キーにBGMを読みこむ
		manager->bgm[fileName] = LoadSoundMem(filePath.c_str());
	}
}

void SoundManager::SetSE(const char* fileName)
{
	//ローカル変数iteratorにfileNameキーの検索結果を代入
	auto iterator = manager->se.find(string(fileName));

	//設定されていない場合
	if (iterator == manager->se.end())
	{
		//ファイルのパス
		string filePath;
		filePath = "resources/sounds/SE/" + string(fileName) + ".wav";

		//キーにSEを読みこむ
		manager->se[fileName] = LoadSoundMem(filePath.c_str());
	}
}

void SoundManager::SetVolumeBGM(const char* fileName, const int volume)
{
	ChangeVolumeSoundMem(255 * volume / 100, manager->bgm[fileName]);
}

void SoundManager::SetVolumeSE(const char* fileName, const int volume)
{
	ChangeVolumeSoundMem(255 * volume / 100, manager->se[fileName]);
}

void SoundManager::SetVolumeBGMs(const int volume)
{	
	for (auto iterator = manager->bgm.begin(); iterator != manager->bgm.end(); ++iterator)
	{
		ChangeVolumeSoundMem(255 * volume / 100, manager->bgm[iterator->first]);
	}
}

void SoundManager::SetVolumeSEs(const int volume)
{
	for (auto iterator = manager->se.begin(); iterator != manager->se.end(); ++iterator)
	{
		ChangeVolumeSoundMem(255 * volume / 100, manager->se[iterator->first]);
	}
}

void SoundManager::SetSoundBGMPosition(LONGLONG time, const char* fileName)
{
	SetSoundCurrentTime(time, manager->bgm[fileName]);
	
}

void SoundManager::SetSoundBGMsPosition(LONGLONG time)
{
	for (auto iterator = manager->bgm.begin(); iterator != manager->bgm.end(); ++iterator)
	{
		SetSoundCurrentTime(time, manager->bgm[iterator->first]);
	}
}

void SoundManager::SetSoundSEPosition(LONGLONG time, const char* fileName)
{
	SetSoundCurrentTime(time, manager->se[fileName]);
}

void SoundManager::SetSoundSEsPosition(LONGLONG time)
{
	for (auto iterator = manager->se.begin(); iterator != manager->se.end(); ++iterator)
	{
		SetSoundCurrentTime(time, manager->se[iterator->first]);
	}
}

void SoundManager::PlaySoundBGM(const char* fileName, int playType, int topPositionFlag)
{
	if (!CheckSoundMem(manager->bgm[fileName]))
	{
		PlaySoundMem(manager->bgm[fileName], playType, topPositionFlag);
	}
}

void SoundManager::PlaySoundSE(const char* fileName, bool isSingleUnit, int playType, int topPositionFlag)
{
	if (isSingleUnit)
	{
		if (!CheckSoundMem(manager->se[fileName]))
		{
			PlaySoundMem(manager->se[fileName], playType, topPositionFlag);
		}
	}
	else
	{
		PlaySoundMem(manager->se[fileName], playType, topPositionFlag);
	}
}

void SoundManager::StopSoundBGM(const char* fileName)
{
	StopSoundMem(manager->bgm[fileName]);
}

void SoundManager::StopSoundBGMs()
{
	for (auto iterator = manager->bgm.begin(); iterator != manager->bgm.end(); ++iterator)
	{
		StopSoundMem(manager->bgm[iterator->first]);
	}
}

void SoundManager::StopSoundSE(const char* fileName)
{
	StopSoundMem(manager->se[fileName]);
}

void SoundManager::StopSoundSEs()
{
	for (auto iterator = manager->se.begin(); iterator != manager->se.end(); ++iterator)
	{
		StopSoundMem(manager->se[iterator->first]);
	}
}
