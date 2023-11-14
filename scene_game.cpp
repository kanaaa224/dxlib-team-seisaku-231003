//////////////////////////////////////////////////
// ゲームメイン シーン
// 作成：
//////////////////////////////////////////////////
#include "main.h"

GameScene::GameScene() {
	state = 1;
	frameCounter = 0;
	bookFlg = false;

	//////////////////////////////////////////////////

	player = new Player;
	backimg = new Stage;
	Weapon = new weapon;
	secondweapon = new second_weapon;
	gameUI = new GameUI;
	map = new Map;

	//////////////////////////////////////////////////
	
	//
	weapon_selection = new Weapon_Selection(weapon_selected);
	weapon_level_up = new WeaponLevelUp;
	blacksmith = new Blacksmith;

	is_weapon_select = false;
	weapon_selected = false;

	// レベルアップ画面用
	open_level_up = false;
	restor_cursor_position = true;


	//////////////////////////////////////////////////

	exp = level = 0; // 仮

	map->ResetStage();
};

GameScene::~GameScene() {
	delete player;
	delete backimg;
	delete Weapon;
	delete gameUI;
	delete weapon_level_up;
	delete map;
	delete blacksmith;
};

Scene* GameScene::update() {
	if (InputCtrl::GetKeyState(KEY_INPUT_ESCAPE)) return new DebugScene(); // 仮

	if (InputCtrl::GetKeyState(KEY_INPUT_P) == PRESS || InputCtrl::GetButtonState(XINPUT_BUTTON_START) == PRESS) {
		if (state) state = 0;
		else state++;
	};

	if (!state) return this; // Pause

	//////////////////////////////////////////////////

	if (map->GetIsMapMode())
	{
		map->update();
		return this;
	}

	//武器選択画面
	if (is_weapon_select != true)
	{
		weapon_selection->update(Weapon, secondweapon,is_weapon_select);
		if (is_weapon_select == true)
		{
			delete weapon_selection;
			weapon_selection = nullptr;
			weapon_selected = true;
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
		// 鍛冶ステージテスト用
		//blacksmith->update(Weapon, secondweapon, weapon_level_up);
		return this;
	}

	//敵//
	HitCheck();
	SlimeUpdate();
	SkeletonUpdate();
	WizardUpdate();

	//武器と敵の当たり判定
	if (stage == 1) {
		for (int i = 0; i < SLIME_1_STAGE_NUM; i++) {
			if (slime[i] != nullptr) {
				if (Weapon->WeaponCollision(slime[i]->GetEnemyLocation(), slime[i]->GetEnemyRadius())) {
					if (slime[i]->GetHitFrameCnt() == 0) {
						slime[i]->SetHitWeaponFlg();
						//ダメージアップ
						if (secondweapon->GetWeaponType() == book && secondweapon->GetWeaponLevel() == 7) {
							slime[i]->SetHitHP(Weapon->GetDamage() * 2);
						}
						else {
							slime[i]->SetHitHP(Weapon->GetDamage());
						}
						slime[i]->SetHit1stFrameFlg(true);
					}
				}
				if (secondweapon->WeaponCollision(slime[i]->GetEnemyLocation(), slime[i]->GetEnemyRadius())) {
					if (slime[i]->GetHitFrameCnt() == 0) {
						slime[i]->SetHitWeaponFlg();
						slime[i]->SetHitHP(secondweapon->GetDamage());
						slime[i]->SetHit1stFrameFlg(true);
					}
				}
			}
		}

		for (int i = 0; i < SKELETON_1_STAGE_NUM; i++) {
			if (skeleton[i] != nullptr) {
				if (Weapon->WeaponCollision(skeleton[i]->GetEnemyLocation(), skeleton[i]->GetEnemyRadius())) {
					if (skeleton[i]->GetHitFrameCnt() == 0) {
						skeleton[i]->SetHitWeaponFlg();
						skeleton[i]->SetHitHP(Weapon->GetDamage());
						skeleton[i]->SetHit1stFrameFlg(true);
					}
				}
				if (secondweapon->WeaponCollision(skeleton[i]->GetEnemyLocation(), skeleton[i]->GetEnemyRadius())) {
					if (skeleton[i]->GetHitFrameCnt() == 0) {
						skeleton[i]->SetHitWeaponFlg();
						skeleton[i]->SetHitHP(Weapon->GetDamage());
						skeleton[i]->SetHit1stFrameFlg(true);
					}
				}
			}
		}
	}

	//バリア
	if (secondweapon->GetWeaponType() == book && secondweapon->GetWeaponLevel() == 7 && secondweapon->GetCoolTime() == 0) {
		Weapon->SetCoolTime(0.1f, true);
		secondweapon->SetBarrierFlg(true);
		bookFlg = true;
	}
	else if (secondweapon->GetCoolTime() < INIT_COOLTIME_BOOK_LEVEL7 * 0.5f && bookFlg == true) {
		Weapon->SetCoolTime(1.0f, false);
		secondweapon->SetBarrierFlg(false);
		bookFlg = false;
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

	if (!secondweapon->GetLevelUpFlg()) {
		if (InputCtrl::GetKeyState(KEY_INPUT_4) == PRESS) {
			secondweapon->SetWeaponType(spear);
		}
		if (InputCtrl::GetKeyState(KEY_INPUT_5) == PRESS) {
			secondweapon->SetWeaponType(frail);
		}
		if (InputCtrl::GetKeyState(KEY_INPUT_6) == PRESS) {
			secondweapon->SetWeaponType(book);
		}
	}

	////////////
	player->SetLeftTop(backimg->GetStageArray(0));
	player->SetRightBottom(backimg->GetStageArray(3));
	backimg->update(player->Player_MoveX(), player->Player_MoveY());
	player->update();
	Weapon->Update(player->Player_AimingX(), player->Player_AimingY(),player->Player_Location(),player);
	Vector tmpV = { player->Player_MoveX(),player->Player_MoveY(),0 };
	secondweapon->Update(player->Player_AimingX(), player->Player_AimingY(), player->Player_Location(), tmpV);
	gameUI->update(this);


	// ゲームオーバー画面へ遷移
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_Y) == PRESS) {
		return new GameOverScene;
	}
	
	EnemyInc();//敵のダメージストップ関係

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

	//gameUI->setScore((SLIME_1_STAGE_NUM - enemies) * 100);
	gameUI->setHP(player->GetPlayer_HP(), 100, (int)(player->GetPlayer_HP()));
	gameUI->setEXP(exp, 2000, (exp / 20));
	gameUI->setLevel(level);

	gameUI->setFloor(-2);
	gameUI->setEnemy(enemies, SLIME_1_STAGE_NUM);

	gameUI->setWeapon({ Weapon->GetWeaponType(), Weapon->GetWeaponLevel(), false }, { secondweapon->GetWeaponType(), secondweapon->GetWeaponLevel(), false });
	//////////////////////////////////////////////////
	if (enemies <= 0) {
		gameUI->setBanner("クリア！", "全てのモンスターを倒しました");
		if (gameUI->getState() == 2) {
			gameUI->init();
			gameUI->setState(banner);
		};
		if (gameUI->getState() == 1) {
			////GameScene();
			map->ClearStage();
			map->SetIsMapMode(true);
			//return new Map;
		};
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


	return this;
};

void GameScene::draw() const {
	// 
	if (map->GetIsMapMode())
	{
		map->draw();
	}
	else
	{
		backimg->draw();
		Weapon->Draw();
		secondweapon->Draw();
		player->draw();

		//敵//
		SlimeDraw();
		SkeletonDraw();
		WizardDraw();
		////////////

		if (is_weapon_select != true)
		{
			weapon_selection->draw();
		}
		else {
			gameUI->draw();
			gameUI->drawEnemyHP();

			//gameUI->drawHP();
		};

		// 武器のレベルアップ画面描画
		if (open_level_up)
		{
			weapon_level_up->draw();
			// 鍛冶ステージテスト用
			//blacksmith->draw(weapon_level_up);
		}
	}

	if (!state) gameUI->drawPause();
};

void GameScene::HitCheck()
{
	//スライムの当たり判定
	for (int i = 0; i < MAX_SLIME_NUM; i++) {
		if (slime[i] != nullptr) {
			HitEnemy(slime[i]);//プレイヤーとの当たり判定
			for (int j = 0; j < MAX_SLIME_NUM; j++) {
				if (slime[j] != nullptr && i != j) {
					if (slime[i]->CheckCollision(static_cast<SphereCollider>(*slime[j]), player) == HIT) {//当たっている
						slime[i]->SetHitFlg(HIT);
						slime[j]->SetHitFlg(HIT);

						slime[i]->HitVectorCale(static_cast<SphereCollider>(*slime[j]), player);
						slime[j]->HitVectorCale(static_cast<SphereCollider>(*slime[i]), player);
					}
				}
			}
		}
	}

	//スケルトンの当たり判定
	for (int i = 0; i < MAX_SKELETON_NUM; i++) {
		if (skeleton[i] != nullptr) {
			HitEnemy(skeleton[i]);//プレイヤーとの当たり判定
			for (int j = 0; j < MAX_SKELETON_NUM; j++) {
				if (skeleton[j] != nullptr && i != j) {
					if (skeleton[i]->CheckCollision(static_cast<SphereCollider>(*skeleton[j]), player) == HIT) {
						skeleton[i]->SetHitFlg(HIT);
						skeleton[j]->SetHitFlg(HIT);

						skeleton[i]->HitVectorCale(static_cast<SphereCollider>(*skeleton[j]), player);
						skeleton[j]->HitVectorCale(static_cast<SphereCollider>(*skeleton[i]), player);
					}
				}
			}
		}
	}

	//魔法使いの当たり判定
	for (int i = 0; i < MAX_WIZARD_NUM; i++) {
		if (wizard[i] != nullptr) {
			HitEnemy(wizard[i]);//プレイヤーとの当たり判定
			for (int j = 0; j < MAX_WIZARD_NUM; j++) {
				if (wizard[j] != nullptr && i != j) {
					if (wizard[i]->CheckCollision(static_cast<SphereCollider>(*wizard[j]), player) == HIT) {
						wizard[i]->SetHitFlg(HIT);
						wizard[j]->SetHitFlg(HIT);

						wizard[i]->HitVectorCale(static_cast<SphereCollider>(*wizard[j]), player);
						wizard[j]->HitVectorCale(static_cast<SphereCollider>(*wizard[i]), player);
					}
				}
			}
		}
	}

	//スライムとスケルトンの当たり判定
	for (int i = 0; i < MAX_SLIME_NUM; i++) {
		if (slime[i] != nullptr) {
			for (int j = 0; j < MAX_SKELETON_NUM; j++) {
				if (skeleton[j] != nullptr) {
					if (slime[i]->CheckCollision(static_cast<SphereCollider>(*skeleton[j]), player) == HIT) {
						slime[i]->SetHitFlg(HIT);
						skeleton[j]->SetHitFlg(HIT);

						slime[i]->HitVectorCale(static_cast<SphereCollider>(*skeleton[j]), player);
						skeleton[j]->HitVectorCale(static_cast<SphereCollider>(*slime[i]), player);
					}
				}
			}
		}
	}

	//スライムと魔法使いの当たり判定
	for (int i = 0; i < MAX_SLIME_NUM; i++) {
		if (slime[i] != nullptr) {
			for (int j = 0; j < MAX_WIZARD_NUM; j++) {
				if (wizard[j] != nullptr) {
					if (slime[i]->CheckCollision(static_cast<SphereCollider>(*wizard[j]), player) == HIT) {
						slime[i]->SetHitFlg(HIT);
						wizard[j]->SetHitFlg(HIT);

						slime[i]->HitVectorCale(static_cast<SphereCollider>(*wizard[j]), player);
						wizard[j]->HitVectorCale(static_cast<SphereCollider>(*slime[i]), player);
					}
				}
			}
		}
	}

	//魔法使いとスケルトンの当たり判定
	for (int i = 0; i < MAX_SKELETON_NUM; i++) {
		if (skeleton[i] != nullptr) {
			for (int j = 0; j < MAX_WIZARD_NUM; j++) {
				if (wizard[j] != nullptr) {
					if (skeleton[i]->CheckCollision(static_cast<SphereCollider>(*wizard[j]), player) == HIT) {
						skeleton[i]->SetHitFlg(HIT);
						wizard[j]->SetHitFlg(HIT);

						skeleton[i]->HitVectorCale(static_cast<SphereCollider>(*wizard[j]), player);
						wizard[j]->HitVectorCale(static_cast<SphereCollider>(*skeleton[i]), player);
					}
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
			//バリア
			if (!secondweapon->GetBarrierFlg()) {
				player->SetPlayer_HP(enemy->GetDamage());
				player->SetIsHit(true);
			}
			
		}
	}
}

//----------敵----------//
void GameScene::EnemyInc()
{
	//スライム
	for (int i = 0; i < MAX_SLIME_NUM; i++) {
		if (slime[i] != nullptr) {
			if (slime[i]->GetHitFrameCnt() >= DAMAGE_STOP_FRAME) {
				slime[i]->SetHit1stFrameFlg(false);
				slime[i]->SetHitFrameCnt(0);
			}
		}
	}

	for (int i = 0; i < MAX_SLIME_NUM; i++) {
		if (slime[i] != nullptr) {
			if (slime[i]->GetHit1stFrameFlg() == true) {
				slime[i]->hitFrameCntInc();
			}
		}
	}

	//スケルトン
	for (int i = 0; i < MAX_SKELETON_NUM; i++) {
		if (skeleton[i] != nullptr) {
			if (skeleton[i]->GetHitFrameCnt() >= DAMAGE_STOP_FRAME) {
				skeleton[i]->SetHit1stFrameFlg(false);
				skeleton[i]->SetHitFrameCnt(0);
			}
		}
	}

	for (int i = 0; i < MAX_SKELETON_NUM; i++) {
		if (skeleton[i] != nullptr) {
			if (skeleton[i]->GetHit1stFrameFlg() == true) {
				skeleton[i]->hitFrameCntInc();
			}
		}
	}

	//魔法使い
	for (int i = 0; i < MAX_WIZARD_NUM; i++) {
		if (wizard[i] != nullptr) {
			if (wizard[i]->GetHitFrameCnt() >= DAMAGE_STOP_FRAME) {
				wizard[i]->SetHit1stFrameFlg(false);
				wizard[i]->SetHitFrameCnt(0);
			}
		}
	}

	for (int i = 0; i < MAX_WIZARD_NUM; i++) {
		if (wizard[i] != nullptr) {
			if (wizard[i]->GetHit1stFrameFlg() == true) {
				wizard[i]->hitFrameCntInc();
			}
		}
	}
}

//----------スライム----------//
void GameScene::SlimeUpdate()
{
	if (stage == 1) {
		if (tmpSlimeNum < SLIME_1_STAGE_NUM) {
			slime[tmpSlimeNum] = new Slime(tmpSlimeNum, SLIME_1_STAGE_NUM);
			tmpSlimeNum++;
		}
		for (int i = 0; i < SLIME_1_STAGE_NUM; i++) {
			if (slime[i] != nullptr) {
				slime[i]->Update(i, player, Weapon, *(backimg));
				if (slime[i]->GetHP() <= 0) {
					slime[i] = nullptr;
				}
			}
		}
	}
	else if (stage == 2) {

	}
}

void GameScene::SlimeDraw() const
{
	if (stage == 1) {
		for (int i = 0; i < MAX_SLIME_NUM; i++) {
			if (slime[i] != nullptr) {
				slime[i]->Draw(i);
			}
		}
	}
}

//----------スケルトン----------//
void GameScene::SkeletonUpdate()
{
	if (stage == 1) {
		if (tmpSkeletonNum < SKELETON_1_STAGE_NUM) {
			skeleton[tmpSkeletonNum] = new Skeleton(tmpSkeletonNum, SKELETON_1_STAGE_NUM);
			tmpSkeletonNum++;
		}
		for (int i = 0; i < SKELETON_1_STAGE_NUM; i++) {
			if (skeleton[i] != nullptr) {
				skeleton[i]->Update(i, player, Weapon, *(backimg));
				if (skeleton[i]->GetHP() <= 0) {
					skeleton[i] = nullptr;
				}
			}
		}
	}
}

void GameScene::SkeletonDraw() const
{
	if (stage == 1) {
		for (int i = 0; i < MAX_SKELETON_NUM; i++) {
			if (skeleton[i] != nullptr) {
				skeleton[i]->Draw(i);
			}
		}
	}
}

//----------魔法使い----------//
void GameScene::WizardUpdate()
{
	if (stage == 1) {
		if (tmpWizardNum < WIZARD_1_STAGE_NUM) {
			wizard[tmpWizardNum] = new Wizard(tmpWizardNum, WIZARD_1_STAGE_NUM);
			tmpWizardNum++;
		}
		for (int i = 0; i < WIZARD_1_STAGE_NUM; i++) {
			if (wizard[i] != nullptr) {
				wizard[i]->Update(i, player, Weapon, *(backimg));
				if (wizard[i]->GetHP() <= 0) {
					wizard[i] = nullptr;
				}
			}
		}
	}
}

void GameScene::WizardDraw() const
{
	if (stage == 1) {
		for (int i = 0; i < WIZARD_1_STAGE_NUM; i++) {
			if (wizard[i] != nullptr) {
				wizard[i]->Draw(i);
			}
		}
	}
}
