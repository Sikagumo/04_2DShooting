/* ------
　弾処理
 -------- */

#include "Shot.h"
#include <DxLib.h>

/*　デフォルトコンストラクタ　*/
Shot::Shot(void)
{
	image_ = -1;
	pos_.x  = pos_.y  = 0;
	isAlive_ = false;
}

/*　デストラクタ　*/
Shot::~Shot(void)
{
}


/* --- <<< 処理系 >>> --- */

/*　初期化処理　*/
void Shot::Init(void)
{
	// 弾画像 読み込み
	image_ = LoadGraph("Image/Shot.png");

	pos_.x = pos_.y = 0; // 弾位置 初期化

	isAlive_ = false; // 弾無効化

	/*　各発射キー 割り当て　*/
	zKey_.Init(KEY_INPUT_Z);
	spaceKey_.Init(KEY_INPUT_SPACE);
}

/*　更新処理　*/
void Shot::Update(void)
{
	/*　各発射キー 更新　*/
	zKey_.Update();
	spaceKey_.Update();

	/*　弾有効時の処理　*/
	if (isAlive_)
	{
		pos_.y -= SPEED; // 弾移動処理

		if (pos_.y <= -SIZE_Y)
		{
			// 画面外到達時 弾丸消失
			isAlive_ = false;
		}
	}
}

/*　描画処理　*/
void Shot::Draw(void)
{
	if (isAlive_)
	{
		// 弾有効時 弾画像描画
		DrawGraph(pos_.x, pos_.y, image_, true);
	}
}

/*　画像解放処理　*/
void Shot::Release(void)
{
	// 弾画像 解放
	DeleteGraph(image_);
}


void Shot::Create(int posX, int posY)
{
	pos_.x = posX;
	pos_.y = posY;
	isAlive_ = true;
}


/* --- <<< セッター処理 >>> --- */

void Shot::SetIsAlive(bool isAlive)
{
	isAlive_ = isAlive;
}


/* --- <<< ゲッター処理 >>> --- */

bool Shot::GetIsAlive(void)
{
	return isAlive_;
}

Vector2 Shot::GetPos(void)
{
	return pos_;
}


/*　発射判定 取得　*/
bool Shot::GetIsShotActive(void)
{
	if (isAlive_ == false)
	{
		if (zKey_.GetInputKeyDown() ||
			spaceKey_.GetInputKeyDown())
		{
			return true;
		}
	}
	return false;
}
