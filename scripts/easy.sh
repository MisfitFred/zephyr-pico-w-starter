#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
WORKSPACE_DIR="$(cd "${PROJECT_DIR}/.." && pwd)"

WEST_BIN="${WORKSPACE_DIR}/.venv/bin/west"
ZEPHYR_BASE_DIR="${WORKSPACE_DIR}/zephyr"
BUILD_DIR="${PROJECT_DIR}/build"
BOARD="rpi_pico/rp2040/w"
SNIPPET="usb_serial_port"
OPENOCD_BIN="${HOME}/.pico-sdk/openocd/0.12.0+dev/openocd"
OPENOCD_SCRIPTS="${HOME}/.pico-sdk/openocd/0.12.0+dev/scripts"
PICOTOOL_BIN="${HOME}/.pico-sdk/picotool/2.2.0-a4/picotool/picotool"

usage() {
    cat <<EOF
Einfaches Zephyr-Helferskript

Aufruf:
  ./scripts/easy.sh <befehl>

Befehle:
  build     Projekt bauen (beim ersten Mal automatisch mit Board/Snippet)
  rebuild   Vollständig neu konfigurieren und bauen
  test      Alle Twister-Tests ausführen
  flash     Firmware mit west flash auf das Board übertragen
  run       Firmware mit picotool laden (zephyr.elf)
  help      Diese Hilfe anzeigen
EOF
}

require_west() {
    if [[ ! -x "${WEST_BIN}" ]]; then
        echo "Fehler: west nicht gefunden unter ${WEST_BIN}" >&2
        echo "Bitte zuerst die Umgebung einrichten (README: .venv + west)." >&2
        exit 1
    fi
}

require_picotool() {
    if [[ ! -x "${PICOTOOL_BIN}" ]]; then
        echo "Fehler: picotool nicht gefunden unter ${PICOTOOL_BIN}" >&2
        exit 1
    fi
}

west_cmd() {
    (
        cd "${WORKSPACE_DIR}"
        ZEPHYR_BASE="${ZEPHYR_BASE_DIR}" "${WEST_BIN}" "$@"
    )
}

build_first_time() {
    west_cmd build -p auto -b "${BOARD}" -d "${BUILD_DIR}" "${PROJECT_DIR}" -S "${SNIPPET}" -- \
        -DOPENOCD="${OPENOCD_BIN}" \
        -DOPENOCD_DEFAULT_PATH="${OPENOCD_SCRIPTS}"
}

build_incremental() {
    west_cmd build -d "${BUILD_DIR}"
}

cmd="${1:-help}"

case "${cmd}" in
build)
    require_west
    if [[ -f "${BUILD_DIR}/CMakeCache.txt" ]]; then
        build_incremental
    else
        build_first_time
    fi
    ;;
rebuild)
    require_west
    build_first_time
    ;;
test)
    require_west
    west_cmd twister -T "${PROJECT_DIR}"
    ;;
flash)
    require_west
    west_cmd flash --build-dir "${BUILD_DIR}"
    ;;
run)
    require_picotool
    "${PICOTOOL_BIN}" load "${BUILD_DIR}/zephyr/zephyr.elf" -fx
    ;;
help|-h|--help)
    usage
    ;;
*)
    echo "Unbekannter Befehl: ${cmd}" >&2
    echo
    usage
    exit 1
    ;;
esac
