#include <string>
#include <numeric>
#include <ostream>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <vector>
#include <chrono>
#include <cmath>

#include "words_14bits.h"

#include "words_20bits.h"
// const std::string words_20bits[32768] = {
// 	"search",
// 	"free",
// 	"information",
// 	"site",
// 	"news",
// 	"contact"
// };

#define PERFORM_CHRONO true

// const std::string chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~ \t\n\r\x0b\x0c";

const std::string words_8bits[128] = {
	
	// 100 printable chars (TODO: maaybe arrange in frequency order?)

	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", 
	"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", 
	"k", "l", "m", "n", "o", "p", "q", "r", "s", "t", 
	"u", "v", "w", "x", "y", "z", "A", "B", "C", "D", 
	"E", "F", "G", "H", "I", "J", "K", "L", "M", "N", 
	"O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", 
	"Y", "Z", 

	"!", "\"", "#", "$", "%", "&", "\'", "(", ")", "*", 
	"+", ",", "-", ".", "/", ":", ";", "<", "=", ">", 
	"?", "@", "[", "\\", "]", "^", "_", "`", "{", "|", 
	"}", "~", " ", "\t", "\n", "\r", "\x0b", "\x0c",	

	// 28 most common character groups

	"the ", "of ", "and ", "a ", "to ", "in ", "is ", 
	"you ", "that ", "it ", "he ", "was ", "for ", 
	"on ", "are ", "as ", "with ", "his ", "they ", 
	"I ", "at ", "be ", "this ", "have ", "from ", 
	". ", ", ", "\'s "

};


// template<size_t sRes, size_t s1, size_t s2>
// std::bitset<sRes> concat_bitsets(const std::bitset<s1>& bs1, const std::bitset<s2>& bs2) {
//     std::bitset<sRes> res;
//     for(size_t i=0;i<s1;i++)
//     	res[i]=bs1[i];
//     for(size_t i=0;i<s2;i++)
//     	res[i+s1]=bs2[i];
//     return res;
// }




void print(const std::string& s) {
	std::cout << s << std::endl;
}

void print_bool_vec(const std::vector<bool>& vec) {
	std::string res;
	for (bool x : vec) {
		res += (x ? "1 " : "0 ");
	}
	std::cout << res << std::endl;
}

bool request_bit(std::vector<bool>& data) {
	// print_bool_vec(data);
	if (data.empty()) {
		throw "attempted pop_back on empty vector";
	}
	bool res = data.back();
	data.pop_back();
	return res;
}

uint16_t request_bits(std::vector<bool>& data, uint8_t count) {
	if (data.size() < count) {
		throw "too many bits requested";
	}
	uint16_t res = 0;

	// for (uint16_t i = std::pow(2, count - 1); i > 1; i /= 2) {
	// 	res += request_bit(data) * i;
	// }
	// res += request_bit(data);

	while (count--) {
		res += request_bit(data) * std::pow(2, count);
	}

	return res;
}

void push_bit(std::vector<bool>& data, bool bit) {
	data.push_back(bit);
}

void push_bits(std::vector<bool>& data, const std::vector<bool>& bits) {
	for (bool bit : bits) {
		push_bit(data, bit);
	}
}

std::vector<bool> convert_to_bits(uint16_t number, uint8_t length) {
	std::vector<bool> res;
	while (length--) {
		const uint16_t val = std::pow(2, length);
		if (number < val) {
			push_bit(res, 0);
		} else {
			push_bit(res, 1);
			number -= val;
		}
	}
	return res;
}


std::vector<bool> compress(const std::string& str) {
	std::vector<bool> res;

	std::vector<std::vector<bool>> bit_data;

	// 1. search 28 8bits words in the str
	// std::string str_temp = str;
	// const uint8_t MAXLEN_8BITS_WORDS = 5;
	// for (uint8_t i = 100; i < 128; ++i) {
	// 	const std::string substr = words_8bits[i];
	// 	if (str_temp.find(substr) != std::string::npos) {

	// 	}
	// }



	for (char c : str) {
		const auto f = std::find(words_8bits, words_8bits+100, std::string({c}));
		const size_t d = std::distance(words_8bits, f);
		if (d == 100) {
			throw "char not found in compression";
		}
		push_bit(res, 0);
		push_bits(res, convert_to_bits(d, 7));
	}
	return res;
}

