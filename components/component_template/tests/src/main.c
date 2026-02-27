/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * ztest Unit-Tests für __COMPONENT_NAME__
 *
 * Werden mit Twister auf native_sim ausgeführt (kein Hardware nötig).
 * Aufruf:  west twister --testsuite-root components --platform native_sim
 */

#include <zephyr/ztest.h>

#include "__COMPONENT_NAME__.h"

/* -------------------------------------------------------------------------
 * Test-Fixtures (optional)
 *
 * suite_setup  – wird einmalig vor der Test-Suite ausgeführt
 * before_each  – wird vor jedem Test ausgeführt
 * ---------------------------------------------------------------------- */

static struct __COMPONENT_NAME___dev test_dev;

static void *suite_setup(void)
{
	/* TODO: Gemeinsame Initialisierung für alle Tests */
	return NULL;
}

static void before_each(void *fixture)
{
	ARG_UNUSED(fixture);
	/* Frischen Handle für jeden Test vorbereiten */
	memset(&test_dev, 0, sizeof(test_dev));
}

ZTEST_SUITE(__COMPONENT_NAME__, NULL, suite_setup, before_each, NULL, NULL);

/* -------------------------------------------------------------------------
 * Tests
 * ---------------------------------------------------------------------- */

/**
 * Init mit gültigem Handle muss 0 zurückgeben.
 */
ZTEST(__COMPONENT_NAME__, test_init_valid)
{
	int ret = __COMPONENT_NAME___init(&test_dev);

	zassert_equal(ret, 0, "Init fehlgeschlagen: %d", ret);
}

/**
 * Init mit NULL-Pointer muss -EINVAL zurückgeben.
 */
ZTEST(__COMPONENT_NAME__, test_init_null_pointer)
{
	int ret = __COMPONENT_NAME___init(NULL);

	zassert_equal(ret, -EINVAL, "Erwartet -EINVAL, erhalten: %d", ret);
}

/**
 * TODO: Weiteren Test hinzufügen
 *
 * ZTEST(__COMPONENT_NAME__, test_mein_test)
 * {
 *     zassert_equal(erwartet, erhalten, "Fehlermeldung");
 * }
 */
