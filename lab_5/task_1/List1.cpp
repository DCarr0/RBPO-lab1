#include <iostream>
#include <initializer_list>

template <typename T>
class AbstractDeque {
public:

    virtual int  GetSize() const = 0;  // Получить размер дека

    // Методы для добавления, удаления и просмотра элементов
    virtual bool PushFront(const T& element) = 0;  // Добавить элемент в начало дека
    virtual bool PopFront(T& element) = 0;         // Удалить элемент из начала дека
    virtual bool PushBack(const T& element) = 0;   // Добавить элемент в конец дека
    virtual bool PopBack(T& element) = 0;          // Удалить элемент из конца дека
    virtual bool PeekFront(T& element) = 0;        // Посмотреть элемент в начале дека, не удаляя его
    virtual bool PeekBack(T& element) = 0;         // Посмотреть элемент в конце дека, не удаляя его
};

// Класс узла для однонаправленного списка
template <typename T>
class Node {
public:
    T data;      // Данные узла
    Node* next;  // Указатель на следующий узел

    // Конструктор узла
    Node(const T& value) : data(value), next(nullptr) {}
};

// Класс дека на основе однонаправленного списка
template <typename T>
class DequeBasedOnUnidirectionalLinkedList : public AbstractDeque<T> {
public:
    // Итератор для дека
    class Iterator {
    public:
        Iterator(Node<T>* ptr) : current(ptr) {}

        // Перегрузка оператора инкремента (++i)
        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        // Перегрузка оператора разыменования (*i)
        T& operator*() const {
            return current->data;
        }

        // Перегрузка оператора неравенства (i != other)
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

    private:
        Node<T>* current;  // Указатель на текущий узел
    };

    // Конструкторы и деструктор
    DequeBasedOnUnidirectionalLinkedList();
    ~DequeBasedOnUnidirectionalLinkedList();

    // Явный конструктор преобразования
    explicit DequeBasedOnUnidirectionalLinkedList(unsigned size);

    // Конструктор копирования
    DequeBasedOnUnidirectionalLinkedList(const DequeBasedOnUnidirectionalLinkedList& other);

    // Конструктор перемещения
    DequeBasedOnUnidirectionalLinkedList(DequeBasedOnUnidirectionalLinkedList&& other);

    // Конструктор с использованием списка инициализации
    DequeBasedOnUnidirectionalLinkedList(std::initializer_list<T> list);

    // Функции-члены
    Iterator begin();          // Получить итератор начала дека
    const Iterator begin() const;
    Iterator end();            // Получить итератор конца дека
    const Iterator end() const;

    // Перегруженные операции
    const T& operator[](int index) const;  // Получить элемент по индексу (доступ только для чтения)
    T& operator[](int index);              // Получить элемент по индексу (доступ для записи)
    DequeBasedOnUnidirectionalLinkedList& operator=(const DequeBasedOnUnidirectionalLinkedList& other);  // Оператор присваивания для копирования
    DequeBasedOnUnidirectionalLinkedList& operator=(DequeBasedOnUnidirectionalLinkedList&& other);       // Оператор присваивания для перемещения
    DequeBasedOnUnidirectionalLinkedList& operator=(std::initializer_list<T> ilist);                       // Оператор присваивания для списка инициализации

    // Реализация функции-члена для получения размера дека
    int GetSize() const final {
        return count;
    }

