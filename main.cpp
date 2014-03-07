#include <iostream>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include "cstorage.h"

using namespace std;

// Функция задержки в микросекундах
// Необходима для имитации получения значения с датчика
void DelayMicrosecondsNoSleep (int delay_us)
{
    long int start_time;
    long int time_difference;
    struct timespec gettime_now;

    clock_gettime(CLOCK_REALTIME, &gettime_now);
    start_time = gettime_now.tv_nsec;
    while (1)
    {
        clock_gettime(CLOCK_REALTIME, &gettime_now);
        time_difference = gettime_now.tv_nsec - start_time;
        if (time_difference < 0)
            time_difference += 1000000000;
        if (time_difference > (delay_us * 1000))
            break;
    }
}

// функция чтения из хранилища во втором потоке
void * readFunction(void * stor) {
    CStorage *storage = (CStorage*) stor;
    cout << "Нажмите ENTER чтобы посмотреть последнее записанное в хранилище значение..." << endl;
    while (true) {
      if (cin.get() == '\n') {
        cout << "Последнее значение в хранилище с датчика: " << storage->getLastValue() << endl;
       }
    }
}

// Функция записи в хранилище
void * writeFunction(void * stor) {
    int ret;
    struct sched_param params;
    // Максимальный приоритет
    params.sched_priority = sched_get_priority_max(SCHED_FIFO);
    // приоритет потока на запись будет максимальный
    ret = pthread_setschedparam(pthread_self(), SCHED_FIFO, &params);
    if (ret != 0) {
        std::cout << "Не получилось установить приоритет для потока" << std::endl;
        return 0;
    }

    CStorage *storage = (CStorage*) stor;
    // будем писать 50 значений в секунду
    storage->setWriteSpeed(50);
    // главный цикл для генерации значений, записываемых в поток
    while (true) {
        DelayMicrosecondsNoSleep(1000000000 / storage->getWriteSpeed());
        double f = (double)rand() / RAND_MAX;
        // Записываем случайное значение в хранилище
        storage->addData(f);
    }
}

int main()
{
    int  ret, iret1, iret2;
    // инициализируем случайные числа
    srandom(time(NULL));

    // Создаём хранилище на 10 элементов double
    CStorage storage(1000);

    // 2 потока, один на запись, второй на чтение
     pthread_t readThread, writeThread;

     // создаём поток на запись в хранилище
     iret1 = pthread_create( &writeThread, NULL, writeFunction, (void*) &storage);
     // создаём поток на чтение из хранилища
     iret2 = pthread_create( &readThread, NULL, readFunction, (void*) &storage);

     pthread_join( writeThread, NULL);
     pthread_join( readThread, NULL);
    return 0;
}

