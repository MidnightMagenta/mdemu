#include <fstream>
#include <machine_debug.h>

using namespace mach_dbg;

ROMDevice::ROMDevice(const std::filesystem::path &romImage)
    : BusDevice("rom") {
    std::ifstream rom(romImage, std::ios::ate | std::ios::binary);
    if (!rom.is_open()) { throw std::runtime_error("Could not open ROM image"); }
    size_t romSize = rom.tellg();
    if (romSize > ROM_SIZE) {
        rom.close();
        throw std::runtime_error("ROM image too large");
    }
    rom.seekg(0);
    rom.read((char *) m_data, romSize);
}

void Machine_Debug::run() {
    m_bus.dump_map();
    m_cpu.reset();
    m_cpu.tick();
    m_cpu.tick();
    m_cpu.tick();
}