    // Реализация метода для добавления элемента в начало дека
    bool PushFront(const T& element) final {
        Node<T>* newNode = new Node<T>(element);
        if (!head) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }
        count++;
        return true;
    }

    // Реализация метода для добавления элемента в конец дека
    bool PushBack(const T& element) final {
        Node<T>* newNode = new Node<T>(element);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
        return true;
    }

    // Реализация метода для удаления элемента из начала дека
    bool PopFront(T& element) final {
        if (head) {
            element = head->data;
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            count--;
            return true;
        }
        else {
            std::cerr << "Deque is empty, cannot pop from front." << std::endl;
            return false;
        }
    }

    // Реализация метода для удаления элемента из конца дека
    bool PopBack(T& element) final {
        if (tail) {
            element = tail->data;
            if (head == tail) {
                delete tail;
                head = tail = nullptr;
            }
            else {
                Node<T>* temp = head;
                while (temp->next != tail) {
                    temp = temp->next;
                }
                delete tail;
                tail = temp;
                tail->next = nullptr;
            }
            count--;
            return true;
        }
        else {
            std::cerr << "Deque is empty, cannot pop from back." << std::endl;
            return false;
        }
    }

    // Реализация метода для просмотра элемента в начале дека, не удаляя его
    bool PeekFront(T& element) final {
        if (head) {
            element = head->data;
            return true;
        }
        else {
            std::cerr << "Deque is empty, cannot peek from front." << std::endl;
            return false;
        }
    }

    // Реализация метода для просмотра элемента в конце дека, не удаляя его
    bool PeekBack(T& element) final {
        if (tail) {
            element = tail->data;
            return true;
        }
        else {
            std::cerr << "Deque is empty, cannot peek from back." << std::endl;
            return false;
        }
    }

private:
    Node<T>* head;     // Указатель на начало дека
    Node<T>* tail;     // Указатель на конец дека
    unsigned count;    // Текущее количество элементов в деке
};

// Реализация конструктора по умолчанию
template <typename T>
DequeBasedOnUnidirectionalLinkedList<T>::DequeBasedOnUnidirectionalLinkedList() : head(nullptr), tail(nullptr), count(0) {}

// Реализация деструктора
template <typename T>
DequeBasedOnUnidirectionalLinkedList<T>::~DequeBasedOnUnidirectionalLinkedList() {
    while (head) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
}

// Конструктор с указанием размера
template <typename T>
DequeBasedOnUnidirectionalLinkedList<T>::DequeBasedOnUnidirectionalLinkedList(unsigned size)
    : count(size) {
    if (size > 0) {
        head = new Node<T>(0);  // Создаем первый узел
        tail = head;
        for (unsigned i = 1; i < size; ++i) {
            tail->next = new Node<T>(i);  // Создаем новый узел и связываем его с предыдущим
            tail = tail->next;  // Перемещаем указатель на конец списка
        }
    }
    else {
        // Если размер равен 0, дек остается пустым
        head = tail = nullptr;
    }
}


template <typename T>
DequeBasedOnUnidirectionalLinkedList<T>::DequeBasedOnUnidirectionalLinkedList(const DequeBasedOnUnidirectionalLinkedList& other)
{
    Node<T>* temp = other.head;
    while (temp) {
        PushBack(temp->data);
        temp = temp->next;
    }
}

template <typename T>
DequeBasedOnUnidirectionalLinkedList<T>::DequeBasedOnUnidirectionalLinkedList(DequeBasedOnUnidirectionalLinkedList&& other)
{
    head = other.head;
    tail = other.tail;
    count = other.count;

    other.head = other.tail = nullptr;
    other.count = 0;
}

template <typename T>
DequeBasedOnUnidirectionalLinkedList<T>::DequeBasedOnUnidirectionalLinkedList(std::initializer_list<T> ilist)
{
    for (const auto& element : ilist) {
        PushBack(element);
    }
}


// Реализация итераторов для начала и конца дека
template <typename T>
typename DequeBasedOnUnidirectionalLinkedList<T>::Iterator DequeBasedOnUnidirectionalLinkedList<T>::begin() {
    return Iterator(head);
}

template <typename T>
const typename DequeBasedOnUnidirectionalLinkedList<T>::Iterator DequeBasedOnUnidirectionalLinkedList<T>::begin() const {
    return Iterator(head);
}

template <typename T>
typename DequeBasedOnUnidirectionalLinkedList<T>::Iterator DequeBasedOnUnidirectionalLinkedList<T>::end() {
    return Iterator(nullptr);
}

template <typename T>
const typename DequeBasedOnUnidirectionalLinkedList<T>::Iterator DequeBasedOnUnidirectionalLinkedList<T>::end() const {
    return Iterator(nullptr);
}


// Реализация перегруженной операции индексации для чтения элемента
template <typename T>
const T& DequeBasedOnUnidirectionalLinkedList<T>::operator[](int index) const {
    Node<T>* current = head;
    for (int i = 0; i < index; ++i) {
        if (current) {
            current = current->next;
        }
        else {
            std::cerr << "Index out of bounds." << std::endl;
            throw std::out_of_range("Index out of bounds");
        }
    }
    return current->data;
}

