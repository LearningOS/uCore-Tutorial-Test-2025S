#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>

/*
理想结果：输出 Test 04_5 ummap OK!
*/

int main()
{
	uint64 start = 0x10000000;
	uint64 len = 4096;
	int prot = PROT_READ | PROT_WRITE;
	assert_eq(0, mmap((void *)start, len, prot, MAP_ANONYMOUS));
	assert_eq(mmap((void *)(start + len), len * 2, prot, MAP_ANONYMOUS), 0);
	assert_eq(munmap((void *)start, len), 0);
	assert_eq(mmap((void *)(start - len), len + 1, prot, MAP_ANONYMOUS), 0);
	for (uint64 i = (start - len); i < (start + len * 3); ++i) {
		uint8 *addr = (uint8 *)i;
		*addr = (uint8)i;
	}
	for (uint64 i = (start - len); i < (start + len * 3); ++i) {
		uint8 *addr = (uint8 *)i;
		assert_eq(*addr, (uint8)i);
	}
	puts("Test 04_4 ummap OK!");
	return 0;
}