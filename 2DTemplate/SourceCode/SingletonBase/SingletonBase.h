#ifndef SINGLETON_BASE_H
#define SINGLETON_BASE_H

#include <memory>

/***********************************
*	シングルトン基底クラス.
*/
namespace tpl
{
	template <class T>
	class singleton
	{
	private:
		using class_type = T;

	protected:
		static class_type* GetInstance()
		{
			static std::unique_ptr<class_type> pInstance = std::make_unique<class_type>();
			return pInstance.get();
		}

		singleton() {};
		virtual ~singleton() {}


	private:
		// コピー・ムーブコンストラクタ, 代入演算子の削除.
		singleton( const singleton & )				= delete;
		singleton( singleton && )					= delete;
		singleton& operator = ( const singleton & )	= delete;
		singleton& operator = ( singleton && )		= delete;
	};
};	// namespace tpl.

#endif	// #ifndef SINGLETON_BASE_H.