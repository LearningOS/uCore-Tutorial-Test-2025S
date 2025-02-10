#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	uint8 v = 111;
	assert_eq(v, trace_read(&v));
	v = 22;
	assert_eq(22, trace_read(&v));
	assert_eq(0, trace_write(&v, 33));

	assert_eq(-1, trace_read((uint8 *)0xfffffffful));
	assert_eq(-1, trace_write((uint8 *)0xfffffffful, 0));
	assert_eq(-1, trace_read((uint8 *)0x80200000ul));
	assert_eq(-1, trace_write((uint8 *)0x80200000ul, 0));
	assert(-1 != trace_read((uint8 *)main));
	assert_eq(-1, trace_write((uint8 *)main, 0));

	puts("Test trace_1 OK!");
	return 0;
}
