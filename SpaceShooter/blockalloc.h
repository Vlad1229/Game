#ifndef BLOCKALLOC_H
#define BLOCKALLOC_H

#include "memorypool.h"

template<class T, int numberOfBlocks>
class BlockAlloc
{
public:
    static void* operator new(size_t s) {
        if (s != sizeof(T)) {
            return ::operator new(s);
        }
        return pool->AllockBlock();
    }

    static void operator delete(void* ptr, size_t s) {
        if (s != sizeof(T)) {
            return ::operator delete(ptr);
        } else if (ptr != nullptr) {
            pool->FreeBlockr(reinterpret_cast<T*>(ptr));
        }
    }
private:
    static MemoryPool<T>* pool;
};

template <class T, int numberOfBlocks> MemoryPool<T>* BlockAlloc<T, numberOfBlocks>::pool = new MemoryPool<T>(numberOfBlocks);

#endif // BLOCKALLOC_H
