#include <windows.h>
#include <stdio.h>
#include <memory>

void ReadAndPrintC(LPSTR fileName){
    DWORD dwRead = 0;

    HANDLE hFile = CreateFileA(
        fileName, 
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );
    if(hFile != INVALID_HANDLE_VALUE){
        printf("Failed to open %s:%d\n", fileName, GetLastError());
        return;
    }
    LARGE_INTEGER lFileSize;
    BOOL bGetSize = GetFileSizeEx(hFile, &lFileSize);
    char * buffer = NULL;
    // Assume file is < 4gb
    buffer = (char*) malloc(lFileSize.LowPart + 1); // need space for the null byte!
    if(ReadFile(hFile, buffer, lFileSize.LowPart, &dwRead, NULL)){
        buffer[lFileSize.LowPart] = '\0';
        printf("Contents of %s:%d\n%s", fileName, dwRead, buffer);
    } else{
        printf("Failed to Read %s:%d\n", fileName, GetLastError());
    }
    free(buffer);
    return;
}

void ReadAndPrintCpp(LPSTR fileName){
    DWORD dwRead = 0;

    HANDLE hFile = ::CreateFileA(
        fileName, 
        GENERIC_READ,
        FILE_SHARE_READ,
        nullptr,
        OPEN_EXISTING,
        0,
        nullptr
    );
    if(hFile != INVALID_HANDLE_VALUE){
        printf("Failed to open %s:%d\n", fileName, ::GetLastError());
        return;
    }
    LARGE_INTEGER lFileSize;
    BOOL bGetSize = ::GetFileSizeEx(hFile, &lFileSize);
    char * buffer = nullptr;
    // Assume file is < 4gb
    buffer = new char[lFileSize.LowPart + 1];

    if(::ReadFile(hFile, buffer, lFileSize.LowPart, &dwRead, NULL)){
        buffer[lFileSize.LowPart] = '\0';
        printf("Contents of %s:%d\n%s", fileName, dwRead, buffer);
    } else{
        printf("Failed to Read %s:%d\n", fileName, ::GetLastError());
    }
    delete [] buffer;
    return;
}

void ReadAndPrintModernCpp(LPSTR fileName){
      DWORD dwRead = 0;

    HANDLE hFile = ::CreateFileA(
        fileName, 
        GENERIC_READ,
        FILE_SHARE_READ,
        nullptr,
        OPEN_EXISTING,
        0,
        nullptr
    );
    if(hFile != INVALID_HANDLE_VALUE){
        printf("Failed to open %s:%d\n", fileName, ::GetLastError());
        return;
    }
    LARGE_INTEGER lFileSize;
    BOOL bGetSize = ::GetFileSizeEx(hFile, &lFileSize);
    // Smart Pointer! Is automatically freed when it goes out of scope!
    auto buffer = std::make_unique<char[]>(lFileSize.LowPart + 1);

    if(::ReadFile(hFile, buffer.get(), lFileSize.LowPart, &dwRead, NULL)){
        buffer[lFileSize.LowPart] = '\0';
        printf("Contents of %s:%d\n%s", fileName, dwRead, buffer.get());
    } else{
        printf("Failed to Read %s:%d\n", fileName, ::GetLastError());
    }

    return;
}


int main(int argc, char* argv[]){
    if (argc<2){
        printf("Usage: %s file\n", argv[0]);
        return -1;
    }
    if (argc == 2){

    }
}