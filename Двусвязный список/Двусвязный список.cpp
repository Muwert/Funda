// Двусвязный список.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
struct Node
{
    Node* prev;
    Node* next;
    int data;
    int cnt;
};


void AddElement(Node*& head, Node*& tail, int elem) {
    Node* tmp = new Node();
    tmp->data = elem;
    tmp->next = nullptr;
    tmp->prev = nullptr;

    if (head == nullptr) {
        head = tmp;
        tail = tmp;
    }
    else {
        Node* p = head;
        if (head->data > elem)
        {
            tmp->next = head;
            tmp->prev = nullptr;
            head->prev = tmp;
            head = tmp;
        }
        else
        {
            while (p->next != nullptr && p->data < elem) {
                p = p->next;
            }
            if (p->data == elem) {
                p->cnt += 1;
            }
            else if (p->data > elem) {
                tmp->prev = p->prev;
                p->prev->next = tmp;
                tmp->next = p;
                p->prev = tmp;
            }
            else {
                p->next = tmp;
                tmp->next = nullptr;
                tmp->prev = p;
                tail = tmp;
            }
        }
    }
}

void PrintList_start_stop(Node* head) {
    if (head != nullptr) {
        while (head != nullptr) {
            std::cout << head->data << " : " << head->cnt << "<-->";
            head = head->next;
        }
        std::cout << std::endl;
    }
    else std::cout << "Список пустой ";
}

void PrintList_stop_start(Node* tail) {
    if (tail != nullptr) {
        while (tail != nullptr) {
            if (tail->cnt != 0) {
                std::cout << " (Количество повторений: " << tail->cnt << ") ";
            }
            std::cout << tail->data << "<-->";
            tail = tail->prev;
        }
    }
    else std::cout << "Список пустой ";
}

void DeleteElement(Node*&head,Node*&tail, int num) {
    if (head != nullptr)  {
        Node* p = head;
        if (head->data == num && head->prev == nullptr && head->next != nullptr) {
            if (head->cnt == 0) {
                Node* ud = head;
                head->next->prev = nullptr;
                head = head->next;
                delete (ud);
            }
            else head->cnt -= 1;
        }
        else if (head->data == num && head->prev == nullptr && head->next == nullptr) {
            if (head->cnt == 0) {
                tail = head;
                delete(head);
                head = nullptr;
                tail = nullptr;
            }
            else head->cnt -= 1;
        }
        else if (head->data != num) {
            while (p->data != num && p->next != nullptr) {
                p = p->next;
            }
            if (p->data == num && p->next != nullptr) {
                if (p->cnt == 0) {
                    p->next->prev = p->prev;
                    p->prev->next = p->next;
                    delete(p);
                }
                else p->cnt -= 1;
            }
            else if (p->data == num && p == tail) {
                if (p->cnt == 0) {
                    p->prev->next = nullptr;
                    tail = p->prev;
                    delete(p);
                }
                else p->cnt -= 1;
            }
            else if (p == tail && p->data != num) std::cout << "False" << std::endl;
        }
        
    }
}

void Peresechenie(Node*& head, Node*& tail, Node*& head1, Node*& tail1, Node*& head2, Node*& tail2) {
    Node* current = head1;
    Node* temp = head;
    if (current != nullptr && temp != nullptr) {
        while (current != nullptr && temp != nullptr) {
            if (temp->data == current->data) {
                AddElement(head2, tail2, current->data);
                temp = temp->next;
                current = current->next;
            }
            else {
                if (temp->data > current->data) {
                    current = current->next;
                }
                else {
                    temp = temp->next;
                }
            }
        }
    }
}


void Delete_all(Node*&list, Node*&tail) 
{
    if (list != nullptr) {
        while (list != nullptr) {
            Node* p = list;
            list = list->next;
            delete(p);
        }
    }
    tail = list;
    delete(list);
    delete(tail);
}


bool FindElement(Node* list, Node* tail, int f) {
    bool mesto = false;
    Node* find = list;
    if (find != nullptr) {
        while (find != nullptr) {
            if (find->data == f) {
                mesto = true;
                find = find->next;
            }
            else if (find->data != f) {
                while (find != nullptr && find->data != f) {
                    find = find->next;
                }
            }
        }
    }
    return mesto;
}


int main() {
    setlocale(LC_ALL, "Russian");
    Node* spisok_head = nullptr;
    Node* spisok_tail = nullptr;
    Node* spisok1_head = nullptr;
    Node* spisok1_tail = nullptr;
    Node* spisokPeresechenie_head = nullptr;
    Node* spisokPeresechenie_tail = nullptr;
    int n, elem;
    for (int i = 0; i < 21; i++) {
        int a;
        a = rand() % 10 + 1;
        AddElement(spisok_head, spisok_tail, a);
    }
    PrintList_start_stop(spisok_head);
    AddElement(spisok_head, spisok_tail, 35);
    AddElement(spisok1_head, spisok1_tail, 4);
    AddElement(spisok1_head, spisok1_tail, 35);
    AddElement(spisok1_head, spisok1_tail, 71);
    PrintList_start_stop(spisok1_head);
    DeleteElement(spisok_head, spisok_tail, 5);
    PrintList_start_stop(spisok_head);
    DeleteElement(spisok_head, spisok_tail, 10);
    PrintList_start_stop(spisok_head);
    DeleteElement(spisok_head, spisok_tail, 7);
    Peresechenie(spisok_head, spisok_tail, spisok1_head, spisok1_tail, spisokPeresechenie_head, spisokPeresechenie_tail);
    PrintList_start_stop(spisokPeresechenie_head);
    std::cout << std::endl << FindElement(spisok_head, spisok_tail, 67);
    Delete_all(spisok_head, spisok_tail);
}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.