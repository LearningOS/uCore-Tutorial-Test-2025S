#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	// simple usage
	uint8 v = 111;
	assert_eq(v, trace_read(&v));
	v = 22;
	assert_eq(22, trace_read(&v));
	assert_eq(0, trace_write(&v, 33));
	assert_eq(33, v);

	// invalid address
	assert_eq(-1, trace_read((uint8 *)0xfffffffful));
	assert_eq(-1, trace_write((uint8 *)0xfffffffful, 0));
	
	// kernel address
	assert_eq(-1, trace_read((uint8 *)0x80200000ul));
	assert_eq(-1, trace_write((uint8 *)0x80200000ul, 0));

	// check R/W permissions
	uint8 *p0 = (uint8 *)0x10000000;
	size_t len = 4096;
	assert_eq(0, mmap(p0, len, PROT_READ, MAP_ANONYMOUS));

	assert(-1 != trace_read(p0));
	assert_eq(-1, trace_write(p0, 0));

	assert_eq(0, munmap(p0, len));

	assert_eq(-1, trace_read(p0));
	assert_eq(-1, trace_write(p0, 0));

	puts("Test trace_1 OK!");
	return 0;
}
