#include "IntelligentCompanion.h"
#include <iostream>
#include <windows.h>

namespace IntelligentCompanion {

// Global companion manager instance
static std::unique_ptr<CompanionManager> g_companionManager;

// Initialize the plugin
extern "C" __declspec(dllexport) void InitializePlugin() {
    std::cout << "[IntelligentCompanion] Plugin initializing..." << std::endl;
    
    // Create companion manager
    g_companionManager = std::make_unique<CompanionManager>();
    
    if (!g_companionManager->Initialize()) {
        std::cout << "[IntelligentCompanion] Failed to initialize manager!" << std::endl;
        return;
    }
    
    // Create companion NPC
    if (!g_companionManager->CreateCompanion("Companion")) {
        std::cout << "[IntelligentCompanion] Failed to create companion!" << std::endl;
        return;
    }
    
    std::cout << "[IntelligentCompanion] Plugin initialized successfully!" << std::endl;
}

// Update the plugin (called every frame)
extern "C" __declspec(dllexport) void UpdatePlugin(float deltaTime) {
    if (g_companionManager) {
        g_companionManager->Update(deltaTime);
    }
}

// Cleanup the plugin
extern "C" __declspec(dllexport) void ShutdownPlugin() {
    std::cout << "[IntelligentCompanion] Plugin shutting down..." << std::endl;
    g_companionManager.reset();
    std::cout << "[IntelligentCompanion] Plugin shutdown complete!" << std::endl;
}

} // namespace IntelligentCompanion
