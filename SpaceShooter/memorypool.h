#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

#include <iostream>

struct Pointer{
    bool isFree;
    Pointer* next = nullptr;
};

template<class T>
class MemoryPool
{
private:
    size_t numberOfBlocks;
    char* pool;
    Pointer* head;
public:
    MemoryPool(size_t numberOfBlocks){
        size_t blockSize = sizeof(Pointer) + sizeof (T);
        pool = new char[numberOfBlocks * blockSize];
        head = reinterpret_cast<Pointer*>(pool);
        this->numberOfBlocks = numberOfBlocks;
        head->isFree = true;
        for(size_t i = 1; i < numberOfBlocks; i++){
            Pointer* point = reinterpret_cast<Pointer*>(reinterpret_cast<char*>(head) + blockSize);
            point->next = head;
            point->isFree = true;
            head = point;
        }

    }

    ~MemoryPool(){
        delete [] pool;
    }

    T* AllockBlock(){
        Pointer* point = head;

        for(unsigned int i = 0; i < numberOfBlocks; i++)
        {
            if(point->isFree)
            {
                point->isFree = false;
                 return reinterpret_cast<T*>(reinterpret_cast<char*>(point) + sizeof(Pointer));
            }
            else
            {
                point = point->next;
            }
        }

        std::cout<<"Error! Memory Pool filled"<<std::endl;
        return nullptr;
    }

    void FreeBlockr(T* ptr){
        Pointer* point = head;

        for(unsigned int i = 0; i < numberOfBlocks; i++){
            if(ptr == reinterpret_cast<T*>(reinterpret_cast<char*>(point)+sizeof(Pointer))
                    && !point->isFree){
                ptr = reinterpret_cast<T*>(ptr);
                point->isFree = true;
                return;
            }
            else{
                point = point->next;
            }
        }
    }
};

#endif // MEMORYPOOL_H
