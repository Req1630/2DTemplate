/**
* @file XInput.h
* @brief This is Use Xinput Controller file.
* @author Fukuta
* @date 2019/11/09
* @details Xinputを使用するためのクラスです.
**/
#ifndef XINPUT_H
#define XINPUT_H

#include <Windows.h>
#include <crtdbg.h>
#include <Xinput.h>
#include <vector>
#include <memory>

#pragma comment( lib, "xinput.lib" )

static const int IDLE_THUMB_MAX		=  10000;	//!< スティックの遊び.
static const int IDLE_THUMB_MIN		= -10000;	//!< スティックの遊び.
static const int IDLE_TIGGER_MAX	=  100;		//!< トリガーボタンの遊び.

/**
* @brief XInput Class(Singleton).
*
* @details バイブレーション機能以外の機能はついてます.
*/
class CXInput
{
	const int FOUR_LIMITED_CONTROLLER = 4;	//!< 接続コントローラの最大数.
public:
	/**
	* @brief コンストラクタ.
	*/
	CXInput();
	/**
	* @brief デストラクタ.
	*/
	~CXInput();

	/**
	* @fn static void StatsUpdate()
	* @brief コントローラーの状態を更新.
	* @details 毎フレーム事に更新すること.
	*/
	static void StatsUpdate();

	/**
	* @fn static int GetConnectCount()
	* @return int 現在のコントローラーの接続数.
	* @brief コントローラーの接続している数を取得.
	*/
	static int GetConnectCount(){ return GetInstance()->m_ConnectedCount; }
	
	/**
	* @fn static bool A_Button( const int& connectNum = 0 )
	* @brief A ボタンの状態を取得.
	* @param connectNum  使用したいコントローラーの指定 何も指定しない場合は 0 固定.
	* @return bool 押されていたら true。押されていなかったら false.
	*/
	static bool A_Button( const int& connectNum = 0 );
	/**
	* @fn static bool B_Button( const int& connectNum = 0 )
	* @brief B ボタンの状態を取得.
	* @param connectNum  使用したいコントローラーの指定 何も指定しない場合は 0 固定.
	* @return bool 押されていたら true。押されていなかったら false.
	*/
	static bool B_Button( const int& connectNum = 0 );
	/**
	* @fn static bool X_Button( const int& connectNum = 0 )
	* @brief X ボタンの状態を取得.
	* @param connectNum  使用したいコントローラーの指定 何も指定しない場合は 0 固定.
	* @return bool 押されていたら true。押されていなかったら false.
	*/
	static bool X_Button( const int& connectNum = 0 );
	/**
	* @fn static bool Y_Button( const int& connectNum = 0 )
	* @brief Y ボタンの状態を取得.
	* @param connectNum  使用したいコントローラーの指定 何も指定しない場合は 0 固定.
	* @return bool 押されていたら true。押されていなかったら false.
	*/
	static bool Y_Button( const int& connectNum = 0 );

	/**
	* @fn static bool DPadUp( const int& connectNum = 0, const bool& isKeyinput = false )
	* @brief 上ボタンの状態を取得.
	* @param connectNum  使用したいコントローラーの指定 何も指定しない場合は 0 固定.
	* @param isKeyinput キーボードの方向キーを使用するかどうか 何も指定しない場合は false 固定.
	* @return bool 押されていたら true。押されていなかったら false.
	*/
	static bool DPadUp( const int& connectNum = 0, const bool& isKeyinput = false );
	/**
	* @fn static bool DPadDown( const int& connectNum = 0, const bool& isKeyinput = false )
	* @brief 下ボタンの状態を取得.
	* @param connectNum  使用したいコントローラーの指定 何も指定しない場合は 0 固定.
	* @param isKeyinput キーボードの方向キーを使用するかどうか 何も指定しない場合は false 固定.
	* @return bool 押されていたら true。押されていなかったら false.
	*/
	static bool DPadDown( const int& connectNum = 0, const bool& isKeyinput = false );
	/**
	* @fn static bool DPadLEFT( const int& connectNum = 0, const bool& isKeyinput = false )
	* @brief 左ボタンの状態を取得.
	* @param connectNum  使用したいコントローラーの指定 何も指定しない場合は 0 固定.
	* @param isKeyinput キーボードの方向キーを使用するかどうか 何も指定しない場合は false 固定.
	* @return bool 押されていたら true。押されていなかったら false.
	*/
	static bool DPadLEFT( const int& connectNum = 0, const bool& isKeyinput = false );
	/**
	* @fn static bool DPadRIGHT( const int& connectNum = 0, const bool& isKeyinput = false )
	* @brief 右ボタンの状態を取得.
	* @param connectNum  使用したいコントローラーの指定 何も指定しない場合は 0 固定.
	* @param isKeyinput キーボードの方向キーを使用するかどうか 何も指定しない場合は false 固定.
	* @return bool 押されていたら true。押されていなかったら false.
	*/
	static bool DPadRIGHT( const int& connectNum = 0, const bool& isKeyinput = false );

