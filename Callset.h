#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <windows.h>
#include <istream>
#include "Key_Value_Convert.h"
#include "SqList_Creat.h"
void Dial(char* num_send, char* num_receive) {    //����״̬ת�ƺ��������Ų���,��unoccupiedת�Ƶ�dialing
    while (1) {
        std::cout << "������з��ĺ��룺" << std::endl;
        std::cin >> num_send;
        if (subsList.get_num_state(KEY_VALUE(num_send)) == 2) {
            break;
        }
        else if (subsList.get_num_state(KEY_VALUE(num_send)) == 0) {
            std::cout << "�����Ϊ�պţ�����������" << std::endl;
            Sleep(1000);
        }
        else {
            std::cout << "����ĺ�������ͨ���У�����������" << std::endl;
            Sleep(1000);
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    subsList.change_num_state(KEY_VALUE(num_send), 1);   //������״̬��ΪBusy
    usersList.change_user_state(KEY_VALUE(num_send), 1);  //������״̬��Ϊdialing
    while (1) {
        std::cout << "������շ��ĺ��룺" << std::endl;
        std::cin >> num_receive;
        if (strcmp(num_receive, num_send) == 0) {
            std::cout << "����ĺ�������з������ظ�������������" << std::endl;
            Sleep(1000);
        }
        else {
            break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "���з�" << num_send << "���ڲ���" << num_receive << std::endl;
    Sleep(1000);
}
int Sy1(char* num_send, char* num_receive) {    //�Զ�״̬ת�ƺ�������dialingת�Ƶ�unobtainable
    if (subsList.get_num_state(KEY_VALUE(num_receive)) == 0) {  //��������û��绰�����ǷǷ�
        usersList.change_user_state(KEY_VALUE(num_send), 2);  //������״̬��Ϊunobtainable
        std::cout << "����ĵ绰�ǿպţ����ڶϿ�����" << std::endl;
        Sleep(1000);
        usersList.change_user_state(KEY_VALUE(num_send), 0);  //������״̬��Ϊunoccupied
        subsList.change_num_state(KEY_VALUE(num_send), 2);   //�������ĺ���״̬��ΪFree
        std::cout << "������������з��Լ����뷽����" << std::endl;
        Sleep(500);
        return 0;
    }
    return 1;
}
int Sy2(char* num_send, char* num_receive) {    //�Զ�״̬ת�ƺ�������dialingת�Ƶ�engaged
    if (subsList.get_num_state(KEY_VALUE(num_receive)) == 1) {  //��������û��绰������æ��
        usersList.change_user_state(KEY_VALUE(num_send), 3);   //������״̬��Ϊengaged
        std::cout << "����ĵ绰������æ�ߣ����ڶϿ�����" << std::endl;
        Sleep(1000);
        usersList.change_user_state(KEY_VALUE(num_send), 0);   //������״̬��Ϊunoccupied
        subsList.change_num_state(KEY_VALUE(num_send), 2);
        std::cout << "������������з��Լ����뷽����" << std::endl;
        Sleep(500);
        return 0;
    }
    return 1;
}
void Sy3(char* num_send, char* num_receive) {    //�Զ�״̬ת�ƺ�������dialingת�Ƶ�connecting
    if (subsList.get_num_state(KEY_VALUE(num_receive) == 2)) {  //��������û��绰�����ǿ���
        usersList.change_user_state(KEY_VALUE(num_send), 4);   //������״̬��Ϊconnecting
        subsList.change_num_state(KEY_VALUE(num_send), 1);    //����������״̬��ΪBusy
        subsList.change_num_state(KEY_VALUE(num_receive), 1);  //���ܷ�����״̬��ΪBusy
        usersList.change_user_state(KEY_VALUE(num_receive), 4);  //���ܷ�����״̬��Ϊconnecting
        std::cout << "���ųɹ����������ӡ���" << std::endl;
        Sleep(1000);
    }
}
int ClearLine(char* num_send, char* num_receive) {    //����״̬ת�ƺ�������ͨǰ���𷽹Ҷϲ�������connectingת�Ƶ�ringing���connectingת��unoccupied
    int input;
    std::cout << "���з��Ƿ�Ҫ����ͨ����[1Ϊ�ǣ�0Ϊ��]" << std::endl;
    std::cin >> input;
    if (input == 1) {
        std::cout << "���ڶϿ����ӡ���" << std::endl;
        Sleep(1000);
        usersList.change_user_state(KEY_VALUE(num_send), 7);   //������״̬��Ϊdisconnecting
        usersList.change_user_state(KEY_VALUE(num_receive), 7);   //���շ�״̬��Ϊdisconnecting
        std::cout << "ͨ����ֹ" << std::endl;
        usersList.change_user_state(KEY_VALUE(num_send), 0);   //������״̬��Ϊunoccupied
        usersList.change_user_state(KEY_VALUE(num_receive), 0);   //���ܷ�״̬��Ϊunoccupied
        subsList.change_num_state(KEY_VALUE(num_send), 2);      //����������״̬��ΪFree
        subsList.change_num_state(KEY_VALUE(num_receive), 2);      //���ܷ�����״̬��ΪFree
        Sleep(1000);
        return 1;//����1����Ҫ�Ҷ�
    }
    else {
        std::cout << "�Է���ʼ����" << std::endl;
        usersList.change_user_state(KEY_VALUE(num_send), 5);   //������״̬��Ϊringing
        subsList.change_num_state(KEY_VALUE(num_send), 1);      //����������״̬��ΪBsuy
        usersList.change_user_state(KEY_VALUE(num_receive), 5);   //���ܷ�״̬��Ϊunoccupied
        subsList.change_num_state(KEY_VALUE(num_receive), 1);      //���ܷ�����״̬��ΪBusy
        Sleep(1000);
        return 0;//����0�����Ҷ�
    }
}
int ReLift(char* num_send, char* num_receive) {    //����״̬ת�ƺ�������ͨǰ���ܷ��Ҷϲ�������ringingת�Ƶ�speeching���ringingת��unoccupied
    int input;
    std::cout << "���շ����Ƿ�Ҫ��ͨ�绰��[1Ϊ�ǣ�0Ϊ��]" << std::endl;
    std::cin >> input;
    if (input == 0) {
        std::cout << "���շ��ܾ�ͨ�������ڶϿ�����" << std::endl;
        Sleep(1000);
        usersList.change_user_state(KEY_VALUE(num_send), 7);   //������״̬��Ϊdisconnecting
        usersList.change_user_state(KEY_VALUE(num_receive), 7);   //���շ�״̬��Ϊdisconnecting
        std::cout << "�ѹҶ�" << std::endl;
        usersList.change_user_state(KEY_VALUE(num_send), 0);   //������״̬��Ϊunoccupied
        usersList.change_user_state(KEY_VALUE(num_receive), 0);   //���ܷ�״̬��Ϊunoccupied
        subsList.change_num_state(KEY_VALUE(num_send), 2);      //����������״̬��ΪFree
        subsList.change_num_state(KEY_VALUE(num_receive), 2);      //���ܷ�����״̬��ΪFree
        Sleep(1000);
        return 0;//����0����Ҫ�Ҷ�
    }
    else {
        std::cout << "�绰��ͨ" << std::endl;
        usersList.change_user_state(KEY_VALUE(num_send), 6);   //������״̬��Ϊspeeching
        subsList.change_num_state(KEY_VALUE(num_send), 1);      //����������״̬��ΪBsuy
        usersList.change_user_state(KEY_VALUE(num_receive), 6);   //���ܷ�״̬��Ϊspeeching
        subsList.change_num_state(KEY_VALUE(num_receive), 1);      //���ܷ�����״̬��ΪBusy
        Sleep(1000);
        std::cout << "��ʼͨ��" << std::endl;
        return 1;//����1�����Ҷ�
    }
}
void Clear(char* num_send, char* num_receive) {    //����״̬ת�ƺ�������ͨ��Ҷϲ�������speechingת�Ƶ�disconnected
    int input;
    std::cout << "����ͨ���У�����ͨ���밴1" << std::endl;
    std::cin >> input;
    if (input == 1) {
        std::cout << "ͨ�����������ڶϿ�����" << std::endl;
        Sleep(1000);
        usersList.change_user_state(KEY_VALUE(num_send), 7);   //������״̬��Ϊdisconnecting
        usersList.change_user_state(KEY_VALUE(num_receive), 7);   //���շ�״̬��Ϊdisconnecting
        std::cout << "�ѹҶ�" << std::endl;
        usersList.change_user_state(KEY_VALUE(num_send), 0);   //������״̬��Ϊunoccupied
        usersList.change_user_state(KEY_VALUE(num_receive), 0);   //���ܷ�״̬��Ϊunoccupied
        subsList.change_num_state(KEY_VALUE(num_send), 2);      //����������״̬��ΪFree
        subsList.change_num_state(KEY_VALUE(num_receive), 2);      //���ܷ�����״̬��ΪFree
        Sleep(1000);
    }
}