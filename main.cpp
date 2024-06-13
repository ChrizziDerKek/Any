#include "any.hpp"
#include <iostream>

void* HelloWorld(void* a) {
	std::cout << ((IGeneric*)a)->GetString() << std::endl << std::endl;
	return nullptr;
}

int main() {
	Any msg = construct<String>("Hello World!");
	Any func = construct<Function>(HelloWorld);
	func->Call((void*)msg.get());

	Any v1 = construct<Float>(0.1f);
	Any v2 = construct<Float>(0.2f);
	Any result = v1 + v2;
	std::cout << result->GetFloat() << std::endl << std::endl;

	Any i = construct<Int>(0);
	Any limit = construct<Int>(69);
	while (i < limit)
		++i;
	std::cout << i->GetInt() << std::endl;
	std::cout << (i == limit) << std::endl << std::endl;

	for (Any j = construct<Int>(10); j >= construct<Int>(0); j--)
		std::cout << j->GetInt() << std::endl;
	std::cout << std::endl;

	return 0;
}