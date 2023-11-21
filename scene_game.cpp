//////////////////////////////////////////////////
// ゲームメイン シーン
// 作成：
//////////////////////////////////////////////////
#include "main.h"

GameScene::GameScene() {
	mode         = GameSceneMode::map;
	state        = play;
	frameCounter = 0;

	//////////////////////////////////////////////////

	player  = new Player;
	stage   = new Stage;
	weaponA = new weapon;
	weaponB = new second_weapon;
	gameUI  = new GameUI;

	//////////////////////////////////////////////////

	map           = new Map;
	weaponSelect  = new Weapon_Selection(weapon_selected);
	weaponLevelup = new WeaponLevelUp;
	blacksmith    = new Blacksmith;
	rest = new Rest(gameUI);

	//////////////////////////////////////////////////
	
	minotaur = new Minotaur;

	//////////////////////////////////////////////////



	swordHitFlg = false;

	weapon_selected = false;

	// レベルアップ画面用
	restor_cursor_position = true;

	//////////////////////////////////////////////////

	exp = level = 0; // 仮

	map->ResetStage();

	gameUI->setBanner("ステージ " + std::to_string(nowStage), "全てのモンスターを倒してください");
};

GameScene::~GameScene() {
	delete player;
	delete stage;
	delete weaponA;
	delete weaponB;
	delete gameUI;

	delete map;
	delete weaponSelect;
	delete weaponLevelup;
	delete blacksmith;
	delete rest;

	delete minotaur;
};

