#include <windows.h>
#include <iostream>

// Prosty plugin bez Union API - tylko sprawdza czy się ładuje
extern "C" __declspec(dllexport) void InitializePlugin() {
    // Nie robimy nic - tylko sprawdzamy czy Union może załadować plugin
    OutputDebugStringA("[IntelligentCompanion] Plugin loaded successfully!\n");
}

extern "C" __declspec(dllexport) void UpdatePlugin(float deltaTime) {
    // Nie robimy nic
}

extern "C" __declspec(dllexport) void ShutdownPlugin() {
    // Nie robimy nic
    OutputDebugStringA("[IntelligentCompanion] Plugin unloaded!\n");
}
