/*
	Copyright 2003 by Marc J. Rochkind. All rights reserved.
	May be copied only for purposes and under conditions described
	on the Web page www.basepath.com/aup/copyright.htm.

	The Example Files are provided "as is," without any warranty;
	without even the implied warranty of merchantability or fitness
	for a particular purpose. The author and his publisher are not
	responsible for any damages, direct or incidental, resulting
	from the use or non-use of these Example Files.

	The Example Files may contain defects, and some contain deliberate
	coding mistakes that were included for educational reasons.
	You are responsible for determining if and how the Example Files
	are to be used.

*/
#include "ux.hpp"

using namespace Ux;

/**
	Calls mkdir.
*/
void Dir::mkdir(mode_t perms = PERM_DIRECTORY)
{
	if (::mkdir(path, perms) == -1)
		throw Error(errno);
}

/**
	Calls rmdir.
*/
void Dir::rmdir(void)
{
	if (::rmdir(path) == -1)
		throw Error(errno);
}
