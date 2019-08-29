#pragma once
#include<algorithm>
#include <iostream>
#include<fstream>
#include<array>
#include<vector>
#include<random>
#include<functional>
#include<sstream>
#include<time.h>

using ul = unsigned int;
using ull = unsigned long long;
using sc = char;
using uc = unsigned char;
using vuc = std::vector<uc>;

template<size_t datalen>
using auc = std::array<uc, datalen>;

//aes�㷨����des�㷨 ��������Ҳ��
template<size_t datalen, size_t keylen>
using proc = std::function<std::array<uc, datalen>(std::array<uc, datalen>&, const  std::array<uc, keylen>&)>;

//�ӽ���ģʽ
template<size_t datalen, size_t keylen>
using mode = std::function<vuc(const vuc&, const std::array<unsigned char, keylen>&, proc<datalen, keylen>)>;

using std::string;