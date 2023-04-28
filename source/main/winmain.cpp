#include <DxLib.h>

#include"config.h"
#include"app.h"

//初期化前設定
void LoadInit() {
	SetOutApplicationLogValidFlag(LOGSET_MODE)		;//ログの書き出し設定
	ChangeWindowMode(WINDOW_MODE)					;//ウィンドウモードにする
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32)	;//ウィンドウサイズを設定する
	SetWindowSizeExtendRate(WINDOW_EXTEND)			;//ウィンドウ拡大率
	//SetWindowSizeChangeEnableFlag(TRUE)			;//途中大きさ変更あり
	SetWindowStyleMode(WINDOW_STYLE)				;//ウィンドウの最大化ボタンを機能させる。
	SetDrawScreen(DX_SCREEN_BACK)					;//裏画面を描画対象へ
	//SetUseIMEFlag(true)							;//ＩＭＥを使用するかどうかを設定する
	SetWindowText(WINDOW_NAME)						;//ウィンドウの名前
	//SetAlwaysRunFlag(TRUE)						;//ウィンドウが非アクティブでも動くか
	SetUseDXArchiveFlag(TRUE)						;//DxLibのアーカイブを読み込むかどうか
}

//プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	LoadInit()				;//初期化前設定
	
	if (DxLib_Init() == -1)	 // ＤＸライブラリ初期化処理
		return -1			;// エラーが起きたら直ちに終了
	

		
	//SetAlwaysRunFlag(TRUE);//ウィンドウがアクティブではない状態でも動く
	//SetUseZBuffer3D(TRUE)	;
	//SetWriteZBuffer3D(TRUE);
		
	
	APP::Init()				;//最初に１回呼ぶ
	//メイン処理
	while (ProcessMessage() == 0 && !APP::GameEnd()) {
		clsDx()				;//prinfdxの描画を消去
		ClearDrawScreen()	;//裏画面の描画を全て消去

		APP::Update()		;//毎フレームの更新
		if (CheckHitKey(KEY_INPUT_W) && CheckHitKey(KEY_INPUT_LCONTROL))
			break;

		APP::Draw()			;//毎フレームの描画

		ScreenFlip()		;//裏画面と表画面の入替
	}

	APP::Delete()			;//後始末

	DxLib_End()				;// ＤＸライブラリ使用の終了処理

	return 0				;// ソフトの終了 
}
