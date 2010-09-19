#include "chan_util.h"

int send_string(const char *str, Channel *c)
{
	struct str_header h;
	char *bufp = str;

	h.len = strlen(str);
	if (mk_chan(&(h.bytes), sizeof(char)) == -1)
		return -1;

	if (send(c, &h) == -1)
		goto BAD_OUT;
	while (*bufp) {
		if (send(&(h.bytes), bufp++) == -1)
			goto BAD_OUT;
	}
	/* send the NUL */
	if (send(&(h.bytes), bufp) == -1)
		goto BAD_OUT

	free_chan(&(h.bytes));
	return 0;

BAD_OUT:
	free_chan(&(h.bytes));
	return -1;
}

char *recv_string(Channel *c)
{
	struct str_header h;
	char *buf, *p;
	char i;

	if (recv(c, &h) == -1)
		return NULL;

	buf = malloc(h.len+1);
	if (buf == NULL)
		return NULL;

	p = buf;
	for (i=0; i<h.len+1; i++) {
		if (recv(&(h.bytes), p++) == -1)
			return NULL;
	}
	return buf;
}