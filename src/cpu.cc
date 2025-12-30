#include <cpu.h>

void cpu_6502::reset() {
    m_state = State::RESET;
}

void cpu_6502::tick() {
    switch (m_state) {
        case State::RESET:
            m_cycles += 6;// TODO: account of these cycles correctly (?)
            m_flags = reset_flags;
            m_SP    = 0x00;
            m_state = State::RESET_FETCH_LO;
            break;
        case State::RESET_FETCH_LO:
            m_tmp_lo = m_bus.read(0xFFFC);
            m_state  = State::RESET_FETCH_HI;
            break;
        case State::RESET_FETCH_HI:
            m_tmp_hi = m_bus.read(0xFFFD);
            m_PC     = (u16(m_tmp_hi) << 8) | m_tmp_lo;
            m_state  = State::FETCH_OPCODE;
            break;
        case State::FETCH_OPCODE:
            m_tmp_opcode = m_bus.read(m_PC);
            m_PC++;
            m_state = process_opcode();
            break;
        default:
            throw std::runtime_error("Invalid state");
    }

    m_cycles++;
}

bool cpu_6502::get_flag(CPU_Flag f) {
    return bool(m_flags << u8(f)) & 1;
}

void cpu_6502::set_flag(CPU_Flag f) {
    m_flags |= u8(1 << u8(f));
}

void cpu_6502::clear_flag(CPU_Flag f) {
    m_flags &= ~u8(1 << u8(f));
}

cpu_6502::State cpu_6502::process_opcode() {}
