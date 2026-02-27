#!/usr/bin/env bash
# =============================================================================
# new_component.sh – Neue Komponente aus component_template ableiten
#
# Verwendung:
#   cd components/component_template
#   ./new_component.sh
#
# Das Skript:
#   1. Fragt nach dem Namen der neuen Komponente (z.B. "sensor_bme280")
#   2. Legt components/<name>/ an (Kopie dieses Templates)
#   3. Benennt alle Dateien um, die "__COMPONENT_NAME__" im Namen tragen
#   4. Ersetzt alle Vorkommen von "__COMPONENT_NAME__" in Dateiinhalten
#   5. Ersetzt "__COMPONENT_NAME_UPPER___H" durch den korrekten Include-Guard
#   6. Gibt Hinweise aus, was noch manuell ergänzt werden muss
# =============================================================================

set -euo pipefail

# -----------------------------------------------------------------------------
# Hilfsfunktionen
# -----------------------------------------------------------------------------

red()    { printf '\033[0;31m%s\033[0m\n' "$*"; }
green()  { printf '\033[0;32m%s\033[0m\n' "$*"; }
yellow() { printf '\033[0;33m%s\033[0m\n' "$*"; }
bold()   { printf '\033[1m%s\033[0m\n' "$*"; }

die() {
    red "Fehler: $*"
    exit 1
}

# -----------------------------------------------------------------------------
# Sicherstellen, dass das Skript aus dem richtigen Verzeichnis gestartet wird
# -----------------------------------------------------------------------------

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TEMPLATE_DIR="$SCRIPT_DIR"
COMPONENTS_DIR="$(dirname "$TEMPLATE_DIR")"
PROJECT_ROOT="$(dirname "$COMPONENTS_DIR")"

if [[ "$(basename "$TEMPLATE_DIR")" != "component_template" ]]; then
    die "Dieses Skript muss aus components/component_template/ aufgerufen werden."
fi

# -----------------------------------------------------------------------------
# Eingabe: Name der neuen Komponente
# -----------------------------------------------------------------------------

bold "=== Neue Zephyr-Komponente erstellen ==="
echo ""
echo "Der Name wird als Bezeichner in C-Code, Dateinamen und CMake verwendet."
echo "Erlaubt: Kleinbuchstaben, Ziffern, Unterstriche (z.B. sensor_bme280, my_driver)"
echo ""

while true; do
    read -rp "Name der neuen Komponente: " COMPONENT_NAME

    # Validierung: nur lowercase letters, digits, underscores; nicht leer
    if [[ -z "$COMPONENT_NAME" ]]; then
        yellow "Name darf nicht leer sein. Bitte erneut eingeben."
        continue
    fi

    if [[ ! "$COMPONENT_NAME" =~ ^[a-z][a-z0-9_]*$ ]]; then
        yellow "Ungültiger Name '$COMPONENT_NAME'."
        yellow "Erlaubt: Kleinbuchstaben, Ziffern, Unterstriche; muss mit Buchstabe beginnen."
        continue
    fi

    if [[ "$COMPONENT_NAME" == "component_template" ]]; then
        yellow "Der Name 'component_template' ist reserviert. Bitte einen anderen Namen wählen."
        continue
    fi

    TARGET_DIR="$COMPONENTS_DIR/$COMPONENT_NAME"

    if [[ -d "$TARGET_DIR" ]]; then
        yellow "Verzeichnis '$TARGET_DIR' existiert bereits."
        read -rp "Überschreiben? [j/N] " OVERWRITE
        if [[ "${OVERWRITE,,}" != "j" ]]; then
            continue
        fi
        rm -rf "$TARGET_DIR"
    fi

    break
done

# Abgeleitete Namen
COMPONENT_UPPER="${COMPONENT_NAME^^}"   # z.B. SENSOR_BME280
INCLUDE_GUARD="${COMPONENT_UPPER}_H"    # z.B. SENSOR_BME280_H

echo ""
echo "  Komponentenname : $COMPONENT_NAME"
echo "  Präfix (Makros) : ${COMPONENT_UPPER}_"
echo "  Include-Guard   : $INCLUDE_GUARD"
echo "  Zielverzeichnis : $TARGET_DIR"
echo ""
read -rp "Fortfahren? [J/n] " CONFIRM
if [[ "${CONFIRM,,}" == "n" ]]; then
    echo "Abgebrochen."
    exit 0
fi

