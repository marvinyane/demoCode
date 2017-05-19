#include <assert.h>
#include <stdio.h>
#include <nanomsg/nn.h>
#include <nanomsg/pipeline.h>

#define NODE0 "node0"
#define NODE1 "node1"

int node0(const char* url)
{
    int sock = nn_socket(AF_SP, NN_PULL);
    assert(sock >= 0);
    assert(nn_bind(sock, url) >= 0);

    while (1)
    {
        char* buf = NULL;
        int bytes = nn_recv(sock, &buf, NN_MSG, 0);
        assert(bytes >= 0);
        printf("NODE0: RECEIVED \"%s\"\n", buf);
        nn_freemsg(buf);
    }
}

int node1(const char* url, const char* msg)
{
    int sz_msg = strlen(url) + 1;
    int sock = nn_socket(AF_SP, NN_PUSH);
    assert(sock >= 0);
    assert(nn_connect(sock, url) >= 0);

    printf("NODE1: SEDNING \"%s\"\n", msg);

    int bytes = nn_send(sock, msg, sz_msg, 0);
    assert(bytes >= 0);
    return nn_shutdown(sock, 0);
}

int main(int argc, char** argv)
{
    if (strcmp(NODE0, argv[1]) == 0 && argc > 1)
        return node0(argv[2]);
    else if (strcmp(NODE1, argv[1]) == 0 && argc > 2)
        return node1(argv[2], argv[3]);
    else
        printf("error");

    return 0;
}
