#include <unistd.h>
#include "pipe_util.h"

int mk_pipe(Pipe *p)
{
	int fds[2];
	int ret;

	ret = pipe(fds);
	p->reader = fds[0];
	p->writer = fds[1];
	return ret;
}

void close_pipe(Pipe *p)
{
	close(p->reader);
	close(p->writer);
}
