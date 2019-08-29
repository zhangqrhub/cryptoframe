//作者：怒海咸鱼



#include"saltyfish.hpp"

//咸鱼式加解密
int main()
{
	std::string a("qwertyuiop[]asdfghjkl;");

	std::cout << saltyfish_decrypt(saltyfish_encrypt(a)) << std::endl;;
}




////这里是aes加密
//int main()
//{
//	//密钥，随便写
//	std::array<unsigned char, 16 > key =
//	{ 0x01  ,0x12  ,0x23  ,0x34  ,0x45  ,0x56  ,0x67  ,0x78  ,0x89  ,0x9a  ,0xab  ,0xbc  ,0xcd  ,0xde  ,0xef  ,0xf0 };
//
//	int size = 1'000'000;
//	vuc vec(size);
//	//自己拿计算器算至少要多少字节,差不多就行
//	vuc vec2(size + 50);
//	vuc vec3(size + 50);
//	//string str1 = "qwertyuiop[]sdfghjkl;'123456789";
//
//	srand(time(NULL));
//	std::generate(vec.begin(), vec.end(), rand);
//
//	//output(str1);
//
//	proc<16, 16> algo;
//	mode<16, 16> mode_fun;
//	//这里决定使用哪种算法
//
//	//记下开始时间
//	int begintime = clock();
//
//	algo = aes128::aesen;
//
//	//选择一种加密模式
//	//mode_fun = modectr<16, 16>;
//	mode_fun = modecbcen<16, 16>;
//	//mode_fun = modeecb<16,16>;
//
//
//	
//	//int len1 = cryptomem(str1.begin(), str1.end(), vec2.begin(), str1.size(), key, encrypt, mode_fun, algo);
//
//	//进行加密扔掉多余数据
//	vec2.resize(cryptomem(vec.begin(), vec.end(), vec2.begin(), vec.size(), key, encrypt, mode_fun, algo));
//	//output(vec2);
//	int middle = clock();
//	std::cout << "消耗时间" << middle - begintime << std::endl;
//	//这里决定使用哪种算法
//	algo = aes128::aesde;
//
//
//	//选择一种加密模式
//	//mode_fun = modectr<16, 16>;
//	mode_fun = modecbcde<16, 16>;
//	//mode_fun = modeecb<16, 16>;
//	
//	//进行解密扔掉多余数据
//	vec3.resize(cryptomem(vec2.begin(), vec2.end(), vec3.begin(), vec2.size(), key, decrypt, mode_fun, algo));
//
//	int endtime = clock();
//	std::cout <<"消耗时间"<<endtime-middle<< std::endl;
//
//	//看看解密后结果和原文是否相同，不相同就输出
//	for (int i = 0; i < vec.size(); i++)
//	{
//		if ((int)(vec[i]) != (int)(vec3[i]))
//		{
//			std::cout << (int)(vec[i])<<"------"<< (int)(vec3[i])<<"--------"<<i << std::endl;
//		}
//	}
//}
//




//
////这里是des加密，仅供演示，这算法早过时了
//int main()
//{
//	//-------------------加密------------------
//	//密钥
//	std::array<uc, 8 > key =
//	{ 0x01  ,0x12  ,0x23  ,0x34  ,0x45  ,0x56  ,0x67  ,0x78  };
//	//随便找些数据过来
//	string str1 = "qwertyuiop[]sdfghjkl;'123456789";
//	//多分配点内存
//	vuc vec2(400);
//	vuc vec3(400);
//
//	//输出下加密前的数据
//	output(str1);
//	//用啥算法
//	proc<8, 8> algo;
//	//用什么模式
//	mode<8, 8> mode_fun;
//	//用desen （des加密算法）
//	algo = des::desen;
//	//用cbc模式 加密
//	mode_fun = modectr<8,8>;
//	//加密，len1是返回的数据长度
//	int len1 = cryptomem(str1.begin(), str1.end(), vec2.begin(), str1.size(), key, encrypt, mode_fun, algo);
//	//不要的数据扔了
//	vec2.resize(len1);
//	//输出来看看加密成了啥玩意
//	output(vec2);
//
//	//-------------------解密------------------
//	//用desde算法解密
//	algo = des::desen;
//	//用cbc 解密模式
//	mode_fun = modectr<8, 8>;
//	//同上
//	int len2 = cryptomem(vec2.begin(), vec2.end(), vec3.begin(), vec2.size(), key, decrypt, mode_fun, algo);
//	vec3.resize(len2);
//	output(vec3);
//}
//
//int main()
//{
//	//ull data = 12356;
//	//ull key = 789456;
//	//auto t1 = des::DES(data, key, des::DESMODE::encrypt);
//	//auto t2 = des::DES(t1, key, des::DESMODE::decrypt);
//
//	//std::cout << t2.to_ullong() << std::endl;
//
//
//	std::array<uc, 8>  data{',','1','5' };
//	std::array<uc, 8>  key{ 1,2,3,4,5,6,7,8 };
//
//	auto t1=des::desen(data, key);
//	auto t2 = des::desde(t1, key);
//	for (auto i : t2)
//	{
//		std::cout << i << std::ends;
//	}
//}
//
//
//int main()
//{
//	std::array<unsigned char, 16 > key =
//	{ 0x01  ,0x12  ,0x23  ,0x34  ,0x45  ,0x56  ,0x67  ,0x78  ,0x89  ,0x9a  ,0xab  ,0xbc  ,0xcd  ,0xde  ,0xef  ,0xf0 };	
//	std::array<unsigned char, 16 > data =
//	{ 0x01  ,0x12  ,0x23  ,0x34  ,0x45  ,0x56  ,0x67  ,0x78  ,0x89  ,0x9a  ,0xab  ,0xbc  ,0xcd  ,0xde  ,0xef  ,0xf0 };
//
//	int begintime = clock();
//	for (int i = 0; i < 10000; ++i)
//	{
//		aes128::aesen(data, key);
//	}
//	int middletime = clock();
//	std::cout << "消耗时间" << middletime - begintime << std::endl;
//	for (int i = 0; i < 10000; ++i)
//	{
//		aes128::aesde(data, key);
//	}
//	int endtime = clock();
//	std::cout <<"消耗时间"<<endtime- middletime << std::endl;
//}



