#include"defines.hpp"
#include"util.hpp"

//对内存加密,在这里干些杂七杂八的事
//begin to dest 一看就知道干啥的    len 数据长度      m 加密还是解密       mode_ 模式       func用什么算法加解密 
template<size_t datalen, size_t keylen, typename from, typename to>
ull cryptomem(from begin, from end, to dest, ull len, std::array<unsigned char, keylen> key, int m, mode<datalen, keylen> mode_, proc<datalen, keylen> func)
{
	vuc vec;

	//加密就在数据头部加上数据长度
	if (m & encrypt)
	{
		addhead(vec, len);
	}

	for (; begin != end; ++begin)
	{
		vec.push_back(*begin);
	}

	//数据尾部不整齐，随便找点东西填充进去
	if (m & encrypt)
	{
		auto padstr = padbytes(vec, datalen, "Qz1\t)H`b\\9!~\n4m * / a2u) ^ \r2@Is? - 2pd");

		//把该填充的东西push进去
		for (const auto& i : padstr)
		{
			vec.push_back(i);
		}
	}

	//结果
	////////////////
	//核心在这里
	vec = std::move(mode_(vec, key, func));
	////////////////
	ull dlen = 0;

	//如果是解密模式，就把解密出来的数据前八个字节转化成unsigned long long ，这是指加密之前的数据长度
	if (m & decrypt)
	{
		dlen = toull(vec);
	}

	//加密就把结果全都输出
	if (encrypt & m)
	{
		for (auto& i : vec)
		{
			*dest = i;
			++dest;
		}
		//返回加密后数据长度
		return (vec.size() + 8);
	}
	else
	{
		//解密就把前8字节扔了，前八字节是数据长度
		for (int i = 8; i < 8 + dlen; ++i)
		{
			*dest = vec[i];
			++dest;
		}
		//返回解密后数据长度
		return dlen;
	}
}
