#ifndef _UTIL_CHECK_HPP
#define _UTIL_CHECK_HPP

#include <ft2build.h>
#include FT_FREETYPE_H

#define GL_CHECK() _glCheck(__FILE__, __LINE__)
bool _glCheck(const char* file, int line);

#define FT_CHECK(error) _ftCheck(error, __FILE__, __LINE__)
bool _ftCheck(int error, const char* file, int line);

#endif
