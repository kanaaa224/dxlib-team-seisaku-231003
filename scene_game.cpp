//////////////////////////////////////////////////
// ゲームメイン シーン
// 作成：
//////////////////////////////////////////////////
#include "main.h"

GameScene::GameScene() {
	state = 0;
	frameCounter = 0;

	//////////////////////////////////////////////////

	player = new Player;
	backimg = new Stage;
	Weapon = new weapon;
	secondweapon = new second_weapon;
	gameUI = new GameUI;

	//////////////////////////////////////////////////
	
	//
	weapon_selection = new Weapon_Selection();
	weapon_level_up = new WeaponLevelUp;

	is_weapon_selct = false;

	// レベルアップ画面用
	open_level_up = false;
	restor_cursor_position = true;


	//////////////////////////////////////////////////

	exp = level = 0; // 仮
};

GameScene::~GameScene() {
	delete player;
	delete backimg;
	delete Weapon;
	delete gameUI;
	delete weapon_level_up;
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
			restor_cursor_position = true;
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
		weapon_level_up->update(Weapon, secondweapon, restor_cursor_position);
		return this;
	}
	
	//敵//
	HitCheck();

	if (tmpSlimeNum < SLIME_1_STAGE_NUM) {
		slime[tmpSlimeNum] = new Slime(tmpSlimeNum, SLIME_1_STAGE_NUM);
		tmpSlimeNum++;
	}

	if (stage == 1) {
		for (int i = 0; i < SLIME_1_STAGE_NUM; i++) {
			if (slime[i] != nullptr) {
				slime[i]->Update(i, player, Weapon,*(backimg));
				if (slime[i]->GetHP() <= 0) {
					slime[i] = nullptr;
				}
			}
		}
	}

	

	//武器と敵の当たり判定
	if (stage == 1) {
		for (int i = 0; i < SLIME_1_STAGE_NUM; i++) {
			if (slime[i] != nullptr) {
				if (Weapon->WeaponCollision(slime[i]->GetEnemyLocation(), slime[i]->GetEnemyRadius())) {
					if (slime[i]->GetHitFrameCnt() == 0) {
						slime[i]->SetHitWeaponFlg();
						slime[i]->SetHitHP(Weapon->GetDamage());
						slime[i]->SetHit1stFrameFlg(true);
					}
				}
				if (secondweapon->WeaponCollision(slime[i]->GetEnemyLocation(), slime[i]->GetEnemyRadius())) {
					if (slime[i]->GetHitFrameCnt() == 0) {
						slime[i]->SetHitWeaponFlg();
						slime[i]->SetHitHP(Weapon->GetDamage());
						slime[i]->SetHit1stFrameFlg(true);
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
	player->SetLeftTop(backimg->GetStageArray(0));
	player->SetRightBottom(backimg->GetStageArray(3));
	backimg->update(player->Player_MoveX(), player->Player_MoveY());
	player->update();
	Weapon->Update(player->Player_AimingX(), player->Player_AimingY(),player->Player_Location());
	secondweapon->Update(player->Player_AimingX(), player->Player_AimingY(),player->Player_Location());
	gameUI->update(this);


	// ゲームオーバー画面へ遷移
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_Y) == PRESS) {
		return new GameOverScene;
	}
	
	for (int i = 0; i < MAX_SLIME_NUM; i++) {
		if (slime[i] != nullptr) {
			if (slime[i]->GetHitFrameCnt() >= DAMAGE_STOP_FRAME) {
				slime[i]->SetHit1stFrameFlg(false);
				slime[i]->SetHitFrameCnt(0);
			}
		}
	}
	/*if (hitFrameCounter >= DAMAGE_STOP_FRAME) {
		hitFlg = false;
		hitFrameCounter = 0;
	}*/

	for (int i = 0; i < MAX_SLIME_NUM; i++) {
		if (slime[i] != nullptr) {
			if (slime[i]->GetHit1stFrameFlg() == true) {
				slime[i]->hitFrameCntInc();
			}
		}
	}
	/*if (hitFlg == true) {
		hitFrameCounter++;
	}*/
	frameCounter++;






	//////////////////////////////////////////////////
	// GameUI 仮
	gameUI->setBanner("ミッション（仮）", "全てのモンスターを倒してください");

	int enemies = 0;
	for (int i = 0; i < SLIME_1_STAGE_NUM; i++) {
		if (slime[i] != nullptr) enemies++;
	};

	if ((int)FPSCtrl::Get()) {
		if (frameCounter % ((int)FPSCtrl::Get() * 2) == 0) exp += 200;
		if (exp > 2000) {
			exp = 0;
			level++;
		};
	};

	gameUI->setScore((SLIME_1_STAGE_NUM - enemies) * 100);
	gameUI->setHP(player->GetPlayer_HP(), 100, (int)(player->GetPlayer_HP()));
	gameUI->setEXP(exp, 2000, (exp / 20));
	gameUI->setLevel(level);

	gameUI->setFloor(-2);
	gameUI->setEnemy(enemies, SLIME_1_STAGE_NUM);

	if(state) gameUI->setWeapon({ Weapon->GetWeaponType(), Weapon->GetWeaponLevel(), true }, { greatSword, 5, false });
	else      gameUI->setWeapon({ Weapon->GetWeaponType(), Weapon->GetWeaponLevel(), false }, { greatSword, 5, true });
	//////////////////////////////////////////////////
	if (enemies <= 0) {
		gameUI->setBanner("クリア！", "全てのモンスターを倒しました");
		if (gameUI->getState() == 2) {
			gameUI->init();
			gameUI->setState(banner);
		};
		if (gameUI->getState() == 1) return new Map;
	};
	if (player->GetPlayer_HP() <= 0) {
		gameUI->setBanner("失敗、、", "体力が尽きました、、");
		if (gameUI->getState() == 2) {
			gameUI->init();
			gameUI->setState(banner);
		};
		if (gameUI->getState() == 1) return new GameOverScene;
	};
	//////////////////////////////////////////////////
	gameUI->setEnemyHP("魔王 猫スライム", enemies, SLIME_1_STAGE_NUM, enemies * 10); // 怪奇現象発生中
	//printfDx("%d\n", static_cast<int>((SLIME_1_STAGE_NUM / c) * 100.0f));
	//printfDx("%f\n", (c / SLIME_1_STAGE_NUM) * 100.0f);
	//////////////////////////////////////////////////
	if (InputCtrl::GetKeyState(KEY_INPUT_SPACE) == PRESS || InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS) {
		if (state) state = 0;
		else state++;
	};
	//////////////////////////////////////////////////
	

	return this;
};

void GameScene::draw() const {
	//DrawExtendGraph(0, 0, 1280, 720, img_background, TRUE); // 仮

	backimg->draw();
	Weapon->Draw();
	secondweapon->Draw();
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
	else {
		gameUI->draw();
		gameUI->drawEnemyHP();
	};

	// 武器のレベルアップ画面描画
	if (open_level_up)
	{
		weapon_level_up->draw();
	}
};

void GameScene::HitCheck()
{
	//スライムの当たり判定
	for (int i = 0; i < MAX_SLIME_NUM; i++) {
		if (slime[i] != nullptr) {
			HitEnemy(slime[i]);
			for (int j = 0; j < MAX_SLIME_NUM; j++) {
				if (slime[j] != nullptr && i != j) {
					if (slime[i]->CheckCollision(static_cast<SphereCollider>(*slime[j]), player) == HIT) {//当たっている
						slime[i]->SetHitFlg(HIT);
						slime[j]->SetHitFlg(HIT);

						////
						//slime[i]->SetHitLocation_X(slime[j]->GetLX());
						//slime[i]->SetHitLocation_Y(slime[j]->GetLY());
						//slime[i]->SetHitVector_X(slime[j]->GetVX());
						//slime[i]->SetHitVector_Y(slime[j]->GetVY());
						////
						//slime[j]->SetHitLocation_X(slime[i]->GetLX());
						//slime[j]->SetHitLocation_Y(slime[i]->GetLY());
						//slime[j]->SetHitVector_X(slime[i]->GetVX());
						//slime[j]->SetHitVector_Y(slime[i]->GetVY());

						slime[i]->HitVectorCale(static_cast<SphereCollider>(*slime[j]), player);
						slime[j]->HitVectorCale(static_cast<SphereCollider>(*slime[i]), player);
					}

					/*if (slime[i]->GetHitFlg() == HIT) {
						if (slime[i]->CheckCollision(static_cast<SphereCollider>(*slime[j]), player) == NO_COLLISION) {
							slime[i]->SetHitFlg(NO_COLLISION);
						}
					}*/
				}
			}
		}
	}
}

void GameScene::HitEnemy(EnemyBase* enemy)
{
	if (player->GetIsHit() != true && player->GetPlayer_Avoidance() != true)
	{
		if (player->CheckCollision(*(enemy), player) == HIT)
		{
			player->SetPlayer_HP(enemy->GetDamage());
			player->SetIsHit(true);
		}
	}
}
