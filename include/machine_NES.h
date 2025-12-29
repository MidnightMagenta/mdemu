#ifndef MACHINE_C64_H
#define MACHINE_C64_H

#include <cpu.h>
#include <machine.h>
#include <memory.h>

class Machine_NES : public Machine {
public:
    Machine_NES()
        : m_cpu(m_memory),
          m_memory(64 * units::kib) {};
    ~Machine_NES() {};

    void run() override;

private:
    cpu_6502 m_cpu;
    Memory   m_memory;
};

#endif
