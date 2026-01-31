#pragma once

#include <stdint.h>
#include <string>

struct Data
{
	int intVal;
	double	dblVal;
	std::string strVal;
};

class Serializer
{
	private:
		// Class is not instantiable
		Serializer();
		Serializer(const Serializer&);
		~Serializer();
		Serializer& operator=(const Serializer&);

	public:
		static uintptr_t serialize(Data *ptr);
		static Data* deserialize(uintptr_t raw);
};
