/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * component_a – Implementierung
 *
 * TODO: Modulbeschreibung ergänzen
 */

#include "component_a.h"

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(component_a, LOG_LEVEL_DBG);

/* -------------------------------------------------------------------------
 * Task-Ressourcen (privat – nicht im Header sichtbar)
 * ---------------------------------------------------------------------- */

K_THREAD_STACK_DEFINE(component_a_stack, COMPONENT_A_STACK_SIZE);
static struct k_thread component_a_thread;


/* -------------------------------------------------------------------------
 * Private Konstanten & Makros
 *
 * Hier kommen Konstanten, die NUR intern in dieser Datei gebraucht werden.
 * Sie sind mit "static" (bei Variablen) oder einfach durch ihre Position
 * (nur in dieser .c-Datei) von außen unsichtbar.
 *
 * Faustregel:
 *   Öffentlich (alle Nutzer brauchen es)  → in das .h-File
 *   Privat   (nur diese Datei braucht es) → hier im .c-File
 *
 * Beispiel:
 *   #define INIT_RETRY_COUNT  3
 *   #define REG_CTRL          0x20
 * ---------------------------------------------------------------------- */

/* -------------------------------------------------------------------------
 * Private Datenstrukturen & Typen
 *
 * Typen, die nur intern benötigt werden – nicht im Header deklariert.
 * So bleibt die öffentliche Schnittstelle schlank (Information Hiding).
 *
 * Beispiel für einen privaten Zustandsautomaten:
 *
 *   typedef enum {
 *       STATE_UNINIT = 0,
 *       STATE_IDLE,
 *       STATE_RUNNING,
 *   } component_a_state_t;
 *
 * Interne Felder dann in den Handle aufnehmen:
 *
 *   struct component_a_dev {
 *       component_a_state_t state;
 *       ...
 *   };
 *
 * Oder als rein lokale Variable im Task:
 *
 *   static component_a_state_t s_state = STATE_UNINIT;
 * ---------------------------------------------------------------------- */


/* -------------------------------------------------------------------------
 * Private Hilfsfunktionen
 * ---------------------------------------------------------------------- */

/* TODO: Private Funktionen hier */

/**
 * @brief Haupt-Loop des component_a Tasks.
 *
 * Diese Funktion läuft als eigenständiger Zephyr-Thread.
 * p1/p2/p3 sind optionale Parameter, die beim Start übergeben werden können.
 */
static void component_a_thread_fn(void *p1, void *p2, void *p3)
{
    struct component_a_dev *dev = (struct component_a_dev *)p1;

    ARG_UNUSED(p2);
    ARG_UNUSED(p3);

    LOG_INF("component_a Task gestartet");

    while (1) {
        /* TODO: periodische Aufgabe implementieren */
        component_a_do_something(dev);

        k_sleep(K_MSEC(100)); /* TODO: Zykluszeit anpassen */
    }
}

/* -------------------------------------------------------------------------
 * Öffentliche API
 * ---------------------------------------------------------------------- */

int component_a_init(struct component_a_dev *dev)
{
    if (dev == NULL) {
        return -EINVAL;
    }

    /* TODO: Initialisierung implementieren */

    LOG_INF("component_a initialisiert");
    return 0;
}

int component_a_start(struct component_a_dev *dev)
{
    if (dev == NULL) {
        return -EINVAL;
    }

    k_thread_create(&component_a_thread, component_a_stack,
                    K_THREAD_STACK_SIZEOF(component_a_stack), component_a_thread_fn,
                    dev, NULL, NULL, COMPONENT_A_PRIORITY, 0, K_NO_WAIT);

    k_thread_name_set(&component_a_thread, "component_a");

    LOG_INF("component_a Task erstellt");
    return 0;
}

int component_a_do_something(struct component_a_dev *dev)
{
    if (dev == NULL) {
        return -EINVAL;
    }

    /* TODO: Funktion implementieren */

    return 0;
}
