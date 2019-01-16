#include <iostream>
#include <string>
#include <vector>

#include<range/v3/all.hpp>

typedef std::string string;
typedef std::vector<string> StringVector;
typedef std::vector<int> IntVector;

template<char S = ' '>
StringVector split(const string &str) {
    StringVector r;

    string::size_type start = 0;
    string::size_type stop = str.find_first_of(S);
    while(stop != string::npos) {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(S, start);
    }

    r.push_back(str.substr(start));

    return r;
}

template<typename T>
bool filter(const int cond, const T &arg) {
	return cond == arg;
}

template<typename T, typename... Args>
bool filter(const int cond, const T &arg, const Args&... args) {
	if (cond == arg)
		return true;
	return filter(cond, args...);
}

int main() {
	try {
		std::vector<IntVector> ip_pool;

		auto stoi = [](const auto &sv) {
			return sv | ranges::view::transform([](const auto &l) { return std::stoi(l); });
		};

		for(string line ; std::getline(std::cin, line);) {
			const auto ip = split<'\t'>(line).front();
			ip_pool.push_back(stoi(split<'.'>(ip)));
		}

		ranges::sort(ip_pool, std::greater<IntVector>());

		auto print_ip = [](const auto &ip) {
			for(const auto &ip_part : ip) {
				if (&ip_part != &ip.front())
					std::cout << ".";
				std::cout << ip_part;
			}
			std::cout << std::endl;
		};

		ranges::for_each(ip_pool, print_ip);

		ranges::for_each(ip_pool
					| ranges::view::filter([](const auto &ip) {return filter(1, ip.front());})
				, print_ip);
		ranges::for_each(ip_pool
					| ranges::view::filter([](const auto &ip) {return filter(46, ip[0]) && filter(70, ip[1]);})
				, print_ip);
		ranges::for_each(ip_pool
					| ranges::view::filter([](const auto &ip) {return filter(46, ip[0], ip[1], ip[2], ip[3]);})
				, print_ip);
	} catch(const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
