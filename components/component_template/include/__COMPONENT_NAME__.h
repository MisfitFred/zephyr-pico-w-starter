/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * __COMPONENT_NAME__ – Öffentliche Schnittstelle
 *
 * TODO: Modulbeschreibung ergänzen
 */

#ifndef __COMPONENT_NAME_UPPER___H
#define __COMPONENT_NAME_UPPER___H

#include <stdint.h>
#include <zephyr/kernel.h>

/* -------------------------------------------------------------------------
 * Konstanten & Makros
 *
 * Öffentliche Konstanten, die für ALLE Nutzer der Komponente sichtbar sind.
 *
 * Wann #define, wann enum?
 *   - #define  → einzelne Zahlenwerte, Bitmasken, Standardwerte
 *   - enum     → zusammengehörige Zustände/Fehlercodes (Typ-sicher, debugbar)
 *
 * Beispiel:
 *   #define __COMPONENT_NAME_UPPER___TIMEOUT_MS  500
 *
 *   typedef enum {
 *       __COMPONENT_NAME_UPPER___STATE_IDLE = 0,
 *       __COMPONENT_NAME_UPPER___STATE_BUSY,
 *       __COMPONENT_NAME_UPPER___STATE_ERROR,
 *   } __COMPONENT_NAME___state_t;
 * ---------------------------------------------------------------------- */

/** Stack-Größe des __COMPONENT_NAME__ Tasks in Byte – bei Bedarf anpassen */
#define __COMPONENT_NAME_UPPER___STACK_SIZE 1024

/** Thread-Priorität (kooperativ: negativ, preemptiv: 0–CONFIG_NUM_PREEMPT_PRIORITIES-1) */
#define __COMPONENT_NAME_UPPER___PRIORITY 5

/* -------------------------------------------------------------------------
 * Typen & Datenstrukturen
 *
 * Typen, die in der öffentlichen API verwendet werden.
 *
 * Typische Muster in C:
 *   typedef struct { ... } my_t;   → kompakter Typ-Alias, kein "struct" beim Benutzen
 *   typedef enum  { ... } my_e;   → Aufzählungstyp
 *   typedef uint8_t my_id_t;      → semantischer Alias für einfache Typen
 *
 * Zephyr-Konvention:
 *   Für Geräte-Handles wird meist kein typedef verwendet ("struct x_dev *"),
 *   damit der Pointer-Charakter im Code sichtbar bleibt.
 * ---------------------------------------------------------------------- */

/**
 * @brief Geräte-Handle für __COMPONENT_NAME__.
 *
 * Wird beim Init befüllt und bei jedem Funktionsaufruf übergeben.
 */
struct __COMPONENT_NAME___dev {
	/* TODO: Felder ergänzen */
	int placeholder;
};

/* -------------------------------------------------------------------------
 * Öffentliche Funktionen
 * ---------------------------------------------------------------------- */

/**
 * @brief Initialisiert __COMPONENT_NAME__.
 *
 * @param dev  Zu befüllender Handle
 * @return 0 bei Erfolg, negativer Fehlercode sonst
 */
int __COMPONENT_NAME___init(struct __COMPONENT_NAME___dev *dev);

/**
 * @brief Startet den __COMPONENT_NAME__ Task.
 *
 * Muss nach __COMPONENT_NAME___init() aufgerufen werden.
 * Der Task läuft dann dauerhaft in __COMPONENT_NAME___thread_fn().
 *
 * @param dev  Initialisierter Handle
 * @return 0 bei Erfolg, negativer Fehlercode sonst
 */
int __COMPONENT_NAME___start(struct __COMPONENT_NAME___dev *dev);

/**
 * @brief TODO: Funktion beschreiben.
 *
 * @param dev  Initialisierter Handle
 * @return 0 bei Erfolg, negativer Fehlercode sonst
 */
int __COMPONENT_NAME___do_something(struct __COMPONENT_NAME___dev *dev);

#endif /* __COMPONENT_NAME_UPPER___H */
