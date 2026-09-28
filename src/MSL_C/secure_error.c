#include "secure_error.h"

static msl_constraint_handler __msl_constraint_handler;

void __msl_runtime_constraint_violation_s(const char* msg, void* ptr, int error) {
    if (__msl_constraint_handler != NULL) {
        __msl_constraint_handler(msg, ptr, error);
    }
}
