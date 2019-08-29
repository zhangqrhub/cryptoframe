#pragma once
#include"defines.hpp"
#include"util.hpp"
//可以在这拓展/////////////////////////////////////////以下是加密模式///////////////////////////////////////
//加密模式ecb
template<size_t datalen, size_t keylen>
vuc modeecb(const vuc& data, const std::array<unsigned char, keylen>& key, proc<datalen, keylen> func)
{
	vuc output_(data.size());
	std::array<uc, datalen> block;
	std::array<uc, datalen> result;
#pragma omp parallel for
	for (int i = 0; i < data.size() / datalen; ++i)
	{
		std::copy((data.begin() + (i * datalen)), (data.begin() + (i * datalen + datalen)), block.begin());
		result = std::move(func(block, key));
		std::copy(result.begin(), result.end(), output_.begin() + datalen * i);
	}
	return output_;
}

///加密模式cbc 加密
template<size_t datalen, size_t keylen>
vuc modecbcen(const vuc& data, const std::array<unsigned char, keylen>& key, proc<datalen, keylen> func)
{
	vuc output_(data.size());
	std::array<uc, datalen> block;
	std::array<uc, datalen> result = initial<datalen>("asdf");

	for (int i = 0; i < data.size() / datalen; ++i)
	{
		std::copy((data.begin() + (i * datalen)), (data.begin() + (i * datalen + datalen)), block.begin());

		block ^= result;
		result = std::move(func(block, key));

		std::copy(result.begin(), result.end(), output_.begin() + datalen * i);
	}
	return output_;
}

///加密模式cbc 解密
template<size_t datalen, size_t keylen>
vuc modecbcde(const vuc& data, const std::array<unsigned char, keylen>& key, proc<datalen, keylen> func)
{
	vuc output_(data.size());
	std::array<uc, datalen> block;
	std::array<uc, datalen> preblock = initial<datalen>("asdf");
	std::array<uc, datalen> result;

	for (int i = 0; i < data.size() / datalen; ++i)
	{
		std::copy((data.begin() + (i * datalen)), (data.begin() + (i * datalen + datalen)), block.begin());

		result = std::move(func(block, key));
		result ^= preblock;

		std::copy(block.begin(), block.end(), preblock.begin());

		std::copy(result.begin(), result.end(), output_.begin() + datalen * i);
	}
	return output_;
}

//ctr 模式,伪随机数生成器以后自己写个
template<size_t datalen, size_t keylen>
vuc modectr(const vuc& data, const std::array<unsigned char, keylen>& key, proc<datalen, keylen> func)
{
	vuc output_(data.size());

	ull num = 1;

	for (int i = 0; i < keylen; i++)
	{
		if (i != 0)
		{
			i *= num;
		}
	}

	std::mt19937_64 keygen(num);

	std::array<uc, datalen> block;
	std::array<uc, datalen> result;
	auc<keylen> tkey;

	for (int i = 0; i < data.size() / datalen; ++i)
	{
		tkey = ull_ar<keylen>(keygen());

		std::copy((data.begin() + (i * datalen)), (data.begin() + (i * datalen + datalen)), block.begin());

		result = std::move(func(tkey, key));
		block ^= result;

		std::copy(block.begin(), block.end(), output_.begin() + datalen * i);
	}

	return output_;
}


//////////////////////////////////////////////以上是加密模式/////////////////////////////////////////////////////
