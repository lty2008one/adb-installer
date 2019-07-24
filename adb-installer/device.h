//
//  device.h
//  adb-get
//
//  Created by 上坂龍二 on 2019/7/24.
//  Copyright © 2019 上坂龍二. All rights reserved.
//

#ifndef device_h
#define device_h

#include <fstream>
#include <iostream>
#include <unistd.h>
#include "console.h"

class config{
private:
    std::string ipaddress;
    int host;
public:
    bool recent;
    config() {
        std::ifstream configfile;
        configfile.open("adb-get.ip");
        if(!configfile.is_open()) {
            recent = false;
        } else {
            recent = true;
            configfile >> ipaddress;
            configfile >> host;
        }
    }
    std::string set() {
        std::cout << "请输入需要连接设备的IP地址(192.168.xxx.xxx):";
        std::cin >> ipaddress;
        std::cout << "请输入需要连接的端口号(5555):";
        std::cin >> host;
        CLEARLINES(2);
        std::fstream configfile;
        configfile.open("adb-get.ip", std::ios::out);
        if(!configfile.is_open()) {
            std::cout << "IP配置保存失败" << std::endl;
        } else {
            configfile << ipaddress << "\n";
            configfile << host;
            configfile.close();
            std::cout << "IP配置已保存" << std::endl;
        }
        usleep(200);
        CLEARLINES(1);
        return get();
    }
    std::string get() {
        std::string p;
        p.assign(ipaddress);
        p.append(":");
        p.append(std::to_string(host));
        return p;
    }
};

int USBconnect() {
    system("adb kill-server");
    system("adb devices >& adb.log");
    std::fstream log;
    std::string logbuf;
    log.open("adb.log");
    getline(log, logbuf);
    getline(log, logbuf);
    getline(log, logbuf);
    if(log >> logbuf) {
        if(logbuf.compare("device") == 0) return 0;
        if(logbuf.compare("unauthorized") == 0) return 1;
    }
    return -1;
}

int WIFIconnect(std::string IP) {
    system("adb kill-server");
    std::string conn("adb connect ");
    conn.append(IP);
    conn.append(" >& adb.log");
    system(conn.c_str());
    system("adb devices >& adb.log");
    std::fstream log;
    std::string logbuf;
    log.open("adb.log");
    getline(log, logbuf);
    if(log >> logbuf) {
        log >> logbuf;
        if(logbuf.compare("device") == 0) return 0;
        if(logbuf.compare("unauthorized") == 0) return 1;
    }
    return -1;
}

bool connectstates(int re, std::string way) {
    switch(re) {
        case 0:
            CLEARLINES(way.compare("USB")?2:1);
            std::cout << L_GREEN << "设备已成功通过" << way << "连接" << NONE << std::endl;
            return true;
        case 1:
            std::cout << "需要在设备上同意ADB授权" << std::endl;
            std::cout << "请在设备上" << L_RED << "默认" << NONE << "同意后按回车键继续";
            getchar();
            CLEARLINES(2);
            return false;
        case -1:
            CLEARLINES(1);
            std::cout << YELLOW << way << "未成功连接设备" << NONE << std::endl;
            return false;
    }
    return false;
}

void installapk() {
    CLEARLINES(1);
    std::string install("adb install ");
    std::string app;
    std::cout << "###############################" << std::endl;
    std::cout << "#                             #" << std::endl;
    std::cout << "#                             #" << std::endl;
    std::cout << "#                             #" << std::endl;
    std::cout << "#        " << L_BLUE << "将应用安装包拖" << NONE << "       #" << std::endl;
    std::cout << "#          " << L_BLUE << "进这个框" << NONE << "           #" << std::endl;
    std::cout << "#                             #" << std::endl;
    std::cout << "#                             #" << std::endl;
    std::cout << "#                             #" << std::endl;
    std::cout << "###############################" << std::endl;
    std::cout << "安装包路径是(按回车开始):" << std::endl;
    std::cin >> app;
    install.append(app);
    install.append(" >& adb.log");
    system(install.c_str());
    std::fstream log;
    std::string logbuf;
    log.open("adb.log");
    getline(log, logbuf);
    log >> logbuf;
    CLEARLINES(13);
    if(logbuf.compare("Success") == 0) {
        std::cout << L_GREEN << "安装成功" << NONE << std::endl;
    } else {
        std::cout << L_RED << "安装失败" << NONE <<std::endl;
    }
}

#endif /* device_h */
