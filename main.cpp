//
// Created by Petr on 18.11.2019.
//

#include <iostream>
#include "error_handling/exceptions.h"
#include "config/JsonConfig.h"
#include "types/CachedProperty.h"
#include "various/StringUtils.h"
#include "types/Range.h"
#include "io/logger.h"
#include "io/print.h"

#include "various/ByteLiterals.h"
#include "various/isin.h"
#include "types/Lazy.h"

#include "graphics/BoundingBox.h"
#include "graphics/BoundingSphere.h"
#include "graphics/Geometry.h"
#include "graphics/ViewFrustum.h"

#include "time/FPSCounter.h"

#include "various/loc_assert.h"

using namespace ByteLiterals;
using String = StringDecorator<std::string>;

String operator ""_s(const char *str, size_t) {
    return String{str};
}

int main() {
    print(String::Format("{}.{}.{} se narodil jeden z nejvetsich mozku historie lidstva.", 8, 6, 1995));
    String templ{"{}.{}.{} se narodil jeden z nejvetsich mozku historie lidstva."};
    print(templ.format(8, 6, 1995));
    print("{}.{}.{} se narodil jeden z nejvetsich mozku historie lidstva."_s.format(8, 6, 1995));
    Logger logger{std::cout};

    logger.remember("lala", "{}.{}.{} se narodil jeden z nejvetsich mozku historie lidstva."_s.format(8, 6, 1995));
    const unsigned int iterations = 10;
    logger.measure([] {
        std::string str{"test"};
        auto str2 = str.substr(2);
    }, iterations, "Old str");
    logger.measure([] {
        String str{"test"};
        auto str2 = str.substr(2);
    }, iterations, "New str");

    print(isIn(10, {1, 2, 5}));
    print(10_MB);

    Lazy<int> l{[] { return 10; }};
    print(l.value());

    CachedProperty<int> p{[] { return 10; }};
    print(p.getRef());

    print(logger.recall<String>("lala"));

    FPSCounter counter;
    print(counter);

    JsonConfig<false> config{"C:\\Users\\Petr\\CLionProjects\\Utilities\\test.json"};
    print(config.get<int>("yah", "bah"));
    config.set(150, "yah", "bah");
    print(config.get<int>("yah", "bah"));
    print(config.contains("yah", "bah"));
    print(config.contains("syah", "bah"));

    loc_assert(0 == 1);
}