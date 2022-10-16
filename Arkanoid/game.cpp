#pragma once
#define _WINDOWS

#include <string>
#include "gamerules.h"

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		int w = stoi(argv[1]);
		int h = stoi(argv[2]);
		scale(w, h);
	}

	return run(new MyFramework);
}
