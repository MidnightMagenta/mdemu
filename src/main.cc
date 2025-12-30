#include <machine_debug.h>

int main() {
    mach_dbg::Machine_Debug mach("tests/mach_dbg/rom.bin");
    mach.run();
    return 0;
}
