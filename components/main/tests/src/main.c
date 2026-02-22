#include <zephyr/ztest.h>

#include "app_start.h"

ZTEST_SUITE(main_component, NULL, NULL, NULL, NULL, NULL);

ZTEST(main_component, test_app_start_returns_success)
{
	int ret = app_start();

	zassert_equal(ret, 0, "app_start fehlgeschlagen: %d", ret);
}
