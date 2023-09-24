#pragma once

int dummy();

template <typename ...Args_t>
int dummy(Args_t &&...)
{
	return 0;
}

