//
//  main.cpp
//  adb-get
//
//  Created by 上坂龍二 on 2019/7/23.
//  Copyright © 2019 上坂龍二. All rights reserved.
//
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "version.h"
#include "selection.h"
#include "console.h"
#include "device.h"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    int retn, goon = 1;
    if(argc == 1) {
        HIDE();
        cout << "欢迎使用adb-install程序" << endl;
        cout << "当前版本为" << ver::get() << ((ver::release)?"(Release)":"(Debug)") << endl;
        cout << "############请稍等#############" << endl;
        
        cout << ">正在尝试通过USB连接到设备<" << endl;
        do retn = USBconnect();
        while(!connectstates(retn, "USB") && retn != -1);
        if(retn == -1) {
            cout << ">正在尝试通过WI-FI连接到设备<" << endl;
            SHOW();
            config device;
            selection userecent;
            userecent.addItem('n', "使用新配置");
            if(device.recent) userecent.addItem('r', "使用上次的配置");
            do {
                if(userecent.select() == 1)
                    retn = WIFIconnect(device.get());
                else retn = WIFIconnect(device.set());
            } while(!connectstates(retn, "WI-FI"));
        }
        while(goon) {
            cout << "############主菜单#############" << endl;
            selection mainmenu;
            mainmenu.addItem('i', "#从本地安装应用程序到设备#");
            //mainmenu.addItem('n', "#从网上安装应用程序到设备#");
            //mainmenu.addItem('s', "#对本应用进行设置#");
            mainmenu.addItem('q', "#退出本应用#");
            switch(mainmenu.select()) {
                case  0: installapk(); break;
                default: goon = false; break;
            }
        }
        
    } else {
        
    }
    CLEARLINES(5);
    SHOW();
    return 0;
}
