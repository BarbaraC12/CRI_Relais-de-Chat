#include "Server.hpp"
#include "bnf.hpp"
#include "Param.hpp"
#include <algorithm>
#include <ctime>
#include <csignal>
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <utility>
#include <stdlib.h>

#ifndef SOCK_NONBLOCK
# define SOCK_NONBLOCK O_NONBLOCK
#endif
#define BUFFER_SIZE_IRC	512
#define SSTR( x ) static_cast< std::ostringstream & >( \
		( std::ostringstream() << std::dec << x ) ).str()
