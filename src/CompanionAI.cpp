#include "IntelligentCompanion.h"
#include <iostream>

namespace IntelligentCompanion {

// CompanionManager implementation
CompanionManager::CompanionManager() 
    : isInitialized_(false) {
}

CompanionManager::~CompanionManager() {
}

bool CompanionManager::Initialize() {
    if (isInitialized_) {
        return true;
    }

    isInitialized_ = true;
    std::cout << "[IntelligentCompanion] Manager initialized successfully" << std::endl;
    return true;
}

bool CompanionManager::CreateCompanion(const std::string& name) {
    if (!isInitialized_) {
        std::cout << "[IntelligentCompanion] Manager not initialized!" << std::endl;
        return false;
    }

    companionName_ = name;
    
    // Create companion AI
    companionAI_ = std::make_shared<CompanionAI>(name);
    
    std::cout << "[IntelligentCompanion] Created companion: " << name << std::endl;
    
    return true;
}

void CompanionManager::Update(float deltaTime) {
    if (!companionAI_) {
        return;
    }

    // Update companion AI
    companionAI_->Update(deltaTime);
}

// CompanionAI implementation
CompanionAI::CompanionAI(const std::string& name)
    : name_(name), currentState_(CompanionState::FOLLOWING),
      playerInstance_(nullptr), followDistance_(300.0f) {
    
    std::cout << "[CompanionAI] Created AI for: " << name << std::endl;
}

CompanionAI::~CompanionAI() {
}

void CompanionAI::Update(float deltaTime) {
    // Update based on current state
    switch (currentState_) {
        case CompanionState::FOLLOWING:
            FollowPlayer();
            break;
        case CompanionState::COMBAT:
            // Basic combat - just follow player
            FollowPlayer();
            break;
    }
}

void CompanionAI::SetState(CompanionState newState) {
    if (currentState_ != newState) {
        std::cout << "[CompanionAI] State changed from " << static_cast<int>(currentState_) 
                  << " to " << static_cast<int>(newState) << std::endl;
        currentState_ = newState;
    }
}

void CompanionAI::FollowPlayer() {
    // Basic following logic - in real implementation this would
    // use Gothic's AI functions to make NPC follow the player
    std::cout << "[CompanionAI] Following player..." << std::endl;
}

} // namespace IntelligentCompanion
