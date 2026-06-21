#pragma once
template <typename T>
class Identifiable
{
private:
    const int _id;

    static int generateId();
public:
    int getId() const;
protected:
    Identifiable() : _id(generateId()) {}
};

template <typename T>
int Identifiable<T>::generateId() {
    static int nextId = 1;
    return nextId++;
}

template <typename T>
int Identifiable<T>::getId() const {
    return _id;
}