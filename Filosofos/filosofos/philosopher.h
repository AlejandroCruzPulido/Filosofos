#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <QThread>
#include <QSemaphore>

class Philosopher : public QThread {
public:
    Philosopher(int numPhilosophers, QSemaphore& philosopherSemaphore, QSemaphore& riceBowlSemaphore, int maxCycles, QSemaphore& finishedSemaphore);
    void init(int philosopherId);
    ~Philosopher();
    void run() override;

private:
    int id;
    int numPhilosophers;
    int maxCycles;
    QSemaphore& philosopherSemaphore;
    QSemaphore& riceBowlSemaphore;
    QSemaphore& finishedSemaphore;

    void think();
    void eat();
};

#endif // PHILOSOPHER_H
