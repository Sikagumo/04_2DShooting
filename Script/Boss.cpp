/* --------
　ボス処理
 ---------- */

#include "SceneManager.h"
#include "Boss.h"
#include <math.h>
#include <DxLib.h>

/*　デフォルトコンストラクタ　*/
Boss::Boss(void)
{
	image_	 = -1;	   // ボス画像
	isAlive_ = true;   // 生存フラグ
	hp_		 = MAX_HP; // 現在HP

	pos_.x = pos_.y = 0; // 位置

	state_	  = STATE::NONE; // ボス状態
	invCount_ = INV_COUNT;	 // 無敵時間

	idleCounter_	= 0; // 待機カウンタ
	warningCounter_	= 0; // 警告演出カウンタ
	warningAlpha_	= 0; // 警告透明値
}

/*　デストラクタ処理　*/
Boss::~Boss(void)
{
	// ボス画像 解放処理
	DeleteGraph(image_);
}


/*　初期化処理　*/
void Boss::Init(void)
{
	// ボス画像 読み込み
	image_ = LoadGraph("Image/EnemyBoss.png");

	hp_	   = MAX_HP; // 現在HP 初期化
	isAlive_ = true; // 生存フラグ 有効化

	pos_.x = pos_.y = 0; // 位置初期化

	idleCounter_	= 0; // 待機時間 初期化
	warningCounter_ = 0; // 警告カウンタ 初期化
	warningAlpha_	= 0; // 警告透明値 初期化

	// 待機状態
	ChangeState(Boss::STATE::IDLE);
	

	/*　HP情報 割り当て　*/
	Vector2 pos;
	pos.x = HP_POS_X;
	pos.y = HP_POS_Y;
	hpBer_.InitHP(MAX_HP, pos,
				  HP_SIZE_X, HP_SIZE_Y,
				  HP_COLOR, HP_COLOR_BACK);

	/*　HPバー割り当て　*/
	int berX = (SceneManager::SCREEN_SIZE_X / 2) - (GetDrawStringWidth("B O S S", 7) / 2);
	hpBer_.InitHPBer(BER_POS_X, BER_POS_Y,
					 BER_SIZE_X, BER_SIZE_Y, BER_COLOR,
					 (char*)"B O S S", berX, BER_POS_Y,TEXT_COLOR);

}


/* --- <<< 更新処理 >>> --- */
void Boss::Update(void)
{
	switch (state_)
	{
	case Boss::STATE::IDLE:
		/*　出現待機　*/
		UpdateIdle();
		break;


	case Boss::STATE::MOVE:
		/*　出現演出　*/
		UpdateMove();
		break;


	case Boss::STATE::ACTIVE:
		/*　ボス有効化　*/
		UpdateActive();
		break;
	}

	if (state_ == STATE::IDLE || state_ == STATE::MOVE)
	{
		warningCounter_ += WARNING_SPEED; // 警告カウンタ増加

		// 警告状態 変動
		warningAlpha_ = (WARNING_ALPHA / 2) + cosf(warningCounter_) * (WARNING_ALPHA / 2);
	}
}

/*　出現待機状態　*/
void Boss::UpdateIdle(void)
{
	idleCounter_++; // 待機カウンタ増加

	/*　待機終了時 画面遷移　*/
	if (idleCounter_ >= IDLE_CONUT)
	{
		ChangeState(STATE::MOVE);
	}
}

/*　出現状態　*/
void Boss::UpdateMove(void)
{
	pos_.y += SPEED; // ボス移動処理

	/*　一定位置到達時 状態遷移　*/
	if (pos_.y + (SIZE_Y / 2) > SceneManager::SCREEN_SIZE_Y / 4)
	{
		ChangeState(STATE::ACTIVE);
	}
}

/*　ボス有効 状態　*/
void Boss::UpdateActive(void)
{
	if (invCount_ > 0)
	{
		// 無敵時間減少処理
		invCount_ -= 1;
	}
}

/*　描画処理　*/
void Boss::Draw(void)
{
	if (isAlive_)
	{
		// ボス 描画処理
		DrawGraph(pos_.x, pos_.y, image_, true);
	}
}

/*　HP描画処理　*/
void Boss::DrawHP(void)
{
	/*　ボス出現完了時 HP表示　*/
	if (isAlive_ && state_ == STATE::ACTIVE)
	{
		hpBer_.DrawHPBer();
	}
}

/*　警告演出描画処理　*/
void Boss::DrawWarning(void)
{
	if (isAlive_)
	{
		if (state_ == STATE::IDLE || state_ == STATE::MOVE)
		{
			/*　透明度変動演出で描画　*/
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(warningAlpha_));
			DrawBox(0, 0, SceneManager::SCREEN_SIZE_X, SceneManager::SCREEN_SIZE_Y, 0xFF0000, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}

/*　画像解放処理　*/
void Boss::Release(void)
{
	// ボス画像 解放処理
	DeleteGraph(image_);
}


/*　状態遷移処理　*/
void Boss::ChangeState(STATE state)
{
	state_ = state;

	switch (state_)
	{
	case Boss::STATE::IDLE:

		/*　位置初期化　*/
		pos_.x = (SceneManager::SCREEN_SIZE_X / 2) - (SIZE_X / 2);
		pos_.y = -SIZE_Y;

		idleCounter_ = 0; // 待機カウンタ 初期化
		break;

	case Boss::STATE::MOVE:

		invCount_ = 0; // 無敵無効化

		break;

	case Boss::STATE::ACTIVE:


		break;
	}
}


/*　被ダメ処理　*/
void Boss::Damage() 
{
	hp_--; // HP減少

	// 無敵化
	invCount_ = INV_COUNT;

	/*　HP異常減少制限　*/
	if (hp_ < 0)
	{
		hp_ = 0;
	}

	// HPバーに反映
	hpBer_.SetHP(hp_);
}


/* --- <<< ゲッター処理 >>> --- */

/*　ボス有効判定 取得　*/
bool Boss::GetIsAlive(void)
{
	return isAlive_;
}

/*　位置 取得　*/
Vector2 Boss::GetPos(void)
{
	return pos_;
}

/*　現在HP 取得　*/
int Boss::GetHP(void)
{
	return hp_;
}

/*　無敵状態 確認　*/
bool Boss::GetIsInvincive(void)
{
	if (invCount_ > 0)
	{
		return true;
	}
	return false;
}
