#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <cassert>

using Round = std::pair<size_t, size_t>;

/* Rock(1) -> scissor(3) */
/* Paper(2) -> rock(1) */
/* Scissor(3) -> paper(2) */

static bool draws(size_t lhs, size_t rhs) {
	return lhs == rhs;
}

static bool wins(size_t lhs, size_t rhs) {
	return (rhs == 1u && lhs == 3u) || (rhs == 2u && lhs == 1u) || (rhs == 3u && lhs == 2u);
}

static bool looses(size_t lhs, size_t rhs) {
	return !wins(lhs, rhs) && !draws(lhs, rhs);
}

static size_t win_against(size_t lhs) {
	if (lhs == 3u) {
		return 1u;
	}
	if (lhs == 2u) {
		return 3u;
	}
	return 2u;
}

static size_t loose_against(size_t lhs) {
	if (lhs == 3u) {
		return 2u;
	}
	if (lhs == 2u) {
		return 1u;
	}
	return 3u;
}

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

size_t score(size_t lhs, size_t rhs) {
	if (wins(lhs, rhs)) {
		return 6 + rhs;
	}
	else if (looses(lhs, rhs)) {
		return rhs;
	}
	return 3 + rhs;
}

int main() {
	auto const content = read_file("input.txt");
	auto strategy_score = 0ui64;
	auto secret_score = 0ui64;
	std::vector<Round> rounds{};
	for (auto const& row : split_string(content, '\n')) {
		rounds.emplace_back(static_cast<size_t>(row[0] - 'A') + 1, static_cast<size_t>(row[2] - 'X') + 1);
	}

	for (auto const& [lhs, rhs] : rounds) {
		strategy_score += score(lhs, rhs);
	}
	for (auto const& [lhs, rhs] : rounds) {
		auto new_draw = 0ui64;
		if (rhs == 3) {
			new_draw = win_against(lhs);
		}
		else if (rhs == 1) {
			new_draw = loose_against(lhs);
		}
		else if (rhs == 2) {
			new_draw = lhs;
		}

		secret_score += score(lhs, new_draw);
	}
	std::cout << "p1: " << strategy_score << std::endl;
	std::cout << "p2: " << secret_score << std::endl;
}