std::string decompress(std::vector<bool> data) {
	std::reverse(data.begin(), data.end());
	std::string res;
	while (!data.empty()) {
		std::string word;
		const bool bit1 = request_bit(data);
		if (bit1) {
			const bool bit2 = request_bit(data);
			if (bit2) {
				const uint16_t id = request_bits(data, 15);
				word = words_20bits[id];
			} else {
				const uint16_t id = request_bits(data, 9);
				word = words_14bits[id];
			}
			const bool mod_bit1 = request_bit(data);
			const bool mod_bit2 = request_bit(data);
			
			if (mod_bit1) {
				if (mod_bit2) {
					transform(word.begin(), word.end(), word.begin(), ::toupper);
				} else {
					word[0] = ::toupper(word[0]);
				}
			} else {
				if (mod_bit2) {
					// custom casing
					std::string temp_word;
					for (char c : word) {
						if (::isalpha(c)) {
							if (request_bit(data)) {
								temp_word.push_back(::toupper(c));
							} else {
								temp_word.push_back(c);
							}
						} else {
							temp_word.push_back(c);
						}
					}
					word = temp_word;
				}
			}
			const bool has_space_after = request_bit(data);
			if (has_space_after) {
				word.push_back(' ');
			}
		} else {
			word = words_8bits[request_bits(data, 7)];
		}
		res += word;
	}
	return res;
}

struct ReplaceInfo {
	uint32_t start_index{};
	uint8_t length{};
	std::vector<bool> data{};
};


std::vector<bool> str_to_bool_vec(const std::string& data) {
	std::vector<bool> res;
	for (char c : data) {
		res.push_back(c == '1');
	}
	return res;
}


int run(int argc, const char *argv[]) {
	// std::vector<bool> compressed = compress("\x0cLOLOLlls");
	// print_bool_vec(compressed);
	// print(decompress(compressed));
	// std::vector<bool> data = 
	std::string in = "100000111101010110101001100100101010011110011000100101100101101000100010001110011000011001100111000100001101111001011001111100000011111010100111000000100111111001011001111100001000110010000101110100011001001100000011111010100001111111100011101100010110100101100111110001101110100101011100000000011010000001001011";
	std::string ex = "What is the best way to go about calling a function given a string with the function's name in a Python program.";
	std::string res = decompress(str_to_bool_vec(in));
	print(res);
	print(res == ex? "GOOD":"BAD");

	// std::string WORDLIST[5] = {"123", "234", "678", "789", "912"};
	// uint8_t MAXLEN_WORDS = 20;

	// std::vector<ReplaceInfo> repinfo;
	
	// std::string str = "123456789";
	// for (uint32_t start_pos = 0; start_pos < str.size(); ++start_pos) {
	// 	for (uint8_t word_len = 1; (word_len <= MAXLEN_WORDS) && ((start_pos + word_len) <= str.size()); ++word_len) {

	// 		std::string substr;
	// 		for (uint8_t letter = 0; letter < word_len; ++letter) {
	// 			substr.push_back(str[start_pos + letter]);
	// 		}
	// 		std::cout << substr << '\n';
	// 		const auto find_result = std::find(std::begin(WORDLIST), std::end(WORDLIST), substr);
	// 		if (find_result != std::end(WORDLIST)) {
	// 			// if substring found
	// 			const auto dist = std::distance(std::begin(WORDLIST), find_result);
	// 			// std::vector<bool> bits = {};  // TODO
	// 			std::vector<bool> bits = convert_to_bits(dist, 14);
	// 			ReplaceInfo ri{start_pos, word_len, bits};
	// 			repinfo.push_back(ri);
	// 		}
	// 	}
	// }
	// print_bool_vec(convert_to_bits(25, 5));
	return 0;
}


int main(int argc, char const *argv[]) {
	try {
		if (PERFORM_CHRONO) {
			auto begin = std::chrono::high_resolution_clock::now();
			run(argc, argv);
			auto end = std::chrono::high_resolution_clock::now();
			std::cout << std::chrono::duration_cast
				<std::chrono::nanoseconds>(end-begin).count()
				<< "ns" << std::endl;
		} else {
			run(argc, argv);
		}
	} catch (const char* s) {
		std::cerr << "ERROR: " << s << std::endl;
	}
	return 0;
}