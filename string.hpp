#ifndef STRING_H_
#define STRING_H

class string
{
    private:
        int length;
        char* content;
        int size();
        int size(const char* data);
        long long print_via_syscall(long long syscallnum, long long arg0, long long arg1, long long arg2);
    
    public:
        string();
        string(const char* data);
        char operator[](const int pos);
        void append(const char* data);
        string operator+(const string& right_string);
        void print();
        char* data();
        int find(const char c);
        void clear();
        ~string();
};

#endif
