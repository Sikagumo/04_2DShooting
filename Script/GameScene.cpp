/* ----------------
　ゲームシーン処理
 ------------------*/

#include "SceneData.h"
#include "SceneManager.h"
#include "GameScene.h"
#include <DxLib.h>

/*　デフォルトコンストラクタ　*/
GameScene::GameScene(void)
{
	enemyParam_	   = ENEMY_PARAM::MOB_ACTIVE; // 敵出現状態
	nextGameScene_ = SCENE_TYPE::GAME;		  // 次シーン状態

	hitStopCnt_ = 0; // ヒットストップカウンタ
	tempScreen_ = 0; // 一時的画面領域

	// 振動位置
	shakePos_.x = shakePos_.y = 0;

	// 振動カウンタ
	shakeCounterX_ = shakeCounterY_ = 0;

	// 画面遅延カウンタ
	slowCounter_   = 0;

	// 敵撃破カウンタ
	enemyKillCounter_ = 0;
}

/*　デストラクタ　*/
GameScene::~GameScene(void)
{
	
}


/* --- <<< 処理系 >>> --- */

/*　初期化処理　*/
void GameScene::Init(void)
{
	nextGameScene_ = SCENE_TYPE::GAME; // 次シーン状態 初期化

	pause_.Init();		// 一時停止 初期化
	backGround_.Init(); // 背景 初期化
	player_.Init();		// プレイヤー 初期化
	shot_.Init();		// 弾 初期化
	blast_.Init();		// 爆発 初期化

	hitStopCnt_ = 0; // ヒットストップカウンタ 初期化

	// 振動位置初期化
	shakePos_.x = shakePos_.y = 0;

	// 一時的描画画面 割り当て
	tempScreen_ = MakeScreen(SceneManager::SCREEN_SIZE_X, SceneManager::SCREEN_SIZE_Y, true);

	// 敵撃破数 初期化
	enemyKillCounter_ = KILL_COUNT;

	// 雑魚敵 生成処理
	ChangeEnemyParam(ENEMY_PARAM::MOB_ACTIVE);
}

void GameScene::Update(void)
{
	pause_.Update(); // 一時停止確認 更新

	if (pause_.GetIsActive() == false)
	{
		/*　ヒットストップ処理　*/
		if (hitStopCnt_ > 0)
		{
			HitStop(); // ヒットストップ処理

			/*　遅延処理　*/
			if (slowCounter_ % 5 != 0)
			{
				return;
			}
		}
		else
		{
			enemy_.ResetSpeedY(); // 移動速度 通常化

			/*　プレイヤー撃墜時 ゲームオーバー状態に遷移　*/
			if (player_.GetHP() <= 0)
			{
				nextGameScene_ = SCENE_TYPE::GAME_OVER;
			}

			/*　ボス撃破時 ゲームクリア状態に遷移　*/
			else if (enemyParam_ == ENEMY_PARAM::BOSS_ACTIVE &&
				boss_.GetHP() <= 0)
			{
				nextGameScene_ = SCENE_TYPE::GAME_CLEAR;
			}
		}

		/*　プレイヤー有効時　*/
		if (player_.GetIsAlive() == true)
		{
			backGround_.Update(); // 背景 更新
			player_.Update();	  // プレイヤー更新

			if (enemyParam_ == ENEMY_PARAM::MOB_ACTIVE)
			{
				// 雑魚敵 更新
				enemy_.Update(player_.GetPos().x, Player::SIZE_X);

				/*　ボス状態 遷移処理　*/
				if (enemyKillCounter_ <= 0)
				{
					ChangeEnemyParam(ENEMY_PARAM::BOSS_ACTIVE);
				}
			}
			else if (enemyParam_ == ENEMY_PARAM::BOSS_ACTIVE)
			{
				// ボス敵 更新処理
				boss_.Update();
			}

			/*　再出現処理 + 発射判定　*/
			if (shot_.GetIsShotActive() == true)
			{
				// プレイヤーの座標を取得して弾を生成
				shot_.Create(player_.GetPos().x, player_.GetPos().y);
			}
		}

		shot_.Update();	 // プレイヤー弾 更新処理
		blast_.Update(); // 爆発 更新処理

		Collision(); //衝突処理
	}
}


