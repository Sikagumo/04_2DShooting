/* --------------
　プレイヤー処理
 ---------------- */

#include "Player.h"
#include "SceneManager.h"
#include "GameScene.h"
#include <DxLib.h>

/*　デフォルトコンストラクタ　*/
Player::Player(void)
{
	image_	   = -1;	 // プレイヤー画像
	isAlive_   = true;	 // 生存フラグ
	invCount_  = 0;		 // 無敵カウント
	hp_		   = MAX_HP; // 現在HP
	posLimitY_ = 0;		 // 縦移動制限位置

	// プレイヤー位置
	pos_.x = pos_.y = 0;
}

/*　デストラクタ　*/
Player::~Player(void)
{
	// プレイヤー画像 解放
	DeleteGraph(image_);
}


/* --- <<< 処理系 >>> --- */

/*　初期化処理　*/
void Player::Init()
{
	// プレイヤー画像 読み込み
	image_ = LoadGraph("Image/Player.png");

	/*　プレイヤー位置 初期化　*/
	pos_.x = GameScene::GAME_AREA_X / 2;
	pos_.y = (GameScene::GAME_AREA_Y / 2) + START_Y;

	isAlive_   = true;	 // 生存フラグ 有効化
	hp_		   = MAX_HP; // HP 初期化
	posLimitY_ = 0;		 // 移動制限位置 初期化

	/* HPバー 初期化 */
	Vector2 hp;
	hp.x = HP_POS_X;
	hp.y = GameScene::GAME_AREA_Y + HP_POS_Y;

	// HPバー情報 初期化
	hpBer_.InitHP(MAX_HP, hp,
				  HP_SIZE_X, HP_SIZE_Y,
				  HP_COLOR, HP_COLOR_BACK);

	// HPバー 初期化
	hpBer_.InitHPBer(0, GameScene::GAME_AREA_Y,
					 GameScene::GAME_AREA_X, SceneManager::SCREEN_SIZE_Y,
					 HP_FRAME_COLOR, (char*)"PlayerHP",
					 HP_TEXT_POS_X, HP_TEXT_POS_Y, HP_TEXT_COLOR);
}

/*　更新処理　*/
void Player::Update(void)
{
	/*　無敵カウント 減少処理　*/
	if (invCount_ > 0)
	{
		invCount_--;
	}


	/*　移動処理　*/
	if (pos_.y > posLimitY_)
	{
		/*　制限位置にいる時は 手動縦移動不可　*/
		PlayerMove(0, -SPEED_Y, KEY_INPUT_W, KEY_INPUT_UP);  // 上移動
		PlayerMove(0, SPEED_Y, KEY_INPUT_S, KEY_INPUT_DOWN); // 下移動
	}
	PlayerMove(-SPEED_X, 0, KEY_INPUT_A, KEY_INPUT_LEFT);  // 左移動
	PlayerMove( SPEED_X, 0, KEY_INPUT_D, KEY_INPUT_RIGHT); // 右移動


	/*　横移動制限　*/
	if (pos_.x < 0)
	{
		// 左移動制限
		pos_.x = 0;
	}
	else if ((pos_.x + SIZE_X) > GameScene::GAME_AREA_X)
	{
		// 右移動制限
		pos_.x = (GameScene::GAME_AREA_X - SIZE_X);
	}

	/*　縦移動制限　*/
	if (pos_.y <= posLimitY_)
	{
		// 上移動制限
		pos_.y += SPEED_Y / 2;
	}
	else if ((pos_.y + SIZE_Y) > GameScene::GAME_AREA_Y)
	{
		// 下移動制限
		pos_.y = (GameScene::GAME_AREA_Y - SIZE_Y);
	}
}

/*　描画処理　*/
void Player::Draw(void)
{
	if (isAlive_)
	{
		bool isTrans = false; // 半透明フラグ
		if (invCount_ > 0)
		{
			/*　被ダメ時 点滅処理　*/
			if ((invCount_ / 5) % 2 == 0)
			{
				isTrans = true;
			}
		}

		if (isTrans)
		{
			/*　被ダメ時の自機の描画　*/
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			DrawGraph(pos_.x, pos_.y, image_, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else
		{
			// 通常描画
			DrawGraph(pos_.x, pos_.y, image_, true);
		}
	}
}

/*　HP描画処理　*/
void Player::DrawHP(void)
{
	hpBer_.DrawHPBer(); // HPバー 描画
	hpBer_.DrawHP();	// HP 描画
}

/*　解放処理　*/
void Player::Release(void)
{
	DeleteGraph(image_); // プレイヤー画像解放
}


/*　移動処理　*/
void Player::PlayerMove(int moveX, int moveY, int keyCode1, int keyCode2)
{
	if (CheckHitKey(keyCode1) ||
		CheckHitKey(keyCode2))
	{
		pos_.x += moveX;
		pos_.y += moveY;
	}
}

/*　被ダメ処理　*/
void Player::Damage(void)
{
	hp_--; // HP減少処理

	if (hp_ > 0)
	{
		invCount_ = INV_COUNT; //無敵カウント 初期化
	}
	else
	{
		isAlive_ = false; //プレイヤー無効化
	}

	// HPバー更新
	hpBer_.SetHP(hp_);
}


/* --- <<< セッター処理 >>> --- */

/*　移動制限位置 割り当て　*/
void Player::SetPosLimitY(int limitY)
{
	posLimitY_ = limitY;
}


/* --- <<< ゲッター処理 >>> --- */

/*　現在HP 取得　*/
int Player::GetHP(void)
{
	return hp_;
}

/*　位置 取得　*/
Vector2 Player::GetPos(void)
{
	return pos_;
}

/*　有効判定 取得　*/
bool Player::GetIsAlive(void)
{
	return isAlive_;
}

/*　無敵カウンタ 取得　*/
int Player::GetInvCount(void)
{
	return invCount_;
}