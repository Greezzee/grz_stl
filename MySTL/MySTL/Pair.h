#pragma once
template <typename F, typename S>
class Pair
{
public:
	Pair(F f, S s)
	{
		_first = f;
		_second = s;
	}

	F _first;
	S _second;
};

