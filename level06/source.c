#include <stdio.h>
#include <stdlib.h>

int main()
{
	fgets(esp + 0x2c, 32, stdin);	Login

	scanf(%u, esp + 0x28);	Serial

	if (auth(Login, Serial))
		system("/bin/sh");
}

auth(Login ebp + 0x8, Serial ebp + 0xc)
{
	int	temp;
	Login[strcspn('\n', Login)] = '\0';	Replaces '\n' with '\0'
	temp = strnlen(Login, 32);
	
}
