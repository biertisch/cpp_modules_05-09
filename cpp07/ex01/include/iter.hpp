#pragma once

template <typename T, typename L, typename F>
void iter(T* array, const L length, F function)
{
	for (L i = 0; i < length; i++)
		function(array[i]);
}