Scene* GameScene::update() {
	if (InputCtrl::GetKeyState(KEY_INPUT_ESCAPE)) return new DebugScene(); // 仮

	// ポーズ
	if (InputCtrl::GetKeyState(KEY_INPUT_P) == PRESS || InputCtrl::GetButtonState(XINPUT_BUTTON_START) == PRESS) {
		if (state) state = 0;
		else state++;
	};

	if (state == pause) return this;

	//////////////////////////////////////////////////

	if (mode >= GameSceneMode::main && gameUI->getState() == 2) {
		// 武器のレベルアップ画面 - Xボタンで表示と非表示を切り替え
		if (InputCtrl::GetKeyState(KEY_INPUT_X) == PRESS || InputCtrl::GetButtonState(XINPUT_BUTTON_X) == PRESS) {
			if (mode == GameSceneMode::weaponLevelup) mode = GameSceneMode::main;
			else mode = GameSceneMode::weaponLevelup;
		};
	};

	// 鍛冶ステージテスト用
	if (InputCtrl::GetKeyState(KEY_INPUT_B) == PRESS) {
		if (mode == GameSceneMode::blacksmith) mode = GameSceneMode::main;
		else mode = GameSceneMode::blacksmith;
	};

	// 強制ゲームオーバー
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_Y) == PRESS) return new GameOverScene;

	//////////////////////////////////////////////////

	if (mode == GameSceneMode::main) {
		gameUI->update(this);

		if (gameUI->getState() >= 1) {

			//敵
			HitCheck();
			SlimeUpdate();
			SkeletonUpdate();
			WizardUpdate();
			MinotaurUpdate();


			//武器と敵の当たり判定
			if (true/*nowStage == 1*/) {
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
								if (weaponA->GetIsAttacking() && !swordHitFlg) {
									swordHitFlg = true;
									weaponA->SetHitCnt(true);
									weaponA->SwordLevel8(player);
									weaponA->SwordLevel8Heel(player);
								}
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
								if (weaponA->GetIsAttacking() && !swordHitFlg) {
									swordHitFlg = true;
									weaponA->SetHitCnt(true);
									weaponA->SwordLevel8(player);
									weaponA->SwordLevel8Heel(player);
								}
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

				for (int i = 0; i < WIZARD_1_STAGE_NUM; i++) {
					if (wizard[i] != nullptr) {
						if (weaponA->WeaponCollision(wizard[i]->GetEnemyLocation(), wizard[i]->GetEnemyRadius())) {
							if (wizard[i]->GetHitFrameCnt() == 0) {
								wizard[i]->SetHitWeaponFlg();
								//ダメージアップ
								if (weaponB->GetWeaponType() == book && weaponB->GetWeaponLevel() == 7) {
									wizard[i]->SetHitHP(weaponA->GetDamage() * 2);
								}
								else {
									wizard[i]->SetHitHP(weaponA->GetDamage());
								}
								wizard[i]->SetHit1stFrameFlg(true);
								if (weaponA->GetIsAttacking() && !swordHitFlg) {
									swordHitFlg = true;
									weaponA->SetHitCnt(true);
									weaponA->SwordLevel8(player);
								}
							}
						}
						if (weaponB->WeaponCollision(wizard[i]->GetEnemyLocation(), wizard[i]->GetEnemyRadius())) {
							if (wizard[i]->GetHitFrameCnt() == 0) {
								wizard[i]->SetHitWeaponFlg();
								wizard[i]->SetHitHP(weaponB->GetDamage());
								wizard[i]->SetHit1stFrameFlg(true);
							}
						}
					}
				}
			}

			if (!weaponA->GetIsAttacking() && weaponA->GetOldIsAttacking()) {
				if (!swordHitFlg) {
					weaponA->SetHitCnt(false);
				}
				swordHitFlg = false;
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

			////////////
			player->SetLeftTop(stage->GetStageArray(0));
			player->SetRightBottom(stage->GetStageArray(8));
			stage->update(player->Player_MoveX(), player->Player_MoveY());
			player->update();
			weaponA->Update(player->Player_AimingX(), player->Player_AimingY(), player->Player_Location(), player);
			Vector tmpV = { player->Player_MoveX(),player->Player_MoveY(),0 };
			weaponB->Update(player->Player_AimingX(), player->Player_AimingY(), player->Player_Location(), tmpV, player);

			EnemyInc();//敵のダメージストップ関係

			//////////////////////////////////////////////////
			// GameUI 仮
			//gameUI->setScore((SLIME_1_STAGE_NUM - enemies) * 100);
			gameUI->setHP(player->GetPlayer_HP(), 100, (int)(player->GetPlayer_HP()));
			gameUI->setEXP(exp, 2000, (exp / 20));
			gameUI->setLevel(level);

			gameUI->setFloor(nowStage);
			gameUI->setEnemy(getEnemiesNum(0), SLIME_1_STAGE_NUM);

			gameUI->setWeapon({ weaponA->GetWeaponType(), weaponA->GetWeaponLevel(), false }, { weaponB->GetWeaponType(), weaponB->GetWeaponLevel(), false });
			//////////////////////////////////////////////////
			if (getEnemiesNum(0) <= 0 && frameCounter) {
				gameUI->setBanner("クリア！", "全てのモンスターを倒しました");
				if (gameUI->getState() == 2) {
					gameUI->init();
					gameUI->setState(banner);
				};
				if (gameUI->getState() == 1) {
					//GameScene();
					map->ClearStage();
					//return new Map;

					init();
					nowStage++;
					mode = GameSceneMode::map;
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
			if (InputCtrl::GetKeyState(KEY_INPUT_V) == PRESSED) gameUI->setEnemyHP("魔王 猫スライム", getEnemiesNum(0), SLIME_1_STAGE_NUM, getEnemiesNum(0) * 10); // 怪奇現象発生中
			//printfDx("%d\n", static_cast<int>((SLIME_1_STAGE_NUM / c) * 100.0f));
			//printfDx("%f\n", (c / SLIME_1_STAGE_NUM) * 100.0f);
			//////////////////////////////////////////////////
		};

		frameCounter++;
	};

	if (mode == GameSceneMode::weaponSelect) {
		weaponSelect->update(weaponA, weaponB, weapon_selected, mode);
		return this;
	};

	if (mode == GameSceneMode::weaponLevelup) {
		weaponLevelup->update(weaponA, weaponB, restor_cursor_position);
		return this;
	};

	//////////////////////////////////////////////////

	if (mode == GameSceneMode::map) {
		map->update(mode, weapon_selected);
		return this;
	};

	if (mode == GameSceneMode::blacksmith) {
		blacksmith->update(weaponA, weaponB, weaponLevelup);
		weaponLevelup->SetIsBlacksmith(false);
		return this;
	};

	if (mode == GameSceneMode::rest)
	{
		map->ClearStage();
		rest->update(player, mode, nowStage);
		return this;
	}

	return this;
};

void GameScene::draw() const {
	if (mode >= GameSceneMode::main) {
		stage->draw();

		player->draw();

		weaponA->Draw();
		weaponB->Draw();

		// 敵
		SlimeDraw();
		SkeletonDraw();
		WizardDraw();
		EnemyBulletDraw();
		MinotaurDraw();

		//////////////////////////////////////////////////

		if (mode == GameSceneMode::weaponSelect) {
			weaponSelect->draw(weapon_selected);
		}
		else {
			gameUI->draw();
			if (InputCtrl::GetKeyState(KEY_INPUT_V) == PRESSED) gameUI->drawEnemyHP();

			//gameUI->drawHP(); // プレイヤーHP単体表示
		};

		if (mode == GameSceneMode::weaponLevelup) weaponLevelup->draw();
	};

	//////////////////////////////////////////////////

	if (mode == GameSceneMode::map) map->draw();

	if (mode == GameSceneMode::blacksmith) blacksmith->draw(weaponLevelup);
	if (mode == GameSceneMode::main) 	DrawFormatString(0, 80, 0xffffff, "キーボードBで鍛冶画面");

	if (mode == GameSceneMode::rest)rest->draw();

	//////////////////////////////////////////////////

	if (state == pause) gameUI->drawPause();
};

void GameScene::init() {
	//delete player;
	//player = new Player();

	delete stage;
	stage = new Stage();

	weaponA->InitWeapon();
	
	for (int i = 0; i < SLIME_1_STAGE_NUM; i++) {
		slime[i] = nullptr;
	};
	tmpSlimeNum = 0;
	for (int i = 0; i < SKELETON_1_STAGE_NUM; i++) {
		skeleton[i] = nullptr;
	};
	tmpSkeletonNum = 0;
	for (int i = 0; i < WIZARD_1_STAGE_NUM; i++) {
		wizard[i] = nullptr;
	};
	tmpWizardNum = 0;
	for (int i = 0; i < MAX_BULLET_NUM; i++) {
		enemyBullet[i] = nullptr;
	};
	tmpBulletNum = 0;

	gameUI->setBanner("ステージ " + std::to_string(nowStage), "全てのモンスターを倒してください");
	gameUI->init();
	gameUI->setState(banner);
};

int GameScene::getEnemiesNum(int type) {
	int enemies = 0;

	if (type == 0) {
		for (int i = 0; i < SLIME_1_STAGE_NUM; i++) {
			if (slime[i] != nullptr) enemies++;
		};

		for (int i = 0; i < SKELETON_1_STAGE_NUM; i++) {
			if (skeleton[i] != nullptr) enemies++;
		};

		for (int i = 0; i < WIZARD_1_STAGE_NUM; i++) {
			if (wizard[i] != nullptr) enemies++;
		};
	};

	if (type == 1) {
		for (int i = 0; i < SLIME_1_STAGE_NUM; i++) {
			if (slime[i] != nullptr) enemies++;
		};
	};

	return enemies;
};


//////////////////////////////////////////////////
// 当たり判定・敵の処理
//////////////////////////////////////////////////

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

	for (int i = 0; i < MAX_BULLET_NUM; i++) {
		if (enemyBullet[i] != nullptr) {
			if (HitEnemy(enemyBullet[i]) == true) {
				enemyBullet[i] = nullptr;
				tmpBulletNum--;
			}
		}
	}
}

bool GameScene::HitEnemy(EnemyBase* enemy)
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
			return true;
		}
	}
	return false;
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
	if (true/*nowStage == 1*/) {
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
	else if (nowStage == 2) {
		if (tmpSlimeNum < SLIME_2_STAGE_NUM) {
			slime[tmpSlimeNum] = new Slime(tmpSlimeNum, SLIME_2_STAGE_NUM);
			tmpSlimeNum++;
		}
		for (int i = 0; i < SLIME_2_STAGE_NUM; i++) {
			if (slime[i] != nullptr) {
				slime[i]->Update(i, player, weaponA, *(stage));
				if (slime[i]->GetHP() <= 0) {
					slime[i] = nullptr;
				}
			}
		}
	}
}

