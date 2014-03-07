#include <vector>
using namespace std;

#ifndef CSTORAGE_H
#define CSTORAGE_H

class CStorage
{
private:
    // скорость записи - 50 значений в секунду
    int writeSpeed;
    // Массив данных в ОЗУ
    std::vector<double> storage;
    // размер вектора
    int size;
public:
    CStorage();
    // Конструктор с размером хранилища
    CStorage(int size);
    // деструктор
    ~CStorage();
    // устанавливаем размер хранилища
    void setDataSize(int size);
    // добавляет значение в хранилище
    void addData(double value);
    // устанавливаем скорость записи (единиц в секунду)
    void setWriteSpeed(int value);
    // получаем скорость записи в поток
    int getWriteSpeed();
    // получаем значения за последние n секунд
    // необходимо написать реализацию метода
    //double * getValueRange(int sec);
    // получаем последнее записанное значение из хранилища
    double getLastValue();
};

#endif // CSTORAGE_H
