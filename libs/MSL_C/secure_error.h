#ifndef SECURE_ERROR_H
#define SECURE_ERROR_H

#include "__internal/__NULL.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*msl_constraint_handler)(const char*, void*, int);

void __msl_runtime_constraint_violation_s(const char* msg, void* ptr, int error);

#ifdef __cplusplus
}
#endif

#endif