	/**
	* @fn static SHORT LThumbX_Axis( const int& connectNum = 0 )
	* @brief LスティックのX軸の値を取得.
	* @param connectNum  使用したいコントローラーの指定 何も指定しない場合は 0 固定.
	* @return SHORT スティックの傾きの値.
	*/
	static SHORT LThumbX_Axis( const int& connectNum = 0 );
	/**
	* @fn static SHORT LThumbY_Axis( const int& connectNum = 0 )
	* @brief LスティックのY軸の値を取得.
	* @param connectNum  使用したいコントローラーの指定 何も指定しない場合は 0 固定.
	* @return SHORT スティックの傾きの値.
	*/
	static SHORT LThumbY_Axis( const int& connectNum = 0 );

	/**
	* @fn static SHORT RThumbX_Axis( const int& connectNum = 0 )
	* @brief RスティックのX軸の値を取得.
	* @param connectNum  使用したいコントローラーの指定 何も指定しない場合は 0 固定.
	* @return SHORT スティックの傾きの値.
	*/
	static SHORT RThumbX_Axis( const int& connectNum = 0 );
	/**
	* @fn static SHORT RThumbY_Axis( const int& connectNum = 0 )
	* @brief RスティックのY軸の値を取得.
	* @param connectNum  使用したいコントローラーの指定 何も指定しない場合は 0 固定.
	* @return SHORT スティックの傾きの値.
	*/
	static SHORT RThumbY_Axis( const int& connectNum = 0 );

	/**
	* @fn static bool LThumb_Button( const int& connectNum = 0 )
	* @brief Lスティックボタンの状態を取得.
	* @param connectNum  使用したいコントローラーの指定 何も指定しない場合は 0 固定.
	* @return bool 押されていたら true。押されていなかったら false.
	*/
	static bool LThumb_Button( const int& connectNum = 0 );
	/**
	* @fn static bool RThumb_Button( const int& connectNum = 0 )
	* @brief Rスティックボタンの状態を取得.
	* @param connectNum  使用したいコントローラーの指定 何も指定しない場合は 0 固定.
	* @return bool 押されていたら true。押されていなかったら false.
	*/
	static bool RThumb_Button( const int& connectNum = 0 );

	/**
	* @fn static INT LTrigger( const int& connectNum = 0 )
	* @brief Lトリガーの状態を取得.
	* @param connectNum  使用したいコントローラーの指定 何も指定しない場合は 0 固定.
	* @return INT トリガーの押し込み値.
	*/
	static INT LTrigger( const int& connectNum = 0 );
	/**
	* @fn static INT RTrigger( const int& connectNum = 0 )
	* @brief Rトリガーの状態を取得.
	* @param connectNum  使用したいコントローラーの指定 何も指定しない場合は 0 固定.
	* @return INT トリガーの押し込み値.
	*/
	static INT RTrigger( const int& connectNum = 0 );

	/**
	* @fn static bool L_Button( const int& connectNum = 0 )
	* @brief L ボタンの状態を取得.
	* @param connectNum  使用したいコントローラーの指定 何も指定しない場合は 0 固定.
	* @return bool 押されていたら true。押されていなかったら false.
	*/
	static bool L_Button( const int& connectNum = 0 );
	/**
	* @fn static bool R_Button( const int& connectNum = 0 )
	* @brief R ボタンの状態を取得.
	* @param connectNum  使用したいコントローラーの指定 何も指定しない場合は 0 固定.
	* @return bool 押されていたら true。押されていなかったら false.
	*/
	static bool R_Button( const int& connectNum = 0 );

	/**
	* @fn static bool Start_Button( const int& connectNum = 0 )
	* @brief スタート ボタンの状態を取得.
	* @param connectNum 使用したいコントローラーの指定 何も指定しない場合は 0 固定.
	* @return bool 押されていたら true。押されていなかったら false.
	*/
	static bool Start_Button( const int& connectNum = 0 );
	/**
	* @fn static bool Back_Button( const int& connectNum = 0 )
	* @brief バック ボタンの状態を取得.
	* @param connectNum 使用したいコントローラーの指定 何も指定しない場合は 0 固定.
	* @return bool 押されていたら true。押されていなかったら false.
	*/
	static bool Back_Button( const int& connectNum = 0 );

private:
	/**
	* @fn void ConnectCheck( const int& connectNum )
	* @brief 接続の数を確認 クラス内で使用.
	* @param connectNum 指定したコントローラー.
	*/
	void ConnectCheck( const int& connectNum );
	/**
	* @fn bool IsButtonInput( const int& connectNum, const DWORD& button_mask )
	* @brief ボタン系の状態を取得 クラス内で使用.
	* @param connectNum 指定したコントローラー.
	* @param button_mask 指定したいボタン.
	* @return bool 押されていたら true。押されていなかったら false.
	*/
	bool IsButtonInput( const int& connectNum, const DWORD& button_mask );
	/**
	* @fn static CXInput* GetInstance()
	* @brief 自身のクラスを作成、取得.
	* @return CXInput* 作成された自身を返す.
	*/
	static CXInput* GetInstance()
	{
		static std::unique_ptr<CXInput> pInstance = std::make_unique<CXInput>();
		return pInstance.get();
	}

private:
	std::vector<XINPUT_STATE> m_State;	//!< 接続したコントローラーの状態.
	int m_ConnectedCount;				//!< 接続したコントローラーの数.

	// コピー・ムーブコンストラクタ, 代入演算子の削除.
	CXInput( const CXInput & )				= delete;
	CXInput( CXInput && )					= delete;
	CXInput& operator = ( const CXInput & )	= delete;
	CXInput& operator = ( CXInput && )		= delete;
};


#endif	// #ifndef XINPUT_H.