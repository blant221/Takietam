// This file is included separately for each engine version

namespace GOTHIC_NAMESPACE 
{
	// Global variables for companion management
	oCNpc* g_companion = nullptr;
	oCNpc* g_player = nullptr;
	bool g_companionCreated = false;

	void Game_LoadBegin_NewGame()
	{
		// Called when new game starts loading
		OutputDebugStringA("[IntelligentCompanion] New game loading started\n");
	}

	void Game_LoadEnd_NewGame()
	{
		// Get player instance
		oCGame* game = oCGame::GetGame();
		if (!game) {
			OutputDebugStringA("[IntelligentCompanion] Failed to get game instance!\n");
			return;
		}

		g_player = game->GetSelfPlayerVob();
		if (!g_player) {
			OutputDebugStringA("[IntelligentCompanion] Failed to get player instance!\n");
			return;
		}

		// Get object factory
		oCObjectFactory* factory = oCObjectFactory::GetInstance();
		if (!factory) {
			OutputDebugStringA("[IntelligentCompanion] Failed to get object factory!\n");
			return;
		}

		// Try to get PC_HERO prototype ID
		int heroPrototypeId = -1;
		zCParser* parser = zCParser::GetParser();
		if (parser) {
			heroPrototypeId = parser->GetPrototype("PC_HERO", 0);
			if (heroPrototypeId == -1) {
				// Fallback to HumanS if PC_HERO not found
				heroPrototypeId = parser->GetPrototype("HumanS", 0);
				OutputDebugStringA("[IntelligentCompanion] PC_HERO not found, using HumanS as fallback\n");
			}
		}

		if (heroPrototypeId == -1) {
			OutputDebugStringA("[IntelligentCompanion] Failed to get prototype ID!\n");
			return;
		}

		// Create companion NPC
		g_companion = factory->CreateNpc(heroPrototypeId);
		if (!g_companion) {
			OutputDebugStringA("[IntelligentCompanion] Failed to create companion NPC!\n");
			return;
		}

		// Set companion position near player
		zVEC3 playerPos = g_player->GetPositionWorld();
		playerPos.x += 100.0f; // Offset to the right
		g_companion->SetPositionWorld(playerPos);

		// Enable the companion
		g_companion->Enable(TRUE);

		// Add to world
		oCWorld* world = game->GetGameWorld();
		if (world) {
			world->InsertVobInWorld(g_companion);
			OutputDebugStringA("[IntelligentCompanion] Companion created and added to world!\n");
			g_companionCreated = true;
		} else {
			OutputDebugStringA("[IntelligentCompanion] Failed to get game world!\n");
		}
	}

	void Game_Loop()
	{
		// Update companion AI if it exists
		if (g_companionCreated && g_companion && g_player) {
			// Simple follow behavior - move towards player
			zVEC3 playerPos = g_player->GetPositionWorld();
			zVEC3 companionPos = g_companion->GetPositionWorld();
			
			zVEC3 direction = playerPos - companionPos;
			float distance = direction.Length();
			
			// If too far, move closer
			if (distance > 200.0f) {
				direction.Normalize();
				zVEC3 newPos = companionPos + direction * 50.0f;
				g_companion->SetPositionWorld(newPos);
			}
		}
	}

	void Game_Exit()
	{
		// Cleanup
		if (g_companion) {
			g_companion = nullptr;
		}
		g_player = nullptr;
		g_companionCreated = false;
		OutputDebugStringA("[IntelligentCompanion] Plugin cleanup completed\n");
	}

	// Hook for Game_LoadEnd_NewGame
	void __fastcall oCGame_LoadGame(oCGame* self, void* vtable, int slot, const zSTRING& levelPath);
	auto Hook_oCGame_LoadGame = Union::CreateHook(reinterpret_cast<void*>(zSwitch(0x0063C070, 0x00662B20, 0x00669970, 0x006C65A0)), &oCGame_LoadGame, Union::HookType::Hook_Detours);
	void __fastcall oCGame_LoadGame(oCGame* self, void* vtable, int slot, const zSTRING& levelPath)
	{
		Game_LoadBegin_NewGame();
		Hook_oCGame_LoadGame(self, vtable, slot, levelPath);
		Game_LoadEnd_NewGame();
	}

	// Hook for Game_Loop
	void __fastcall oCGame_MainWorld_Render(Union::Registers& reg);
	auto Partial_zCWorld_Render = Union::CreatePartialHook(reinterpret_cast<void*>(zSwitch(0x0063DC76, 0x0066498B, 0x0066BA76, 0x006C87EB)), &oCGame_MainWorld_Render);
	void __fastcall oCGame_MainWorld_Render(Union::Registers& reg)
	{
		Game_Loop();
	}
}
