#ifndef CPU_H
#define CPU_H

#include <bus.h>
#include <types.h>

class cpu_6502 {
public:
    cpu_6502() = delete;
    cpu_6502(cpu_Bus &bus)
        : m_bus(bus) {}
    ~cpu_6502() {}

    void reset();
    void tick();

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

    enum class State {
        RESET,
        RESET_FETCH_LO,
        RESET_FETCH_HI,

        // fetches - PC addressed reads
        FETCH_OPCODE,
        FETCH_OPERAND_0,
        FETCH_OPERAND_1,
    };

    static constexpr u16 reset_vector_addr = 0xFFFC;
    static constexpr u8  reset_flags       = 0b00000100;

private:
    bool get_flag(CPU_Flag f);
    void set_flag(CPU_Flag f);
    void clear_flag(CPU_Flag f);

    State process_opcode();

private:
    // architectural registers
    u16      m_PC;
    u8       m_SP;
    u8       m_flags;
    u8       m_A;
    u8       m_X;
    u8       m_Y;
    cpu_Bus &m_bus;

private:
    // virtual state registers
    u8 m_tmp_opcode;
    u8 m_tmp_lo;
    u8 m_tmp_hi;

    u64   m_cycles = 0;
    State m_state;
};

#endif
