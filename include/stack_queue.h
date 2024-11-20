#include <iostream>

using namespace std;

template <typename T>
class Vector {
protected:
    T* pMem;
    size_t sz;
    size_t capacity;
public:
    Vector(size_t _capacity = 0) : sz(0), capacity(_capacity) {
        if (_capacity < 0)
            throw logic_error("you can't create a vector of negative length");
        if (_capacity == 0)
            capacity = 2;
        pMem = new T[capacity];
        if (pMem == nullptr)
            throw bad_alloc();
    }
    // конструктор копирования не нужен, так как сложно представить случаи, в которых необходимо копировать стэки
    ~Vector() {
        delete[] pMem;
        pMem = nullptr;
    }
    size_t size() noexcept {
        return sz;
    }
    size_t cap() noexcept {
        return capacity;
    }
    bool IsFull() noexcept {
        return sz == capacity;
    }
    bool IsEmpty() noexcept {
        return sz == 0;
    }
    void MemoryAlloc() {
        T* temp = new T[sz * 2];
        if (temp == nullptr)
            throw bad_alloc();
        copy(pMem, pMem + sz, temp);
        delete[] pMem;
        pMem = temp;
        capacity *= 2;
    }
    T& operator[](int i) {
        if (i < 0 || i >= sz)
            throw out_of_range("");
        return pMem[i];
    }
    void push_front (T elem) {
        if (IsFull())
            MemoryAlloc();
        for (int i = 0; i < sz; i++)
            pMem[i + 1] = pMem[i];
        pMem[0] = elem;
        sz++;
    }
    void push_back (T elem) {
        if (IsFull())
            MemoryAlloc();
        pMem[sz++] = elem;
    }
    T& back() {
        if (IsEmpty())
            throw logic_error("Vector is empty");
        return pMem[sz - 1];
    }
    virtual T front() {
        if (IsEmpty())
            throw logic_error("Vector is empty");
        return pMem[0];
    }
    void pop_back() {
        if (IsEmpty())
            throw logic_error("Vector is empty");
        sz--;
    }
    void pop_front() {
        if (IsEmpty())
            throw logic_error("Vector is empty");
        sz--;
        for (int i = 0; i < sz; i++)
            pMem[i] = pMem[i + 1];
    }
    void erase(int index) {
        if (IsEmpty())
            throw logic_error("Vector is empty");
        for (int i = index + 1; i < sz; i++)
            pMem[i] = pMem[i - 1];
        sz--;
    }
};

template <typename T>
class Stack : public Vector<T> {
    T front() override {
        return T();
    }
    void insert(T elem, int index) {};
    using Vector<T>::push_back;
    using Vector<T>::push_front;
    using Vector<T>::back;
    using Vector<T>::pop_back;
    using Vector<T>::pop_front;
    using Vector<T>::erase;
public:
    Stack(size_t n = 10) : Vector<T>(n) {};
    void push(T elem) {
        this->push_back(elem);
    }
    void pop() {
        this->pop_back();
    }
    T& top() {
        return this->back();
    }
};

template <typename T>
class Queue : public Vector<T> {
    using Vector<T>::sz;
    using Vector<T>::push_back;
    using Vector<T>::push_front;
    using Vector<T>::back;
    using Vector<T>::pop_back;
    using Vector<T>::pop_front;
    using Vector<T>::erase;
    size_t front;
    size_t bck;
public:
    Queue(size_t _capacity = 10) : Vector<T>(_capacity), front(0), bck(0) {}
    void push(T elem) noexcept {
        this->push_back(elem);
        if(bck == this->cap())
            bck = 0;
        else bck++;
    }
    void pop() {
        if (this->IsEmpty())
            throw logic_error("Queue is empty");
        if (front == this->cap())
            front = 0;
        else front++;
        sz--;
    }
    T& GetFront() {
        return this->pMem[front];
    }
    T& GetBack() {
        if (bck == 0)
            return this->pMem[this->cap() - 1];
        return this->pMem[bck - 1];
    }
};

template <typename T>
class QueueSt{
    Stack<T> st1;
    Stack<T> st2;
    size_t sz;
    size_t capacity;
    void push_back(T elem) noexcept {
        sz++;
        st1.push(elem);
    }
    void pop_front() {
        if (this->IsEmpty())
            throw logic_error("Queue is empty");
        sz--;
        T temp = T();
        if (!st2.IsEmpty())
            st2.pop();
        else {
            while (!st1.IsEmpty()) {
                temp = st1.top();
                st2.push(temp);
                st1.pop();
            }
            st2.pop();
        }
    }
public:
    QueueSt(size_t _capacity = 10) : st1(_capacity), st2(_capacity), sz(0), capacity(_capacity) {}
    bool IsEmpty() noexcept {
        return (st1.IsEmpty() && st2.IsEmpty());
    }
    size_t size() noexcept {
        return sz;
    }
    T& front() {
        if (IsEmpty())
            throw logic_error("Queue is empty");
        if (!st2.IsEmpty())
            return st2.top();
        T temp;
        while (!st1.IsEmpty()) {
            temp = st1.top();
            st2.push(temp);
            st1.pop();
        }
        return st2.top();
    }
    T& GetF() {
        return front();
    }
    void IncQueue(T elem) noexcept {
        this->push_back(elem);
    }
    void DeQueue() {
        pop_front();
    }
};



