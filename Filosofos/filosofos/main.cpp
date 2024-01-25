#include <QCoreApplication>
#include "philosopher.h"
#include "ricebowl.h"
#include <vector>
#include <QSemaphore>

const int numPhilosophers = 5;
QSemaphore chopsticks[numPhilosophers];
RiceBowl riceBowl;
QSemaphore philosopherSemaphore(0);  // Inicializado en 0 para esperar a que todos terminen
QSemaphore riceBowlSemaphore(1);  // Inicializado en 1 para controlar el acceso al cuenco de arroz
QSemaphore finishedSemaphore(0);   // Inicializado en 0 para contar cuántos filósofos han terminado
const int maxCycles = 1;  // Número de veces que cada filósofo pensará y comerá

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    for (int i = 0; i < numPhilosophers; ++i) {
        chopsticks[i].release();
    }

    std::vector<Philosopher*> philosophers;
    philosophers.reserve(numPhilosophers);

    for (int i = 0; i < numPhilosophers; ++i) {
        philosophers.push_back(new Philosopher(numPhilosophers, philosopherSemaphore, riceBowlSemaphore, maxCycles, finishedSemaphore));
        philosophers[i]->init(i);
        philosophers[i]->start();
    }

    // Esperar a que todos los filósofos terminen
    philosopherSemaphore.acquire(numPhilosophers);

    // Esperar a que todos los filósofos hayan terminado antes de finalizar
    finishedSemaphore.acquire(numPhilosophers);

    // Terminar y esperar a que los filósofos terminen
    for (auto philosopher : philosophers) {
        philosopher->wait();
        delete philosopher;
    }

    return a.exec();
}
