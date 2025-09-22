#pragma once

#include <memory>
#include <string>
#include "IntelligentCompanion.h"

namespace IntelligentCompanion {

// Forward declarations
class CompanionAI;

// Companion states
enum class CompanionState {
    FOLLOWING,      // Following the player
    COMBAT          // In combat
};

// Main companion manager class
class CompanionManager {
public:
    CompanionManager();
    ~CompanionManager();

    // Initialize the companion system
    bool Initialize();
    
    // Create a new companion NPC
    bool CreateCompanion(const std::string& name);
    
    // Update companion AI
    void Update(float deltaTime);
    
    // Get companion instance
    std::shared_ptr<CompanionAI> GetCompanion() const { return companionAI_; }

private:
    std::shared_ptr<CompanionAI> companionAI_;
    bool isInitialized_;
    std::string companionName_;
};

// Companion AI class
class CompanionAI {
public:
    CompanionAI(const std::string& name);
    ~CompanionAI();

    // AI update loop
    void Update(float deltaTime);
    
    // State management
    void SetState(CompanionState newState);
    CompanionState GetState() const { return currentState_; }
    
    // Interaction with player
    void FollowPlayer();

private:
    std::string name_;
    CompanionState currentState_;
    
    // Player tracking
    oCNpc* playerInstance_;
    float followDistance_;
};

} // namespace IntelligentCompanion
