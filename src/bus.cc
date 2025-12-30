#include <algorithm>
#include <bus.h>
#include <cassert>
#include <iostream>
#include <stdexcept>

void cpu_Bus::connect(u16 base, std::unique_ptr<BusDevice> dev) {
    assert(!m_locked);
    u16 size = dev->size();
    assert(base + size <= MAX_ADDR + 1);

    for (auto &m : m_devices) {
        if (!(base + size <= m.base || base >= m.base + m.size)) {
            throw std::logic_error("Bus address overlap");
        }
    }

    m_devices.push_back({base, size, std::move(dev)});
    std::sort(m_devices.begin(), m_devices.end(), [](auto &a, auto &b) { return a.base < b.base; });
}

void cpu_Bus::disconnect(u16 base) {
    assert(!m_locked);
    auto it = std::find_if(m_devices.begin(), m_devices.end(), [&](const BusMapping &m) {
        return m.base == base;
    });

    if (it == m_devices.end()) throw std::logic_error("No device mapped at base");

    m_devices.erase(it);
    std::sort(m_devices.begin(), m_devices.end(), [](auto &a, auto &b) { return a.base < b.base; });
}

void cpu_Bus::dump_map() const {
    std::cout << "CPU bus device mapping:\n";
    for (const auto &m : m_devices) {
        std::cout << "dev: " << m.dev->id() << '\n';
        std::cout << "\tbase: 0x" << std::hex << m.base << '\n';
        std::cout << "\tend:  0x" << m.base + m.size - 1 << std::dec << '\n';
    }
}

byte cpu_Bus::read(u16 addr) {
    assert(m_locked);
    for (auto &m : m_devices) {
        if (addr < m.base) { break; }
        if (addr >= m.base && addr < m.base + m.size) {
            byte v     = m.dev->read(addr - m.base);
            m_open_bus = v;
            return v;
        }
    }
    return m_open_bus;
}

void cpu_Bus::write(u16 addr, byte v) {
    assert(m_locked);
    for (auto &m : m_devices) {
        if (addr < m.base) { break; }
        if (addr >= m.base && addr < m.base + m.size) {
            m_open_bus = v;
            m.dev->write(addr - m.base, v);
            return;
        }
    }
}
