#ifndef __THREAD_HPP__
#define __THREAD_HPP__

#ifndef __WINDOWS__
#include "threadlinux.hpp"
#else
#include "threadwindows.hpp"
#endif

#endif // __THREAD_HPP__