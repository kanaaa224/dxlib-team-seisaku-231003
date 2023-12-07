#include "main.h"

Help::Help()
{
	//ƒwƒ‹ƒv‰æ‘œ‚Ì“Ç‚Ýž‚Ý
	if (HelpImage1 = LoadGraph("resources/images/Help/Help_Img2.png")) {}
	if (HelpImage2 = LoadGraph("resources/images/Help/Help_Stage_Img.png")) {}
	if (HelpImage3 = LoadGraph("resources/images/Help/Help_weapon_system.png")) {}

	Help_Abtn_Count = 0;
}

Help::~Help()
{
	DeleteGraph(HelpImage1);
	DeleteGraph(HelpImage2);
	DeleteGraph(HelpImage3);
}

Scene*Help::update()
{
	//ƒwƒ‹ƒv2‰æ–Ê‚Ö‘JˆÚ
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS) {

		SoundManager::PlaySoundSE("se_system_normal_decision", DX_PLAYTYPE_BACK);
		Help_Abtn_Count++;
	}
	else {
		SoundManager::StopSoundSEs();
	}

	if (Help_Abtn_Count > 2 && Help_Abtn_Count < 4) {

		SoundManager::StopSoundBGMs();
		return new GameScene;
	}
	else if(Help_Abtn_Count > 1 && Help_Abtn_Count < 3 && InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS) {

		SoundManager::StopSoundBGMs();
		return new Title;
	}
	
	return this;
}

void Help::draw()const
{
	if (Help_Abtn_Count == 0) {

		DrawGraph(0, 0, HelpImage1, TRUE);
	}
	else if(Help_Abtn_Count > 0 && Help_Abtn_Count < 2){//1

		//ƒwƒ‹ƒv‰æ‘œ‚Ì•\Ž¦
		DrawGraph(0, 0, HelpImage2, TRUE);
	}
	else if (Help_Abtn_Count > 1 && Help_Abtn_Count < 3) {//2


		//ƒwƒ‹ƒv‰æ‘œ‚Ì•\Ž¦
		DrawGraph(0, 0, HelpImage3, TRUE);
	}
}
