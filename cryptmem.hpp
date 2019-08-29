#include"defines.hpp"
#include"util.hpp"

//���ڴ����,�������Щ�����Ӱ˵���
//begin to dest һ����֪����ɶ��    len ���ݳ���      m ���ܻ��ǽ���       mode_ ģʽ       func��ʲô�㷨�ӽ��� 
template<size_t datalen, size_t keylen, typename from, typename to>
ull cryptomem(from begin, from end, to dest, ull len, std::array<unsigned char, keylen> key, int m, mode<datalen, keylen> mode_, proc<datalen, keylen> func)
{
	vuc vec;

	//���ܾ�������ͷ���������ݳ���
	if (m & encrypt)
	{
		addhead(vec, len);
	}

	for (; begin != end; ++begin)
	{
		vec.push_back(*begin);
	}

	//����β�������룬����ҵ㶫������ȥ
	if (m & encrypt)
	{
		auto padstr = padbytes(vec, datalen, "Qz1\t)H`b\\9!~\n4m * / a2u) ^ \r2@Is? - 2pd");

		//�Ѹ����Ķ���push��ȥ
		for (const auto& i : padstr)
		{
			vec.push_back(i);
		}
	}

	//���
	////////////////
	//����������
	vec = std::move(mode_(vec, key, func));
	////////////////
	ull dlen = 0;

	//����ǽ���ģʽ���Ͱѽ��ܳ���������ǰ�˸��ֽ�ת����unsigned long long ������ָ����֮ǰ�����ݳ���
	if (m & decrypt)
	{
		dlen = toull(vec);
	}

	//���ܾͰѽ��ȫ�����
	if (encrypt & m)
	{
		for (auto& i : vec)
		{
			*dest = i;
			++dest;
		}
		//���ؼ��ܺ����ݳ���
		return (vec.size() + 8);
	}
	else
	{
		//���ܾͰ�ǰ8�ֽ����ˣ�ǰ���ֽ������ݳ���
		for (int i = 8; i < 8 + dlen; ++i)
		{
			*dest = vec[i];
			++dest;
		}
		//���ؽ��ܺ����ݳ���
		return dlen;
	}
}
