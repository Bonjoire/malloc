#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define M (1024 * 1024)

void print(char *s)
{
    write(1, s, strlen(s));
}

int     main()
{
    char *addr1;
    char *addr2;
    char *addr3;

    addr1 = (char*)malloc(16*M);
    if (addr1 == NULL)
    {
        print("Failed to allocate memory\n");
        exit(1);
    }
    strcpy(addr1, "Hello world!\n");
    print(addr1);
    addr2 = (char*)malloc(16*M);
    if (addr2 == NULL)
    {
        print("Failed to allocate memory\n");
        exit(1);
    }
    addr3 = (char*)realloc(addr1, 128*M);
    if (addr3 == NULL)
    {
        print("Failed to reallocate memory\n");
        exit(1);
    }
    addr3[127*M] = 42;
    print(addr3);
    return (0);
}
