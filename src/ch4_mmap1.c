#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>

/*
理想结果：程序触发访存异常，被杀死。不输出 error 就算过。
*/

int main()
{
	uint64 start = 0x10000000;
	uint64 len = 4096;
	int prot = PROT_READ;
	assert_eq(0, mmap((void *)start, len, prot, MAP_ANONYMOUS));
	uint8 *addr = (uint8 *)start;
	*addr = (uint8)start;
	puts("Should cause error, Test 04_1 fail!");
	return 0;
}