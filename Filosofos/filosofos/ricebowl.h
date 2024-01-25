#ifndef RICEBOWL_H
#define RICEBOWL_H

#include <QSemaphore>

class RiceBowl {
public:
    RiceBowl();

    void takeRice(int philosopherId);

private:
    QSemaphore riceSemaphore;
};

#endif // RICEBOWL_H
