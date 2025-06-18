#include <tchar.h>
#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include <system_error>
#include "../include/core/WinRarConfig.hpp"
#include "../include/core/WinRarKeygen.hpp"

void Help() {
    _putts(TEXT("WinRAR Registration Key Generator\n"));
    _putts(TEXT("Usage:"));
    _putts(TEXT("    winrar-keygen.exe <Username> <License Type>"));
    _putts(TEXT("\nParameters:"));
    _putts(TEXT("    Username     - The name to register WinRAR under"));
    _putts(TEXT("    License Type - The type of license to generate"));
    _putts(TEXT("\nExample:"));
    _putts(TEXT("    winrar-keygen.exe \"John Doe\" \"Single PC usage license\"\n"));
    _putts(TEXT("Note: Both parameters must be enclosed in quotes if they contain spaces\n"));
}

void PrintRegisterInfo(const WinRarKeygen<WinRarConfig>::RegisterInfo& Info) {
    try {
        if (Info.UserName.empty() || Info.LicenseType.empty()) {
            throw std::invalid_argument("Invalid registration info: Username or License Type is empty");
        }

        _tprintf_s(TEXT("%hs\n"), "RAR registration data");
        _tprintf_s(TEXT("%hs\n"), Info.UserName.c_str());
        _tprintf_s(TEXT("%hs\n"), Info.LicenseType.c_str());
        _tprintf_s(TEXT("UID=%hs\n"), Info.UID.c_str());
        
        // Print hex data in chunks of 54 characters for readability
        for (size_t i = 0; i < Info.HexData.length(); i += 54) {
            _tprintf_s(TEXT("%.54hs\n"), Info.HexData.c_str() + i);
        }
    } catch (const std::exception& e) {
        _tprintf_s(TEXT("Error printing registration info: %hs\n"), e.what());
        throw;
    }
}

std::string ToACP(PCWSTR lpszUnicodeString) {
    if (!lpszUnicodeString) {
        throw std::invalid_argument("Input string cannot be null");
    }

    const int len = WideCharToMultiByte(CP_ACP, 0, lpszUnicodeString, -1, nullptr, 0, nullptr, nullptr);
    if (len == 0) {
        throw std::system_error(GetLastError(), std::system_category(), "Failed to determine required buffer size");
    }

    std::string result(len - 1, '\0'); // -1 because len includes null terminator
    
    if (WideCharToMultiByte(CP_ACP, 0, lpszUnicodeString, -1, result.data(), len, nullptr, nullptr) == 0) {
        throw std::system_error(GetLastError(), std::system_category(), "Failed to convert string");
    }

    return result;
}

int _tmain(int argc, PTSTR argv[]) {
    try {
        // Set locale for proper character encoding handling
        if (setlocale(LC_ALL, "") == nullptr) {
            _tprintf_s(TEXT("Warning: Failed to set locale\n"));
        }

        if (argc == 3) {
            try {
                PrintRegisterInfo(
#if defined(_UNICODE) || defined(UNICODE)
                    WinRarKeygen<WinRarConfig>::GenerateRegisterInfo(ToACP(argv[1]).c_str(), ToACP(argv[2]).c_str())
#else
                    WinRarKeygen<WinRarConfig>::GenerateRegisterInfo(argv[1], argv[2])
#endif
                );
            } catch (const std::exception& e) {
                _tprintf_s(TEXT("Error generating registration info: %hs\n"), e.what());
                return 1;
            }
        } else {
            Help();
            return argc == 1 ? 0 : 1; // Return 0 if no args, 1 if wrong number of args
        }
        return 0;
    } catch (const std::exception& e) {
        _tprintf_s(TEXT("Fatal error: %hs\n"), e.what());
        return 2;
    }
}
