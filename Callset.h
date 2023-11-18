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
void Dial(char* num_send, char* num_receive) {    //操作状态转移函数：拨号操作,从unoccupied转移到dialing
    while (1) {
        std::cout << "输入呼叫方的号码：" << std::endl;
        std::cin >> num_send;
        if (subsList.get_num_state(KEY_VALUE(num_send)) == 2) {
            break;
        }
        else if (subsList.get_num_state(KEY_VALUE(num_send)) == 0) {
            std::cout << "输入的为空号，请重新输入" << std::endl;
            Sleep(1000);
        }
        else {
            std::cout << "输入的号码正在通话中，请重新输入" << std::endl;
            Sleep(1000);
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    subsList.change_num_state(KEY_VALUE(num_send), 1);   //发出方状态变为Busy
    usersList.change_user_state(KEY_VALUE(num_send), 1);  //发出方状态变为dialing
    while (1) {
        std::cout << "输入接收方的号码：" << std::endl;
        std::cin >> num_receive;
        if (strcmp(num_receive, num_send) == 0) {
            std::cout << "输入的号码与呼叫方号码重复，请重新输入" << std::endl;
            Sleep(1000);
        }
        else {
            break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "呼叫方" << num_send << "正在拨号" << num_receive << std::endl;
    Sleep(1000);
}
int Sy1(char* num_send, char* num_receive) {    //自动状态转移函数：从dialing转移到unobtainable
    if (subsList.get_num_state(KEY_VALUE(num_receive)) == 0) {  //被拨打的用户电话号码是非法
        usersList.change_user_state(KEY_VALUE(num_send), 2);  //发出方状态变为unobtainable
        std::cout << "拨打的电话是空号，正在断开连接" << std::endl;
        Sleep(1000);
        usersList.change_user_state(KEY_VALUE(num_send), 0);  //发出方状态变为unoccupied
        subsList.change_num_state(KEY_VALUE(num_send), 2);   //发出方的号码状态变为Free
        std::cout << "请重新输入呼叫方以及输入方号码" << std::endl;
        Sleep(500);
        return 0;
    }
    return 1;
}
int Sy2(char* num_send, char* num_receive) {    //自动状态转移函数：从dialing转移到engaged
    if (subsList.get_num_state(KEY_VALUE(num_receive)) == 1) {  //被拨打的用户电话号码是忙线
        usersList.change_user_state(KEY_VALUE(num_send), 3);   //发出方状态变为engaged
        std::cout << "拨打的电话是正在忙线，正在断开连接" << std::endl;
        Sleep(1000);
        usersList.change_user_state(KEY_VALUE(num_send), 0);   //发出方状态变为unoccupied
        subsList.change_num_state(KEY_VALUE(num_send), 2);
        std::cout << "请重新输入呼叫方以及输入方号码" << std::endl;
        Sleep(500);
        return 0;
    }
    return 1;
}
void Sy3(char* num_send, char* num_receive) {    //自动状态转移函数：从dialing转移到connecting
    if (subsList.get_num_state(KEY_VALUE(num_receive) == 2)) {  //被拨打的用户电话号码是空闲
        usersList.change_user_state(KEY_VALUE(num_send), 4);   //发出方状态变为connecting
        subsList.change_num_state(KEY_VALUE(num_send), 1);    //发出方号码状态变为Busy
        subsList.change_num_state(KEY_VALUE(num_receive), 1);  //接受方号码状态变为Busy
        usersList.change_user_state(KEY_VALUE(num_receive), 4);  //接受方号码状态变为connecting
        std::cout << "拨号成功，正在连接……" << std::endl;
        Sleep(1000);
    }
}
int ClearLine(char* num_send, char* num_receive) {    //操作状态转移函数：接通前发起方挂断操作，从connecting转移到ringing或从connecting转到unoccupied
    int input;
    std::cout << "呼叫方是否要放弃通话？[1为是，0为否]" << std::endl;
    std::cin >> input;
    if (input == 1) {
        std::cout << "正在断开连接……" << std::endl;
        Sleep(1000);
        usersList.change_user_state(KEY_VALUE(num_send), 7);   //发出方状态变为disconnecting
        usersList.change_user_state(KEY_VALUE(num_receive), 7);   //接收方状态变为disconnecting
        std::cout << "通话终止" << std::endl;
        usersList.change_user_state(KEY_VALUE(num_send), 0);   //发出方状态变为unoccupied
        usersList.change_user_state(KEY_VALUE(num_receive), 0);   //接受方状态变为unoccupied
        subsList.change_num_state(KEY_VALUE(num_send), 2);      //发出方号码状态变为Free
        subsList.change_num_state(KEY_VALUE(num_receive), 2);      //接受方号码状态变为Free
        Sleep(1000);
        return 1;//返回1代表要挂断
    }
    else {
        std::cout << "对方开始振铃" << std::endl;
        usersList.change_user_state(KEY_VALUE(num_send), 5);   //发出方状态变为ringing
        subsList.change_num_state(KEY_VALUE(num_send), 1);      //发出方号码状态变为Bsuy
        usersList.change_user_state(KEY_VALUE(num_receive), 5);   //接受方状态变为unoccupied
        subsList.change_num_state(KEY_VALUE(num_receive), 1);      //接受方号码状态变为Busy
        Sleep(1000);
        return 0;//返回0代表不挂断
    }
}
int ReLift(char* num_send, char* num_receive) {    //操作状态转移函数：接通前接受方挂断操作，从ringing转移到speeching或从ringing转到unoccupied
    int input;
    std::cout << "接收方方是否要接通电话？[1为是，0为否]" << std::endl;
    std::cin >> input;
    if (input == 0) {
        std::cout << "接收方拒绝通话，正在断开连接" << std::endl;
        Sleep(1000);
        usersList.change_user_state(KEY_VALUE(num_send), 7);   //发出方状态变为disconnecting
        usersList.change_user_state(KEY_VALUE(num_receive), 7);   //接收方状态变为disconnecting
        std::cout << "已挂断" << std::endl;
        usersList.change_user_state(KEY_VALUE(num_send), 0);   //发出方状态变为unoccupied
        usersList.change_user_state(KEY_VALUE(num_receive), 0);   //接受方状态变为unoccupied
        subsList.change_num_state(KEY_VALUE(num_send), 2);      //发出方号码状态变为Free
        subsList.change_num_state(KEY_VALUE(num_receive), 2);      //接受方号码状态变为Free
        Sleep(1000);
        return 0;//返回0代表要挂断
    }
    else {
        std::cout << "电话接通" << std::endl;
        usersList.change_user_state(KEY_VALUE(num_send), 6);   //发出方状态变为speeching
        subsList.change_num_state(KEY_VALUE(num_send), 1);      //发出方号码状态变为Bsuy
        usersList.change_user_state(KEY_VALUE(num_receive), 6);   //接受方状态变为speeching
        subsList.change_num_state(KEY_VALUE(num_receive), 1);      //接受方号码状态变为Busy
        Sleep(1000);
        std::cout << "开始通话" << std::endl;
        return 1;//返回1代表不挂断
    }
}
void Clear(char* num_send, char* num_receive) {    //操作状态转移函数：接通后挂断操作，从speeching转移到disconnected
    int input;
    std::cout << "正在通话中，结束通话请按1" << std::endl;
    std::cin >> input;
    if (input == 1) {
        std::cout << "通话结束，正在断开连接" << std::endl;
        Sleep(1000);
        usersList.change_user_state(KEY_VALUE(num_send), 7);   //发出方状态变为disconnecting
        usersList.change_user_state(KEY_VALUE(num_receive), 7);   //接收方状态变为disconnecting
        std::cout << "已挂断" << std::endl;
        usersList.change_user_state(KEY_VALUE(num_send), 0);   //发出方状态变为unoccupied
        usersList.change_user_state(KEY_VALUE(num_receive), 0);   //接受方状态变为unoccupied
        subsList.change_num_state(KEY_VALUE(num_send), 2);      //发出方号码状态变为Free
        subsList.change_num_state(KEY_VALUE(num_receive), 2);      //接受方号码状态变为Free
        Sleep(1000);
    }
}