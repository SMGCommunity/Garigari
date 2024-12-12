#ifndef _MSL_SIZE_T_H
#define _MSL_SIZE_T_H

#ifdef __cplusplus
extern "C" {
#endif

#define SIZE_T_TYPE __typeof__(sizeof(0))
typedef SIZE_T_TYPE size_t;

#ifdef __cplusplus
}
#endif

#endif // _MSL_SIZE_T_H
