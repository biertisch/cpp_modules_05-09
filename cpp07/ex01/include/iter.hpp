#pragma once

template <typename T, typename F>
void iter(T* array, const unsigned int length, F& function)
{
	if (!array)
		return;

	for (unsigned int i = 0; i < length; i++)
		function(array[i]);
}
