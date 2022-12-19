#pragma once
#define _WINDOWS

#include <string>
#include "gamerules.h"

int main(int argc, char *argv[])
{
	if (argc == 4 && !strcmp(argv[1], "-window"))
	{
		int w = stoi(argv[2]);
		int h = stoi(argv[3]);
		scale(w, h);
	}

	return run(new MyFramework);
}
