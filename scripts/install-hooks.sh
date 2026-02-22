#!/usr/bin/env bash
#
# Installiert die Git-Hooks aus dem hooks/-Verzeichnis ins lokale .git/hooks/.
# Einmalig nach dem Klonen des Repos ausführen:
#
#   bash scripts/install-hooks.sh

set -euo pipefail

REPO_ROOT=$(git rev-parse --show-toplevel)
HOOKS_SRC="$REPO_ROOT/hooks"
HOOKS_DST="$REPO_ROOT/.git/hooks"

echo "Installiere Git-Hooks ..."

for HOOK in "$HOOKS_SRC"/*; do
    NAME=$(basename "$HOOK")
    DST="$HOOKS_DST/$NAME"

    cp "$HOOK" "$DST"
    chmod +x "$DST"
    echo "  ✓ $NAME"
done

echo ""
echo "Fertig. Hooks aktiv in: $HOOKS_DST"
