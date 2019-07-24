//
//  selection.h
//  adb-get
//
//  Created by 上坂龍二 on 2019/7/24.
//  Copyright © 2019 上坂龍二. All rights reserved.
//

#ifndef selection_h
#define selection_h

#include <vector>
#include <string>
#include <iostream>

#include "console.h"

class selection{
private:
    class group{
    public:
        char mark;
        std::string ItemName;
        group(char mark, std::string Item) {
            this->mark = mark;
            ItemName.assign(Item);
        }
    };
    int countItem;
    std::vector<group> Items;
    
public:
    selection():countItem(0) {}
    ~selection() {}
    void addItem(char mark, std::string Item) {
        group p(mark, Item);
        countItem++;
        Items.push_back(p);
    }
    int select() {
        char select;
        int i;
        for(i=0; i<countItem; i++)
            std::cout << "[" << Items[i].mark << "]" << Items[i].ItemName << std::endl;
        while(true) {
            std::cout << "你的选择是:";
            std::cin >> select;
            for(i=0; i<countItem; i++) {
                if(Items[i].mark == select) {
                    CLEARLINES(countItem+1);
                    return i;
                }
            }
            std::cout << L_RED << "你的输入不合法,";
            std::cout << "请您从" << std::endl << "[";
            for(int j=0; j<countItem; j++) {
                if(j!=0) std::cout << ",";
                std::cout << Items[j].mark;
            }
            std::cout << "]" << std::endl <<"中任选一个输入" << std::endl;
            std::cout << "按回车键回到选择" << NONE;
            std::cin.ignore(1000, '\n');
            getchar();
            CLEARLINES(5);
        }
        return -2;
    }
};



#endif /* selection_h */
