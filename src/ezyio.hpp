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
#define main() int main()
#define foreach(x, y, z) do { for (let y : x) { z; } } while(0)
#define func var

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

    // ------------------------- add operators -------------------------
    
    template<typename T>
    T operator+(T vl) {
        if (! is_type<T>()) {
            throw runtime_error("error : use of `+` operator between different variable types.");
        }
        return val<T>() + vl;
    }

    std::string operator+(std::string vl) {
        return vl + val();
    }

    std::string operator+(const char * vl) {
        return val() + vl;
    }

    template<typename T>
    var& operator+=(T vl) {
        ival = (*this) + vl;;
        return *this;
    }

    // ------------------------- subtract operators -------------------------

    template<typename T>
    T operator-(T vl) {
        if (! is_type<T>()) {
            throw runtime_error("error : use of `-` operator between different variable types.");
        }
        return val<T>() - vl;
    }

    template<typename T>
    var& operator-=(T vl) {
        ival = (*this) - vl;
        return *this;
    }

    // ------------------------- multiply operators -------------------------

    template<typename T>
    T operator*(T vl) {
        if (! is_type<T>()) {
            throw runtime_error("error : use of `*` operator between different variable types.");
        }
        return val<T>() * vl;
    }

    template<typename T>
    var& operator*=(T vl) {
        ival = (*this) * vl;
        return *this;
    }

    // ------------------------- divide operators -------------------------

    template<typename T>
    T operator/(T vl) {
        if (! is_type<T>()) {
            throw runtime_error("error : use of `/` operator between different variable types.");
        }
        return val<T>() / vl;
    }

    template<typename T>
    var& operator/=(T vl) {
        ival = (*this) / vl;
        return *this;
    }

    // ------------------------- boolean operators -------------------------

    template<typename T>
    bool operator==(T vl) {
        if (! is_type<T>() ) {
            return false;
        }
        return val<T>() == vl;
    }

    bool operator==(var& v) {
        return v.val() == val() && is_same_type(v);
    }

    bool operator!=(var& v) {
        return !(*this == v);
    }

    template<typename T>
    bool operator!=(T vl) {
        return !(*this == vl);
    }

    template<typename T>
    bool operator<(T vl) {
        if (! is_type<T>()) {
            throw runtime_error("error : use of `<` operator between different variable types.");
        }
        return val<T>() < vl;
    }

    bool operator<(var& b) {
        if (! is_same_type(b)) {
            throw runtime_error("error : use of `<` operator between different variable types.");
        }
        if (is_type<int>()) {
            return val<int>() < b.val<int>();
        } else if (is_type<bool>()) {
            return val<bool>() < b.val<bool>();
        } else if (is_type<unsigned int>()) {
            return val<unsigned int>() < b.val<unsigned int>();
        } else if (is_type<short>()) {
            return val<short>() < b.val<short>();
        } else if (is_type<unsigned short>()) {
            return val<unsigned short>() < b.val<unsigned short>();
        } else if (is_type<char *>() || is_type<const char*>() || is_type<string>()) {
            return val().length() < b.val().length();
        } else if (is_type<char>()) {
            return val<char>() < b.val<char>();
        } else if (is_type<double>()) {
            return val<double>() < b.val<double>();
        } else if (is_type<float>()) {
            return val<float>() < b.val<float>();
        } else if (is_type<long>()) {
            return val<long>() < b.val<long>();
        } else if (is_type<unsigned long>()) {
            return val<unsigned long>() < b.val<unsigned long>();
        } else {
            throw runtime_error("error: use of `<` operator between unknown / custom variable types.");
        }
    }

    template<typename T>
    bool is_less_than(var& b) {
        return val<T>() < b.val<T>();
    }

    template<typename T>
    bool is_less_than_as(var& b, T v) {
        return val<T>() < b.val<T>();
    }

    template<typename T>
    bool _not() {
        return !val<T>();
    }

    template<typename T>
    bool not_as(T v) {
        return !val<T>();
    }

    bool operator!() {
        if (is_type<int>()) {
            return !val<int>();
        } else if (is_type<unsigned int>()) {
            return !val<unsigned int>();
        } else if (is_type<bool>()) {
            return !val<bool>();
        } else if (is_type<long>()) {
            return !val<long>();
        } else if (is_type<unsigned long>()) {
            return !val<unsigned long>();
        } else if (is_type<char>()) {
            return !val<char>();
        } else if (is_type<char *>() || is_type<const char*>() || is_type<string>()) {
            return val() == "";
        } else if (is_type<float>()) {
            return !val<float>();
        } else if (is_type<double>()) {
            return !val<double>();
        } else if (is_type<short>()) {
            return !val<short>();
        } else if (is_type<unsigned short>()) {
            return !val<unsigned short>();
        }
        throw runtime_error("error: use of `!` operator on unknown / custom variable type.");
    }

    template<typename T>
    bool operator>(T vl) {
        if (! is_type<T>()) {
            throw runtime_error("error : use of `>` operator between different variable types.");
        }
        return val<T> > vl;
    }

    bool operator>(var& b) {
        if (! is_same_type(b)) {
            throw runtime_error("error : use of `>` operator between different variable types.");
        }
        if (is_type<int>()) {
            return val<int>() > b.val<int>();
        } else if (is_type<bool>()) {
            return val<bool>() > b.val<bool>();
        } else if (is_type<unsigned int>()) {
            return val<unsigned int>() > b.val<unsigned int>();
        } else if (is_type<short>()) {
            return val<short>() > b.val<short>();
        } else if (is_type<unsigned short>()) {
            return val<unsigned short>() > b.val<unsigned short>();
        } else if (is_type<char *>() || is_type<const char*>() || is_type<string>()) {
            return val().length() > b.val().length();
        } else if (is_type<char>()) {
            return val<char>() > b.val<char>();
        } else if (is_type<double>()) {
            return val<double>() > b.val<double>();
        } else if (is_type<float>()) {
            return val<float>() > b.val<float>();
        } else if (is_type<long>()) {
            return val<long>() > b.val<long>();
        } else if (is_type<unsigned long>()) {
            return val<unsigned long>() > b.val<unsigned long>();
        } else {
            throw runtime_error("error: use of `>` operator between unknown / custom variable types.");
        }
    }

    template<typename T>
    bool is_greater_than(var& b) {
        return val<T>() > b.val<T>();
    }

    template<typename T>
    bool is_greater_than_as(var& b, T v) {
        return val<T>() > b.val<T>();
    }

    // general get value
    template<typename T>
    T val()
    {
        return any_cast<T>(ival);
    }

    // ---------------- operator end ------------------

    // get value representation in string
    string val()
    {
        stringstream s;
        s << (*this);
        return s.str();
    }

    // get value as another type
    template<typename T>
    T val_as(T v)
    {
        return any_cast<T>(ival);
    }

    // typecheck
    template<typename T>
    bool is_type()
    {
        return ival.type()==typeid(T);
    }

    // typecheck
    template<typename T>
    bool is_same_type(T v)
    {
        return ival.type()==typeid(T);
    }

    bool is_same_type(var& v)
    {
        return ival.type()==v.ival.type();
    }

    // typename
    const char * type_name() {
        return ival.type().name();
    }
    
    // operators

    friend ostream& operator<<(ostream& os, var& l)
    {
        if( l.is_type<int>()) { os << l.val<int>(); }
        else if( l.is_type<unsigned int>() ) { os << l.val<unsigned int>(); } 
        else if( l.is_type<bool>()) { os << (l.val<bool>()?"true":"false"); }
        else if( l.is_type<char>() ) { os << l.val<char>(); }
        else if( l.is_type<string>() ) { os << l.val<string>(); }
        else if( l.is_type<char *>() ) { os << l.val<char *>(); }
        else if( l.is_type<const char *>() ) {os << l.val<const char*>(); }
        else if( l.is_type<long>() ) { os << l.val<long>(); }
        else if( l.is_type<unsigned long>() ) { os << l.val<unsigned long>(); }
        else if( l.is_type<float>() ) { os << l.val<float>(); }
        else if( l.is_type<double>() ) { os << l.val<double>(); }
        else if( l.is_type<short>() ) { os << l.val<short>(); }
        else if( l.is_type<unsigned short>() ) { os << l.val<unsigned short>(); }
        else {
            throw invalid_argument(
                "Type is not supported for operator `<<` , use `stream << var::val<type>()` instead."
            );
        }
        return os;
    }
};

