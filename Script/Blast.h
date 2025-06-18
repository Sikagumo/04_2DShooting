/* ----------
　爆発データ
 ------------ */

#pragma once
#include "Vector2.h"

class Blast
{
public:

	/* --- <<< 定数定義 >>> --- */

	static constexpr int IMAGE_COUNT_X	 = 6;  // 横画像数
	static constexpr int IMAGE_COUNT_Y	 = 4;  // 縦画像数
	static constexpr int IMAGE_COUNT_ALL = 21; // 全画像数

	static constexpr int SIZE_X = (576 / IMAGE_COUNT_X); // 横画像サイズ
	static constexpr int SIZE_Y = (384 / IMAGE_COUNT_Y); // 縦画像サイズ

	static constexpr int IMAGE_FRAME = 1; //フレーム増加倍率


	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	Blast(void);  // デフォルトコンストラクタ

	~Blast(); // デストラクタ

	// 初期化処理(最初の１回のみ実行)
	void Init(void);

	// 更新処理(毎フレーム処理)
	void Update(void);

	// 描画処理(毎フレーム処理)
	void Draw(void);

	// 解放処理(最後の１回のみ実行)
	void Release(void);


	// 生成処理
	void Create(int posX, int posY);


private:

	/* --- <<< 変数定義 >>> --- */

	// 画像ハンドル
	int image_[IMAGE_COUNT_ALL];

	Vector2 pos_;  // 位置
	bool isAlive_; // 描画有効フラグ
	int count_;	   // 描画カウンタ
};