/*　描画処理　*/
void GameScene::Draw(void)
{
	// 描画先のスクリーンを設定
	SetDrawScreen(tempScreen_);

	backGround_.Draw(); // 背景描画
	shot_.Draw();		// 弾描画
	player_.Draw();		// プレイヤー描画

	if (enemyParam_ == ENEMY_PARAM::MOB_ACTIVE)
	{
		enemy_.Draw(); // 敵描画
	}
	if (enemyParam_ == ENEMY_PARAM::BOSS_ACTIVE)
	{
		boss_.Draw(); // ボス敵描画
	}

	blast_.Draw();		 // 爆発描画
	player_.DrawHP();	 // プレイヤーHPバー
	boss_.DrawHP();		 // ボスHPバー

	boss_.DrawWarning(); // ボス警告演出
	pause_.Draw();		 // 一時停止描画


	//描画先のスクリーンをバックグラウンドに戻す
	SetDrawScreen(DX_SCREEN_BACK);


	/*　振動演出時 描画　*/
	if (hitStopCnt_ > SHAKE_STOP_COUNT)
	{
		DrawGraph(shakePos_.x, shakePos_.y, tempScreen_, true);
	}
	/*　通常描画　*/
	else
	{
		DrawGraph(0, 0, tempScreen_, true);
	}
}


/*　画像解放処理　*/
void GameScene::Release(void)
{
	pause_.Release();	   // 一時停止 解放
	boss_.Release();	   // ボス敵 解放
	blast_.Release();	   // 爆破 解放
	shot_.Release();	   // プレイヤー弾 解放
	enemy_.Release();	   // 敵 解放
	player_.Release();	   // プレイヤー 解放
	backGround_.Release(); // 背景 解放
}

/*　衝突処理　*/
void GameScene::Collision(void)
{
	if (player_.GetIsAlive()   == true &&
		enemy_.GetIsAlive()	   == true &&
		player_.GetInvCount()  <= 0)
	{
		/*　プレイヤーと敵モブの当たり判定　*/
		if (CheckCollisions(player_.GetPos(),Player::SIZE_X, Player::SIZE_Y,
						  enemy_.GetPos(), Enemy::SIZE_X, Enemy::SIZE_Y))
		{
			player_.Damage(); // プレイヤー被ダメ処理

			if (player_.GetHP() <= 0)
			{
				HitPerform(); // 撃破ヒットストップ
			}
			else
			{
				hitStopCnt_ = HIT_STOP / 2; // ヒットストップ(弱)
			}

			/*　爆発処理　*/
			int blastPosX = player_.GetPos().x + (Player::SIZE_X - Blast::SIZE_X) / 2;
			int blastPosY = player_.GetPos().y + (Player::SIZE_Y - Blast::SIZE_Y) / 2;
			blast_.Create(blastPosX, blastPosY);
		}
	}


	if (boss_.GetIsAlive()   == true &&
		player_.GetIsAlive() == true &&
		player_.GetInvCount() <= 0)
	{
		/*　プレイヤーと敵ボスの当たり判定　*/
		if (CheckCollisions(boss_.GetPos(), Boss::SIZE_X, Boss::SIZE_Y,
						  player_.GetPos(), Player::SIZE_X, Player::SIZE_Y))
		{
			player_.Damage(); // プレイヤー被ダメ処理

			if (player_.GetHP() <= 0)
			{
				HitPerform(); // 撃破ヒットストップ
			}
			else
			{
				hitStopCnt_ = HIT_STOP / 2; // ヒットストップ(弱)
			}

			/*　爆発処理　*/
			int blastPosX = player_.GetPos().x + (Player::SIZE_X - Blast::SIZE_X) / 2;
			int blastPosY = player_.GetPos().y + (Player::SIZE_Y - Blast::SIZE_Y) / 2;
			blast_.Create(blastPosX, blastPosY);
		}
	}


	if (shot_.GetIsAlive()	== true &&
		enemy_.GetIsAlive() == true)
	{
		/*　弾と敵モブの当たり判定　*/
		if (CheckCollisions(shot_.GetPos(), Shot::SIZE_X, Shot::SIZE_Y,
						enemy_.GetPos(), Enemy::SIZE_X, Enemy::SIZE_Y))
		{
			shot_.SetIsAlive(false);

			enemy_.Damage(); // 被ダメ処理

			if (enemy_.GetHP() <= 0)
			{
				HitPerform(); // 撃破ヒットストップ

				enemyKillCounter_--; // 敵撃破数増加
			}
			else
			{
				hitStopCnt_ = HIT_STOP / 2; // ヒットストップ(弱)
			}

			/*　爆発処理　*/
			int blastPosX = enemy_.GetPos().x + (Enemy::SIZE_X - Blast::SIZE_X) / 2;
			int blastPosY = enemy_.GetPos().y + (Enemy::SIZE_Y - Blast::SIZE_Y) / 2;;
			blast_.Create(blastPosX, blastPosY);
		}
	}

	
	if (shot_.GetIsAlive() == true &&
		boss_.GetIsAlive() == true)
	{
		/*　弾と敵ボスの当たり判定　*/
		if (CheckCollisions(shot_.GetPos(), Shot::SIZE_X, Shot::SIZE_Y,
						  boss_.GetPos(), Boss::SIZE_X, Boss::SIZE_Y))
		{
			shot_.SetIsAlive(false); // 弾丸無効化

			/*　ボスの無敵状態無効化時の処理　*/
			if (boss_.GetIsInvincive() == false)
			{
				boss_.Damage(); // 被ダメ処理

				if (boss_.GetHP() <= 0)
				{
					HitPerform(); // 撃破ヒットストップ
				}
				else
				{
					hitStopCnt_ = HIT_STOP / 2; // ヒットストップ(弱)
				}

				/*　爆発処理　*/
				int blastPosX = shot_.GetPos().x + (Shot::SIZE_X - Blast::SIZE_X) / 2;
				int blastPosY = shot_.GetPos().y + (Shot::SIZE_Y - Blast::SIZE_Y) / 2;;
				blast_.Create(blastPosX, blastPosY);
			}
		}
	}
}

