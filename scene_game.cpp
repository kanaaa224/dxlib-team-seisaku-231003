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
	rest          = new Rest(gameUI);

	//////////////////////////////////////////////////
	
	minotaur = new Minotaur;
	devilKing = new Devil_king;

	//////////////////////////////////////////////////

	swordHitFlg = false;
	bookFlg     = false;

	weapon_selected = false;

	// レベルアップ画面用
	restor_cursor_position = true;

	//////////////////////////////////////////////////

	hp    = 100;
	exp   = 0;
	level = 0;
	point = 0;

	currentFloor = 0;
	//currentStage = 0;
	battleMode   = 0;

	bossState = 0;


	map->ResetStage();

	SoundManager::SetBGM("bgm_normal");
	SoundManager::SetBGM("bgm_middleboss");
	SoundManager::SetBGM("bgm_middleboss_end");
	SoundManager::SetVolumeBGMs(50);
	SoundManager::SetVolumeSEs(50);
	SetLoopPosSoundMem(470, SoundManager::GetBGMHandle("bgm_normal"));
	SetLoopPosSoundMem(45900, SoundManager::GetBGMHandle("bgm_middleboss"));

	gameUI->setBanner(std::to_string(currentFloor + 1) + "F - 冒険の始まり", "全てのモンスターを倒し、塔の最上階を目指せ！", 1);


	// 仮 - 敵をどのステージでどれだけ出すかのデータ生成
	std::map<std::string, int> data;
	data["slime"]    = 10;
	data["skeleton"] = 0;
	data["wizard"]   = 0;
	shimabukuro.push_back(data);
	for (int i = 1; i < 20; i++) {
		data["slime"]    = 0;
		data["skeleton"] = 0;
		data["wizard"]   = 0;
		shimabukuro.push_back(data);
	};
	enemySpawnData = shimabukuro[currentFloor];

	// 仮 - 経験値の最大値データ生成
	for (int i = 1; i < 20; i++) {
		expData.push_back(i * 120);
	};
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
	delete devilKing;
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

	// 武器のレベルアップ画面（プレイヤーが動けるようになってから）
	if (mode >= GameSceneMode::main && gameUI->getState() == playerUI) {
		if (mode == GameSceneMode::weaponLevelup && weaponLevelup->GetCloseMode() == 2)
		{
			restor_cursor_position = true;
			mode = GameSceneMode::main;
		}
		// 武器のレベルアップ画面
		if (InputCtrl::GetKeyState(KEY_INPUT_X) == PRESS || InputCtrl::GetButtonState(XINPUT_BUTTON_X) == PRESS) {
			if (restor_cursor_position == true)
			{
				weaponLevelup->SetCloseMode(0);
			}
			mode = GameSceneMode::weaponLevelup;
		};
	};

#ifdef _DEBUG
	// 鍛冶ステージテスト用
	if (InputCtrl::GetKeyState(KEY_INPUT_B) == PRESS) {
		SoundManager::StopSoundBGMs();
		if (mode == GameSceneMode::blacksmith) mode = GameSceneMode::main;
		else mode = GameSceneMode::blacksmith;
	};


	// 強制ゲームクリア
	if (InputCtrl::GetButtonState(XINPUT_BUTTON_Y) == PRESS) {
		SoundManager::StopSoundBGMs();
		return new GameClearScene(weaponA, weaponB, map);
	}

	// デバッグ - Oキーで強制ボス戦
	if (InputCtrl::GetKeyState(KEY_INPUT_O) == PRESS) {
		SoundManager::StopSoundBGMs();
		battleMode = GameSceneBattleMode::boss;
	};

	// デバッグ - Iキーで強制中ボス戦
	if (InputCtrl::GetKeyState(KEY_INPUT_I) == PRESS) {
		SoundManager::StopSoundBGMs();
		battleMode = GameSceneBattleMode::midBoss;
	};
