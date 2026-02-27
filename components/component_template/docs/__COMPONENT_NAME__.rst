__COMPONENT_NAME__
==================

.. TODO: Kurzbeschreibung der Komponente (1–2 Sätze)

Übersicht
---------

.. TODO: Was macht diese Komponente? Welches Problem löst sie?

API
---

Initialisierung
~~~~~~~~~~~~~~~

.. code-block:: c

   struct __COMPONENT_NAME___dev dev;
   int ret = __COMPONENT_NAME___init(&dev);
   if (ret != 0) {
       /* Fehlerbehandlung */
   }

Funktionen
~~~~~~~~~~

.. TODO: Weitere Funktionen dokumentieren

Datenstrukturen
---------------

``__COMPONENT_NAME___dev``
~~~~~~~~~~~~~~~~~~~~~~~~~~

.. TODO: Felder beschreiben

Fehlerbehandlung
----------------

Alle Funktionen geben ``0`` bei Erfolg zurück.
Negative Werte entsprechen Zephyr-Fehlercodes (``-EINVAL``, ``-EIO``, …).

Abhängigkeiten
--------------

.. TODO: Benötigte Zephyr-Subsysteme / Kconfig-Optionen auflisten,
   z.B.:
   - ``CONFIG_I2C=y``
