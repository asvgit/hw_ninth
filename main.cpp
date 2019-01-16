#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include<range/v3/all.hpp>

typedef std::string string;
typedef std::vector<string> StringVector;
typedef std::vector<int> IntVector;

namespace str {

StringVector split(const string &str, const char d) {
    StringVector r;

    string::size_type start = 0;
    string::size_type stop = str.find_first_of(d);
    while(stop != string::npos) {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

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
			IntVector ip(sv.size());
			std::transform(sv.begin(), sv.end()
					, ip.begin(), [](auto l) { return std::stoi(l); });
			return ip;
		};

		for(string line ; std::getline(std::cin, line);) {
			auto v = str::split(line, '\t');
			ip_pool.push_back(stoi(str::split(v.front(), '.')));
		}

		std::sort(ip_pool.begin(), ip_pool.end(), std::greater<IntVector>());

		auto print_ip = [](const auto &ip) {
			for(const auto &ip_part : ip) {
				if (&ip_part != &ip.front())
					std::cout << ".";
				std::cout << ip_part;
			}
			std::cout << std::endl;
		};

		for(const auto &ip : ip_pool)
			print_ip(ip);

		// filter_1 filter_46_70 filter_any_46; 
		std::vector<IntVector> filters = {{}, {}, {}};
		int ind = 0;
		for (const auto &ip : ip_pool) {
			if (filter(1, ip.front())) {
				filters[0].push_back(ind);
			} else if (filter(46, ip[0]) && filter(70, ip[1])) {
				filters[1].push_back(ind);
			}
			if (filter(46, ip[0], ip[1], ip[2], ip[3])) {
				filters[2].push_back(ind);
			}
			++ind;
		}

		for (const auto &f : filters) {
			for (const auto &item : f)
				print_ip(ip_pool[item]);
		}
	} catch(const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
