# zephyr-pico-w-starter

Starter-Template für Zephyr RTOS auf dem Raspberry Pi Pico W (RP2040).  
Enthält eine interaktive USB-Shell sowie GPIO/I2C/SPI-Unterstützung, Debug-Konfiguration für Pico Probe (CMSIS-DAP) und eine vollständige VS Code-Entwicklungsumgebung.

> Dieses Repository ist das **west Manifest-Repo**. `west init -m` richtet den gesamten Workspace inklusive Zephyr und aller Module automatisch ein.

## Umgebung einrichten

Diese Anleitung beschreibt die vollständige Einrichtung der Entwicklungsumgebung unter **Linux / WSL2 (Ubuntu)**.

---

### 1. Systemabhängigkeiten installieren

```bash
sudo apt-get update
sudo apt-get install -y git cmake ninja-build gperf ccache dfu-util device-tree-compiler \
  wget python3-dev python3-pip python3-setuptools python3-tk python3-wheel xz-utils file \
  make gcc gcc-multilib g++-multilib libsdl2-dev libmagic1 libhidapi-hidraw0
```

---

### 2. West und Python-Umgebung einrichten

```bash
cd ~/zephyrproject
python3 -m venv .venv
source .venv/bin/activate
pip install west
```

---

### 3. Zephyr-Workspace initialisieren

Dieses Repo ist das West-Manifest-Repo. West klont Zephyr und alle benötigten Module automatisch:

```bash
# Workspace initialisieren und dieses Repo als Manifest verwenden
west init -m https://github.com/<dein-user>/zephyr-pico-w-starter ~/zephyrproject

# Alle Abhängigkeiten (Zephyr, HALs, Module) herunterladen
cd ~/zephyrproject
west update
west zephyr-export
pip install -r zephyr/scripts/requirements.txt
```

> **Hinweis:** Die resultierende Verzeichnisstruktur:
> ```
> ~/zephyrproject/
> ├── .venv/
> ├── .west/
> ├── zephyr/                    (ZEPHYR_BASE, von west geklont)
> ├── modules/                   (von west geklont)
> └── zephyr-pico-w-starter/     (dieses Repo = west Manifest)
> ```

---

### 4. Zephyr SDK installieren

Installation des Zephyr SDK über `west`:

```bash
cd ~/zephyrproject
source .venv/bin/activate
west sdk install
```

`west` lädt das passende Zephyr SDK herunter, installiert es und registriert die Toolchain für den Workspace.

> Optional (manuell): SDK-Tarball von `zephyrproject-rtos/sdk-ng` laden und `./setup.sh` ausführen.

---

### 5. VS Code Extensions installieren

Empfohlene Extensions sind in `.vscode/extensions.json` hinterlegt und werden von VS Code automatisch vorgeschlagen:

| Extension | ID |
|---|---|
| Cortex-Debug | `marus25.cortex-debug` |
| C/C++ | `ms-vscode.cpptools` |
| CMake Tools | `ms-vscode.cmake-tools` |
| Serial Monitor | `ms-vscode.vscode-serial-monitor` |
| Raspberry Pi Pico | `raspberry-pi.raspberry-pi-pico` |

---

### 6. Projekt bauen

VS Code **aus dem Projektverzeichnis** öffnen:

```bash
code ~/zephyrproject/zephyr-pico-w-starter
```

Dann **Strg+Shift+B** (Task: *Compile Project*). Die `.vscode/tasks.json` verwendet relative Pfade (`${workspaceFolder}/..`) und findet `west`, Zephyr und OpenOCD automatisch.

Alternativ direkt im Terminal:

```bash
cd ~/zephyrproject
source .venv/bin/activate

west build -p auto -b rpi_pico/rp2040/w \
  -d zephyr-pico-w-starter/build \
  zephyr-pico-w-starter \
  -S usb_serial_port \
  -- \
  -DOPENOCD=~/.pico-sdk/openocd/0.12.0+dev/openocd \
  -DOPENOCD_DEFAULT_PATH=~/.pico-sdk/openocd/0.12.0+dev/scripts
```

Bei einem korrupten Build-Cache (z. B. nach Pfadänderungen) hilft:

```bash
rm -rf zephyr-pico-w-starter/build
```

---

### 7. Firmware flashen

**Per UF2 (ohne Debug-Probe):** Pico W in Bootloader-Modus versetzen (BOOTSEL-Taste gedrückt halten beim Anschließen), dann `zephyr.uf2` aus `build/zephyr/` auf das Laufwerk kopieren.

**Per picotool:**

```bash
~/.pico-sdk/picotool/2.2.0-a4/picotool/picotool load build/zephyr/zephyr.elf -fx
```

In VS Code: Task *Run Project* (baut und flasht automatisch).

---

## Debugging in WSL2 mit Pico Probe (CMSIS-DAP)

### Voraussetzungen

- Windows mit [usbipd-win](https://github.com/dorssel/usbipd-win) installiert
- WSL2 (Ubuntu)
- VS Code mit Cortex-Debug Extension

---

### 1. Fehlende Systembibliothek installieren (einmalig)

OpenOCD benötigt `libhidapi-hidraw0`. In WSL2 ausführen:

```bash
sudo apt-get install -y libhidapi-hidraw0
```

Ohne diese Bibliothek schlägt OpenOCD mit folgendem Fehler fehl:

```
error while loading shared libraries: libhidapi-hidraw.so.0: cannot open shared object file: No such file or directory
```

---

### 2. Pico Probe per usbipd an WSL2 weiterleiten

USB-Geräte sind in WSL2 nicht automatisch verfügbar. Der Pico Probe muss jedes Mal nach dem Anschließen weitergeleitet werden.

#### 2.1 Verbundene USB-Geräte auf Windows anzeigen

PowerShell (als Administrator) auf Windows:

```powershell
usbipd list
```

Beispielausgabe:

```
BUSID  VID:PID    DEVICE                                          STATE
3-9    2e8a:000c  CMSIS-DAP v2 Interface, Serielles USB-Gerät    Not shared
```

#### 2.2 Pico Probe freigeben und an WSL2 anhängen

Einmalig binden (nur beim ersten Mal nötig):

```powershell
usbipd bind --busid 3-9
```

Jedes Mal nach dem Anschließen in WSL2 weiterleiten:

```powershell
usbipd attach --wsl --busid 3-9
```

> **Hinweis:** Die BUSID (`3-9`) kann je nach USB-Port variieren. Immer zuerst `usbipd list` ausführen um die aktuelle BUSID zu ermitteln.

#### 2.3 USB-Berechtigungen in WSL2 setzen

Da udevd in WSL2 nicht läuft, müssen die Berechtigungen manuell gesetzt werden:

```bash
sudo chmod a+rw $(lsusb | grep "2e8a" | sed "s/Bus \([0-9]*\) Device \([0-9]*\).*/\/dev\/bus\/usb\/\1\/\2/")
```

Um dies automatisch bei jedem WSL2-Start zu erledigen, folgende Zeile zur `~/.bashrc` hinzufügen:

```bash
echo 'sudo chmod a+rw $(lsusb | grep "2e8a" | sed "s/Bus \([0-9]*\) Device \([0-9]*\).*/\/dev\/bus\/usb\/\1\/\2/") 2>/dev/null' >> ~/.bashrc
```

### 3. Ablauf bei jeder Debug-Session

1. Pico Probe an USB anschließen
2. **Windows PowerShell (Admin):** `usbipd attach --wsl --busid <BUSID>`
3. **WSL2:** Neues Terminal öffnen (`.bashrc` setzt Berechtigungen automatisch)
4. Debug-Session in VS Code starten (F5)
