#include "ricebowl.h"
#include <QDebug>
#include <QThread>

RiceBowl::RiceBowl() {
    riceSemaphore.release();
}

void RiceBowl::takeRice(int philosopherId) {
    qDebug() << "Filósofo " << philosopherId << " está tomando arroz del cuenco.";
    riceSemaphore.acquire();
    QThread::sleep(1);
}
