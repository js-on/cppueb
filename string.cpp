#include <malloc.h>
#include "string.hpp"

/* Default constructor */
string::string()
{
    this->length = 0;
    this->content = (char *)malloc(sizeof(char));
    this->content[0] = '\0';
}

/* Default constructor with data */
string::string(const char *data)
{
    this->length = this->size(data);
    this->content = (char *)malloc(this->length * sizeof(char));
    for (int i = 0; i < this->length; i++)
    {
        this->content[i] = data[i];
    }
}

/* Calculate size of current string */
int string::size()
{
    int size = 0;
    while (this->content[size] != '\0')
        size++;
    return size;
}

/* Calculate size of submitted data */
int string::size(const char *data)
{
    int size = 0;
    while (data[size] != '\0')
        size++;
    return size;
}

/* Wrapper for print_via_syscall */
void string::print()
{
    char *copy = this->data();
    copy = (char*)realloc(copy, this->length+1);
    copy[this->length] = '\n';
    print_via_syscall(/*write*/ 1, /*fileno*/ 1, (long long)copy, (long long)this->length+1);
}

/* Copy data of string */
char* string::data() {
    return this->content;
}

/* Make chars accessible via index */
char string::operator[](const int pos) {
    if (pos < 0 || pos >= this->length) {
        // TODO: Raise IndexError
        return '\0';
    }
    return this->content[pos];
}

/* Return first position of char to find */
int string::find(const char c) {
    int size = 0;
    while (this->content[size] != '\0') {
        if (this->content[size] == c)
            return size;
        size++;
    }
    return -1;
}

/* Clear content of string */
void string::clear() {
    free(this->content);
    this->content = nullptr;
    this->length = 0;
}

/* Append string at the end of current string */
void string::append(const char* data) {
    int data_size = this->size(data);
    int subset = this->length;
    this->content = (char*)realloc(this->content, (data_size+subset+1)*sizeof(char));
    for (int i = 0; i < data_size; i++) {
        this->content[i+subset] = data[i];
    }
    this->length = this->size();
    this->content[this->length] = '\0';
}

string string::operator+(const string& right_string) {
    this->append(right_string.content);
    return *this;
}

/* Dtor */
string::~string()
{
    // free(): double free detected in tcache 2
    // 484424 Aborted (core dumped) ./main
    // free(this->content);
    // Therefore (not working either):
    // this->clear();
    free(this->content);
}

/* Inline assembly for printing the string 
   Stolen from gcc.gnu.org: https://gcc.gnu.org/bugzilla/attachment.cgi?id=33523
*/
long long string::print_via_syscall(long long syscall, long long arg0, long long arg1, long long arg2)
{
    register long long syscall_ __asm__("eax");
    register long long arg0_ __asm__("edi");
    register long long arg1_ __asm__("rsi");
    register long long arg2_ __asm__("edx");
    syscall_ = syscall;
    arg0_ = arg0;
    arg1_ = arg1;
    arg2_ = arg2;
    asm volatile(
        "syscall"
        : "+r"(syscall_)
        : "r"(arg0_), "r"(arg1_), "r"(arg2_)
        : "%rcx", "%r11", "memory");
    return syscall_;
}