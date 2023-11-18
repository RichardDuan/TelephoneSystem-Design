#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Key_Value_Convert.h"
#define MAXSIZE 1000000
//int KEY_VALUE(const char* input);
struct subnum {
    char* num;
    int state;
};
struct userdata {
    char* num;
    int state;
};
class Subs_SqList {
private:
    subnum* data;
    int capacity;
    int length;

public:
    Subs_SqList() : data(nullptr), capacity(0), length(0) {}

    ~Subs_SqList() {
        if (data != nullptr) {
            free(data);
        }
    }

    void initList_Subs(int initCapacity) {
        data = (subnum*)malloc(initCapacity * sizeof(subnum));
        if (data == nullptr) {        //�ڴ����ʧ��
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < initCapacity - 1; i++) {

            data[i].num = new char[12]; // +1 ��Ϊ�������ַ���ĩβ��β��
            strcpy(data[i].num, "###########"); // ʹ�� strcpy �����ַ���
            data[i].state = 0;

        }

        capacity = initCapacity;
        length = 0;
    }

    void insert_Subs(const char* num, int state, int i) {
        // �����������Ҫȷ�� i �ĺϷ��ԣ�����ʡ���˱߽���
        if (length == capacity) {          //�б�����
            exit(EXIT_FAILURE);
        }



        data[i].num = new char[strlen(num) + 1]; // +1 ��Ϊ�������ַ���ĩβ�� null �ַ�
        strcpy(data[i].num, num); // ʹ�� strcpy �����ַ���

        data[i].state = state;

        ++length;
    }

    subnum remove_Subs(int i) {
        // ɾ����������Ҫȷ�� i �ĺϷ��ԣ�����ʡ���˱߽���
        subnum removed = data[i];


        delete[] data[i].num; // �ͷ��ڴ�
        data[i].state = 0;
        strcpy(data[i].num, "###########");
        --length;

        return removed;
    }

    int get_num_state(int i) {
        return data[i].state;
    }

    void change_num_state(int i, int e) {  //�ı��i���û���״̬Ϊe
        data[i].state = e;
    }

    void display_Subs() {
        std::cout << "Subs���뼯��:" << std::endl;
        for (int i = 0; i < capacity - 1; ++i) {
            if (strcmp(data[i].num, "###########") != 0) {
                std::cout << "Index: " << i << ", Number: " << data[i].num << ", State: ";
                if (data[i].state == 0) {
                    std::cout << "Invalid" << std::endl;
                }
                if (data[i].state == 1) {
                    std::cout << "Busy" << std::endl;
                }
                if (data[i].state == 2) {
                    std::cout << "Free" << std::endl;
                }
            }

        }
        std::cout << std::endl;
    }

};
class Users_SqList {
private:
    userdata* data;
    int capacity;
    int length;

public:
    Users_SqList() : data(nullptr), capacity(0), length(0) {}

    ~Users_SqList() {
        if (data != nullptr) {
            free(data);
        }
    }

    void initList_Users(int initCapacity) {
        data = (userdata*)malloc(initCapacity * sizeof(userdata));
        if (data == nullptr) {        //�ڴ����ʧ��
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < initCapacity - 1; i++) {

            data[i].num = new char[12]; // +1 ��Ϊ�������ַ���ĩβ��β��
            strcpy(data[i].num, "###########"); // ʹ�� strcpy �����ַ���
            data[i].state = 0;

        }

        capacity = initCapacity;
        length = 0;
    }

    void insert_Users(const char* num, int state, int i) {
        // �����������Ҫȷ�� i �ĺϷ��ԣ�����ʡ���˱߽���
        if (length == capacity) {          //�б�����
            exit(EXIT_FAILURE);
        }



        data[i].num = new char[strlen(num) + 1]; // +1 ��Ϊ�������ַ���ĩβ�� null �ַ�
        strcpy(data[i].num, num); // ʹ�� strcpy �����ַ���

        data[i].state = state;

        ++length;
    }

    userdata remove_Users(int i) {
        // ɾ����������Ҫȷ�� i �ĺϷ��ԣ�����ʡ���˱߽���
        userdata removed = data[i];


        delete[] data[i].num; // �ͷ��ڴ�
        data[i].state = 0;
        strcpy(data[i].num, "###########");
        --length;

        return removed;
    }

    int get_user_state(int i) {   //��ȡ��i���û���״̬
        return data[i].state;
    }

    void change_user_state(int i, int e) {  //�ı��i���û���״̬Ϊe
        data[i].state = e;
    }

    void display_Users() {
        std::cout << "Users�û���:" << std::endl;
        for (int i = 0; i < capacity - 1; ++i) {
            if (strcmp(data[i].num, "###########") != 0) {
                std::cout << "Index: " << i << ", Number: " << data[i].num << ", State: ";
                if (data[i].state == 0) {
                    std::cout << "unoccupied" << std::endl;
                }
                if (data[i].state == 1) {
                    std::cout << "dialing" << std::endl;
                }
                if (data[i].state == 2) {
                    std::cout << "unobtainable" << std::endl;
                }
                if (data[i].state == 3) {
                    std::cout << "engaged" << std::endl;
                }
                if (data[i].state == 4) {
                    std::cout << "connecting" << std::endl;
                }
                if (data[i].state == 5) {
                    std::cout << "ringing" << std::endl;
                }
                if (data[i].state == 6) {
                    std::cout << "speeching" << std::endl;
                }
                if (data[i].state == 7) {
                    std::cout << "disconnecting" << std::endl;
                }

            }

        }
        std::cout << std::endl;
    }

};
static Subs_SqList subsList;
static Users_SqList usersList;
void InitList() {
    subsList.initList_Subs(MAXSIZE);
    usersList.initList_Users(MAXSIZE);
    //��ʼ��Subs���뼯�е�Ԫ��
    subsList.insert_Subs("12345678901", 2, KEY_VALUE("12345678901"));
    subsList.insert_Subs("42345679800", 2, KEY_VALUE("42345679800"));
    subsList.insert_Subs("85412369711", 1, KEY_VALUE("85412369711"));
    subsList.insert_Subs("35862314556", 2, KEY_VALUE("35862314556"));
    subsList.insert_Subs("65478213658", 2, KEY_VALUE("65478213658"));
    subsList.insert_Subs("98765432109", 1, KEY_VALUE("98765432109"));
    //��ʼ��Users�û����е�Ԫ��
    usersList.insert_Users("12345678901", 0, KEY_VALUE("12345678901"));
    usersList.insert_Users("42345679800", 0, KEY_VALUE("42345679800"));
    usersList.insert_Users("85412369711", 6, KEY_VALUE("85412369711"));
    usersList.insert_Users("35862314556", 0, KEY_VALUE("35862314556"));
    usersList.insert_Users("65478213658", 0, KEY_VALUE("65478213658"));
    usersList.insert_Users("98765432109", 5, KEY_VALUE("98765432109"));
}