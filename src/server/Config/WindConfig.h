/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 22/06/18
 */

#ifndef __WIND_CONFIG_H__
#define __WIND_CONFIG_H__


#include <yaml-cpp/include/yaml-cpp/node/node.h>

namespace Config{
//    namespace Wind{
//        struct Range{
//            explicit Range(YAML::Node &config);
//        };
//    }
    struct Wind{
        float minIntensity;
        float maxIntensity;
        int xDirection;
        float instensity;
    };
} // namespace Config


#endif //__WIND_CONFIG_H__
