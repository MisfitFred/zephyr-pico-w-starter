/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Einstiegspunkt der Anwendung.
 *
 * Jede Komponente wird initialisiert und ihr Task gestartet.
 * main() kehrt danach zurück – die Tasks laufen eigenständig weiter.
 *
 * TODO: Eigene Komponenten einbinden und hier starten.
 */

#include "app_start.h"

/* TODO: Eigene Header einbinden, z.B.:
 * #include "component_a.h"
 * #include "component_b.h"
 */

int main(void)
{
	return app_start();
}
