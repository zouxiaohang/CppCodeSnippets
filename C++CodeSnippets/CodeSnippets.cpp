#include <vector>

//*******************************************************************************
namespace CodeSnippet1
{
	//在编译期间进行选择
	template<bool flag, class T, class U>
	struct Select
	{
		typedef T Result;
	};
	template<class T, class U>
	struct Select<false, T, U>
	{
		typedef U Result;
	};
	//usage:
	template<class T, bool isPolymorphic>
	struct Container
	{
		//根据参数isPolymorphic，在编译时期决定container的元素的类型
		typedef typename Select<isPolymorphic, T*, T>::Result ValueType;
		std::vector<ValueType> container;
	};
}