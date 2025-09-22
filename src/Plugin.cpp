// Disable macro redefinition warning
#pragma warning(disable: 4005)

#include <Union/Hook.h>
#include <ZenGin/zGothicAPI.h>

#ifdef __G2A
#define GOTHIC_NAMESPACE Gothic_II_Addon
#define ENGINE Engine_G2A
HOOKSPACE(Gothic_II_Addon, GetGameVersion() == ENGINE);
#include "Sources.hpp"
#endif

HOOKSPACE(Global, true);