template<typename T>
T operator-(T v, var& vl)
{
    return -(vl-v);
}

template<typename T>
T operator+(T v, var& vl)
{
    return vl+v;
}

std::string operator+(std::string v, var& vl)
{
    return v + vl.val();
}

std::string operator+(const char * v, var& vl)
{
    return v + vl.val();
}

void print_wn() {}
template<typename T, typename... TAIL>
void print_wn(const T &t, TAIL... tail)
{
    cout << t << print_sep;
    print_wn(tail...);
}

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

template <typename... TAIL>
void print(var &v, TAIL... tail)
{
    cout << v << print_sep;
    print(tail...);
}

void print(var &v) {
    cout << v << print_sep;
    print();
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

bool startswith(std::string base, std::string to_test) {
    return base.find(to_test) == 0;
}

bool endswith(std::string base, std::string to_test) {
    return (base.find(to_test) + to_test.length())==base.length();
}

int convertint(string num, int base = 10)
{
    int val = 0;
    int sgn = 1;
    if(num[0]=='-'||num[0]=='+') {
        sgn = (num[0]=='-')?-1:1;
        num = num.substr(1);
    }
    startdecode:
    if ( startswith(num, "0x") ) {
        num = num.substr(2);
        base = 16;
        goto startdecode;
    } else if ( startswith(num, "0b") ) {
        num = num.substr(2);
        base = 2;
        goto startdecode;
    } else if ( startswith(num, "0o") ) {
        num = num.substr(2);
        base = 8;
        goto startdecode;
    } else if(base==10) {
        for(let x : num) {
            if(x>'9' || x<'0') {
                return 0;
            }
            val *= 10;
            val += (x-'0');
        }
        return val * sgn;
    } else{
        return (int)stoul(num, nullptr, base) * sgn;
    }
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