//////////////////////////////////////////////////
// ゲームメイン シーン
// 作成：
//////////////////////////////////////////////////
#include "main.h"

GameScene::GameScene() {
	state = 0;
	frameCounter = 0;

	player = new Player;
	backimg = new Stage;
	Weapon = new weapon;
	gameUI = new GameUI;

	
	//
	weapon_selection = new Weapon_Selection();
	weapon_level_up = new WeaponLevelUp;

	is_weapon_selct = false;
	open_level_up = false;

	is_hit = false;


	//////////////////////////////////////////////////

	//img_background = LoadGraph("./resources/images/background.png"); // 仮
};

GameScene::~GameScene() {

	delete player;
	delete backimg;
	delete Weapon;
	delete gameUI;

	//////////////////////////////////////////////////

	//DeleteGraph(img_background); // 仮
};

Scene* GameScene::update() {
	

	if (InputCtrl::GetKeyState(KEY_INPUT_ESCAPE)) return new DebugScene(); // 仮

	//武器選択画面
	if (is_weapon_selct != true)
	{
		weapon_selection->update(Weapon, is_weapon_selct);
		if (is_weapon_selct == true)
		{
			delete weapon_selection;
			weapon_selection = nullptr;
		}
		return this;
	}

	// 武器のレベルアップ画面
	// Xボタンで表示と非表示を切り替え
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_X) == PRESS)
	{
		if (open_level_up)
		{
			// 非表示
			open_level_up = false;
		}
		else
		{
			// 表示
			open_level_up = true;
		}
	}

	// 武器のレベルアップ画面を表示しているときは以下の処理をしない
	if (open_level_up)
	{
		weapon_level_up->update();
		return this;
	}

	//敵//
	if (tmpSlimeNum < SLIME_1_STAGE_NUM) {
		slime[tmpSlimeNum] = new Slime(tmpSlimeNum);
		tmpSlimeNum++;
	}

	if (stage == 1) {
		for (int i = 0; i < SLIME_1_STAGE_NUM; i++) {
			if (slime[i] != nullptr) {
				slime[i]->Update(i, player, Weapon);
				if (slime[i]->GetHP() <= 0) {
					slime[i] = nullptr;
				}
			}
		}
	}

	HitCheck();

	//武器と敵の当たり判定
	if (stage == 1) {
		for (int i = 0; i < SLIME_1_STAGE_NUM; i++) {
			if (slime[i] != nullptr) {
				if (Weapon->WeaponCollision(slime[i]->GetEnemyLocation(), slime[i]->GetEnemyRadius())) {
					if (hitFrameCounter == 0) {
						slime[i]->SetHitWeaponFlg();
						slime[i]->SetHitHP(Weapon->GetDamage());
						hitFlg = true;
					}
				}
			}
		}
	}

	//武器のレベルアップ（デバッグ用）
	if (!Weapon->GetLevelUpFlg()) {
		if (InputCtrl::GetKeyState(KEY_INPUT_1) == PRESS) {
			Weapon->SetWeaponType(sword);
		}
		if (InputCtrl::GetKeyState(KEY_INPUT_2) == PRESS) {
			Weapon->SetWeaponType(dagger);
		}
		if (InputCtrl::GetKeyState(KEY_INPUT_3) == PRESS) {
			Weapon->SetWeaponType(greatSword);
		}
	}
	////////////
	backimg->update();
	player->update();
	Weapon->Update(player->Player_AimingX(), player->Player_AimingY());
	gameUI->update(this);


	// ゲームオーバー画面へ遷移
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_Y) == PRESS) {
		return new GameOverScene;
	}
	
	if (hitFrameCounter >= DAMAGE_STOP_FRAME) {
		hitFlg = false;
		hitFrameCounter = 0;
	}

	if (hitFlg == true) {
		hitFrameCounter++;
	}
	frameCounter++;
	return this;
};

void GameScene::draw() const {
	//DrawExtendGraph(0, 0, 1280, 720, img_background, TRUE); // 仮

	backimg->draw();
	Weapon->Draw();
	player->draw();

	//敵//
	if (stage == 1) {
		for (int i = 0; i < MAX_SLIME_NUM; i++) {
			if (slime[i] != nullptr) {
				slime[i]->Draw(i);
			}
		}
	}
	////////////

	if (is_weapon_selct != true)
	{
		weapon_selection->draw();
	}

	// 武器のレベルアップ画面
	if (open_level_up)
	{
		weapon_level_up->draw();
	}

	if (is_hit)
	{
		DrawString(player->GetLocation().x - 12, player->GetLocation().y - 27, "Hit", 0xffffff);
	}

	//gameUI->draw();
}

void GameScene::HitCheck()
{
	//スライムの当たり判定
	for (int i = 0; i < MAX_SLIME_NUM; i++) {
		if (slime[i] != nullptr) {
			if (player->CheckCollision(*(slime[i]), player) == HIT)
			{
				is_hit = true;
			}
			//else
			//{
			//	is_hit = false;
			//}
			for (int j = 0; j < MAX_SLIME_NUM; j++) {
				if (slime[j] != nullptr && i != j) {
					if (slime[i]->CheckCollision(static_cast<SphereCollider>(*slime[j]), player) == HIT) {//当たっている
						slime[i]->SetHitFlg(HIT);
						slime[j]->SetHitFlg(HIT);
					}
					//else if (slime[i]->CheckCollision(static_cast<SphereCollider>(*slime[j]), player) == NO_COLLISION) {//当たってない
					//	if (slime[j]->CheckCollision(static_cast<SphereCollider>(*slime[i]), player) == NO_COLLISION) {//当たってない
					//		if (!slime[i]->GetHitFlg()) slime[i]->SetHitFlg(NO_COLLISION);
					//		if (!slime[j]->GetHitFlg()) slime[j]->SetHitFlg(NO_COLLISION);
					//	}
					//}
				}
			}
		}
	}
}