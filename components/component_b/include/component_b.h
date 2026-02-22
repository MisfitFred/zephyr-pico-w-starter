/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * component_b – Öffentliche Schnittstelle
 *
 * TODO: Modulbeschreibung ergänzen
 */

#ifndef COMPONENT_B_H
#define COMPONENT_B_H

/* Include-Guard, um Mehrfacheinbindung zu verhindern, Name entsprechend anpassen */

#include <stdint.h>
#include <zephyr/kernel.h>

/* -------------------------------------------------------------------------
 * Konstanten & Makros
 *
 * Hier kommen Konstanten und Makros, die für ALLE Nutzer der Komponente
 * sichtbar sein sollen (öffentliche API).
 *
 * Wann #define, wann enum?
 *   - #define  → einzelne Zahlenwerte, Bitmasken, Standardwerte
 *   - enum     → zusammengehörige Zustände/Fehlercodes (Typ-sicher, debugbar)
 *
 * Beispiel:
 *   #define COMPONENT_B_TIMEOUT_MS  500
 *
 *   typedef enum {
 *       COMPONENT_B_STATE_IDLE = 0,
 *       COMPONENT_B_STATE_BUSY,
 *       COMPONENT_B_STATE_ERROR,
 *   } component_b_state_t;
 * ---------------------------------------------------------------------- */

/** Stack-Größe des component_b Tasks in Byte – bei Bedarf anpassen */
#define COMPONENT_B_STACK_SIZE 1024

/** Thread-Priorität (kooperativ: negativ, preemptiv: 0–CONFIG_NUM_PREEMPT_PRIORITIES-1) */
#define COMPONENT_B_PRIORITY 5

/* -------------------------------------------------------------------------
 * Typen & Datenstrukturen
 *
 * Hier kommen Typen, die in der öffentlichen API verwendet werden.
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
 * @brief Geräte-Handle für component_b.
 *
 * Wird beim Init befüllt und bei jedem Funktionsaufruf übergeben.
 */
struct component_b_dev {
	/* TODO: Felder ergänzen */
	int placeholder;
};

/* -------------------------------------------------------------------------
 * Öffentliche Funktionen
 * ---------------------------------------------------------------------- */

/**
 * @brief Initialisiert component_b.
 *
 * @param dev  Zu befüllender Handle
 * @return 0 bei Erfolg, negativer Fehlercode sonst
 */
int component_b_init(struct component_b_dev *dev);

/**
 * @brief Startet den component_b Task.
 *
 * Muss nach component_b_init() aufgerufen werden.
 * Der Task läuft dann dauerhaft in component_b_thread_fn().
 *
 * @param dev  Initialisierter Handle
 * @return 0 bei Erfolg, negativer Fehlercode sonst
 */
int component_b_start(struct component_b_dev *dev);

/**
 * @brief TODO: Funktion beschreiben.
 *
 * @param dev  Initialisierter Handle
 * @return 0 bei Erfolg, negativer Fehlercode sonst
 */
int component_b_do_something(struct component_b_dev *dev);

#endif /* COMPONENT_B_H */
