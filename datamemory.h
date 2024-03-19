#ifndef DATAMEMORY_H
#define DATAMEMORY_H

#include <unordered_map>
class DataMemory
{
public:
    int size;
    std::unordered_map<int ,int> __memory;
public:
    DataMemory(int size);

    void store(int address, int value);

    int load(int address);

    void resize(int size);
};

#endif // DATAMEMORY_H