void GameScene::SlimeDraw() const
{
	for (int i = 0; i < MAX_SLIME_NUM; i++) {
		if (slime[i] != nullptr) {
			slime[i]->Draw(i);
		}
	}
}

//----------スケルトン----------//
void GameScene::SkeletonUpdate()
{
	if (true/*nowStage == 1*/) {
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

void GameScene::SkeletonDraw() const
{
	for (int i = 0; i < MAX_SKELETON_NUM; i++) {
		if (skeleton[i] != nullptr) {
			skeleton[i]->Draw(i);
		}
	}
}

//----------魔法使い----------//
void GameScene::WizardUpdate()
{
	if (true/*nowStage == 1*/) {
		if (tmpWizardNum < WIZARD_1_STAGE_NUM) {
			wizard[tmpWizardNum] = new Wizard(tmpWizardNum, WIZARD_1_STAGE_NUM);
			tmpWizardNum++;
		}
		for (int i = 0; i < WIZARD_1_STAGE_NUM; i++) {
			if (wizard[i] != nullptr) {
				wizard[i]->Update(i, player, weaponA, *(stage));

				if (wizard[i]->GetShootFlg() == true) {
					EnemyBulletUpdate(wizard[i]->GetEnemyLocation());
					if (wizard[i]->GetCreateBulletFlg() == true) {//弾の生成処理
						if (tmpBulletNum < MAX_BULLET_NUM) {
							enemyBullet[tmpBulletNum] = new EnemyBullet(wizard[i]->GetEnemyLocation() , player);
						}
						tmpBulletNum++;
					}
				}

				if (wizard[i]->GetHP() <= 0) {
					wizard[i] = nullptr;
				}
			}
		}
	}
}

void GameScene::WizardDraw() const
{
	for (int i = 0; i < WIZARD_1_STAGE_NUM; i++) {
		if (wizard[i] != nullptr) {
			wizard[i]->Draw(i);
		}
	}
}

//----------弾----------//
void GameScene::EnemyBulletUpdate(Location location)
{
	for (int i = 0; i < MAX_BULLET_NUM; i++) {
		if (enemyBullet[i] != nullptr) {
			enemyBullet[i]->Update(player);
			if (enemyBullet[i]->GetlifeTimeCnt() <= 0) {
				enemyBullet[i] = nullptr;
				tmpBulletNum--;
			}
		}
	}
}

void GameScene::EnemyBulletDraw() const
{
	for (int i = 0; i < MAX_BULLET_NUM; i++) {
		if (enemyBullet[i] != nullptr) {
			enemyBullet[i]->Draw();
		}
	}
}

void GameScene::MinotaurUpdate()
{
	minotaur->Update();
}

void GameScene::MinotaurDraw() const
{
	minotaur->Draw();
}
