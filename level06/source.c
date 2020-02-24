#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>

int auth(char *login_str ebp + 0x8, unsigned int Serial ebp + 0xc)
{
	int	login_len; // EBP - 0xc

	login_str[strcspn('\n', login_str)] = 0;
	login_len = strnlen(login_str, 32);
	
	if (login_len <= 5) {
		return 1;
	}
	if (ptrace(0, 0, 1, 0) == 0xffffffff) { // checks for ltrace/gdb
		puts("\e[32m.---------------------------.");
		puts("\e[31m| !! TAMPERING DETECTED !!  |");
		puts("\e[32m.---------------------------.");
		return 1;
	}
	
	int hash; // EBP - 0x10
	hash = (int) (login_str[3]) ^ 0x1337 + 0x5eeded; 

	int index; // EBP - 0x14
	for (index = 0; index < login_len; index++) {
		if (login_str[index] <= 31)	; '1'
			return 1;
		/*
		 *	hash_operations(login_str[index], hash); 
		 */
	}
	if (hash == Serial)
		return 0;
	else
		return 1;
}

int main()
{
	fgets(esp + 0x2c, 32, stdin);	Login

	scanf(%u, esp + 0x28);	Serial

	if (!auth(Login, Serial))
		system("/bin/sh");
}
