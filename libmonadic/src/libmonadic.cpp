
// MFW
#include <monadic.hpp>

// ZeroMQ
#ifdef __USE_ZMQ__
#include <zmq.h>
#endif

// Global ZMQ context
#ifdef __USE_ZMQ__
void * zmq_context = zmq_init (1);
#endif