# -----------------------------------------------------------------------------
# Schritt 1: Template-Verzeichnis kopieren (ohne das Skript selbst)
# -----------------------------------------------------------------------------

echo ""
bold "Schritt 1/4: Verzeichnis kopieren …"

cp -r "$TEMPLATE_DIR" "$TARGET_DIR"

# Skript nicht in neue Komponente übernehmen
rm -f "$TARGET_DIR/new_component.sh"

green "  OK: $TARGET_DIR angelegt"

# -----------------------------------------------------------------------------
# Schritt 2: Dateien mit __COMPONENT_NAME__ im Dateinamen umbenennen
# -----------------------------------------------------------------------------

echo ""
bold "Schritt 2/4: Dateien umbenennen …"

# Alle Dateien finden, die "__COMPONENT_NAME__" im Namen tragen
# (tiefenrekursiv, damit include/, src/, docs/, tests/src/ alle erfasst werden)
while IFS= read -r -d '' OLD_PATH; do
    DIR="$(dirname "$OLD_PATH")"
    OLD_BASENAME="$(basename "$OLD_PATH")"
    NEW_BASENAME="${OLD_BASENAME//__COMPONENT_NAME__/$COMPONENT_NAME}"

    if [[ "$OLD_BASENAME" != "$NEW_BASENAME" ]]; then
        mv "$OLD_PATH" "$DIR/$NEW_BASENAME"
        echo "  $OLD_BASENAME → $NEW_BASENAME"
    fi
done < <(find "$TARGET_DIR" -name '*__COMPONENT_NAME__*' -print0)

green "  OK: Dateinamen aktualisiert"

# -----------------------------------------------------------------------------
# Schritt 3: __COMPONENT_NAME__ in Dateiinhalten ersetzen
# -----------------------------------------------------------------------------

echo ""
bold "Schritt 3/4: Platzhalter in Dateiinhalten ersetzen …"

# Alle Textdateien im neuen Verzeichnis durchgehen
while IFS= read -r -d '' FILE; do
    # Binärdateien überspringen
    if ! file --mime "$FILE" | grep -q "text/"; then
        continue
    fi

    # Reihenfolge ist wichtig: spezifischere Token zuerst ersetzen.

    # 1. Uppercase-Token für Makros und Include-Guard
    #    __COMPONENT_NAME_UPPER__ → MY_SENSOR  (z.B. in #define MY_SENSOR_STACK_SIZE)
    sed -i "s/__COMPONENT_NAME_UPPER__/${COMPONENT_UPPER}/g" "$FILE"

    # 2. Lowercase-Token für Funktionen, Structs, Dateinamen, Log-Module
    #    __COMPONENT_NAME__ → my_sensor
    sed -i "s/__COMPONENT_NAME__/${COMPONENT_NAME}/g" "$FILE"

    echo "  $(realpath --relative-to="$TARGET_DIR" "$FILE")"
done < <(find "$TARGET_DIR" -type f -print0)

green "  OK: Platzhalter ersetzt"

# -----------------------------------------------------------------------------
# Schritt 4: Hinweise zur manuellen Integration
# -----------------------------------------------------------------------------

echo ""
bold "Schritt 4/4: Manuelle Schritte (bitte ergänzen) …"

CMAKELIST_ROOT="$PROJECT_ROOT/CMakeLists.txt"
MAIN_CMAKELISTS="$PROJECT_ROOT/components/main/CMakeLists.txt"

echo ""
yellow "  a) Root CMakeLists.txt ($CMAKELIST_ROOT)"
echo "     Zeile ergänzen:"
echo "       add_subdirectory(components/$COMPONENT_NAME)"
echo ""
yellow "  b) Main-Komponente ($MAIN_CMAKELISTS)"
echo "     In target_link_libraries() ergänzen:"
echo "       target_link_libraries(app PRIVATE … $COMPONENT_NAME)"
echo ""
yellow "  c) Implementierung befüllen:"
echo "     $TARGET_DIR/src/$COMPONENT_NAME.c   → TODO-Kommentare ausfüllen"
echo "     $TARGET_DIR/include/$COMPONENT_NAME.h → Typen / API ergänzen"
echo "     $TARGET_DIR/docs/$COMPONENT_NAME.rst  → Dokumentation schreiben"
echo "     $TARGET_DIR/tests/src/main.c          → Tests ergänzen"
echo ""

green "=== Fertig! Neue Komponente '$COMPONENT_NAME' wurde erstellt. ==="
echo ""
echo "Verzeichnis: $TARGET_DIR"
echo ""
