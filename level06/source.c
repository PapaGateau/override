#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>

int auth(login_str ebp + 0x8, Serial ebp + 0xc)
{
	int	login_len; // EBP - 0xc

	login_str[strcspn('\n', login_str)] = 0;
	login_len = strnlen(login_str, 32);
	
	if (login_len != 5) {
		return 1;
	}

	if (ptrace(0, 0, 1, 0) == 0xffffffff) { // ???
		puts("\e[32m.---------------------------.");
		puts("\e[31m| !! TAMPERING DETECTED !!  |");
		puts("\e[32m.---------------------------.");
		return 1;
	}
	
	int value; // EBP - 0x10
	value = (int) (login_str[3]) ^ 0x1337 + 0x5eeded;

}

int main()
{
	fgets(esp + 0x2c, 32, stdin);	Login

	scanf(%u, esp + 0x28);	Serial

	if (!auth(Login, Serial))
		system("/bin/sh");
}
