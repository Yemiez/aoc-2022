#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
	constexpr const auto use_test = false;
	std::ifstream file{ use_test ? "test.txt" : "input.txt" };
	if (!file.is_open())
	{
		std::cerr << "Could not open file\n";
		return 1;
	}

	auto elves = [&]() 
	{
		std::vector<std::uint32_t> elves{};
		std::uint32_t elf{0u};
		std::string line{};
		while (std::getline(file, line))
		{
			if (line == "\n" || line.empty())
			{
				if (elf != 0u) {
					elves.push_back(elf);
					elf = 0u;
				}
			}
			else
			{
				elf += std::stoul(line, nullptr, 10);
			}
		}

		if (elf != 0u)
		{
			elves.push_back(elf);
		}
		return elves;
	}();
	std::sort(elves.begin(), elves.end(), [](auto const& a, auto const& b) { return a > b; });
	std::cout << "Part 1: " << elves.front() << std::endl;
	std::cout << "Part 1: " << elves.at(0) + elves.at(1) + elves.at(2) << std::endl;
	return 0;
}