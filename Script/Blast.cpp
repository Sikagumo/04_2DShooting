/* --------
　爆発処理
 ---------- */

#include "Blast.h"
#include "DxLib.h"

/*　デフォルトコンストラクタ　*/
Blast::Blast()
{
	for (int i = 0; i < IMAGE_COUNT_ALL; i++)
	{
		image_[i] = -1;
	}

	pos_.x = pos_.y = 0;

	isAlive_ = false;
	count_ = 0;
}

/*　デストラクタ　*/
Blast::~Blast()
{
	for (int i = 0; i < IMAGE_COUNT_ALL; i++)
	{
		DeleteGraph(image_[i]);
	}
}


/* --- <<< 処理系 >>> --- */

/*　初期化処理　*/
void Blast::Init(void)
{
	// 爆破画像 読み込み
	LoadDivGraph("Image/Blast.png",IMAGE_COUNT_ALL, IMAGE_COUNT_X, IMAGE_COUNT_Y,
				 SIZE_X,SIZE_Y,image_,true);

	count_   = 0; // 描画カウンタ 初期化
	isAlive_ = false; // 演出フラグ 無効化
	pos_.x = pos_.y = 0; // 爆破位置 初期化
}

/*　更新処理　*/
void Blast::Update(void)
{
	if (isAlive_)
	{
		count_++; //描画画像番号 増加

		/*　演出終了時 無効化　*/
		if (((count_ / IMAGE_FRAME) % IMAGE_COUNT_ALL + 1) == IMAGE_COUNT_ALL)
		{
			isAlive_ = false; // 演出フラグ 無効化
			count_	 = 0;	  // 描画カウンタ 初期化
		}
	}
}

/*　描画処理　*/
void Blast::Draw(void)
{
	if (isAlive_)
	{
		// 演出有効時 爆破描画
		DrawGraph(pos_.x, pos_.y, image_[(count_ / IMAGE_FRAME) % IMAGE_COUNT_ALL], true);
	}
}

/*　解放処理　*/
void Blast::Release(void)
{
	for (int i = 0; i < IMAGE_COUNT_ALL; i++)
	{
		DeleteGraph(image_[i]);
	}
}

/*　生成処理　*/
void Blast::Create(int posX, int posY)
{
	count_	 = 0;	 // 描画カウンタ 初期化
	pos_.x	 = posX; // 縦位置 割り当て
	pos_.y	 = posY; // 横位置 割り当て
	isAlive_ = true; // 爆破演出 有効化
}