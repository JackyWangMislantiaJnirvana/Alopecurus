/*
 * amathlib.c
 *
 * math library
 *
 *  Created on: 2019年9月1日
 *      Author: ueyudiud
 */

#include "alo.h"
#include "aaux.h"
#include "alibs.h"

#include <stdlib.h>
#include <math.h>

#define PI 3.1415926535897932384626433832795
#define E 2.7182818284590452353602874713527

static int math_abs(astate T) {
	int flag;
	aint i = alo_tointegerx(T, 0, &flag);
	if (flag) {
		alo_pushinteger(T, llabs(i));
	}
	else {
		alo_pushnumber(T, fabs(aloL_checknumber(T, 0)));
	}
	return 1;
}

static int math_min(astate T) {
	int n = alo_gettop(T);
	if (n == 0) {
		aloL_argerror(T, 0, "value expected");
	}
	int min = 0;
	for (int i = 1; i < n; ++i) {
		if (alo_compare(T, i, min, ALO_OPLT)) {
			min = i;
		}
	}
	alo_push(T, min);
	return 1;
}

static int math_max(astate T) {
	int n = alo_gettop(T);
	if (n == 0) {
		aloL_argerror(T, 0, "value expected");
	}
	int max = 0;
	for (int i = 1; i < n; ++i) {
		if (alo_compare(T, max, i, ALO_OPLT)) {
			max = i;
		}
	}
	alo_push(T, max);
	return 1;
}

static int math_deg(astate T) {
	alo_pushnumber(T, aloL_checknumber(T, 0) * (180.0 / PI));
	return 1;
}

static int math_rad(astate T) {
	alo_pushnumber(T, aloL_checknumber(T, 0) * (PI / 180.0));
	return 1;
}

static int math_sqrt(astate T) {
	alo_pushnumber(T, sqrt(aloL_checknumber(T, 0)));
	return 1;
}

static int math_cbrt(astate T) {
	alo_pushnumber(T, cbrt(aloL_checknumber(T, 0)));
	return 1;
}

static int math_exp(astate T) {
	alo_pushnumber(T, exp(aloL_checknumber(T, 0)));
	return 1;
}

static int math_sin(astate T) {
	alo_pushnumber(T, sin(aloL_checknumber(T, 0)));
	return 1;
}

static int math_cos(astate T) {
	alo_pushnumber(T, cos(aloL_checknumber(T, 0)));
	return 1;
}

static int math_tan(astate T) {
	alo_pushnumber(T, tan(aloL_checknumber(T, 0)));
	return 1;
}

static int math_ln(astate T) {
	alo_pushnumber(T, log(aloL_checknumber(T, 0)));
	return 1;
}

static int math_log(astate T) {
	alo_pushnumber(T, log(aloL_checknumber(T, 0)) / log(aloL_getoptnumber(T, 1, E)));
	return 1;
}

static int math_asin(astate T) {
	alo_pushnumber(T, asin(aloL_checknumber(T, 0)));
	return 1;
}

static int math_acos(astate T) {
	alo_pushnumber(T, acos(aloL_checknumber(T, 0)));
	return 1;
}

static int math_atan(astate T) {
	alo_pushnumber(T, atan2(aloL_checknumber(T, 0), aloL_getoptnumber(T, 1, 0)));
	return 1;
}

static int math_floor(astate T) {
	int flag;
	aint i = alo_tointegerx(T, 0, &flag);
	if (flag) {
		alo_pushinteger(T, i);
	}
	else {
		alo_pushnumber(T, floor(aloL_checknumber(T, 0)));
	}
	return 1;
}

static int math_ceil(astate T) {
	int flag;
	aint i = alo_tointegerx(T, 0, &flag);
	if (flag) {
		alo_pushinteger(T, i);
	}
	else {
		alo_pushnumber(T, ceil(aloL_checknumber(T, 0)));
	}
	return 1;
}

static const acreg_t mod_funcs[] = {
	{ "E", NULL },
	{ "INTMAX", NULL },
	{ "INTMIN", NULL },
	{ "NAN", NULL },
	{ "PI", NULL },
	{ "abs", math_abs },
	{ "acos", math_acos },
	{ "asin", math_asin },
	{ "atan", math_atan },
	{ "cbrt", math_cbrt },
	{ "ceil", math_ceil },
	{ "cos", math_cos },
	{ "deg", math_deg },
	{ "exp", math_exp },
	{ "floor", math_floor },
	{ "log", math_log },
	{ "ln", math_ln },
	{ "max", math_max },
	{ "min", math_min },
	{ "rad", math_rad },
	{ "sin", math_sin },
	{ "sqrt", math_sqrt },
	{ "tan", math_tan },
	{ NULL, NULL }
};

int aloopen_mathlib(astate T) {
	alo_bind(T, "math.abs", math_abs);
	alo_bind(T, "math.acos", math_acos);
	alo_bind(T, "math.asin", math_asin);
	alo_bind(T, "math.atan", math_atan);
	alo_bind(T, "math.cbrt", math_cbrt);
	alo_bind(T, "math.ceil", math_ceil);
	alo_bind(T, "math.cos", math_cos);
	alo_bind(T, "math.deg", math_deg);
	alo_bind(T, "math.exp", math_exp);
	alo_bind(T, "math.floor", math_floor);
	alo_bind(T, "math.log", math_log);
	alo_bind(T, "math.ln", math_ln);
	alo_bind(T, "math.min", math_min);
	alo_bind(T, "math.max", math_max);
	alo_bind(T, "math.rad", math_rad);
	alo_bind(T, "math.sin", math_sin);
	alo_bind(T, "math.sqrt", math_sqrt);
	alo_bind(T, "math.tan", math_tan);
	alo_newtable(T, 0);
	aloL_setfuns(T, -1, mod_funcs);
	alo_pushnumber(T, NAN);
	alo_rawsets(T, -2, "NAN");
	alo_pushnumber(T, PI);
	alo_rawsets(T, -2, "PI");
	alo_pushnumber(T, E);
	alo_rawsets(T, -2, "E");
	alo_pushinteger(T, ALO_INT_PROP(MAX));
	alo_rawsets(T, -2, "INTMAX");
	alo_pushinteger(T, ALO_INT_PROP(MIN));
	alo_rawsets(T, -2, "INTMIN");
	return 1;
}
