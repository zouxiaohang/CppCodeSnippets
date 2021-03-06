//windows header files
#include <Windows.h>

//c++ std header files
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

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

//*******************************************************************************
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

//*******************************************************************************
namespace CodeSnippet3
{
	//windows 递归遍历文件夹
	void RecursiveTraverseDir(const std::string& path, std::vector<std::string>& v)
	{
		const std::string szPath = (path + "\\");
		std::string szFile;
		std::string szFind;

		WIN32_FIND_DATA FindFileData;
		szFind += (szPath + "*.*");

		HANDLE hFind = ::FindFirstFile(szFind.c_str(), &FindFileData);

		if (INVALID_HANDLE_VALUE == hFind) 
			return;
		while (true)
		{
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (FindFileData.cFileName[0] != '.')
				{
					szFile = (szPath + FindFileData.cFileName);
					RecursiveTraverseDir(szFile, v);
				}
			}
			else
			{
				v.emplace_back(szPath + FindFileData.cFileName);
			}
			if (!FindNextFile(hFind, &FindFileData)) 
				break;
		}
		FindClose(hFind);
	}
	//usage:
	void fcn()
	{
		std::vector<std::string> v;
		RecursiveTraverseDir("C:\\Users\\zou\\Documents\\Visual Studio 2013\\Projects\\MyRayTracing\\MyRayTracing", v);
	}
}

//*******************************************************************************
namespace CodeSnippet4
{
	//c++ 按行读取文件内容
	void readFileByLine(const std::string& file)
	{
		std::ifstream ifs(file);
		std::string line;

		while (std::getline(ifs, line))
		{
			//std::cout << line << std::endl;
		}

		ifs.close();
	}
	//c++ 一次性读取整个文件的内容
	std::string readFile(const std::string& file)
	{
		std::ifstream ifs(file);
		std::stringstream ss;
		ss << ifs.rdbuf();
		ifs.close();

		std::string content = ss.str();
		return content;
	}
}

//*******************************************************************************
#include <codecvt>
#include <locale>
#include <string>
namespace CodeSnippet5
{
	//string 和 wstring 之间的转换
	// convert UTF-8 string to wstring
	std::wstring utf8_to_wstring(const std::string& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.from_bytes(str);
	}
	// convert wstring to UTF-8 string
	std::string wstring_to_utf8(const std::wstring& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.to_bytes(str);
	}
}

//*******************************************************************************
namespace CodeSnippet6
{
	//根据分隔符来分割字符串, 行为和python中的split一致
	std::vector<std::string> split(const std::string& msg, const std::string& delimiter = " ")
	{
		std::vector<std::string> ret;
		size_t prev = 0, step = delimiter.size();
		auto curr = msg.find(delimiter);
		while (curr != std::string::npos)
		{
			ret.emplace_back(msg.substr(prev, curr - prev));
			prev = curr + step;
			curr = msg.find(delimiter, prev);
		}
		ret.emplace_back(msg.substr(prev, msg.size() - prev));
		return ret;
	}
	//usage:
	void fcn()
	{
		std::string ss = " 1  1 ";
		auto v = CodeSnippet6::split(ss);//['', '1', '', '1', '']
	}
}

//*******************************************************************************
#include <chrono>
namespace CodeSnippet7
{
	//测试程序运行时间
	template<class Clock = std::chrono::steady_clock>
	class TimeProfiler
	{
	public:
		typedef typename Clock::time_point TimePoint;
		typedef std::chrono::duration<double, std::ratio<1, 1>> DurationTime;//单位秒
	private:
		TimePoint startTime;
		TimePoint finishTime;
		DurationTime durationTime;
	public:
		TimeProfiler(){}
		void start(){ startTime = Clock::now(); }
		void finish()
		{
			finishTime = Clock::now();
			durationTime = std::chrono::duration_cast<DurationTime>(finishTime - startTime);
		}

		double seconds(){ return durationTime.count(); }
	};
	//usage:
	void fcn()
	{
		int i = 1000;
		TimeProfiler<> p;
		p.start();
		while (i--){}
		p.finish();
		auto time = p.seconds();
	}
}

int main()
{
	auto s = CodeSnippet4::readFile("D:\\Projects\\C++CodeSnippets\\C++CodeSnippets\\CodeSnippets.cpp");
	std::cout << s;
	system("pause");
}