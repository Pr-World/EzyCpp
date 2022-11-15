#pragma once
#include <iostream>
#include <type_traits>
#include <vector>
#include <bits/stdc++.h>

#define var auto
#define int(x) convertint(x)
#define float(x) (float)convertdouble(x)
#define double(x) convertdouble(x)

/// prints given content. Syntax : print(smth, smth2, smth3, ...);
void print()
{
    std::cout << std::endl;
}
template <typename T, typename... TAIL>
void print(const T &t, TAIL... tail)
{
    std::cout << t << " ";
    print(tail...);
}
void print_wn(void){return;}
template <typename T, typename... TAIL>
void print_wn(const T &t, TAIL... tail)
{
    std::cout << t << " ";
    print_wn(tail...);
}

template <typename T, size_t size>
void print_arr(const T(&t)[size], std::string sep = ", ", std::string end = "\n", bool braces = true)
{
    std::cout << (braces ? "{" : "");
    bool done = false;
    for (T v: t) {
        if (std::is_same<T,std::string>::value || std::is_same<T,char *>::value || std::is_same<T,const char*>::value)
            std::cout << (done?sep:"") << '"' << v << '"';
        else
            std::cout << (done?sep:"") << v;
        done = true;
    }
    std::cout << (braces ? "}" : "") << end;
}

template <typename T>
void print_arr(std::vector<T> t, std::string sep = ", ", std::string end = "\n", bool braces = true)
{
    std::cout << (braces ? "{" : "");
    bool done = false;
    for (T v: t) {
        if (std::is_same<T,std::string>::value || std::is_same<T,char *>::value || std::is_same<T,const char*>::value)
            std::cout << (done?sep:"") << '"' << v << '"';
        else
            std::cout << (done?sep:"") << v;
        done = true;
    }
    std::cout << (braces ? "}" : "") << end;
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

template <typename T, typename... TAIL>
T dyn_input(T v, TAIL... tail)
{
    v = input<T>(tail...);
    return v;
}

std::string operator * (std::string val, size_t s) {
    std::string ret;
    while(s--)
        ret += val;
    return ret;
}

std::string operator * (size_t s, std::string val) {
    return val * s;
}

std::vector<int> range(int mnmax = 0, int max = 0, int step = 1)
{
    std::vector<int> v;
    if ( step > 0 ) {
        for(int i = (max?mnmax:0); i < (max?max:mnmax); i+=step)
            v.push_back(i);
    } else if ( step < 0 ) {
        for (int i = (max?mnmax:0); i > (max?max:mnmax); i+=step)
            v.push_back(i);
    }
    return v;
}

// integer to binary converter
std::string bin(int num, bool standard = true)
{
    std::string ret;
    bool ng = num < 0;
    num = abs(num);
    while ( num >>= 1 ) ret += '0'+num%2;
    std::reverse(ret.begin(), ret.end());
    ret = (ng ? "-": "") + (standard ? "0b" + ret: ret);
    return ret;
}

// integer to hex converter
std::string hex(int num, bool standard = true)
{
    std::string ret;
    std::string htable = "0123456789abcdef";
    bool ng = num < 0;
    num = abs(num);
    do { ret += htable[num%16]; } while ( num >>=4 );
    std::reverse(ret.begin(),ret.end());
    ret = (ng ? "-": "") + (standard ? "0x" + ret: ret);
    return ret;
}

std::string input(std::string prompt = "")
{
    std::string val;
    std::cout << prompt;
    std::getline(std::cin, val);
    return val;
}

int convertint(std::string num, int base = 10)
{
    int val = 0;
    int sgn = 1;
    if(base==10) {
        if(num[0]=='-'||num[0]=='+') {
            sgn = (num[0]=='-')?-1:1;
            num = num.substr(1);
        }
        for(var x : num) {
            if(x>'9' || x<'0') {
                return 0;
            }
            val *= 10;
            val += (x-'0');
        }
    } else if(base==16) {
        // todo
    }
    return val*sgn;
}

double convertdouble(std::string num)
{
    double val;
    int sgn = 1;
    if(num[0]=='-'||num[0]=='+') {
        sgn = (num[0]=='-')?-1:1;
        num = num.substr(1);
    }
    std::size_t ppos = num.find(".");
    if(ppos==-1) {
        return int(num)*sgn;
    } else {
        val = int(num.substr(0, ppos));
        std::string lp = num.substr(ppos+1);
        val += ((double)int(lp))/(pow(10,lp.length()));
    }
    return val*sgn;
}