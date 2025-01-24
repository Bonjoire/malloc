# include "includes/malloc.h"

#define M (1024 * 1024)

int main()
{
    void* a = malloc(1);
    void* b = malloc(2);
    void* c = malloc(4);
    void* d = malloc(8);
    void* e = malloc(16);
    void* f = malloc(32);
    void* g = malloc(64);
    void* h = malloc(128);
    void* i = malloc(256);
    void* j = malloc(512);
    void* k = malloc(1024);
    void* l = malloc(1024 * 2);
    void* m = malloc(1024 * 4); 
    void* n = malloc(1024 * 32);
    void* o = malloc(M);
    void* p = malloc(16*M);
    void* q = malloc(128*M);
    show_alloc_mem(); 
    return (0); 
}