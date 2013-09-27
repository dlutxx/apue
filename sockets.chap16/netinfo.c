#include "lib.h"
#include <netdb.h>

void hosts()
{
    struct hostent* host = NULL;
    sethostent(1);

    while (NULL!=(host=gethostent())) {
        pr("host name=%s, addrtype=%d, length=%d, \naliases: ", host->h_name, host->h_addrtype, host->h_length);

        while(NULL!=*host->h_aliases) {
            pr("%s, ", *host->h_aliases++);
            // ++host->h_aliases;
        }
        pr("\naddress list: ");
        while (NULL!=*host->h_addr_list) {
            pr("%s, ", *host->h_addr_list);
            ++host->h_addr_list;
        }
        pr("\n------\n");
    }
    endhostent();
}

void nets()
{
    struct netent * buf = NULL;
    setnetent(1);

    while( NULL !=(buf = getnetent()) ) {
        pr("name=%s, addr type=%d, net num=%u, alias: ", buf->n_name, buf->n_addrtype, buf->n_net);

        while( NULL != *buf->n_aliases ) {
            pr("%s, ", *buf->n_aliases++);
        }
        pr("\n");
    }
    endnetent();
}

void protocols()
{
    struct protoent* buf = NULL;
    setprotoent(1);

    while (NULL!=(buf=getprotoent())) {
        pr("protocol name=%s, number=%d, aliases: ", buf->p_name, buf->p_proto);

        while (NULL!=*buf->p_aliases) {
            pr("%s, ", *buf->p_aliases++);
        }
        pr("\n");
    }
    endprotoent();
}

int main(int argc, char* argv[])
{
    hosts();
    nets();
    protocols();
    return 0;
}
