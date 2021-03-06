/*
 * afun.h
 *
 * methods and properties for function value.
 *
 *  Created on: 2019年7月23日
 *      Author: ueyudiud
 */

#ifndef AFUN_H_
#define AFUN_H_

#include "aobj.h"

#define aclosizel(l) (sizeof(aclosure_t) + (l) * sizeof(atval_t))
#define aclosize(o) aclosizel((o)->length)

aclosure_t* aloF_new(astate, size_t, aproto_t*);
aclosure_t* aloF_newc(astate, acfun, size_t);
aproto_t* aloF_newp(astate);
atval_t* aloF_get(aclosure_t*, size_t);
acap* aloF_find(astate, askid_t);
void aloF_close(astate, askid_t);
void aloF_deletep(astate, aproto_t*);

#endif /* AFUN_H_ */
