﻿#pragma once
#include "INIReader.h"
#include <cmath>
#include <cstdint>
#include <print>
#include "runtime_format.h"    //支持std::format的运行时格式化，c++26前暂时凑合用

//此类中是一些游戏中的公式，例如使用物品的效果，伤害公式等
//通常来说应该全部是静态函数
class GameUtil : public INIReaderNormal
{
private:
    GameUtil();
    ~GameUtil();

public:
    static GameUtil* getInstance()
    {
        static GameUtil gu;
        return &gu;
    }

    static const std::string& VERSION()
    {
        static std::string v = "";
        return v;
    }

    static std::string& PATH()
    {
#ifndef __ANDROID__
        static std::string s = "../game/";
#else
        static std::string s = "/sdcard/game/";
#endif
        return s;
    }

    static int sign(int v)
    {
        if (v > 0)
        {
            return 1;
        }
        if (v < 0)
        {
            return -1;
        }
        return 0;
    }

    //返回限制值
    template <typename T, typename T2>
    static T limit(T current, T2 min_value, T2 max_value)
    {
        if (current < min_value)
        {
            current = min_value;
        }
        if (current > max_value)
        {
            current = max_value;
        }
        return current;
    }

    //limit2是直接修改引用值，有两个重载
    static void limit2(int& current, int min_value, int max_value)
    {
        current = limit(current, min_value, max_value);
    }

    static void limit2(int16_t& current, int min_value, int max_value)
    {
        current = limit(current, min_value, max_value);
    }

    static void limit2(uint16_t& current, int min_value, int max_value)
    {
        current = limit(current, min_value, max_value);
    }

    //计算某个数值的位数
    static int digit(int x)
    {
        int n = floor(log10(0.5 + abs(x)));
        if (x >= 0)
        {
            return n;
        }
        else
        {
            return n + 1;
        }
    }
};

template <typename... Args>
void LOG(std::format_string<Args...> fmt, Args... args)
{
    std::print(fmt, std::forward<Args>(args)...);
}

