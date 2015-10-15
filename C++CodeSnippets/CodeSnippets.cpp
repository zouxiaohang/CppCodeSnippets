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

namespace CodeSnippet2
{
	//将常整数映射为类型型别
	template<int v>
	struct Int2Type
	{
		enum{ value = v };
	};

	//一般而言，符合以下两个条件便可使用Int2Type
	//（1）根据某个编译期间常数调用不同的函数
	//（2）有必要在编译期实施dispatch

	//usage:
	template<class T>
	void fcn(T *p, Int2Type<true>){}
	template<class T>
	void fcn(T *p, Int2Type<false>){}
}