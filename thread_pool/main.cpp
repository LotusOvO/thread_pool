#include<iostream>
#include<random>
#include"thread_pool.h"

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> dist(-1000, 1000);
auto rnd = std::bind(dist, mt);

void shc() {
	std::this_thread::sleep_for(std::chrono::milliseconds(2000 + rnd()));
}

void test1(const int a, const int b) {
	shc();
	int const res = a * b;
	std::cout << a << "*" << b << "="<< res << "\n";
}

int test3(const int a, const int b) {
	shc();
	const int c = a * b;
	return c;
}

void example() {
	ThreadPool pool(3);

	pool.init();

	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			pool.submit(test1, i, j);
		}
	}
	auto f = pool.submit(test3, 9, 9);
	int res = f.get();
	std::cout << res << "\n";

	pool.shutdown();
}

int main() {
	example();
	return 0;
}