//////////////////////////////////////////////////
// 戦闘シーン
// 作成：島袋
//////////////////////////////////////////////////
#include "main.h"

GameScene_Main::GameScene_Main() {
	state = 0;
	frameCounter = 0;

	player = new Player;

	stage = new Stage;

	weaponA = new weapon;
	weaponB = new second_weapon;
};

GameScene_Main::~GameScene_Main() {
	delete player;
	delete stage;
	delete weaponA;
	delete weaponB;
};

void GameScene_Main::update(GameScene* gameScene) {
	
	gameData = gameScene->gameData;

	//////////////////////////////////////////////////
	// 敵と武器
	//////////////////////////////////////////////////

	HitCheck();
	SlimeUpdate();
	SkeletonUpdate();
	WizardUpdate();
	for (int i = 0; i < MAX_WIZARD_NUM; i++) {
		if (wizard[i] != nullptr) {
			if (wizard[i]->GetCreateBulletFlg() == true) {
				//ここに弾の生成処理を書く
			}
		}
	}

	//武器と敵の当たり判定
	if (stage == 1) {
		for (int i = 0; i < SLIME_1_STAGE_NUM; i++) {
			if (slime[i] != nullptr) {
				if (weaponA->WeaponCollision(slime[i]->GetEnemyLocation(), slime[i]->GetEnemyRadius())) {
					if (slime[i]->GetHitFrameCnt() == 0) {
						slime[i]->SetHitWeaponFlg();
						//ダメージアップ
						if (weaponB->GetWeaponType() == book && weaponB->GetWeaponLevel() == 7) {
							slime[i]->SetHitHP(weaponA->GetDamage() * 2);
						}
						else {
							slime[i]->SetHitHP(weaponA->GetDamage());
						}
						slime[i]->SetHit1stFrameFlg(true);
					}
				}
				if (weaponB->WeaponCollision(slime[i]->GetEnemyLocation(), slime[i]->GetEnemyRadius())) {
					if (slime[i]->GetHitFrameCnt() == 0) {
						slime[i]->SetHitWeaponFlg();
						slime[i]->SetHitHP(weaponB->GetDamage());
						slime[i]->SetHit1stFrameFlg(true);
					}
				}
			}
		}

		for (int i = 0; i < SKELETON_1_STAGE_NUM; i++) {
			if (skeleton[i] != nullptr) {
				if (weaponA->WeaponCollision(skeleton[i]->GetEnemyLocation(), skeleton[i]->GetEnemyRadius())) {
					if (skeleton[i]->GetHitFrameCnt() == 0) {
						skeleton[i]->SetHitWeaponFlg();
						skeleton[i]->SetHitHP(weaponA->GetDamage());
						skeleton[i]->SetHit1stFrameFlg(true);
					}
				}
				if (weaponB->WeaponCollision(skeleton[i]->GetEnemyLocation(), skeleton[i]->GetEnemyRadius())) {
					if (skeleton[i]->GetHitFrameCnt() == 0) {
						skeleton[i]->SetHitWeaponFlg();
						skeleton[i]->SetHitHP(weaponA->GetDamage());
						skeleton[i]->SetHit1stFrameFlg(true);
					}
				}
			}
		}
	}

	//バリア
	if (weaponB->GetWeaponType() == book && weaponB->GetWeaponLevel() == 7 && weaponB->GetCoolTime() == 0) {
		weaponA->SetCoolTime(0.1f, true);
		weaponB->SetBarrierFlg(true);
		bookFlg = true;
	}
	else if (weaponB->GetCoolTime() < INIT_COOLTIME_BOOK_LEVEL7 * 0.5f && bookFlg == true) {
		weaponA->SetCoolTime(1.0f, false);
		weaponB->SetBarrierFlg(false);
		bookFlg = false;
	}


	//////////////////////////////////////////////////
	// プレイヤー
	//////////////////////////////////////////////////

	player->SetLeftTop(stage->GetStageArray(0));
	player->SetRightBottom(stage->GetStageArray(3));
	player->update();

	stage->update(player->Player_MoveX(), player->Player_MoveY());

	Vector tmpV = { player->Player_MoveX(), player->Player_MoveY(), 0 };
	weaponA->Update(player->Player_AimingX(), player->Player_AimingY(), player->Player_Location(), player);
	weaponB->Update(player->Player_AimingX(), player->Player_AimingY(), player->Player_Location(), tmpV);
	
	EnemyInc(); // 敵のダメージストップ関係


	//////////////////////////////////////////////////
	// デバッグ
	//////////////////////////////////////////////////

	//武器のレベルアップ（デバッグ用）
	if (!weaponA->GetLevelUpFlg()) {
		if (InputCtrl::GetKeyState(KEY_INPUT_1) == PRESS) {
			weaponA->SetWeaponType(sword);
		}
		if (InputCtrl::GetKeyState(KEY_INPUT_2) == PRESS) {
			weaponA->SetWeaponType(dagger);
		}
		if (InputCtrl::GetKeyState(KEY_INPUT_3) == PRESS) {
			weaponA->SetWeaponType(greatSword);
		}
	}

	if (!weaponB->GetLevelUpFlg()) {
		if (InputCtrl::GetKeyState(KEY_INPUT_4) == PRESS) {
			weaponB->SetWeaponType(spear);
		}
		if (InputCtrl::GetKeyState(KEY_INPUT_5) == PRESS) {
			weaponB->SetWeaponType(frail);
		}
		if (InputCtrl::GetKeyState(KEY_INPUT_6) == PRESS) {
			weaponB->SetWeaponType(book);
		}
	}


	frameCounter++;
};

