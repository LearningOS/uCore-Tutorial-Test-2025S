#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// NOTE: make sure these match with those in syscall_ids.h
#define SYSCALL_WRITE 64
#define SYSCALL_EXIT 93
#define SYSCALL_YIELD 124
#define SYSCALL_GETTIMEOFDAY 169
#define SYSCALL_TRACE 410

int main()
{
	int64 t1 = get_mtime();
	get_mtime();
	sleep(500);
	int64 t2 = get_mtime();
	int64 t3 = get_mtime();

	assert(3 <= count_syscall(SYSCALL_GETTIMEOFDAY));
	// 注意这次 sys_trace 调用本身也计入
	assert_eq(2, count_syscall(SYSCALL_TRACE));
	assert_eq(0, count_syscall(SYSCALL_WRITE));
	assert(0 < count_syscall(SYSCALL_YIELD));
	assert_eq(0, count_syscall(SYSCALL_EXIT));

	// 看看puts的实现，想想为什么 write 调用只有一次
	// NOTE: This differs from rCore's user lib implementation
	puts("string from task trace test");
	int64 t4 = get_mtime();
	int64 t5 = get_mtime();
	assert(5 <= count_syscall(SYSCALL_GETTIMEOFDAY));
	assert_eq(7, count_syscall(SYSCALL_TRACE));
	assert_eq(1, count_syscall(SYSCALL_WRITE)); // (...)
	assert(0 < count_syscall(SYSCALL_YIELD));
	assert_eq(0, count_syscall(SYSCALL_EXIT));

	uint8 v = 111;
	assert_eq(111, trace_read(&v));

	uint8 u = (uint8)t1 ^ t2 ^ t3 ^ t4 ^ t5;
	trace_write(&v, u);
	assert_eq(u, *(volatile uint8 *)&v);

	assert(-1 != trace_read((uint8 *)main));
    
    puts("Test trace OK!");
	return 0;
}
