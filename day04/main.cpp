#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

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

using Range = std::pair<size_t, size_t>;
std::pair<Range, Range> extract_id_pair(std::string const& line)
{
	auto const first_dash = line.find('-');
	auto const first_comma = line.find(',');
	auto const second_dash = line.find('-', first_comma);
	auto const s1 = line.substr(0, first_dash);
	auto const s2 = line.substr(first_dash + 1, first_comma - first_dash - 1);
	auto const s3 = line.substr(first_comma + 1, second_dash - first_comma - 1);
	auto const s4 = line.substr(second_dash + 1);

	return {
		{ std::stoull(s1), std::stoull(s2) },
		{ std::stoull(s3), std::stoull(s4) },
	};
}

bool contained_within(Range lhs, Range rhs)
{
	return (lhs.first >= rhs.first && lhs.second <= rhs.second) || (rhs.first >= lhs.first && rhs.second <= lhs.second);
}

bool is_overlapped(Range lhs, Range rhs)
{
	return !(lhs.second < rhs.first or rhs.second < lhs.first);
}

int main() {
	const auto lines = split_string(read_file("input.txt"), '\n');
	auto contains = 0ui64;
	auto overlapped = 0ui64;

	for (auto const& line : lines)
	{
		auto const& [lhs, rhs] = extract_id_pair(line);

		if (contained_within(lhs, rhs))
		{
			++contains;
		}
		if (is_overlapped(lhs, rhs))
		{
			++overlapped;
		}
	}
	std::cout << "p1: " << contains << '\n';
	std::cout << "p2: " << overlapped << '\n';
}