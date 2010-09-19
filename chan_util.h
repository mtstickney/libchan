/* include list
	chan.h
*/

struct str_header
{
	size_t len;
	Channel bytes;
};

int send_string(Channel *c, const char *str);

char *recv_string(Channel *c);