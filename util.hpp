#ifndef UTIL_HPP
#define UTIL_HPP
#include"defines.hpp"
using ull = unsigned long long;
using uc = unsigned char;
using vuc = std::vector<uc>;
//效率低以后再说
template<size_t size>
auc<size> ull_ar(ull num)
{
	std::mt19937 keygen(num);
	auc<size> ar;
	for (auto& i : ar)
	{
		i = keygen();
	}
	return ar;
}

//ctr模式用   没找到标准写法，随便写的
template<size_t size>
ull ar_ull(auc<size>& key)
{
	ull num = 1;

	for (int i = 0; i < size; i++)
	{
		if (i != 0)
		{
			i *= num;
		}
	}
	return num;
}

//加密还是解密
enum ende
{
	encrypt = 1,
	decrypt = 2
};

//默认机器是小端序
//把unsigned long long 转化成一串 unsigned char
template<bool littleendian = true>
void addhead(vuc& data, ull len)
{
	uc* t;
	if constexpr (littleendian)
	{
		t = (uc*)&len;
		for (int i = 0; i < 8; i++)
		{
			data.push_back(*t);
			t++;
		}
	}
	else
	{
		t = (uc*)(&len) + 8;
		for (int i = 0; i < 8; i++)
		{
			data.push_back(*t);
			t--;
		}
	}
}

//把一串 unsigned char 转化成 unsigned long long
template<typename T=vuc,bool littleendian = true>
ull toull(T& data)
{
	ull t;
	uc* p;
	if constexpr (littleendian)
	{
		p = (uc*)&t;
		for (int i = 0; i < 8; ++i)
		{
			*p = data[i];
			p++;
		}
	}
	else
	{
		p = (uc)&t + 8;
		for (int i = 0; i < 8; ++i)
		{
			*p = data[i];
			p--;
		}
	}
	return t;
}

//输出,测试时看起来方便
template<typename T>
void output(T& data)
{
	for (const auto& i : data)
	{
		std::cout << i << std::ends;
	}
	std::cout << std::endl;
}

//网上没找到怎么把密码转成固定长度密钥，我就随便写了个,将就着用
//通过伪随机数生成器,将一些字符串生成一串 vector<unsigned char>
//测试代码
//constexpr int size = 24;
//auc<size> ar = std::move(pw2key<size>("sasdf破解阿文fd"));
//for (auto& i : ar)
//{
//	std::cout << (int)i << std::endl;
//}
//size 密钥长度
//string 输入的密码
template<size_t datalen>
auc<datalen> initial(string pw)
{
	auc<datalen> i_auc;
	//来点随机数,这里随便改
	pw += "P!89zq啊*为毛_下";
	ul sum = 0;
	for (auto& i : pw)
	{
		sum += i;
	}
	std::mt19937 mt(sum);
	for (int i = 0; i < datalen; ++i)
	{
		i_auc[i] = mt();
	}
	return i_auc;
}


//数组内元素逐个异或,
template<size_t datalen>
void operator^=(std::array<uc, datalen>& l, const std::array<uc, datalen>& r)
{
	for (int i = 0; i < datalen; ++i)
	{
		l[i] ^= r[i];
	}
}

#endif