#endif
	//////////////////////////////////////////////////

	if (mode == GameSceneMode::main) {
		if (battleMode == GameSceneBattleMode::normal)
		{
			SoundManager::PlaySoundBGM("bgm_normal");
		}
		if (battleMode == GameSceneBattleMode::midBoss)
		{
			if (!CheckSoundMem(SoundManager::GetBGMHandle("bgm_middleboss_end")))
			{
				SoundManager::PlaySoundBGM("bgm_middleboss");
			}
		}
		if (battleMode == GameSceneBattleMode::boss)
		{

		}

		gameUI->update(/*this*/);

		if (gameUI->getState() >= banner_playerUI) {

			//敵
			HitCheck();
			if (battleMode == GameSceneBattleMode::normal) SlimeUpdate();
			if (battleMode == GameSceneBattleMode::normal) SkeletonUpdate();
			if (battleMode == GameSceneBattleMode::normal) WizardUpdate();
			if (battleMode == GameSceneBattleMode::midBoss) MinotaurUpdate();
			if (battleMode == GameSceneBattleMode::boss) DevilKingUpdate();

			//武器と敵の当たり判定
			if (true/*currentFloor == 1*/) {
				for (int i = 0; i < enemySpawnData["slime"]; i++) {
					if (slime[i] != nullptr) {
						if (weaponA->WeaponCollision(slime[i]->GetEnemyLocation(), slime[i]->GetEnemyRadius())) {
							if (slime[i]->GetHitFrameCnt() == 0) {
								slime[i]->SetHitWeaponFlg();
								//ダメージアップ
								slime[i]->SetHitHP(weaponA->GetDamage() * weaponB->GetAttackBufRate());
								slime[i]->SetHit1stFrameFlg(true);
								if (weaponA->GetIsAttacking() && !swordHitFlg) {
									swordHitFlg = true;
									weaponA->SetHitCnt(true);
									weaponA->SwordLevel8(player);
									weaponA->SwordLevel8Heel(player);
								}
								weaponA->AddTotalDamage();
							}
						}
						if (weaponB->WeaponCollision(slime[i]->GetEnemyLocation(), slime[i]->GetEnemyRadius())) {
							if (slime[i]->GetHitFrameCnt() == 0) {
								slime[i]->SetHitWeaponFlg();
								slime[i]->SetHitHP(weaponB->GetDamage() * weaponB->GetAttackBufRate());
								slime[i]->SetHit1stFrameFlg(true);
								
								if (weaponB->GetWeaponType() == spear && weaponB->GetWeaponLevel() == 8) {
									weaponB->SetThunderLocation(slime[i]->GetEnemyLocation());
									if (weaponB->SpearThunderCollision(slime[i]->GetEnemyLocation(), slime[i]->GetEnemyRadius())) {
										slime[i]->SetHitHP(weaponB->GetThunderDamage());
										weaponB->AddTotalDamageThunder();
									}
								}
								weaponB->AddTotalDamage();
							}
						}
						if (weaponA->DustCollision(slime[i]->GetEnemyLocation(), slime[i]->GetEnemyRadius())) {
							if (slime[i]->GetHitFrameCnt() == 0) {
								slime[i]->SetHitWeaponFlg();
								//ダメージアップ
								slime[i]->SetHitHP(weaponA->GetDustDamage());
								slime[i]->SetHit1stFrameFlg(true);
								slime[i]->SetCloudOfDustHitFlg(true);
								weaponA->AddTotalDamageDust();
							}
						}
					}
				}

				for (int i = 0; i < enemySpawnData["skeleton"]; i++) {
					if (skeleton[i] != nullptr) {
						if (weaponA->WeaponCollision(skeleton[i]->GetEnemyLocation(), skeleton[i]->GetEnemyRadius())) {
							if (skeleton[i]->GetHitFrameCnt() == 0) {
								skeleton[i]->SetHitWeaponFlg();
								skeleton[i]->SetHitHP(weaponA->GetDamage() * weaponB->GetAttackBufRate());
								skeleton[i]->SetHit1stFrameFlg(true);
								if (weaponA->GetIsAttacking() && !swordHitFlg) {
									swordHitFlg = true;
									weaponA->SetHitCnt(true);
									weaponA->SwordLevel8(player);
									weaponA->SwordLevel8Heel(player);
								}
								weaponA->AddTotalDamage();
							}
						}
						if (weaponB->WeaponCollision(skeleton[i]->GetEnemyLocation(), skeleton[i]->GetEnemyRadius())) {
							if (skeleton[i]->GetHitFrameCnt() == 0) {
								skeleton[i]->SetHitWeaponFlg();
								skeleton[i]->SetHitHP(weaponB->GetDamage() * weaponB->GetAttackBufRate());
								skeleton[i]->SetHit1stFrameFlg(true);

								if (weaponB->GetWeaponType() == spear && weaponB->GetWeaponLevel() == 8) {
									weaponB->SetThunderLocation(skeleton[i]->GetEnemyLocation());
									if (weaponB->SpearThunderCollision(skeleton[i]->GetEnemyLocation(), skeleton[i]->GetEnemyRadius())) {
										skeleton[i]->SetHitHP(weaponB->GetThunderDamage());
										weaponB->AddTotalDamageThunder();
									}
								}
								weaponB->AddTotalDamage();
							}
						}
						if (weaponA->DustCollision(skeleton[i]->GetEnemyLocation(), skeleton[i]->GetEnemyRadius())) {
							if (skeleton[i]->GetHitFrameCnt() == 0) {
								skeleton[i]->SetHitWeaponFlg();
								//ダメージアップ
								skeleton[i]->SetHitHP(weaponA->GetDustDamage());
								skeleton[i]->SetHit1stFrameFlg(true);
								skeleton[i]->SetCloudOfDustHitFlg(true);
								weaponA->AddTotalDamageDust();
							}
						}
					}
				}

				for (int i = 0; i < enemySpawnData["wizard"]; i++) {
					if (wizard[i] != nullptr) {
						if (weaponA->WeaponCollision(wizard[i]->GetEnemyLocation(), wizard[i]->GetEnemyRadius())) {
							if (wizard[i]->GetHitFrameCnt() == 0) {
								wizard[i]->SetHitWeaponFlg();
								//ダメージアップ
								wizard[i]->SetHitHP(weaponA->GetDamage() * weaponB->GetAttackBufRate());
								wizard[i]->SetHit1stFrameFlg(true);
								if (weaponA->GetIsAttacking() && !swordHitFlg) {
									swordHitFlg = true;
									weaponA->SetHitCnt(true);
									weaponA->SwordLevel8(player);
								}
								weaponA->AddTotalDamage();
							}
						}
						if (weaponB->WeaponCollision(wizard[i]->GetEnemyLocation(), wizard[i]->GetEnemyRadius())) {
							if (wizard[i]->GetHitFrameCnt() == 0) {
								wizard[i]->SetHitWeaponFlg();
								wizard[i]->SetHitHP(weaponB->GetDamage() * weaponB->GetAttackBufRate());
								wizard[i]->SetHit1stFrameFlg(true);

								if (weaponB->GetWeaponType() == spear && weaponB->GetWeaponLevel() == 8) {
									weaponB->SetThunderLocation(wizard[i]->GetEnemyLocation());
									if (weaponB->SpearThunderCollision(wizard[i]->GetEnemyLocation(), wizard[i]->GetEnemyRadius())) {
										wizard[i]->SetHitHP(weaponB->GetThunderDamage());
										weaponB->AddTotalDamageThunder();
									}
								}
								weaponB->AddTotalDamage();
							}
						}
						if (weaponA->DustCollision(wizard[i]->GetEnemyLocation(), wizard[i]->GetEnemyRadius())) {
							if (wizard[i]->GetHitFrameCnt() == 0) {
								wizard[i]->SetHitWeaponFlg();
								//ダメージアップ
								wizard[i]->SetHitHP(weaponA->GetDustDamage());
								wizard[i]->SetHit1stFrameFlg(true);
								wizard[i]->SetCloudOfDustHitFlg(true);
								weaponA->AddTotalDamageDust();
							}
						}
					}
				}
				//ミノタウロス
				if (minotaur != nullptr) {
					if (weaponA->WeaponCollision(minotaur->GetEnemyLocation(), minotaur->GetEnemyRadius())) {
						if (minotaur->GetHitFrameCnt() == 0) {
							minotaur->SetHitWeaponFlg();
							//ダメージアップ
							minotaur->SetHitHP(weaponA->GetDamage() * weaponB->GetAttackBufRate());
							minotaur->SetHit1stFrameFlg(true);
							if (weaponA->GetIsAttacking() && !swordHitFlg) {
								swordHitFlg = true;
								weaponA->SetHitCnt(true);
								weaponA->SwordLevel8(player);
							}
							weaponA->AddTotalDamage();
						}
					}
					if (weaponB->WeaponCollision(minotaur->GetEnemyLocation(), minotaur->GetEnemyRadius())) {
						if (minotaur->GetHitFrameCnt() == 0) {
							minotaur->SetHitWeaponFlg();
							minotaur->SetHitHP(weaponB->GetDamage() * weaponB->GetAttackBufRate());
							minotaur->SetHit1stFrameFlg(true);

							if (weaponB->GetWeaponType() == spear && weaponB->GetWeaponLevel() == 8) {
								weaponB->SetThunderLocation(minotaur->GetEnemyLocation());
								if (weaponB->SpearThunderCollision(minotaur->GetEnemyLocation(), minotaur->GetEnemyRadius())) {
									minotaur->SetHitHP(weaponB->GetThunderDamage());
									weaponB->AddTotalDamageThunder();
								}
							}
							weaponB->AddTotalDamage();
						}
					}
					if (weaponA->DustCollision(minotaur->GetEnemyLocation(), minotaur->GetEnemyRadius())) {
						if (minotaur->GetHitFrameCnt() == 0) {
							minotaur->SetHitWeaponFlg();
							//ダメージアップ
							minotaur->SetHitHP(weaponA->GetDustDamage());
							minotaur->SetHit1stFrameFlg(true);
							minotaur->SetCloudOfDustHitFlg(true);
							weaponA->AddTotalDamageDust();
						}
					}
				}
				//魔王
				if (devilKing != nullptr) {
					if (weaponA->WeaponCollision(devilKing->GetEnemyLocation(), devilKing->GetEnemyRadius())) {
						if (devilKing->GetHitFrameCnt() == 0) {
							devilKing->SetHitWeaponFlg();
							//ダメージアップ
							devilKing->SetHitHP(weaponA->GetDamage() * weaponB->GetAttackBufRate());
							devilKing->SetHit1stFrameFlg(true);
							if (weaponA->GetIsAttacking() && !swordHitFlg) {
								swordHitFlg = true;
								weaponA->SetHitCnt(true);
								weaponA->SwordLevel8(player);
							}
							weaponA->AddTotalDamage();
						}
					}
					if (weaponB->WeaponCollision(devilKing->GetEnemyLocation(), devilKing->GetEnemyRadius())) {
						if (devilKing->GetHitFrameCnt() == 0) {
							devilKing->SetHitWeaponFlg();
							devilKing->SetHitHP(weaponB->GetDamage() * weaponB->GetAttackBufRate());
							devilKing->SetHit1stFrameFlg(true);

							if (weaponB->GetWeaponType() == spear && weaponB->GetWeaponLevel() == 8) {
								weaponB->SetThunderLocation(devilKing->GetEnemyLocation());
								if (weaponB->SpearThunderCollision(devilKing->GetEnemyLocation(), devilKing->GetEnemyRadius())) {
									devilKing->SetHitHP(weaponB->GetThunderDamage());
									weaponB->AddTotalDamageThunder();
								}
							}
							weaponB->AddTotalDamage();
						}
					}
					if (weaponA->DustCollision(devilKing->GetEnemyLocation(), devilKing->GetEnemyRadius())) {
						if (devilKing->GetHitFrameCnt() == 0) {
							devilKing->SetHitWeaponFlg();
							//ダメージアップ
							devilKing->SetHitHP(weaponA->GetDustDamage());
							devilKing->SetHit1stFrameFlg(true);
							devilKing->SetCloudOfDustHitFlg(true);
							weaponA->AddTotalDamageDust();
						}
					}
				}
				//魔王の弾
				for (int i = 0; i < MAX_BULLET_NUM; i++){
					if (bigEnemyBullet[i] != nullptr) {
						if (weaponA->WeaponCollision(bigEnemyBullet[i]->GetEnemyLocation(), bigEnemyBullet[i]->GetEnemyRadius())) {
							//weaponAと魔王の弾の当たり判定
							bigEnemyBullet[i]->SetHitWeapon(true);
							
							if (true);
						}
						if (weaponB->WeaponCollision(bigEnemyBullet[i]->GetEnemyLocation(), bigEnemyBullet[i]->GetEnemyRadius())) {
							//weaponBと魔王の弾の当たり判定
							/*bigEnemyBullet[i]->SetHitWeapon(true);*/
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
			player->update(minotaur->GetRoarHitFlg());
			weaponA->Update(player->Player_AimingX(), player->Player_AimingY(), player->Player_Location(), player);
			Vector tmpV = { player->Player_MoveX(),player->Player_MoveY(),0 };
			weaponB->Update(player->Player_AimingX(), player->Player_AimingY(), player->Player_Location(), tmpV, player);

			EnemyInc();//敵のダメージストップ関係


			//////////////////////////////////////////////////
			// GameUI 仮
			hp = player->GetPlayer_HP();
			int maxHP = player->GetMaxPlayer_hp();

			int maxEXP = expData[level];

			int coolTime = (int)player->GetCoolTimeCounter(), coolTimeMax = 120;

			//printfDx("%f", coolTime);
			
			gameUI->setCoolTime(coolTime, coolTimeMax);

			gameUI->setHP(hp, maxHP, ((float)hp / (float)maxHP) * 100);
			gameUI->setEXP(exp, maxEXP, ((float)exp / (float)maxEXP) * 100);
			gameUI->setPoint(point);

			gameUI->setFloor(currentFloor + 1);
			gameUI->setEnemy(getEnemyNum(0), getEnemyMax(0));

			gameUI->setWeapon({ weaponA->GetWeaponType(), weaponA->GetWeaponLevel(), false, 0, 0 }, { weaponB->GetWeaponType(), weaponB->GetWeaponLevel(), false, 25, 100 });
			//////////////////////////////////////////////////
			if (getEnemyNum(0) <= 0 && frameCounter) {
				if (battleMode == GameSceneBattleMode::midBoss) 
				{
					SoundManager::StopSoundBGM("bgm_middleboss");
					SoundManager::PlaySoundBGM("bgm_middleboss_end");
				}
				if (battleMode == GameSceneBattleMode::normal)  gameUI->setBanner("クリア！", "全てのモンスターを倒しました", 0);
				if (battleMode == GameSceneBattleMode::midBoss) gameUI->setBanner("ミノタウロス討伐完了！", "+ 4 LEVELUP POINT", 0);
				if (battleMode == GameSceneBattleMode::boss)    gameUI->setBanner("魔王討伐完了！", "戦塔を制覇しました", 0);
				if (gameUI->getState() == playerUI) {
					gameUI->init();
					gameUI->setState(banner);
				};
				if (gameUI->getState() == banner_playerUI) {
					// 黒帯消滅後に発火
					map->ClearStage();

					currentFloor++;

					SoundManager::StopSoundBGMs();
					SoundManager::StopSoundSEs();
					
					if (battleMode == GameSceneBattleMode::midBoss)
					{
						mode = GameSceneMode::weaponSelect;
					}
					else if (battleMode == GameSceneBattleMode::boss)
					{
						return new GameClearScene(weaponA, weaponB, map);
					}
					else
					{
						mode = GameSceneMode::map;
					}
				};
			};
			if (player->GetPlayer_HP() <= 0) {
				gameUI->setBanner("失敗", "体力が尽きました、、", 0);
				if (gameUI->getState() == playerUI) {
					gameUI->init();
					gameUI->setState(banner);
				};
				if (gameUI->getState() == banner_playerUI) {
					// 黒帯消滅後に発火
					SoundManager::StopSoundBGMs();
					return new GameOverScene(weaponA, weaponB, map);
				};
			};
			//////////////////////////////////////////////////
			if (battleMode == GameSceneBattleMode::midBoss) gameUI->setEnemyHP("ミノタウロス", (int)(minotaur->GetHP()), MINOTAUR_MAX_HP, (int)((minotaur->GetHP() / MINOTAUR_MAX_HP) * 100.0f));
			if (battleMode == GameSceneBattleMode::boss) if (devilKing != nullptr) gameUI->setEnemyHP("魔王 猫スライム", (int)(devilKing->GetHP()), DEVILKING_MAX_HP, (int)((devilKing->GetHP() / DEVILKING_MAX_HP) * 100.0f));
			//printfDx("%d\n", static_cast<int>((SLIME_1_STAGE_NUM / c) * 100.0f));
			//printfDx("%f\n", (c / SLIME_1_STAGE_NUM) * 100.0f);
			if (InputCtrl::GetKeyState(KEY_INPUT_V) == PRESSED) battleMode = GameSceneBattleMode::boss;
			//////////////////////////////////////////////////

			// 経験値、レベル、ポイント処理
			if (exp >= expData[level]) {
				exp = 0;
				level++;
				point++;

				gameUI->notification("武器強化可能！", "Xボタンで確認", "btnX");
			};

			if (battleMode == GameSceneBattleMode::midBoss) bossState = 1; // 中ボス遭遇済み

		};

		frameCounter++;
	};


	if (mode == GameSceneMode::weaponSelect) {
		weaponSelect->update(weaponA, weaponB, weapon_selected, mode);
		return this;
	};

	if (mode == GameSceneMode::weaponLevelup) {
		weaponLevelup->update(weaponA, weaponB, player, restor_cursor_position, point);
		return this;
	};

	//////////////////////////////////////////////////

	if (mode == GameSceneMode::map) {
		map->update(mode, battleMode, weapon_selected);
		if (mode >= GameSceneMode::main) init();
		return this;
	};

	if (mode == GameSceneMode::blacksmith) {
		blacksmith->update(weaponA, weaponB, weaponLevelup, player, point, mode, currentFloor);
		//if (mode >= GameSceneMode::map) map->ClearStage();
		return this;
	};

	if (mode == GameSceneMode::rest) {
		rest->update(player, mode, currentFloor);
		hp = MAX_HP;
		//if (mode >= GameSceneMode::map) map->ClearStage();
		return this;
	};

#if 0
	clsDx();
	printfDx("敵最大数:（スラ: %d）（スケ: %d）（ウィザ: %d）（ミノ: %d）\n", getEnemyMax(1), getEnemyMax(2), getEnemyMax(3), getEnemyMax(4));
	printfDx("残りの敵:（スラ: %d）（スケ: %d）（ウィザ: %d）（ミノ: %d）\n", getEnemyNum(1), getEnemyNum(2), getEnemyNum(3), getEnemyNum(4));
#endif

	return this;
};

void GameScene::draw() const {

	if (mode >= GameSceneMode::main) {
		stage->draw();

		player->draw();

		weaponA->Draw();
		weaponB->Draw();

		// 敵
		if (battleMode == GameSceneBattleMode::normal) SlimeDraw();
		if (battleMode == GameSceneBattleMode::normal) SkeletonDraw();
		if (battleMode == GameSceneBattleMode::normal) WizardDraw();
		if (battleMode == GameSceneBattleMode::normal) EnemyBulletDraw();
		if (battleMode == GameSceneBattleMode::midBoss) MinotaurDraw();
		if (battleMode == GameSceneBattleMode::boss) DevilKingDraw();
		if (battleMode == GameSceneBattleMode::boss) BigEnemyBulletDraw();
		if (battleMode == GameSceneBattleMode::boss) SmallEnemyBulletDraw();

		//////////////////////////////////////////////////

		if (mode == GameSceneMode::weaponSelect) {
			weaponSelect->draw(weapon_selected);
		}
		else {
			gameUI->draw();
			if (battleMode >= GameSceneBattleMode::midBoss) gameUI->drawEnemyHP(); // ボスの体力ゲージ
		};

		if (mode == GameSceneMode::weaponLevelup) weaponLevelup->draw();
	};

	//////////////////////////////////////////////////

	if (mode == GameSceneMode::map) map->draw();

	if (mode == GameSceneMode::blacksmith) blacksmith->draw(weaponLevelup);

	if (mode == GameSceneMode::rest)rest->draw();

	//////////////////////////////////////////////////

	if (state == pause) gameUI->drawPause();
};

void GameScene::init() {
	delete player;
	player = new Player();

	player->SetPlayerHP(hp);

	delete stage;
	stage = new Stage();

	weaponA->InitWeapon();
	weaponB->InitWeapon(1);
	
	for (int i = 0; i < MAX_SLIME_NUM; i++) {
		slime[i] = nullptr;
	};
	tmpSlimeNum = 0;
	for (int i = 0; i < MAX_SKELETON_NUM; i++) {
		skeleton[i] = nullptr;
	};
	tmpSkeletonNum = 0;
	for (int i = 0; i < MAX_WIZARD_NUM; i++) {
		wizard[i] = nullptr;
	};
	tmpWizardNum = 0;
	for (int i = 0; i < MAX_BULLET_NUM; i++) {
		enemyBullet[i] = nullptr;
	};
	tmpBulletNum = 0;

	     if (battleMode == GameSceneBattleMode::normal)  gameUI->setBanner(std::to_string(currentFloor + 1) + "F - 魔王の手下たちの部屋", "全てのモンスターを倒してください", 1);
	else if (battleMode == GameSceneBattleMode::midBoss) gameUI->setBanner(std::to_string(currentFloor + 1) + "F - ミノタウロスの部屋", "討伐してください", 1);
	else if (battleMode == GameSceneBattleMode::boss)    gameUI->setBanner("最上階 - ラスボス", /*"特に何もしていない*/"魔王を討伐してください", 1);
	gameUI->init();
	gameUI->setState(banner);

	// 仮 - 敵をどのステージでどれだけ出すかのデータ生成（中ボス以降版）
	std::map<std::string, int> data;
	for (int i = currentFloor + 1; i < 20; i++) {
		data["slime"]    = shimabukuro[i - 1]["slime"] + 10;
		data["skeleton"] = 0;
		data["wizard"]   = 0;
		if ((battleMode == GameSceneBattleMode::midBoss) || bossState) data["skeleton"] = shimabukuro[i - 1]["skeleton"] + 5;
		if ((battleMode == GameSceneBattleMode::midBoss) || bossState) data["wizard"]   = shimabukuro[i - 1]["wizard"]   + 3;
		shimabukuro[i] = data;
	};
	enemySpawnData = shimabukuro[currentFloor];

	exp = 0;
};

int GameScene::getEnemyMax(int type) {
	int slimeNum    = 0;
	int skeletonNum = 0;
	int wizardNum   = 0;
	int minotourNum = 0;
	int bossNum     = 0;

	if (battleMode == GameSceneBattleMode::normal)  slimeNum    = enemySpawnData["slime"];
	if (battleMode == GameSceneBattleMode::normal)  skeletonNum = enemySpawnData["skeleton"];
	if (battleMode == GameSceneBattleMode::normal)  wizardNum   = enemySpawnData["wizard"];
	if (battleMode == GameSceneBattleMode::midBoss) minotourNum = 1;
	if (battleMode == GameSceneBattleMode::boss)    bossNum     = 1;

	if (type == 0) return (slimeNum + skeletonNum + wizardNum + minotourNum + bossNum);
	if (type == 1) return slimeNum;
	if (type == 2) return skeletonNum;
	if (type == 3) return wizardNum;
	if (type == 4) return minotourNum;
	if (type == 5) return bossNum;
};

int GameScene::getEnemyNum(int type) {
	int slimeNum    = 0;
	int skeletonNum = 0;
	int wizardNum   = 0;
	int minotourNum = 0;
	int bossNum     = 0;

	if (battleMode == GameSceneBattleMode::normal) {
		for (int i = 0; i < MAX_SLIME_NUM; i++) {
			if (slime[i] != nullptr) slimeNum++;
		};
		for (int i = 0; i < MAX_SKELETON_NUM; i++) {
			if (skeleton[i] != nullptr) skeletonNum++;
		};
		for (int i = 0; i < MAX_WIZARD_NUM; i++) {
			if (wizard[i] != nullptr) wizardNum++;
		};
	};

	if (battleMode == GameSceneBattleMode::midBoss && (minotaur->GetHP() > 0.0f)) minotourNum = 1;

	if (devilKing != nullptr) {
		if (battleMode == GameSceneBattleMode::boss && (devilKing->GetHP() > 0.0f)) bossNum = 1;
	}
	else {
		bossNum = 0;
	};

	if (type == 0) return (slimeNum + skeletonNum + wizardNum + minotourNum + bossNum);
	if (type == 1) return slimeNum;
	if (type == 2) return skeletonNum;
	if (type == 3) return wizardNum;
	if (type == 4) return minotourNum;
	if (type == 5) return bossNum;
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

	//ミノタウロスとプレイヤーの当たり判定
	if (minotaur != nullptr) {
		if (battleMode == GameSceneBattleMode::midBoss) {
			HitEnemy(minotaur);
		}
	}

	//魔王と魔王の武器、プレイヤーの当たり判定
	if (devilKing != nullptr) {
		if (battleMode == GameSceneBattleMode::boss) {
			//魔王とプレイヤー
			HitEnemy(devilKing);
			
			for (int i = 0; i < MAX_BULLET_NUM; i++) {
				if (bigEnemyBullet[i] != nullptr) {
					//大きい弾とプレイヤー
					HitEnemy(bigEnemyBullet[i]);

					//魔王と大きい弾
					if (bigEnemyBullet[i]->CheckCollision(static_cast<SphereCollider>(*devilKing), player) == HIT) {
						devilKing->SetBigBulletHitFlg(true);
						bigEnemyBullet[i] = nullptr;
					}
				}
			}
			//小さい弾とプレイヤー
			for (int i = 0; i < 7; i++) {
				if (smallEnemyBullet[i] != nullptr) {
					HitEnemy(smallEnemyBullet[i]);
				}
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

	if (minotaur != nullptr) {
		if (minotaur->GetHitFrameCnt() >= DAMAGE_STOP_FRAME) {
			minotaur->SetHit1stFrameFlg(false);
			minotaur->SetHitFrameCnt(0);
		}

		if (minotaur->GetHit1stFrameFlg() == true) {
			minotaur->hitFrameCntInc();
		}
	}
}

//----------スライム----------//
void GameScene::SlimeUpdate()
{
	if (tmpSlimeNum < enemySpawnData["slime"]) {
		slime[tmpSlimeNum] = new Slime(player,tmpSlimeNum, enemySpawnData["slime"], currentFloor);
		tmpSlimeNum++;
	}
	for (int i = 0; i < enemySpawnData["slime"]; i++) {
		if (slime[i] != nullptr) {
			slime[i]->Update(i, player, weaponA, *(stage));
			if (slime[i]->GetHP() <= 0) {
				slime[i] = nullptr;
				//tmpSlimeNum--;
				exp += 20;
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
	if (tmpSkeletonNum < enemySpawnData["skeleton"]) {
		skeleton[tmpSkeletonNum] = new Skeleton(player,tmpSkeletonNum, enemySpawnData["skeleton"]);
		tmpSkeletonNum++;
	}
	for (int i = 0; i < enemySpawnData["skeleton"]; i++) {
		if (skeleton[i] != nullptr) {
			skeleton[i]->Update(i, player, weaponA, *(stage));
			if (skeleton[i]->GetHP() <= 0) {
				skeleton[i] = nullptr;
				//tmpSkeletonNum--;
				exp += 30;
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
	for (int i = 0; i < enemySpawnData["wizard"]; i++) {
		if (wizard[i] != nullptr) {
			wizard[i]->Update(i, player, weaponA, *(stage));

			if (wizard[i]->GetShootFlg() == true) {
				if (wizard[i]->GetCreateBulletFlg() == true) {//弾の生成処理
					//if (tmpBulletNum < MAX_BULLET_NUM) {
					//	tmpBulletNum++;
					//}						
					enemyBullet[i] = new EnemyBullet(wizard[i]->GetEnemyLocation() , player);
				}
				EnemyBulletUpdate(i, wizard[i]);
			}
			else
			{
				enemyBullet[i] = nullptr;
			}

			if (wizard[i]->GetHP() <= 0) {
				wizard[i] = nullptr;
				//tmpWizardNum--;
				exp += 40;
			}
		}
		else
		{
			enemyBullet[i] = nullptr;
		}
	}
	if (tmpWizardNum < enemySpawnData["wizard"]) {
		wizard[tmpWizardNum] = new Wizard(player,tmpWizardNum, enemySpawnData["wizard"]);
		tmpWizardNum++;
	}
}

void GameScene::WizardDraw() const
{
	int maxWizard = 0;
	if (enemySpawnData.find("wizard") != enemySpawnData.end()) maxWizard = enemySpawnData.at("wizard");

	for (int i = 0; i < maxWizard; i++) {
		if (wizard[i] != nullptr) {
			wizard[i]->Draw(i);
		}
	}
}

//----------弾----------//
void GameScene::EnemyBulletUpdate(const int& array_num, Wizard* enemy)
{
	//for (int i = 0; i < MAX_BULLET_NUM; i++) {
		if (enemyBullet[array_num] != nullptr) {
			enemyBullet[array_num]->Update(player);
			if (enemyBullet[array_num]->GetlifeTimeCnt() <= 0) {
				enemyBullet[array_num] = nullptr;
				tmpBulletNum--;
			}
		}
	//}
}

void GameScene::EnemyBulletDraw() const
{
	for (int i = 0; i < MAX_BULLET_NUM; i++) {
		if (enemyBullet[i] != nullptr) {
			enemyBullet[i]->Draw();
		}
	}
}

//----------ミノタウロス----------//
void GameScene::MinotaurUpdate()
{
	if (minotaur != nullptr) {
		if (minotaur->GetRespwanFlg() == true) {
			minotaur->Update(player);
		}
		else if (minotaur->GetRespwanFlg() == false) {
			minotaur = nullptr;
		}

		if (minotaur->GetHP() <= 0) {
			point += 2; // 4を入れたいけど倍になる（2の場合、2+4のはずが何故か2+8となり、10になる）
		};
	}
}

void GameScene::MinotaurDraw() const
{
	if (minotaur != nullptr) {
		minotaur->Draw();
	}
}

//----------魔王----------//
void GameScene::DevilKingUpdate()
{
	if (devilKing != nullptr) {
		devilKing->Update(player);

		//大きい弾の生成処理
		if (devilKing->GetBigBulletCreateFlg() == true) {
			for (int i = 0; i < MAX_BULLET_NUM; i++) {
				if (bigEnemyBullet[i] == nullptr) {
					bigEnemyBullet[i] = new BigEnemyBullet(devilKing->GetEnemyLocation(), player);
					devilKing->SetBigBulletCreateFlg(false);
					break;
				}
			}
		}
		//大きい弾のUpdate
		for (int i = 0; i < MAX_BULLET_NUM; i++) {
			BigEnemyBulletUpdate(i);
		}

		for (int i = 0; i < MAX_BULLET_NUM; i++) {
			SmallEnemyBulletUpdate(i);
		}
	}

	if (devilKing != nullptr) {
		if (devilKing->GetHP() <= 0) {
			devilKing = nullptr;
		}
	}
}

void GameScene::DevilKingDraw() const
{
	if (devilKing != nullptr) {
		devilKing->Draw();
	}
}
//大きい弾
void GameScene::BigEnemyBulletUpdate(int array_num)
{
	if (bigEnemyBullet[array_num] != nullptr) {
		bigEnemyBullet[array_num]->Update(player);
		if (bigEnemyBullet[array_num]->GetlifeTimeCnt() <= 0) {
			//小さい弾の生成処理
			for (int i = 0; i < 7; i++) {
				smallEnemyBullet[i] = new SmallEnemyBullet(bigEnemyBullet[array_num]->GetEnemyLocation());
			}
			//大きい弾を削除
			bigEnemyBullet[array_num] = nullptr;
		}
	}
}

void GameScene::BigEnemyBulletDraw() const
{
	for (int i = 0; i < MAX_BULLET_NUM; i++) {
		if (bigEnemyBullet[i] != nullptr) {
			bigEnemyBullet[i]->Draw();
		}
	}
}
//小さい弾
void GameScene::SmallEnemyBulletUpdate(int array_num)
{
	if (smallEnemyBullet[array_num] != nullptr) {
		smallEnemyBullet[array_num]->Update(player);
		if (smallEnemyBullet[array_num]->GetLifeTimeCnt() <= 0) {
			smallEnemyBullet[array_num] = nullptr;
		}
	}
}

void GameScene::SmallEnemyBulletDraw() const
{
	for (int i = 0; i < MAX_BULLET_NUM; i++) {
		if (smallEnemyBullet[i] != nullptr) {
			smallEnemyBullet[i]->Draw();
		}
	}
}
