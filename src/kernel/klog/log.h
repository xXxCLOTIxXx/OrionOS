#ifndef LOG_H
#define LOG_H

#include <lib/types.h>


void LOG_OK(const char *format, ...);
void LOG_INFO(const char *format, ...);
void LOG_WARNING(const char *format, ...);
void LOG_ERROR(const char *format, ...);
void PANIC(const char *format, ...);

#endif