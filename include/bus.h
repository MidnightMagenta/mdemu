#ifndef BUS_H
#define BUS_H

#include <memory>
#include <string_view>
#include <types.h>
#include <vector>

class BusDevice {
public:
    BusDevice() = delete;
    BusDevice(std::string_view devID)
        : m_devID(devID) {}
    virtual ~BusDevice() {}

    const std::string_view id() const {
        return m_devID;
    }
    virtual byte read(u16 addr)          = 0;
    virtual void write(u16 addr, byte v) = 0;
    virtual u16  size() const            = 0;

private:
    const std::string_view m_devID;
};

class cpu_Bus {
public:
    cpu_Bus() {}
    ~cpu_Bus() {}

    void connect(u16 base, std::unique_ptr<BusDevice> dev);
    void disconnect(u16 base);

    void dump_map() const;

    void lock() {
        m_locked = true;
    }

    byte read(u16 addr);
    void write(u16 addr, byte v);

private:
    struct BusMapping {
        // [base, base + size)
        u16                        base;
        u16                        size;
        std::unique_ptr<BusDevice> dev;
    };

private:
    bool                    m_locked   = false;
    byte                    m_open_bus = 0x00;
    std::vector<BusMapping> m_devices;
};

#endif
