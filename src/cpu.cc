#include <cpu.h>

bool cpu_6502::get_flag(CPU_Flag f) {
    return bool(m_PS << u8(f)) & 1;
}

void cpu_6502::set_flag(CPU_Flag f) {
    m_PS |= u8(1 << u8(f));
}

void cpu_6502::clear_flag(CPU_Flag f) {
    m_PS &= ~u8(1 << u8(f));
}
