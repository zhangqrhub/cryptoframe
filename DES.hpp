#include<bitset>
#include"util.hpp"
using namespace std;

namespace des
{
	const array<unsigned int, 64> IP =
	{
		58,50,42,34,26,18,10,2,
		60,52,44,36,28,20,12,4,
		62,54,46,38,30,22,14,6,
		64,56,48,40,32,24,16,8,
		57,49,41,33,25,17, 9,1,
		59,51,43,35,27,19,11,3,
		61,53,45,37,29,21,13,5,
		63,55,47,39,31,23,15,7,
	};

	const array<unsigned int, 64> IP_1 =
	{
		40,8,48,16,56,24,64,32,
		39,7,47,15,55,23,63,31,
		38,6,46,14,54,22,62,30,
		37,5,45,13,53,21,61,29,
		36,4,44,12,52,20,60,28,
		35,3,43,11,51,19,59,27,
		34,2,42,10,50,18,58,26,
		33,1,41, 9,49,17,57,25
	};

	//ip置换
	bitset<64> fip(const bitset<64>& input, const array<unsigned int, 64>& metrix = IP)
	{
		bitset<64> output;
		for (int i = 0; i < 64; i++)
		{
			output[i] = input[metrix[i] - 1];
		}
		return output;
	}


	bitset<64> fip_1(const bitset<64>& input, const array<unsigned int, 64>& metrix = IP_1)
	{
		bitset<64> output;
		for (int i = 0; i < 64; i++)
		{
			output[i] = input[metrix[i] - 1];
		}
		return output;
	}


	const array<unsigned int, 16> SHIFT = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
	const array<unsigned int, 56> PC1 =
	{
		57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
		10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
		63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
		14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4
	};

	const array<unsigned int, 48> PC2 =
	{
		14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
		23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
		41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
		44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
	};


	//生成子密钥
	vector<bitset<48>> subkeygen(const bitset<64>& input, const array<unsigned int, 16>& shiftmetrix = SHIFT, const array<unsigned int, 56>& pc1metrix = PC1, const array<unsigned int, 48> pc2metrix = PC2)
	{
		vector<bitset<48>> output;
		bitset<48> output_val;
		bitset<28> L;
		bitset<28> R;
		bitset<56> LR;
		for (int i = 0; i < 56; i++)
		{
			LR[i] = input[pc1metrix[i] - 1];
		}

		for (int i = 0; i < 28; i++)
		{
			L[i] = LR[i];
			R[i] = LR[i + 28];
		}

		for (int i = 0; i < 16; i++)
		{
			L = (L << shiftmetrix[i]) | L >> (28 - shiftmetrix[i]);
			R = (R << shiftmetrix[i]) | R >> (28 - shiftmetrix[i]);
			for (int i = 0; i < 28; i++)
			{
				LR[i] = L[i];
				LR[i + 28] = R[i];
			}
			for (int i = 0; i < 48; i++)
				output_val[i] = LR[pc2metrix[i] - 1];
			output.push_back(output_val);
		}
		return output;
	}



	const array<unsigned int, 48> E =
	{
		32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
		8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17 ,
		16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
		24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1
	};

	const array<array<array<unsigned int, 16>, 4>, 8> SBOXS =
	{

			14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
			0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
			4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
			15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13,


			15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
			3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
			0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
			13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9,


			10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
			13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
			13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
			1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,


			7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
			13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
			10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
			3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14,


			2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
			14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
			4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
			11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3,

			12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
			10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
			9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
			4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13,

			4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
			13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
			1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
			6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12,

			13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
			1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
			7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
			2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11

	};


	const array<unsigned int, 48> P =
	{ 16,  7, 20, 21,
	   29, 12, 28, 17,
		1, 15, 23, 26,
		5, 18, 31, 10,
		2,  8, 24, 14,
	   32, 27,  3,  9,
	   19, 13, 30,  6,
	   22, 11,  4, 25
	};

	bitset<32> ff(const bitset<32>& data, const bitset<48>& key, const array<unsigned int, 48>& ee = E, const array<array<array<unsigned int, 16>, 4>, 8>& sb = SBOXS, const array<unsigned int, 48>& pp = P)
	{
		bitset<48> exdata;
		bitset<32> cat;
		bitset<32> output;
		for (int i = 0; i < 48; i++)
		{
			exdata[i] = data[ee[i] - 1];
		}
		exdata ^= key;
		int p = 0;
		int _p = 0;
		array<bitset<6>, 8> boxarray;
		//八个盒子
		for (int i = 0; i < 8; i++)
		{
			//六位
			for (int j = 0; j < 6; j++)
			{

				(boxarray[i])[j] = exdata[p];
				++p;
			}
			bitset<2> row;
			int irow;
			bitset<4> col;
			bitset<4> out(0);
			int icol;
			row[0] = boxarray[i][0];
			row[1] = boxarray[i][5];
			irow = row.to_ulong();
			col[0] = boxarray[i][1];
			col[1] = boxarray[i][2];
			col[2] = boxarray[i][3];
			col[3] = boxarray[i][4];
			icol = col.to_ulong();
			out = sb[i][irow][icol];
			for (int i = 0; i < 4; i++)
			{
				cat[_p] = out[i];
				_p++;
			}
		}
		for (int i = 0; i < 32; i++)
		{
			output[i] = cat[pp[i] - 1];
		}
		return output;
	}

	enum DESMODE
	{
		encrypt = 1,
		decrypt = 2
	};

	bitset<64> DES(bitset<64> input, bitset<64> key, const int& mode)
	{
		auto keys = subkeygen(key);
		fip(input);
		bitset<32> L, R, t;
		for (int i = 0; i < 32; i++)
		{
			L[i] = input[i];
			R[i] = input[i + 32];
		}
		for (int i = 0; i < 16; i++)
		{
			if (mode == 1)
			{
				L ^= ff(R, keys[i]);
			}
			else
			{
				L ^= ff(R, keys[15 - i]);
			}
			if (i != 15)
			{
				t = L;
				L = R;
				R = t;
			}
		}
		for (int i = 0; i < 32; i++)
		{
			input[i] = L[i];
			input[i + 32] = R[i];
		}
		fip_1(input);
		return input;
	}

	std::array<unsigned char, 8> toar(ull num)
	{
		std::array<unsigned char, 8> ar;
		char* p = (char*)&num;
		for (int i = 0; i < 8; i++)
		{
			ar[i] = *(p + i);
		}
		return ar;
	}


	std::array<unsigned char, 8> desen(std::array<unsigned char, 8>& data, const std::array<unsigned char, 8>& key) noexcept
	{
		unsigned long long num = toull(data);
		unsigned long long num_ = toull(key);

		std::array<unsigned char, 8> output_ = toar(DES(num, num_, DESMODE::encrypt).to_ullong());

		return output_;
	}

	std::array<unsigned char, 8> desde(std::array<unsigned char, 8>& data, const std::array<unsigned char, 8>& key) noexcept
	{
		unsigned long long num = toull(data);
		unsigned long long num_ = toull(key);

		std::array<unsigned char, 8> output_ = toar(DES(num, num_, DESMODE::decrypt).to_ullong());

		return output_;
	}
}