/*　二つの当たり判定の衝突を判定する　*/
bool GameScene::CheckCollisions(Vector2 pos1, int sizeX1, int sizeY1, Vector2 pos2, int sizeX2, int sizeY2)
{
	if (pos1.x < (pos2.x + sizeX2) &&
	    (pos1.x + sizeX1) > pos2.x &&
		pos1.y < (pos2.y + sizeY2) &&
		(pos1.y + sizeY1) > pos2.y)
	{
		return true;
	}

	return false;
}

/*　ヒットストップ処理　*/
void GameScene::HitStop(void)
{
	hitStopCnt_--;  // ヒットストップカウンタ 減少
	slowCounter_--; // 遅延カウンタ 減少

	// 画面揺れ間隔変数値 増加
	++shakeCounterX_;
	++shakeCounterY_;

	/*　横揺れ 初期化　*/
	if (SHAKE_COUNT_X <= shakeCounterX_)
	{
		shakeCounterX_ = 0;

		if (shakePos_.x == SHAKE_WIDTH_X)
		{
			shakePos_.x = -SHAKE_WIDTH_X;
		}
		else if (shakePos_.x == -SHAKE_WIDTH_X)
		{
			shakePos_.x = SHAKE_WIDTH_X;
		}
	}

	/*　縦揺れ 初期化　*/
	if (SHAKE_COUNT_Y <= shakeCounterY_)
	{
		shakeCounterY_ = 0;

		if (shakePos_.y == SHAKE_WIDTH_Y)
		{
			shakePos_.y = -SHAKE_WIDTH_Y;
		}
		else if (shakePos_.y == -SHAKE_WIDTH_Y)
		{
			shakePos_.y = SHAKE_WIDTH_Y;
		}
	}

}

/*　衝突演出有効処理　*/
void GameScene::HitPerform(void)
{
	// ヒットストップカウント 初期化
	hitStopCnt_ = HIT_STOP;

	// 振動カウント 初期化
	shakeCounterX_ = shakeCounterY_ = 0;

	/*　振動位置 初期化　*/
	shakePos_.x = SHAKE_WIDTH_X;
	shakePos_.y = SHAKE_WIDTH_Y;

	// 遅延カウンタ 初期化
	slowCounter_ = SLOW_CONUT;
}

/*　敵出現状態 遷移処理　*/
void GameScene::ChangeEnemyParam(ENEMY_PARAM param)
{
	// 状態割り当て
	enemyParam_ = param;

	switch (enemyParam_)
	{
	case ENEMY_PARAM::MOB_ACTIVE:
		/*　雑魚敵出現状態　*/
		enemy_.Init();
		break;


	case ENEMY_PARAM::BOSS_ACTIVE:
		/*　ボス出現状態　*/
		boss_.Init();

		// プレイヤー移動制限位置 変更
		player_.SetPosLimitY(SceneManager::SCREEN_SIZE_Y / 2);
		break;
	}
}


/* --- <<< ゲッター処理 >>> --- */

/*　次シーン状態 取得　*/
SCENE_TYPE GameScene::GetNextScene(void)
{
	return nextGameScene_;
}