# Intelligent Companion - Gothic II Plugin

Podstawowy plugin Union dla Gothic II: Noc Kruka, który tworzy NPC towarzysza podążającego za graczem.

## Funkcjonalności

- **Podstawowy NPC** - tworzy towarzysza na początku gry
- **Podążanie za graczem** - NPC automatycznie podąża za głównym bohaterem
- **Prosty system AI** - podstawowe stany zachowania

## Instalacja

1. **Zbuduj plugin:**
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

2. **Plugin zostanie automatycznie skopiowany** do katalogu Gothic II/system/autorun/

3. **Uruchom Gothic II** - plugin załaduje się automatycznie

## Struktura projektu

```
IntelligentCompanion/
├── CMakeLists.txt              # Konfiguracja CMake
├── src/
│   ├── IntelligentCompanion.h  # Nagłówek z klasami
│   ├── CompanionAI.cpp         # Implementacja AI NPC
│   └── IntelligentCompanion.cpp # Główny plik pluginu
└── README.md                   # Ten plik
```

## Użycie

Plugin automatycznie:
- Tworzy NPC o nazwie "Companion" na początku gry
- Ustawia NPC w stanie FOLLOWING (podążanie)
- Aktualizuje AI co klatkę

## Rozwój

Ten plugin to podstawa do dalszego rozwoju. Można dodać:
- System poziomowania
- Inteligentny wybór profesji
- Automatyczną naukę
- Dialogi i interakcje
- Zaawansowane zachowania w walce

## Wymagania

- Gothic II: Noc Kruka
- Union Framework
- Visual Studio 2022 (zalecane)
- CMake 3.20+
