#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#define PASSWORD "ABCD1234!"
/*You need not worry about other include statements if at all any are missing */

void func1()
{
    char * data;
    // alloca gets memory allocated on stack frame of function
    char * dataBuffer = (char *)alloca(100*sizeof(char));
    memset(dataBuffer, 'A', 100-1);
    dataBuffer[100-1] = '\0';
    data = dataBuffer - 8;
    // This kind of code is very dangerous, which can potentially overwrite return address of func1()
    // and can lead to undefined behaviour or possible source for security exploits.
    // For example consider a upward growing stack where return address is just placed before dataBuffer
    // and since strcpy does not check lengths around source and destination pointer here it will overwrite
    // memory of 8 bytes just before dataBuffer.
    // So in general strcpy() combined with stack/heap memory pointers are considered bad code.
    {
        char source[100];
        memset(source, 'C', 100-1); 
        source[100-1] = '\0'; 
        strcpy(data, source);
        if(data != NULL) 
        {
            printf("%s\n", data);
        }
    }
}

void func2()
{
    char * data;
    data = NULL;
    data = (char *)calloc(100, sizeof(char));
    // strcpy() function is considered unsafe as it does not take size of destination array
    // and if larger source string is tried to be copied to small destination buffer then it 
    // may lead to undefined behaviour.
    strcpy(data, "A String");
    if(data != NULL) 
    {
        printf("%s\n", data);
    }
    // memory pointer by data should be deleted before 
    // stack variable data gets deleted once func2() returns.
    // So this is memory leak and it can cause various issues.
}

void func3()
{
    char * password;
    char passwordBuffer[100] = "";
    password = passwordBuffer;
    strcpy(password, PASSWORD);
    // strcpy() with stack or heap memory can cause overflow attacks as they do not take size of dest memory.
    // even strncpy() has takes n bytes of source, but if first n bytes of source does not have NULL character
    // then dest will also not be null terminated string and which is door to vulnerabilities.
    // safe is to use strlcpy which ensures destination string is null terminated.
    {
        HANDLE pHandle;
        char * username = "User";
        char * domain = "Domain";
        /* Let's say LogonUserA is a custom authentication function*/
        if (LogonUserA(
                    username,
                    domain,
                    password,
                    &pHandle) != 0)
        {
            printf("User logged in successfully.\n");
            CloseHandle(pHandle);
        }
        else
        {
            printf("Unable to login.\n");
        }
    }
}


static void func4()
{
    char * data;
    data = NULL;
    data = (char *)calloc(20, sizeof(char));
    if (data != NULL)
    {
        // strcpy() function is considered unsafe as it does not take size of destination array
        // and if larger source string is tried to be copied to small destination buffer then it 
        // may lead to undefined behaviour or even heap buffer overflow attacks.
        // better is to use strlcpy()
        strcpy(data, "Initialize");
        if(data != NULL) 
        {
            printf("%s\n", data);
        }
        free(data);
    }
}

void func5() 
{
    // This loop is infinite loop with given condition.
    // If the intention is to print values from 0 to 255 inclusive
    // condition should be do {...} while(i > 0);
    // This kind of infinite loop can cause DoS attacks or take up too much resources of
    // server and make it crash. 
    int i = 0;
    do
    {
        printf("%d\n", i);
        i = (i + 1) % 256;
    } while(i >= 0);
}

void func6()
{
    char dataBuffer[100] = "";
    char * data = dataBuffer;
    printf("Please enter a string: ");
     // Using fgets() is certainly better than gets() as it takes size as parameters
    // but if programmer makes mistake specifying it then it can still lead to buffer overflows.
    // so better way is fgets(data, sizeof(dataBuffer), stdin) == NULL.

    // This is incorrect way to check if fgets() has failed or not.
    // when it fails it returns NULL and sets ferror.
    // following condition should be fgets(data,...) == NULL
    if (fgets(data, 100, stdin) < 0) 
    {
        printf("fgets failed!\n");
        exit(1);
    }
    if(data != NULL) 
    {
        printf("%s\n", data);
    }

}

void func7()
{
    char * data;
    data = "Fortify";
    data = NULL;
    // Trying to print from NULL is undefined
    // so it could lead to program crash or any other kind of unexpected behaviour.
    // Its better to always check if pointer is not pointing to NULL before printing from it.
    printf("%s\n", data);
}

int main(int argc, char * argv[])
{
    printf("Calling func1\n");
    func1();

    printf("Calling func2\n");
    func2();

    printf("Calling func3\n");
    func3();

    printf("Calling func4\n");
    func4();

    printf("Calling func5\n");
    func5();

    printf("Calling func6\n");
    func6();

    printf("Calling func7\n");
    func7();

    return 0;
}
