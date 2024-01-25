#include "philosopher.h"
#include <QMutex>
#include <QDebug>
#include <QThread>

extern QSemaphore chopsticks[];
extern QMutex chopstickMutex[];

Philosopher::Philosopher(int numPhilosophers, QSemaphore& philosopherSemaphore, QSemaphore& riceBowlSemaphore, int maxCycles, QSemaphore& finishedSemaphore)
    : numPhilosophers(numPhilosophers), philosopherSemaphore(philosopherSemaphore), riceBowlSemaphore(riceBowlSemaphore), maxCycles(maxCycles), finishedSemaphore(finishedSemaphore) {}

void Philosopher::init(int philosopherId) {
    id = philosopherId;
}

Philosopher::~Philosopher() {}

void Philosopher::run() {
    for (int cycle = 0; cycle < maxCycles; ++cycle) {
        think();
        eat();
    }

    finishedSemaphore.release();
    this->exit();
}

void Philosopher::think() {
    qDebug() << "Filósofo " << id << " está pensando.";
    QThread::sleep(1);
}

void Philosopher::eat() {
    qDebug() << "Filósofo " << id << " tiene hambre y está tratando de tomar los palillos.";

    chopsticks[id].acquire();
    chopsticks[(id + 1) % numPhilosophers].acquire();

    qDebug() << "Filósofo " << id << " ha tomado los palillos y está listo para comer.";

    riceBowlSemaphore.acquire();
    qDebug() << "Filósofo " << id << " está tomando arroz del cuenco.";
    QThread::sleep(1);
    riceBowlSemaphore.release();

    qDebug() << "Filósofo " << id << " está comiendo.";
    QThread::sleep(2);

    chopsticks[id].release();
    chopsticks[(id + 1) % numPhilosophers].release();

    qDebug() << "Filósofo " << id << " ha terminado de comer y ha liberado los palillos.";
}
