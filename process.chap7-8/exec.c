#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    /* 
    setenv("MAIL", "mailllll", 1);
    execlp("./env", "env", (char*)NULL);
    */
    // only one environmental var !
    char* env[2] = {"MAIL=mmmmm", (char*)NULL};
    execle("./env", "env", (char*)NULL, env);
    return 0;
}

