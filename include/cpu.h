#ifndef CPU_H
#define CPU_H

#include <memory.h>
#include <types.h>

class cpu_6502 {
public:
    cpu_6502() = delete;
    cpu_6502(Memory &memory)
        : m_memory(memory) {}
    ~cpu_6502() {}

private:
    enum class CPU_Flag : u8 {
        NEGATIVE          = 7,
        OVERFLOW          = 6,
        BREAK             = 4,
        DECIMAL           = 3,
        INTERRUPT_DISABLE = 2,
        ZERO              = 1,
        CARRY             = 0,
    };

private:
    bool get_flag(CPU_Flag f);
    void set_flag(CPU_Flag f);
    void clear_flag(CPU_Flag f);

private:
    u16 m_PC;
    u8  m_SP;
    u8  m_PS;
    u8  m_A;
    u8  m_X;
    u8  m_Y;

    Memory &m_memory;
};

#endif
