#include <stdio.h>
#include <stdlib.h>
#define MEM_PAGE_SIZE 0x1000
typedef struct mempool_s
{

    int block_size; // 内存块大小
    int free_count; // 有多少块可以用
    void *mem;      // 指向整体块
    void *ptr;      // 指向分配的块
} mempool_t;
// size_t 类型在标准 C 中是定义在 <stddef.h> 中的，
// 虽然很多系统中 <stdlib.h> 也会包含它，
// 但最好显式包含
// page,block  // 页面，区块
int memp_init(mempool_t *mp, size_t block_size)
{
    if (!mp)
        return -1;                    // 指针为空则返回-1
    memset(mp, 0, sizeof(mempool_t)); // 清理内存
    mp->block_size = block_size;
    mp->free_count = MEM_PAGE_SIZE / block_size;
    mp->mem = malloc(MEM_PAGE_SIZE);
    if (!mp->mem)
        return -1;
    mp->ptr = mp->mem;
    int i = 0;
    char *ptr = mp->ptr;
    for (i = 0; i < mp->free_count; i++)
    {
        *(char **)ptr = ptr + block_size; //?
        ptr += block_size;
    }
    *(char **)ptr = NULL;
    return 0;
}
void *_malloc(size_t size)
{
    printf("_malloc\n");
}
void _free(void *ptr)
{
    printf("_free\n");
}
#define malloc(size) _malloc(size)
#define free(ptr) _free(ptr)
int main()
{
    void *p1 = malloc(5);
    void *p2 = malloc(10);
    void *p3 = malloc(15);
    free(p1);
    free(p2);
    free(p3);
    return 0;
}
