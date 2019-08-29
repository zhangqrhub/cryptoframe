#include"defines.hpp"
#include"aes128.hpp"
#include"DES.hpp"
#include"util.hpp"
#include"padbytes.hpp"
#include"modes.hpp"
#include"defines.hpp"
#include"cryptmem.hpp"
#include"defines.hpp"


//预定义一些东西
std::array<unsigned char, 16 > defalt16key =
{ 0xe1  ,0xa2  ,0x2c  ,0x34  ,0x45  ,0x56  ,0x67  ,0x78  ,0x89  ,0x9a  ,0xa0  ,0xbc  ,0xcd  ,0xde  ,0xef  ,0xf0 };

template<typename T>
T saltyfish_encrypt(T data, std::array<unsigned char, 16 > key = defalt16key)
{
	proc<16, 16> algo = aes128::aesen;
	mode<16, 16> mode_fun = modecbcen<16, 16>;
	T output_;
	output_.resize(data.size() + 30);
	int len1 = cryptomem(data.begin(), data.end(), output_.begin(), data.size(), key, encrypt, mode_fun, algo);
	output_.resize(len1);
	return output_;
}

template<typename T>
T saltyfish_decrypt(T data, std::array<unsigned char, 16 > key = defalt16key)
{
	proc<16, 16> algo = aes128::aesde;
	mode<16, 16> mode_fun = modecbcde<16, 16>;
	T output_;
	output_.resize(data.size() + 30);
	int len1 = cryptomem(data.begin(), data.end(), output_.begin(), data.size(), key, decrypt, mode_fun, algo);
	output_.resize(len1);
	return output_;
}