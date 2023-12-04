#pragma once
#include<DxLib.h>

class SoundManager
{
private:
	static SoundManager* manager;			//オブジェクト

	std::map<std::string, int>bgm;			//連想配列bgm
	std::map<std::string, int>se;			//連想配列se
public:
	//コンストラクタ
	SoundManager() {};

	//デストラクタ
	~SoundManager() {};

	//SoundManagerの作成
	static void CreateSoundManager();

	//SoundManagerの削除
	static void DeleteSoundManager();

	//連想配列に格納されたサウンドハンドルを取得する
	static int GetBGMHandle(const char* fileName) { return manager->bgm[fileName]; }

	//サウンドハンドルにBGMを設定する
	//＊fileNameにはファイルの名前だけ入れてください
	static void SetBGM(const char* fileName);

	//サウンドハンドルにSEを設定する
	//＊fileNameにはファイルの名前だけ入れてください
	static void SetSE(const char* fileName);

	//BGMの音量を設定する
	static void SetVolumeBGM(const char* fileName, const int volume);

	//SEの音量を設定する
	static void SetvolumeSE(const char* fileName, const int volume);

	//すべてのBGMの音量を設定する
	static void SetVolumeBGMs(const int volume);

	//すべてのSEの音量を設定する
	static void SetVolumeSEs(const int volume);

	//BGMを再生する
	//＊デフォルトの再生形式はループ、再生位置は先頭から
	static void PlaySoundBGM(const char* fileName, int playType = DX_PLAYTYPE_LOOP, int topPositionFlag = TRUE);

	//SEを再生する
	//＊デフォルトの再生形式はバック、再生位置は先頭から
	static void PlaySoundSE(const char* fileName, int playType = DX_PLAYTYPE_BACK, int topPositionFlag = TRUE);

	//BGMを停止する
	static void StopSoundBGM(const char* fileName);

	//すべてのBGMを停止する
	static void StopSoundBGMs();

	//SEを停止する
	static void StopSoundSE(const char* fileName);

	//すべてのSEを停止する
	static void StopSoundSEs();
};

