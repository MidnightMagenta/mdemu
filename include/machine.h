#ifndef MACHINE_H
#define MACHINE_H

class Machine {
public:
    Machine() {}
    virtual ~Machine() {}

    virtual void run() = 0;
};

#endif
