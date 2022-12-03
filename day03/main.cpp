#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <map>

std::string read_file(std::string const& name) {
	std::ifstream file{ name, std::ios_base::binary };
	return { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
}

std::vector<std::string> split_string(const std::string& str, char delimiter)
{
	std::stringstream ss(str);
	std::string token;
	std::vector<std::string> tokens;

	while (std::getline(ss, token, delimiter))
	{
		tokens.push_back(token);
	}

	return tokens;
}

std::map<char, int> duplicate_characters(std::string const& line) {
	auto s1 = line.substr(0, line.length() / 2);
	auto s2 = line.substr(line.length() / 2);
	std::map<char, int> duplicates{};
	for (auto c : s2) {
		auto duplicate = std::find_if(s1.begin(), s1.end(), [&](auto c1) { return c == c1; });
		if (duplicate != s1.end()) {
			duplicates[c] += 1;
		}
	}
	return duplicates;
}

std::map<char, int> duplicate_badges(std::string const& l1, std::string const& l2, std::string const& l3) {
	std::map<char, int> duplicates{};
	for (auto c : l1) {
		auto it1 = std::find_if(l2.begin(), l2.end(), [&](auto c1) { return c == c1; });
		auto it2 = std::find_if(l3.begin(), l3.end(), [&](auto c1) { return c == c1; });
		if (it1 != l2.end() && it2 != l3.end()) {
			duplicates[c] += 1;
		}
	}
	return duplicates;
}

int main() {
	auto lines = split_string(read_file("input.txt"), '\n');
	auto duplicate_score = 0;
	auto badge_score = 0;

	for (auto const& line : lines) {
		auto duplicates = duplicate_characters(line);

		for (auto const& [c, count] : duplicates) {
			if (::isupper(c)) {
				duplicate_score += (c - 'A') + 27;
			}
			else {
				duplicate_score += (c - 'a') + 1;
			}
		}
	}

	for (auto it = lines.begin(); it != lines.end(); it += 3) {
		auto const& l1 = *it;
		auto const& l2 = *(it + 1);
		auto const& l3 = *(it + 2);
		auto d = duplicate_badges(l1, l2, l3);

		for (auto const& [c, count] : d) {
			if (::isupper(c)) {
				badge_score += (c - 'A') + 27;
			}
			else {
				badge_score += (c - 'a') + 1;
			}
		}
	}

	std::cout << "p1: " << duplicate_score << '\n';
	std::cout << "p2: " << badge_score << '\n';

}