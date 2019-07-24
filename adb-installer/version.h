//
//  version.h
//  adb-get
//
//  Created by 上坂龍二 on 2019/7/24.
//  Copyright © 2019 上坂龍二. All rights reserved.
//

#ifndef version_h
#define version_h

#include <string>

class ver {
private:
    const static int higher = 0;
    const static int middle = 0;
    const static int lowwer = 1;
public:
    ver() {}
    ~ver() {}
    const static bool release = false;
    static std::string get() {
        std::string dust;
        dust.assign(std::to_string(higher));
        dust.append(".");
        dust.append(std::to_string(middle));
        dust.append(".");
        dust.append(std::to_string(lowwer));
        return dust;
    }
};

#endif /* version_h */
