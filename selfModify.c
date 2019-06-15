#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

int main(void){
	unsigned char code[] = {
		0x55,
		0x48, 0x89, 0xe5,
		0x48, 0x89, 0x7d, 0xf8,
		0x48, 0x8b, 0x45, 0xf8,
		0xc7, 0x00, 0x09, 0x00, 0x00, 0x00,
		0x90,
		0x5d,
		0xc3
	};

	void* ptr = mmap(0, sizeof(code), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	
	if (ptr == (void*)-1) {
		perror("mmap");
		return 1;
	}

	printf("code[14] : ");
	scanf("%hhd", &code[14]);	

	memcpy(ptr, code, sizeof(code));
	
	void (*funcptr)(int*) = ptr;

	int num = 0;

	funcptr(&num);

	printf("num=%d\n",num);
}
