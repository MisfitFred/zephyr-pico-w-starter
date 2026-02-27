/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * __COMPONENT_NAME__ – Implementierung
 *
 * TODO: Modulbeschreibung ergänzen
 */

#include "__COMPONENT_NAME__.h"

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(__COMPONENT_NAME__, LOG_LEVEL_DBG);

/* -------------------------------------------------------------------------
 * Task-Ressourcen (privat – nicht im Header sichtbar)
 * ---------------------------------------------------------------------- */

K_THREAD_STACK_DEFINE(__COMPONENT_NAME___stack, __COMPONENT_NAME_UPPER___STACK_SIZE);
static struct k_thread __COMPONENT_NAME___thread;

/* -------------------------------------------------------------------------
 * Private Konstanten & Makros
 *
 * Konstanten, die NUR intern in dieser Datei gebraucht werden.
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
 *   } __COMPONENT_NAME___state_t;
 * ---------------------------------------------------------------------- */

/* -------------------------------------------------------------------------
 * Private Hilfsfunktionen
 * ---------------------------------------------------------------------- */

/* TODO: Private Funktionen hier */

/**
 * @brief Haupt-Loop des __COMPONENT_NAME__ Tasks.
 *
 * Diese Funktion läuft als eigenständiger Zephyr-Thread.
 * p1/p2/p3 sind optionale Parameter, die beim Start übergeben werden können.
 */
static void __COMPONENT_NAME___thread_fn(void *p1, void *p2, void *p3)
{
	struct __COMPONENT_NAME___dev *dev = (struct __COMPONENT_NAME___dev *)p1;

	ARG_UNUSED(p2);
	ARG_UNUSED(p3);

	LOG_INF("__COMPONENT_NAME__ Task gestartet");

	while (1) {
		/* TODO: periodische Aufgabe implementieren */
		__COMPONENT_NAME___do_something(dev);

		k_sleep(K_MSEC(100)); /* TODO: Zykluszeit anpassen */
	}
}

/* -------------------------------------------------------------------------
 * Öffentliche API
 * ---------------------------------------------------------------------- */

int __COMPONENT_NAME___init(struct __COMPONENT_NAME___dev *dev)
{
	if (dev == NULL) {
		return -EINVAL;
	}

	/* TODO: Initialisierung implementieren */

	LOG_INF("__COMPONENT_NAME__ initialisiert");
	return 0;
}

int __COMPONENT_NAME___start(struct __COMPONENT_NAME___dev *dev)
{
	if (dev == NULL) {
		return -EINVAL;
	}

	k_thread_create(&__COMPONENT_NAME___thread, __COMPONENT_NAME___stack,
	                K_THREAD_STACK_SIZEOF(__COMPONENT_NAME___stack),
	                __COMPONENT_NAME___thread_fn, dev, NULL,
	                NULL, __COMPONENT_NAME_UPPER___PRIORITY, 0, K_NO_WAIT);

	k_thread_name_set(&__COMPONENT_NAME___thread, "__COMPONENT_NAME__");

	LOG_INF("__COMPONENT_NAME__ Task erstellt");
	return 0;
}

int __COMPONENT_NAME___do_something(struct __COMPONENT_NAME___dev *dev)
{
	if (dev == NULL) {
		return -EINVAL;
	}

	/* TODO: Funktion implementieren */

	return 0;
}
