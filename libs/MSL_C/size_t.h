#ifndef _MSL_SIZE_T_H
#define _MSL_SIZE_T_H

#include "ansi_parms.h"

#ifndef _MSL_SIZE_T_TYPE
	#define _MSL_SIZE_T_TYPE __typeof__(sizeof(0))
#endif

#ifndef _MSL_SIZE_T_DEFINED
	#define _MSL_SIZE_T_DEFINED
	typedef _MSL_SIZE_T_TYPE size_t;
#endif

#endif // _MSL_SIZE_T_H
