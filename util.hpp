#ifndef UTIL_HPP
#define UTIL_HPP
#include"defines.hpp"
using ull = unsigned long long;
using uc = unsigned char;
using vuc = std::vector<uc>;
//Ч�ʵ��Ժ���˵
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

//ctrģʽ��   û�ҵ���׼д�������д��
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

//���ܻ��ǽ���
enum ende
{
	encrypt = 1,
	decrypt = 2
};

//Ĭ�ϻ�����С����
//��unsigned long long ת����һ�� unsigned char
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

//��һ�� unsigned char ת���� unsigned long long
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

//���,����ʱ����������
template<typename T>
void output(T& data)
{
	for (const auto& i : data)
	{
		std::cout << i << std::ends;
	}
	std::cout << std::endl;
}

//����û�ҵ���ô������ת�ɹ̶�������Կ���Ҿ����д�˸�,��������
//ͨ��α�����������,��һЩ�ַ�������һ�� vector<unsigned char>
//���Դ���
//constexpr int size = 24;
//auc<size> ar = std::move(pw2key<size>("sasdf�ƽⰢ��fd"));
//for (auto& i : ar)
//{
//	std::cout << (int)i << std::endl;
//}
//size ��Կ����
//string ���������
template<size_t datalen>
auc<datalen> initial(string pw)
{
	auc<datalen> i_auc;
	//���������,��������
	pw += "P!89zq��*Ϊë_��";
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


//������Ԫ��������,
template<size_t datalen>
void operator^=(std::array<uc, datalen>& l, const std::array<uc, datalen>& r)
{
	for (int i = 0; i < datalen; ++i)
	{
		l[i] ^= r[i];
	}
}

#endif