// Реализация перегруженной операции индексации для записи элемента
template <typename T>
T& DequeBasedOnUnidirectionalLinkedList<T>::operator[](int index) {
    Node<T>* current = head;
    for (int i = 0; i < index; ++i) {
        if (current) {
            current = current->next;
        }
        else {
            std::cerr << "Index out of bounds." << std::endl;
            throw std::out_of_range("Index out of bounds");
        }
    }
    return current->data;
}

// Реализация оператора присваивания для копирования дека
template <typename T>
DequeBasedOnUnidirectionalLinkedList<T>& DequeBasedOnUnidirectionalLinkedList<T>::operator=(const DequeBasedOnUnidirectionalLinkedList& other) {
    if (this != &other) {
        // Очищаем текущее состояние
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }

        // Копируем элементы из other
        Node<T>* temp = other.head;
        while (temp) {
            PushBack(temp->data);
            temp = temp->next;
        }
    }
    return *this;
}

// Реализация оператора присваивания для перемещения дека
template <typename T>
DequeBasedOnUnidirectionalLinkedList<T>& DequeBasedOnUnidirectionalLinkedList<T>::operator=(DequeBasedOnUnidirectionalLinkedList&& other) {
    if (this != &other) {
        // Очищаем текущее состояние
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }

        // Перемещаем элементы из other
        head = other.head;
        tail = other.tail;
        count = other.count;

        // Обнуляем other
        other.head = other.tail = nullptr;
        other.count = 0;
    }
    return *this;
}

// Реализация оператора присваивания для списка инициализации
template <typename T>
DequeBasedOnUnidirectionalLinkedList<T>& DequeBasedOnUnidirectionalLinkedList<T>::operator=(std::initializer_list<T> ilist) {
    // Очищаем текущее состояние
    while (head) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }

    // Добавляем элементы из ilist
    for (const auto& element : ilist) {
        PushBack(element);
    }

    return *this;
}

int main() {

    DequeBasedOnUnidirectionalLinkedList<int> deque1;                  // Конструктор по умолчанию
    DequeBasedOnUnidirectionalLinkedList<int> deque2(3);                  // Явный конструктор преобразования
    DequeBasedOnUnidirectionalLinkedList<int> deque3 = { 1, 2, 7, 4, 5 }; // Конструктор с использованием списка инициализации

    deque1 = deque3;  // Оператор присваивания для копирования

    // Тестирование методов Push, Pop, Peek
    deque1.PushFront(111);
    deque1.PushBack(34);
    deque1.PushBack(505);

    int poppedElement;
    if (deque1.PopFront(poppedElement))
        std::cout << "Popped element from front: " << poppedElement << std::endl;
    else
        std::cout << "Deque is empty, cannot pop." << std::endl;

    if (deque1.PopBack(poppedElement))
        std::cout << "Popped element from back: " << poppedElement << std::endl;
    else
        std::cout << "Deque is empty, cannot pop." << std::endl;

    int peekedElement;
    if (deque3.PeekFront(peekedElement))
        std::cout << "Peeked element from front: " << peekedElement << std::endl;
    else
        std::cout << "Deque is empty, cannot peek." << std::endl;

    if (deque3.PeekBack(peekedElement))
        std::cout << "Peeked element from back: " << peekedElement << std::endl;
    else
        std::cout << "Deque is empty, cannot peek." << std::endl;

    // Вывод размеров очередей
    std::cout << "Size of deque1: " << deque1.GetSize() << std::endl;
    std::cout << "Size of deque2: " << deque2.GetSize() << std::endl;
    std::cout << "Size of deque3: " << deque3.GetSize() << std::endl;

    // Использование итераторов
    std::cout << "Elements of deque1: ";
    for (auto i = deque1.begin(); i != deque1.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    std::cout << "Elements of deque2: ";
    for (auto i = deque2.begin(); i != deque2.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    std::cout << "Elements of deque3: ";
    for (auto i = deque3.begin(); i != deque3.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    return 0;
}
