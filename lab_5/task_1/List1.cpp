#include <iostream>
#include <initializer_list>

template <typename T>
class AbstractDeque {
public:

    virtual int  GetSize() const = 0;  // �������� ������ ����

    // ������ ��� ����������, �������� � ��������� ���������
    virtual bool PushFront(const T& element) = 0;  // �������� ������� � ������ ����
    virtual bool PopFront(T& element) = 0;         // ������� ������� �� ������ ����
    virtual bool PushBack(const T& element) = 0;   // �������� ������� � ����� ����
    virtual bool PopBack(T& element) = 0;          // ������� ������� �� ����� ����
    virtual bool PeekFront(T& element) = 0;        // ���������� ������� � ������ ����, �� ������ ���
    virtual bool PeekBack(T& element) = 0;         // ���������� ������� � ����� ����, �� ������ ���
};

// ����� ���� ��� ����������������� ������
template <typename T>
class Node {
public:
    T data;      // ������ ����
    Node* next;  // ��������� �� ��������� ����

    // ����������� ����
    Node(const T& value) : data(value), next(nullptr) {}
};

// ����� ���� �� ������ ����������������� ������
template <typename T>
class DequeBasedOnUnidirectionalLinkedList : public AbstractDeque<T> {
public:
    // �������� ��� ����
    class Iterator {
    public:
        Iterator(Node<T>* ptr) : current(ptr) {}

        // ���������� ��������� ���������� (++i)
        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        // ���������� ��������� ������������� (*i)
        T& operator*() const {
            return current->data;
        }

        // ���������� ��������� ����������� (i != other)
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

    private:
        Node<T>* current;  // ��������� �� ������� ����
    };

    // ������������ � ����������
    DequeBasedOnUnidirectionalLinkedList();
    ~DequeBasedOnUnidirectionalLinkedList();

    // ����� ����������� ��������������
    explicit DequeBasedOnUnidirectionalLinkedList(unsigned size);

    // ����������� �����������
    DequeBasedOnUnidirectionalLinkedList(const DequeBasedOnUnidirectionalLinkedList& other);

    // ����������� �����������
    DequeBasedOnUnidirectionalLinkedList(DequeBasedOnUnidirectionalLinkedList&& other);

    // ����������� � �������������� ������ �������������
    DequeBasedOnUnidirectionalLinkedList(std::initializer_list<T> list);

    // �������-�����
    Iterator begin();          // �������� �������� ������ ����
    const Iterator begin() const;
    Iterator end();            // �������� �������� ����� ����
    const Iterator end() const;

    // ������������� ��������
    const T& operator[](int index) const;  // �������� ������� �� ������� (������ ������ ��� ������)
    T& operator[](int index);              // �������� ������� �� ������� (������ ��� ������)
    DequeBasedOnUnidirectionalLinkedList& operator=(const DequeBasedOnUnidirectionalLinkedList& other);  // �������� ������������ ��� �����������
    DequeBasedOnUnidirectionalLinkedList& operator=(DequeBasedOnUnidirectionalLinkedList&& other);       // �������� ������������ ��� �����������
    DequeBasedOnUnidirectionalLinkedList& operator=(std::initializer_list<T> ilist);                       // �������� ������������ ��� ������ �������������

    // ���������� �������-����� ��� ��������� ������� ����
    int GetSize() const final {
        return count;
    }

    // ���������� ������ ��� ���������� �������� � ������ ����
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

    // ���������� ������ ��� ���������� �������� � ����� ����
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

    // ���������� ������ ��� �������� �������� �� ������ ����
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

    // ���������� ������ ��� �������� �������� �� ����� ����
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

    // ���������� ������ ��� ��������� �������� � ������ ����, �� ������ ���
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

    // ���������� ������ ��� ��������� �������� � ����� ����, �� ������ ���
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
    Node<T>* head;     // ��������� �� ������ ����
    Node<T>* tail;     // ��������� �� ����� ����
    unsigned count;    // ������� ���������� ��������� � ����
};

// ���������� ������������ �� ���������
template <typename T>
DequeBasedOnUnidirectionalLinkedList<T>::DequeBasedOnUnidirectionalLinkedList() : head(nullptr), tail(nullptr), count(0) {}

// ���������� �����������
template <typename T>
DequeBasedOnUnidirectionalLinkedList<T>::~DequeBasedOnUnidirectionalLinkedList() {
    while (head) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
}

// ����������� � ��������� �������
template <typename T>
DequeBasedOnUnidirectionalLinkedList<T>::DequeBasedOnUnidirectionalLinkedList(unsigned size)
    : count(size) {
    if (size > 0) {
        head = new Node<T>(0);  // ������� ������ ����
        tail = head;
        for (unsigned i = 1; i < size; ++i) {
            tail->next = new Node<T>(i);  // ������� ����� ���� � ��������� ��� � ����������
            tail = tail->next;  // ���������� ��������� �� ����� ������
        }
    }
    else {
        // ���� ������ ����� 0, ��� �������� ������
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


// ���������� ���������� ��� ������ � ����� ����
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


// ���������� ������������� �������� ���������� ��� ������ ��������
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

// ���������� ������������� �������� ���������� ��� ������ ��������
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

// ���������� ��������� ������������ ��� ����������� ����
template <typename T>
DequeBasedOnUnidirectionalLinkedList<T>& DequeBasedOnUnidirectionalLinkedList<T>::operator=(const DequeBasedOnUnidirectionalLinkedList& other) {
    if (this != &other) {
        // ������� ������� ���������
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }

        // �������� �������� �� other
        Node<T>* temp = other.head;
        while (temp) {
            PushBack(temp->data);
            temp = temp->next;
        }
    }
    return *this;
}

// ���������� ��������� ������������ ��� ����������� ����
template <typename T>
DequeBasedOnUnidirectionalLinkedList<T>& DequeBasedOnUnidirectionalLinkedList<T>::operator=(DequeBasedOnUnidirectionalLinkedList&& other) {
    if (this != &other) {
        // ������� ������� ���������
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }

        // ���������� �������� �� other
        head = other.head;
        tail = other.tail;
        count = other.count;

        // �������� other
        other.head = other.tail = nullptr;
        other.count = 0;
    }
    return *this;
}

// ���������� ��������� ������������ ��� ������ �������������
template <typename T>
DequeBasedOnUnidirectionalLinkedList<T>& DequeBasedOnUnidirectionalLinkedList<T>::operator=(std::initializer_list<T> ilist) {
    // ������� ������� ���������
    while (head) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }

    // ��������� �������� �� ilist
    for (const auto& element : ilist) {
        PushBack(element);
    }

    return *this;
}

int main() {

    DequeBasedOnUnidirectionalLinkedList<int> deque1;                  // ����������� �� ���������
    DequeBasedOnUnidirectionalLinkedList<int> deque2(3);                  // ����� ����������� ��������������
    DequeBasedOnUnidirectionalLinkedList<int> deque3 = { 1, 2, 7, 4, 5 }; // ����������� � �������������� ������ �������������

    deque1 = deque3;  // �������� ������������ ��� �����������

    // ������������ ������� Push, Pop, Peek
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

    // ����� �������� ��������
    std::cout << "Size of deque1: " << deque1.GetSize() << std::endl;
    std::cout << "Size of deque2: " << deque2.GetSize() << std::endl;
    std::cout << "Size of deque3: " << deque3.GetSize() << std::endl;

    // ������������� ����������
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
