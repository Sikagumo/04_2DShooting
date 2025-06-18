/* ------------
　キー入力処理
 -------------- */
#include "KeyTrigger.h"
#include <DxLib.h>

/*　デフォルトコンストラクタ　*/
KeyTrigger::KeyTrigger(void)
{
	preKey_  = 0;  // 前キー入力
	curKey_  = 0;  // 現在キー入力
	keyType_ = -1; // 入力キー種類
}

/*　デストラクタ　*/
KeyTrigger::~KeyTrigger(void)
{

}


/* --- <<< 処理系 >>> --- */

/*　初期化処理　*/
void KeyTrigger::Init(int keyType)
{
	// 入力キー 割り当て
	keyType_ = keyType;

	/*　入力状態 初期化　*/
	preKey_  = CheckHitKey(keyType_);
	curKey_  = preKey_;
}

void KeyTrigger::Update(void)
{
	if (keyType_ != -1)
	{
		// 前フレームのキー入力状態 取得
		preKey_ = curKey_;

		// 現在のキー入力 取得
		curKey_ = CheckHitKey(keyType_);
	}
}


/*　キー入力 連続押下判定 取得　*/
bool KeyTrigger::GetInputKey(void)
{
	if (preKey_ == 1 && curKey_ == 1 && preKey_ != -1)
	{
		return true; // 連続押下入力時
	}

	return false;
}

/*　キー入力 押下判定 取得　*/
bool KeyTrigger::GetInputKeyDown(void)
{
	if (preKey_ == 0 && curKey_ == 1 && preKey_ != -1)
	{
		return true; // 押下入力時
	}
	
	return false;
}

/*　キー入力 解放判定 取得　*/
bool KeyTrigger::GetInputKeyUp(void)
{
	if (preKey_ == 1 && curKey_ == 0 && keyType_ != -1)
	{
		return true; // 入力解放時
	}

	return false;
}