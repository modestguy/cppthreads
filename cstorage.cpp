#include "cstorage.h"

// Конструктор
CStorage::CStorage() {
    //
}

// Конструктор
CStorage::CStorage(int size)
{
    this->size = size;
}

// Деструктор
CStorage::~CStorage() {
    //
}

// Добавляем значение
// Необходимо доработать хранилище, если выходит за размер определяемый ОЗУ, пишем в файл
// Сейчас если количество элементов больше - затираем первый и добавляем в конец новое значение
void CStorage::addData(double value) {
    if (this->storage.size() <= this->size) {
        this->storage.push_back(value);
    } else {
        this->storage.erase(this->storage.begin());
    }
}

// Размер данных(не в байтах!) в ОЗУ
void CStorage::setDataSize(int size){
    this->size = size;
}

// Устанавливаем скорость записи в хранилище
void CStorage::setWriteSpeed(int value) {
    this->writeSpeed = value;
}

// Получаем скорость записи
int CStorage::getWriteSpeed() {
    return this->writeSpeed;
}

// Получаем последнее записанное значение из хранилища
double CStorage::getLastValue() {
    return this->storage.back();
}


