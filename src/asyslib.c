/*
 * asyslib.c
 *
 * system library.
 *
 *  Created on: 2019年9月16日
 *      Author: ueyudiud
 */

#include "alo.h"
#include "aaux.h"
#include "alibs.h"

#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>

#define alo_pusherrcode alo_pushinteger

static int sys_exit(astate T) {
	int status = aloL_getoptinteger(T, 0, 0);
	if (aloL_getoptbool(T, 1, false)) {
		alo_deletestate(T);
	}
	aloE_void(exit(status));
	return 0;
}

static int sys_getenv(astate T) {
	alo_pushstring(T, getenv(aloL_checkstring(T, 0)));
	return 1;
}

static int sys_clock(astate T) {
	alo_pushinteger(T, clock() / CLOCKS_PER_SEC);
	return 1;
}

/**
 ** get current time measured in milliseconds from
 ** January 1st, 1970 UTC 0:00 to current time.
 */
static int sys_time(astate T) {
	struct timeval t;
	gettimeofday(&t, NULL);
	alo_pushinteger(T, aloE_cast(aint, t.tv_sec) * 1000 + aloE_cast(aint, t.tv_usec) / 1000);
	return 1;
}

/**
 ** run command in shell, if no parameter exist, return true if
 ** shell is available. If parameter is present, try to run command.
 ** The function has two results, first is a boolean value, when
 ** run meet an error, it return false.
 ** prototype: sys.run([cmd])
 */
static int sys_run(astate T) {
	astr cmd = aloL_getoptstring(T, 0, NULL);
	int stat = system(cmd);
	if (cmd) {
		if (stat == -1) { /* error? */
			int no = errno;
			alo_pushboolean(T, false);
			alo_pusherrcode(T, no);
		}
		else {
			alo_pushboolean(T, true);
			alo_pushinteger(T, stat);
		}
		return 2;
	}
	else {
		alo_pushboolean(T, stat);
		return 1;
	}
}

static const acreg_t mod_funcs[] = {
	{ "exit", sys_exit },
	{ "clock", sys_clock },
	{ "getenv", sys_getenv },
	{ "time", sys_time },
	{ "run", sys_run },
	{ NULL, NULL }
};

int aloopen_syslib(astate T) {
	alo_newtable(T, 0);
	aloL_setfuns(T, -1, mod_funcs);
	return 1;
}
