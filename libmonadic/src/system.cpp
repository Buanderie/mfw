
#if defined(__WINDOWS__)
#include <windows.h>
#elif defined(__MACOSX__)
#include <sys/param.h>
#include <sys/sysctl.h>
#elif defined(__LINUX__)
#include <unistd.h>
#endif

// INTERNAL
#include "system.hpp"

int monadic::System::getNumCores() {
#if defined(__WINDOWS__)
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
#elif defined(__MACOSX__)
    int nm[2];
    size_t len = 4;
    uint32_t count;

    nm[0] = CTL_HW; nm[1] = HW_AVAILCPU;
    sysctl(nm, 2, &count, &len, NULL, 0);

    if(count < 1) {
        nm[1] = HW_NCPU;
        sysctl(nm, 2, &count, &len, NULL, 0);
        if(count < 1) { count = 1; }
    }
    return count;
#elif defined(__LINUX__)
    return sysconf(_SC_NPROCESSORS_ONLN);
#endif
}
