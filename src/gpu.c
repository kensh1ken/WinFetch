#include <stdio.h>
#include <windows.h>
#define BtoGiB (1024*1024*1024)

char* gpuName() {
    HKEY hKey;
    LPCSTR gpuPath = "SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e968-e325-11ce-bfc1-08002be10318}\\0000";
    static char gpuName[256];
    DWORD nameSize = sizeof(gpuName);

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, gpuPath, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        
        if (RegQueryValueExA(hKey, "DriverDesc", NULL, NULL, (LPBYTE)gpuName, &nameSize) != ERROR_SUCCESS) {
            printf("Couldn't get GPU name. Check ./src/gpu.c");
            exit(1);
        }

        RegCloseKey(hKey);
        return gpuName;
    }
}


float vramSpecs(){
    HKEY hKey;
    LPCSTR gpuPath = "SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e968-e325-11ce-bfc1-08002be10318}\\0000";
    unsigned long long vramBytes = 0;
    DWORD vramSize = sizeof(vramBytes);

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, gpuPath, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        if (RegQueryValueExA(hKey, "HardwareInformation.qwMemorySize", NULL, NULL, (LPBYTE)&vramBytes, &vramSize) != ERROR_SUCCESS) {
            printf("Error finding VRAM. Check ./src/gpu.c");
        }
        RegCloseKey(hKey);
        return ((float)vramBytes / BtoGiB);
    }
}

