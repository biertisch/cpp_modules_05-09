#include "Serializer.hpp"
#include <iostream>

int main()
{
	Data data = {0, 1.5, "test"};
	uintptr_t rawPtr = Serializer::serialize(&data);
	Data* dataPtr = Serializer::deserialize(rawPtr);

	std::cout << "Original data address:     " << &data << "\n";
	std::cout << "Serialized raw pointer:    0x" << std::hex << rawPtr << "\n";
	std::cout << "Deserialized data pointer: " << dataPtr << "\n";

	std::cout << "\nContent of initial data structure:\n";
	std::cout << "intVal: " << data.intVal << "\n";
	std::cout << "dblVal: " << data.dblVal << "	\n";
	std::cout << "strVal: " << data.strVal << "	\n";

	std::cout << "\nContent of deserialized version:\n";
	std::cout << "intVal: " << dataPtr->intVal << "\n";
	std::cout << "dblVal: " << dataPtr->dblVal << "	\n";
	std::cout << "strVal: " << dataPtr->strVal << "	\n";

	return 0;
}
