#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int app_start(void)
{
	LOG_INF("Anwendung gestartet");

	/* TODO: Komponenten initialisieren und Tasks starten, z.B.:
	 *
	 * static struct component_a_dev comp_a;
	 * static struct component_b_dev comp_b;
	 *
	 * int ret = component_a_init(&comp_a);
	 * if (ret != 0) {
	 *     LOG_ERR("component_a init fehlgeschlagen: %d", ret);
	 *     return ret;
	 * }
	 * component_a_start(&comp_a);
	 *
	 * ret = component_b_init(&comp_b);
	 * if (ret != 0) {
	 *     LOG_ERR("component_b init fehlgeschlagen: %d", ret);
	 *     return ret;
	 * }
	 * component_b_start(&comp_b);
	 */

	return 0;
}
