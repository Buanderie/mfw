#ifndef __THREAD_HPP__
#define __THREAD_HPP__

#if defined(__LINUX__)
#include "threadlinux.hpp"
#elif defined(__WINDOWS__)
#include "threadwindows.hpp"
#endif

#endif // __THREAD_HPP__
