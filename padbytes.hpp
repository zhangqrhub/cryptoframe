#pragma once
#include"defines.hpp"
//�ֽ��������Ǿ�������
//template<typename T>
//vuc vec{ '1','2' ,'3','4','5' };
//vuc padstr = pad(vec, 4, "", false);
//for (auto& i : vec)
//{
//	std::cout << (int)i << std::endl;
//}
//std::cout << "------" << std::endl;
//for (auto& i : padstr)
//{
//	std::cout << (int)i << std::endl;
//}
//data �������� blocksize �㷨ÿ���ܴ���������ֽ��� padstr ��ʲô��� cycle ѭ����䣬��ʱû��
vuc padbytes(const vuc& data, size_t datalen, string padstr, const bool cycle = true)
{
	vuc padvec;
	size_t lack = datalen - (data.size() % datalen);
	if (lack == datalen)
	{
		lack = 0;
	}
	size_t  p = 0;

	//�������
	if (padstr == "")
	{
		padstr.push_back(0);
	}

	//�������ûɶ��
	if (cycle == true)
	{
		for (size_t i = 0; i < lack; ++i)
		{
			padvec.push_back(padstr[p]);
			++p;
			if (p == padstr.size())
			{
				p = 0;
			}
		}
	}
	else
	{
		if (padstr.size() > lack)
		{
			for (size_t i = 0; i < lack; ++i)
			{
				padvec.push_back(padstr[p]);
				++p;
			}
		}
		else
		{
			for (size_t i = 0; i < lack; ++i)
			{
				if (p < padstr.size())
				{
					padvec.push_back(padstr[p]);
					++p;
				}
				else
				{
					padvec.push_back(0);
				}
			}
		}
	}
	return padvec;
}
