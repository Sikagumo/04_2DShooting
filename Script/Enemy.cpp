/* ----------
　雑魚敵処理
 ------------ */
#include "Enemy.h"
#include "SceneManager.h"
#include "GameScene.h"
#include <DxLib.h>

/*　デフォルトコンストラクタ　*/
Enemy::Enemy()
{
	enemyImage_ = -1;	 // 雑魚敵画像
	isAlive_	= true;  // 生存フラグ
	pos_.x = pos_.y = 0; // 位置

	hp_ = MAX_HP; // 現在HP
	speedY_ = 0;  // 縦移動速度
}

/*　デストラクタ　*/
Enemy::~Enemy()
{
	// 雑魚敵画像 解放
	DeleteGraph(enemyImage_);
}


/* --- <<< 処理系 >>> --- */

/*　初期化処理　*/
void Enemy::Init()
{
	// 敵画像 割り当て
	enemyImage_ = LoadGraph("Image/Enemy.png");

	GameInit(); // ゲーム内初期化
}

/*　ゲーム内初期化　*/
void Enemy::GameInit(void)
{
	/*　雑魚敵位置 割り当て　*/
	pos_.x = GetRand(GameScene::GAME_AREA_X - SIZE_X);
	pos_.y = -SIZE_Y * 2;

	hp_		= MAX_HP;  // HP初期化
	speedY_ = SPEED_Y; // 縦移動速度初期化

	// HPバー初期化
	hpBer_.InitHP(MAX_HP, pos_, SIZE_X, HP_SIZE_Y, HP_COLOR, HP_COLOR_BACK);

	isAlive_ = true; // 敵有効化
}


/*　更新処理　*/
void Enemy::Update(int playerPosX, int playerSizeX)
{
	if (isAlive_ == true)
	{
		pos_.y += speedY_; // 縦移動処理

		// 横移動処理
		MovePosX(playerPosX, playerSizeX);

		// 敵情報 割り当て
		hpBer_.SetPos(pos_);

		if (pos_.y >= GameScene::GAME_AREA_Y)
		{
			isAlive_ = false; // 画面外到達時 敵無効化
		}
	}
	else
	{
		GameInit(); // 初期化
	}
}

/*　描画処理　*/
void Enemy::Draw()
{
	if (isAlive_ == true)
	{
		// 雑魚敵 描画
		DrawGraph(pos_.x, pos_.y, enemyImage_, true);

		// HPバー 描画
		hpBer_.DrawHP();
	}
}

/*　解放処理　*/
void Enemy::Release()
{
	// 雑魚敵画像 解放
	DeleteGraph(enemyImage_);
}


/*　横移動処理　*/
void Enemy::MovePosX(int playerPosX, int playerSizeX)
{
	int speedX		= 0;		   // 横移動速度
	int curSpeedDec = SPEED_X_DEC; // 現在横減少率

	// 敵右位置(プレイヤー画像半分の位置ずらし)
	int enemyRight = (pos_.x + SIZE_X + (playerSizeX / 2));

	// 敵左位置(プレイヤー画像半分の位置ずらし)
	int enemyLeft  = (pos_.x - (playerSizeX / 2));

	// プレイヤー右位置(プレイヤー画像半分の位置ずらし)
	int playerRight = (playerPosX + playerSizeX + (playerSizeX / 2));

	// プレイヤー左位置(プレイヤー画像半分の位置ずらし)
	int playerLeft  = (playerPosX - (playerSizeX / 2));


	if (pos_.y >= ((GameScene::GAME_AREA_Y / 2) + SIZE_Y))
	{
		curSpeedDec = static_cast<int>(SPEED_X_DEC * 2); // 追尾速度減少
	}


	/*　右からの移動　*/
	if (enemyRight >= playerLeft)
	{
		speedX = static_cast<int>((enemyRight - playerLeft) / curSpeedDec);
		pos_.x -= speedX;
	}

	/*　左からの移動　*/
	if (enemyLeft <= playerRight)
	{
		speedX = static_cast<int>((playerRight - enemyLeft) / curSpeedDec);
		pos_.x += speedX;
	}
}


/*　被ダメ処理　*/
void Enemy::Damage(void)
{
	if (isAlive_ == true)
	{
		hp_--; // HP減少

		if (hp_ > 0) 
		{
			speedY_ = SPEED_Y / 2; // 移動速度 半減
		}
		else
		{
			isAlive_ = false; // 生存フラグ無効化
			hp_		 = 0;	  // HP異常減少対策
		}
	}

	// HPバーのHP情報 更新
	hpBer_.SetHP(hp_);
}

/*　移動速度 復活　*/
void Enemy::ResetSpeedY(void)
{
	/*　現在移動速度と不一致時のみ処理　*/
	if (speedY_ != SPEED_Y)
	{
		speedY_ = SPEED_Y;
	}
}


/* --- <<< ゲッター処理 >>> --- */

/*　現在位置 取得　*/
Vector2 Enemy::GetPos()
{
	return pos_;
}

/*　生存フラグ 取得　*/
bool Enemy::GetIsAlive()
{
	return isAlive_;
}

/*　現在HP 取得　*/
int Enemy::GetHP()
{
	return hp_;
}