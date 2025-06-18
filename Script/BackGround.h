/* ---------
　背景データ
 ----------- */

#pragma once

class BackGround
{
public:

	/* --- <<< 定数定義 >>> --- */

	static constexpr int SIZE_Y		= 960; // 横サイズ
	static constexpr int MOVE_SPEED = 5;   // 移動速度


	/* --- <<< 関数プロトタイプ宣言 >>> --- */

	// デフォルトコンストラクタ
	BackGround(void);

	// デストラクタ
	~BackGround(void);

	// 初期化処理(最初の１回のみ実行)
	void Init(void);

	// 更新処理(毎フレーム実行)
	void Update(void);

	// 描画処理(毎フレーム実行)
	void Draw(void);

	// 解放処理(最後の１回のみ実行)
	void Release(void);

private:
	/* --- <<< 変数定義 >>> --- */

	int image_; // 背景画像ハンドル
	int posY_;  // 縦座標
};