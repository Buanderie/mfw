#ifndef __FILESYSTEM_HPP__
#define __FILESYSTEM_HPP__

#if defined(__LINUX__)
#include "filesystemlinux.hpp"
#elif defined(__WINDOWS__)
#include "filesystemwindows.hpp"
#endif

#endif