void GameScene_Main::draw() const {
	stage->draw();

	weaponA->Draw();
	weaponB->Draw();

	player->draw();

	// 敵
	SlimeDraw();
	SkeletonDraw();
	WizardDraw();
};

void GameScene_Main::init() {

};












void GameScene_Main::HitCheck()
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

void GameScene_Main::HitEnemy(EnemyBase* enemy)
{
	if (player->GetIsHit() != true && player->GetPlayer_Avoidance() != true)
	{
		if (player->CheckCollision(*(enemy), player) == HIT)
		{
			//バリア
			if (!weaponB->GetBarrierFlg()) {
				player->SetPlayer_HP(enemy->GetDamage());
				player->SetIsHit(true);
			}

		}
	}
}

//----------敵----------//
void GameScene_Main::EnemyInc()
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
void GameScene_Main::SlimeUpdate()
{
	if (stage == 1) {
		if (tmpSlimeNum < SLIME_1_STAGE_NUM) {
			slime[tmpSlimeNum] = new Slime(tmpSlimeNum, SLIME_1_STAGE_NUM);
			tmpSlimeNum++;
		}
		for (int i = 0; i < SLIME_1_STAGE_NUM; i++) {
			if (slime[i] != nullptr) {
				slime[i]->Update(i, player, weaponA, *(stage));
				if (slime[i]->GetHP() <= 0) {
					slime[i] = nullptr;
				}
			}
		}
	}
	else if (stage == 2) {

	}
}

void GameScene_Main::SlimeDraw() const
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
void GameScene_Main::SkeletonUpdate()
{
	if (stage == 1) {
		if (tmpSkeletonNum < SKELETON_1_STAGE_NUM) {
			skeleton[tmpSkeletonNum] = new Skeleton(tmpSkeletonNum, SKELETON_1_STAGE_NUM);
			tmpSkeletonNum++;
		}
		for (int i = 0; i < SKELETON_1_STAGE_NUM; i++) {
			if (skeleton[i] != nullptr) {
				skeleton[i]->Update(i, player, weaponA, *(stage));
				if (skeleton[i]->GetHP() <= 0) {
					skeleton[i] = nullptr;
				}
			}
		}
	}
}

void GameScene_Main::SkeletonDraw() const
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
void GameScene_Main::WizardUpdate()
{
	if (stage == 1) {
		if (tmpWizardNum < WIZARD_1_STAGE_NUM) {
			wizard[tmpWizardNum] = new Wizard(tmpWizardNum, WIZARD_1_STAGE_NUM);
			tmpWizardNum++;
		}
		for (int i = 0; i < WIZARD_1_STAGE_NUM; i++) {
			if (wizard[i] != nullptr) {
				wizard[i]->Update(i, player, weaponA, *(stage));
				if (wizard[i]->GetHP() <= 0) {
					wizard[i] = nullptr;
				}
			}
		}
	}
}

void GameScene_Main::WizardDraw() const
{
	if (stage == 1) {
		for (int i = 0; i < WIZARD_1_STAGE_NUM; i++) {
			if (wizard[i] != nullptr) {
				wizard[i]->Draw(i);
			}
		}
	}
}