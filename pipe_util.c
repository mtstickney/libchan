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

pid_t begin(const char *path, char  *const args[], Channel *c)
{
	pid_t pid;
	int in, out;

	if (recv(c, &in) == -1) {
		fprintf(stderr, "begin: failed to recv input fd\");
		return -1;
	}
	if (recv(c, &out) == -1) {
		fprintf(stderr, "begin: failed to recv output fd\n");
		return -1;
	}

	if (in >= 0) {
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (out >= 0) {
		dup2(out, STDOUT_FILENO);
		close(out);
	}
	
	switch(pid = fork()) {
	case 0:
		if (execv(path,args) < 0) {
			perror("begin");
			return -1;
		}
		break;
	case -1:
		perror("begin");
		return -1;
		break;
	default:
		return pid;
		break;
	}

}