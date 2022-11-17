#pragma once
#include <iostream>
#include <type_traits>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

#define let auto
#define int(x) convertint(x)
#define float(x) (float)convertdouble(x)
#define double(x) convertdouble(x)

std::string print_sep = " ";
std::string print_end = "\n";

class var {
    any ival;
    public:
    var(){};
    var(any v):ival(v){};
    var(int v):ival(v){};
    var(char v):ival(v){};
    var(string v):ival(v){};
    var(float v):ival(v){};
    var(double v):ival(v){};
    var(bool v):ival(v){};
    var(char * v):ival(v){};
    var(const char * v):ival(v){};
    var(long v):ival(v){};
    var(unsigned long v):ival(v){};
    var(unsigned int v):ival(v){};

    // general constructor
    template<typename T>
    var(T v):ival(v){};

    var& operator=(var& v){ival = v.ival; return *this;}
    var& operator=(any v){ival = v; return *this;};

    // general get value
    template<typename T>
    T val()
    {
        return any_cast<T>(ival);
    }

    // get value representation in string
    string val()
    {
        stringstream s;
        s << (*this);
        return s.str();
    }

    // typecheck
    template<typename T>
    bool is_type(T)
    {
        return ival.type()==typeid(T);
    }

    // typename
    const char * type_name() {
        return ival.type().name();
    }
    
    // operators

    friend ostream& operator<<(ostream& s, const var& l)
    {
        stringstream os;
        if(l.ival.type()==typeid(int)) { os << any_cast<int>(l.ival); }
        else if(l.ival.type()==typeid(unsigned int)) { os << any_cast<unsigned int>(l.ival); } 
        else if(l.ival.type()==typeid(bool)) { os << (any_cast<bool>(l.ival)?"true":"false"); }
        else if(l.ival.type()==typeid(char)) { os << any_cast<char>(l.ival); }
        else if(l.ival.type()==typeid(string)) { os << any_cast<string>(l.ival); }
        else if(l.ival.type()==typeid(char *)) { os << any_cast<char *>(l.ival); }
        else if(l.ival.type()==typeid(const char *)) {os << any_cast<const char*>(l.ival); }
        else if(l.ival.type()==typeid(long)) { os << any_cast<long>(l.ival); }
        else if(l.ival.type()==typeid(unsigned long)) { os << any_cast<unsigned long>(l.ival); }
        else if(l.ival.type()==typeid(float)) { os << any_cast<float>(l.ival); }
        else if(l.ival.type()==typeid(double)) { os << any_cast<double>(l.ival); }
        else {
            throw invalid_argument(
                "Type is not supported for operator `<<` , use `stream << var::val<type>()` instead."
            );
        }
        s << os.str();
        return s;
    }
};

/// prints given content. Syntax : print(smth, smth2, smth3, ...);
void print()
{
    cout << print_end;
}

template <typename T, typename... TAIL>
void print(const T &t, TAIL... tail)
{
    cout << t << print_sep;
    print(tail...);
}

void print(var& v) {
    cout << v << print_sep << print_end;
}

template <typename T, typename... TAIL>
void print(const var& v, TAIL... tail)
{
    cout << v << print_sep;
    print(tail...);
}

template <typename T>
string str(T v)
{
    stringstream s;
    s << v;
    return s.str();
}

void print_r(void){return;}
template <typename T, typename... TAIL>
void print_r(const T &t, TAIL... tail)
{
    cout << t;
    print_r(tail...);
}

template <typename T, size_t size>
void print_arr(const T(&t)[size], string sep = ", ", string end = "\n", bool braces = true)
{
    cout << (braces ? "{" : "");
    bool done = false;
    for (T v: t) {
        if (is_same<T,string>::value || is_same<T,char *>::value || is_same<T,const char*>::value)
            cout << (done?sep:"") << '"' << v << '"';
        else
            cout << (done?sep:"") << v;
        done = true;
    }
    cout << (braces ? "}" : "") << end;
}

template <typename T>
void print_arr(vector<T> t, string sep = ", ", string end = "\n", bool braces = true)
{
    cout << (braces ? "{" : "");
    bool done = false;
    for (T v: t) {
        if (is_same<T,string>::value || is_same<T,char *>::value || is_same<T,const char*>::value)
            cout << (done?sep:"") << '"' << v << '"';
        else
            cout << (done?sep:"") << v;
        done = true;
    }
    cout << (braces ? "}" : "") << end;
}

/// inputs to a letiable, Syntax : input(let1, let2, let3, ...);
template <typename T>
T input(string prompt = "")
{
    T v;
    cout << prompt;
    cin >> v;
    return v;
}

template <typename T, typename... TAIL>
T dyn_input(T v, TAIL... tail)
{
    v = input<T>(tail...);
    return v;
}

string operator * (string val, size_t s) {
    string ret;
    while(s--)
        ret += val;
    return ret;
}

string operator * (size_t s, string val) {
    return val * s;
}

vector<int> range(int mnmax = 0, int max = 0, int step = 1)
{
    vector<int> v;
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
string bin(int num, bool standard = true)
{
    string ret;
    bool ng = num < 0;
    num = abs(num);
    do { ret += '0'+num%2; } while ( num >>= 1 );
    reverse(ret.begin(), ret.end());
    ret = (ng ? "-": "") + (standard ? "0b" + ret: ret);
    return ret;
}

// integer to hex converter
string hex(int num, bool standard = true)
{
    string ret;
    string htable = "0123456789abcdef";
    bool ng = num < 0;
    num = abs(num);
    do { ret += htable[num%16]; } while ( num >>=4 );
    reverse(ret.begin(),ret.end());
    ret = (ng ? "-": "") + (standard ? "0x" + ret: ret);
    return ret;
}

string oct(int num, bool standard = true)
{
    string ret;
    bool ng = num < 0;
    num = abs(num);
    do { ret += '0'+(num%8); } while ( num >>=3 );
    reverse(ret.begin(),ret.end());
    ret = (ng ? "-": "") + (standard ? "0o" + ret: ret);
    return ret;
}

string input(string prompt = "")
{
    string val;
    cout << prompt;
    getline(cin, val);
    return val;
}

int convertint(string num, int base = 10)
{
    int val = 0;
    int sgn = 1;
    if(base==10) {
        if(num[0]=='-'||num[0]=='+') {
            sgn = (num[0]=='-')?-1:1;
            num = num.substr(1);
        }
        for(let x : num) {
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

int convertint(double val)
{
    return (int)val;
}

double convertdouble(string num)
{
    double val;
    int sgn = 1;
    if(num[0]=='-'||num[0]=='+') {
        sgn = (num[0]=='-')?-1:1;
        num = num.substr(1);
    }
    size_t ppos = num.find(".");
    if(ppos==-1) {
        return int(num)*sgn;
    } else {
        val = int(num.substr(0, ppos));
        string lp = num.substr(ppos+1);
        val += ((double)int(lp))/(pow(10,lp.length()));
    }
    return val*sgn;
}