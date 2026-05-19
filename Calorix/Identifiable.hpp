#pragma once
template <typename T>
class Identifiable
{
private:
    const int _id;

    static int generateId() {
        static int nextId = 1;
        return nextId++;
    }

public:
    int getId() const {
        return _id;
    }

protected:
    Identifiable() : _id(generateId()) {}
};