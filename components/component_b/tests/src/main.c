/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * ztest Unit-Tests für component_b
 *
 * Werden mit Twister auf native_sim ausgeführt (kein Hardware nötig).
 * Aufruf:  west twister --testsuite-root components --platform native_sim
 */

#include <zephyr/ztest.h>

#include "component_b.h"

/* -------------------------------------------------------------------------
 * Test-Fixtures (optional)
 *
 * setup  – wird vor jedem Test ausgeführt
 * before – wird vor jeder Test-Suite ausgeführt
 * ---------------------------------------------------------------------- */

static struct component_b_dev test_dev;

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

ZTEST_SUITE(component_b, NULL, suite_setup, before_each, NULL, NULL);

/* -------------------------------------------------------------------------
 * Tests
 * ---------------------------------------------------------------------- */

/**
 * Init mit gültigem Handle muss 0 zurückgeben.
 */
ZTEST(component_b, test_init_valid)
{
    int ret = component_b_init(&test_dev);

    zassert_equal(ret, 0, "Init fehlgeschlagen: %d", ret);
}

/**
 * Init mit NULL-Pointer muss -EINVAL zurückgeben.
 */
ZTEST(component_b, test_init_null_pointer)
{
    int ret = component_b_init(NULL);

    zassert_equal(ret, -EINVAL, "Erwartet -EINVAL, erhalten: %d", ret);
}

/**
 * TODO: Weiteren Test hinzufügen
 *
 * ZTEST(component_b, test_mein_test)
 * {
 *     zassert_equal(erwartet, erhalten, "Fehlermeldung");
 * }
 */
