/* include list
	unistd.h
*/

typedef struct pipe {
	int reader;
	int writer;
} Pipe;

int mk_pipe(Pipe *p);

void close_pipe(Pipe *p);
