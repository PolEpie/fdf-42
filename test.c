#include <stdio.h>
#include <stdbool.h>

int main(void)
{
	bool staked = false;

	printf("%d", (staked && -3) || 5);
}