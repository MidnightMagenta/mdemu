#ifndef MEMORY_H
#define MEMORY_H

#include <cassert>
#include <types.h>
#include <units.h>

class Memory {
public:
    static constexpr u32 MAX_MEM = 64 * units::kib;

public:
    Memory() {
        m_memory = new byte[MAX_MEM];
        m_size   = MAX_MEM;
    }
    Memory(u32 memSize) {
        assert(memSize <= MAX_MEM);
        m_memory = new byte[memSize];
        m_size   = memSize;
    }
    ~Memory() {
        delete[] m_memory;
        m_size = 0;
    }

    byte operator[](u16 addr) const {
        assert(addr < m_size);
        return m_memory[addr];
    }

    byte &operator[](u16 addr) {
        assert(addr < m_size);
        return m_memory[addr];
    }

private:
    byte *m_memory;
    u32   m_size;
};

#endif
