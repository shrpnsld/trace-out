#pragma once

int dummy();

template <typename Arg_t>
int dummy(const Arg_t &)
{
	return 0;
}

template <typename Arg1_t, typename Arg2_t>
int dummy(const Arg1_t &, const Arg2_t &)
{
	return 0;
}

