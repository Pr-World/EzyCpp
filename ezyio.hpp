#pragma once
#include <iostream>
#include <type_traits>

/// prints given content. Syntax : print(smth, smth2, smth3, ...);
void print()
{
    std::cout << '\n';
}
template <typename T, typename... TAIL>
void print(const T &t, TAIL... tail)
{
    std::cout << t << " ";
    print(tail...);
}

template <typename T, size_t size>
void print_arr(const T(&t)[size], std::string sep = ", ", bool braces = true)
{
    std::cout << (braces ? "{" : "");
    bool done = false;
    for (T v: t) {
        if (std::is_same<T,std::string>::value || std::is_same<T,char *>::value || std::is_same<T,const char*>::value)
        {
            std::cout << (done?sep:"") << '"' << v << '"';
        } else {
            std::cout << (done?sep:"") << v;
        }
        done = true;
    }
    std::cout << (braces ? "}": "");
}

/// inputs to a variable, Syntax : input(var1, var2, var3, ...);
template <typename T>
T input(std::string prompt = "")
{
    T v;
    std::cout << prompt;
    std::cin >> v;
    return v;
}