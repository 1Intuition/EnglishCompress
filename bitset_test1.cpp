#include <bitset>
#include <iostream>
#include <ostream>
#include <vector>
#include <cmath>

// creates a concatinated bitset
template<size_t sRes, size_t s1, size_t s2>
std::bitset<sRes> concat_bitsets(const std::bitset<s1>& bs1, const std::bitset<s2>& bs2)
{
    std::bitset<sRes> res;
    for(size_t i=0;i<s1;i++)
    	res[i]=bs1[i];
    for(size_t i=0;i<s2;i++)
    	res[i+s1]=bs2[i];
    return res;
}

// inject the the second bitset into the first
template<size_t s1,size_t s2>
void injectLoop(std::bitset<s1>& bs1, const std::bitset<s2>& bs2, int start=s1-s2)
{
    for(size_t i=0;i<s2;i++)
        bs1[i+start]=bs2[i];
}

int main(int argc, char const *argv[])
{
	// std::bitset<8> bits1("11110000");
	// std::bitset<8> bits2("10101010");
	// std::bitset<16> bits3 = concatLoop<16, 8, 8>(bits1,bits2);
	// std::cout << bits3.to_ulong() << std::endl;

	// std::bitset<8> bits3("11110000");
	// std::cout << (bits3<<=3) << std::endl;
	// std::cout << bits3 << std::endl;

	// std::bitset<8> bits4('\xFF');
	// std::cout << bits4 << std::endl;

	// std::bitset<8> temp_byte;
	// temp_byte = 'a';
	// std::cout << char(temp_byte.to_ulong()) << std::endl;

	// std::bitset<16> bset("1000000000000111");
	// std::cout<<((bset<<1)>>4)<<std::endl;

	// std::bitset<16> bset("1000000000000111");
	// std::cout<< bset % 2<<std::endl;

	// std::string s("lol");
	// std::cout << ::toupper(s[0]) << std::endl;

	// std::vector<bool> v;
	// v.pop_back();

	// std::cout<< std::pow(2, 5) << std::endl;
	// std::vector<bool> v {0};
	// std::cout << v.empty() << std::endl;

	// int c = 2048;
	// while ((c/=2) != 1) {
	// 	std::cout << c << '\n';
	// }
	// int count = 10;
	// while (--count) {
	// 	std::cout << count << '\n';
	// }

	bool arr[5] = {0, 0, 0, 1, 1};
	for (bool x : arr) {
		std::cout << std::to_string(x) << '\n';
	}
	return 0;
}


/**
BITSET OPERATORS:

^	XOR
&	AND
|	OR
<<	SHL
>>	SHR
~	NOT
==	Equal
!=	Not Equal

bs.flip(optional size_t pos)
bs.test(size_t pos)
bs.count()
bs.any()
bs.none()
bs.set(size_t pos = default: all, bool val = 1)
bs.reset(optional pos)


*/