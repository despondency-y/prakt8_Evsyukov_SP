// prakt8_Evsyukov_SP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>


using namespace std;

struct Route {
    int number;
    char destination[50];
    int travelTime;
};

struct Node {
    Route data;
    Node* next;
    Node* prev;
};

struct DoublyLinkedList {
    Node* head;
    Node* tail;

    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void push_front(Route r) {
        Node* newNode = new Node;
        newNode->data = r;
        newNode->prev = nullptr;
        newNode->next = head;

        if (head != nullptr)
            head->prev = newNode;
        else
            tail = newNode;

        head = newNode;
    }

    void push_back(Route r) {
        Node* newNode = new Node;
        newNode->data = r;
        newNode->next = nullptr;
        newNode->prev = tail;

        if (tail != nullptr)
            tail->next = newNode;
        else
            head = newNode;

        tail = newNode;
    }

    void pop_front() {
        if (head == nullptr) {
            cout << "Список пуст.\n";
            return;
        }

        Node* temp = head;
        head = head->next;

        if (head != nullptr)
            head->prev = nullptr;
        else
            tail = nullptr;

        delete temp;
    }

    void pop_back() {
        if (tail == nullptr) {
            cout << "Список пуст.\n";
            return;
        }

        Node* temp = tail;
        tail = tail->prev;

        if (tail != nullptr)
            tail->next = nullptr;
        else
            head = nullptr;

        delete temp;
    }

    void display_forward() {
        if (head == nullptr) {
            cout << "Список пуст.\n";
            return;
        }

        Node* current = head;
        while (current != nullptr) {
            cout << "Номер: " << current->data.number << ", Направление: " << current->data.destination << ", Время: " << current->data.travelTime << " мин\n";
            current = current->next;
        }
    }

    void display_backward() {
        if (tail == nullptr) {
            cout << "Список пуст.\n";
            return;
        }

        Node* current = tail;
        while (current != nullptr) {
            cout << "Номер: " << current->data.number << ", Направление: " << current->data.destination << ", Время: " << current->data.travelTime << " мин\n";
            current = current->prev;
        }
    }

    Node* find_by_number(int number) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data.number == number)
                return current;
            current = current->next;
        }
        return nullptr;
    }

    void remove_node(Node* node) {
        if (node == nullptr) return;

        if (node->prev != nullptr)
            node->prev->next = node->next;
        else
            head = node->next;

        if (node->next != nullptr)
            node->next->prev = node->prev;
        else
            tail = node->prev;

        delete node;
    }

    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
    }

    // инд1
    void find_min_travel_time() {
        if (head == nullptr) {
            cout << "Список пуст.\n";
            return;
        }

        Node* minNode = head;
        Node* current = head->next;

        while (current != nullptr) {
            if (current->data.travelTime < minNode->data.travelTime)
                minNode = current;
            current = current->next;
        }

        cout << "Маршрут с минимальным временем поездки:\n";
        cout << "Номер: " << minNode->data.number << ", Направление: " << minNode->data.destination << ", Время: " << minNode->data.travelTime << " мин\n";
    }

    // инд 2
    void remove_by_travel_time(int maxTime) {
        Node* current = head;
        bool removed = false;

        while (current != nullptr) {
            Node* nextNode = current->next;

            if (current->data.travelTime > maxTime) {
                remove_node(current);
                removed = true;
            }

            current = nextNode;
        }

        if (removed)
            cout << "Маршруты с временем поездки больше " << maxTime << " удалены.\n";
        else
            cout << "Подходящих маршрутов для удаления не найдено.\n";
    }

    // инд 3
    void insert_after_number(int number, Route newRoute) {
        Node* target = find_by_number(number);

        if (target == nullptr) {
            cout << "Маршрут с номером " << number << " не найден.\n";
            return;
        }

        Node* newNode = new Node;
        newNode->data = newRoute;
        newNode->next = target->next;
        newNode->prev = target;

        if (target->next != nullptr)
            target->next->prev = newNode;
        else
            tail = newNode;

        target->next = newNode;

        cout << "Новый маршрут вставлен после маршрута с номером " << number << ".\n";
    }
};

Route inputRoute() {
    Route r;
    cout << "Номер маршрута: ";
    cin >> r.number;

    cin.ignore();

    cout << "Направление: ";
    cin.getline(r.destination, 50);

    cout << "Время поездки (мин): ";
    cin >> r.travelTime;

    return r;
}




int main()
{
    setlocale(LC_ALL, "Russian");

    DoublyLinkedList list;

    int choice = -1;
    while (choice != 11) {
        
        cout << "\n\tТекстовое меню" << endl;

        cout << "1. Добавить элемент в начало" << endl;
        cout << "2. Добавить элемент в конец" << endl;
        cout << "3. Удалить первый элемент" << endl;
        cout << "4. Удалить последний элемент" << endl;
        cout << "5. Вывести список" << endl;
        cout << "6. Вывести список в обратном порядке" << endl;
        cout << "7. Найти элемент" << endl;
        cout << "8. Выполнить инд. операцию 1 (маршрут с мин временем)" << endl;
        cout << "9. Выполнить инд. операцию 2 (удалить маршруты > заданного времени)" << endl;
        cout << "10. Выполнить инд. операцию 3 (вставить маршрут после другого)" << endl;
        cout << "11. Выход" << endl;

        cout << "Выберите функцию: ";
        cin >> choice;

        if (choice > 0 && choice < 12) {
            if (choice == 1) {
                Route r = inputRoute();
                list.push_front(r);
            }
            else if (choice == 2) {
                Route r = inputRoute();
                list.push_back(r);
            }
            else if (choice == 3) {
                list.pop_front();
            }
            else if (choice == 4) {
                list.pop_back();
            }
            else if (choice == 5) {
                list.display_forward();
            }
            else if (choice == 6) {
                list.display_backward();
            }
            else if (choice == 7) {
                int number;
                cout << "Номер маршрута для поиска: ";
                cin >> number;
                Node* found = list.find_by_number(number);
                if (found != nullptr) {
                    cout << "Найденный маршрут:\n";
                    cout << "Номер: " << found->data.number << "\nНаправление: " << found->data.destination
                        << "\nВремя: " << found->data.travelTime << " мин." << endl;
                    char answer;
                    cout << "Удалить маршрут? (y/n): ";
                    cin >> answer;
                    if (answer == 'y' || answer == 'Y') {
                        list.remove_node(found);
                        cout << "Маршрут удалн." << endl;
                    }
                }
                else {
                    cout << "Маршрут с таким номером не найден.";
                }
            }
            else if (choice == 8) {
                list.find_min_travel_time();
            }
            else if (choice == 9) {
                int maxTime;
                cout << "Введите максимально время поездки: ";
                cin >> maxTime;
                list.remove_by_travel_time(maxTime);
            }
            else if (choice == 10) {
                int number;
                cout << "Номер маршрута, после которого вставить новый: ";
                cin >> number;
                Route r = inputRoute();
                list.insert_after_number(number, r);
            }
            else if (choice == 11) cout << "Выход из программы" << endl;
        }
        else {
            cout << "Неверынй выбор в меню.\n";
        }
    }
    
    list.clear();
    return 0;
}


