#ifndef MACHINE_DEBUG_H
#define MACHINE_DEBUG_H

#include <bus.h>
#include <cassert>
#include <cpu.h>
#include <filesystem>
#include <iostream>
#include <machine.h>

namespace mach_dbg {
class RAMDevice : public BusDevice {
public:
    RAMDevice()
        : BusDevice("ram") {}
    ~RAMDevice() {}

    virtual byte read(u16 addr) override {
        assert(addr < RAM_SIZE);
        return m_data[addr];
    }
    virtual void write(u16 addr, byte v) override {
        assert(addr < RAM_SIZE);
        m_data[addr] = v;
    }
    virtual u16 size() const override {
        return RAM_SIZE;
    }

private:
    static constexpr u16 RAM_SIZE = 32 * units::kib;

private:
    byte m_data[RAM_SIZE];
};

class ROMDevice : public BusDevice {
public:
    ROMDevice(const std::filesystem::path &romImage);
    ~ROMDevice() {}

    virtual byte read(u16 addr) override {
        assert(addr < ROM_SIZE);
        return m_data[addr];
    }
    virtual void write(u16 addr, byte v) override {
        std::cerr << "ROM write at address " << addr << '\n';
        return;
    }
    virtual u16 size() const override {
        return ROM_SIZE;
    }

private:
    static constexpr u16 ROM_SIZE = 32 * units::kib;

private:
    byte m_data[ROM_SIZE];
};

class Machine_Debug : public Machine {
public:
    Machine_Debug(const std::filesystem::path &rom)
        : m_cpu(m_bus) {
        m_bus.connect(RAM_OFFSET, std::make_unique<RAMDevice>());
        m_bus.connect(ROM_OFFSET, std::make_unique<ROMDevice>(rom));
        m_bus.lock();
    }
    ~Machine_Debug() {}

    void run() override;

private:
    static constexpr u16 RAM_OFFSET = 0x0000;
    static constexpr u16 ROM_OFFSET = 0x8000;

private:
    cpu_6502 m_cpu;
    cpu_Bus  m_bus;
};
}// namespace mach_dbg

#endif
