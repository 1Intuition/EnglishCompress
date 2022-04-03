#include <iostream>

int main(int argc, char const *argv[])
{
	int c = 2048;
	while ((c/=2) != 1) {
		std::cout << "C: " << c << '\n';
	}
	return 0;
}

