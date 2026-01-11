# setup simulide:

## 0. Prerequisite:
- *Before install simulide, you must have installed the tools. See [setup tools](./1-setup-tools.md).*

---

## 1. Download and install SimulIDE:
- Download SimulIDE from [SimulIDE download page](https://simulide.com/p/downloads/).
  - Select `Last Stable Version`, and select `Operating System` to be `Windows 64` for Windows and `MacOs x86` for macOS.
  - You may put in **`0`** as the donation amount. Then click `Download`.

- **macOS:** unzip the download and drag `simulide` to your `Applications` folder.

- **Windows:** unzip the download. Rename the folder from `SimulIDE_1.1.x...` to `simulide`. There's no installer for Windows. Change `NAME` to your *username* below:

  - Put `simulide` folder in: `C:\Users\NAME\Documents` so this file exists:
  
    `C:\Users\NAME\Documents\simulide\simulide.exe`

  - Go into `C:\Users\NAME\Documents\simulide\` folder, right click on `simulide.exe` and select `Pin to Start`

---

## 2. Set class subcircuits

- Launch `simulide`. It will probably not run the first time.

- **Windows:** You may get a prompt that `simulide` is a software downloaded from the internet. *Allow* it to run.

- **macOS:** Go to `System Settings` → `Privacy & Security` → scroll to bottom, you will see:
  > ```
  > "simulide" was blocked to protect your Mac
  > ```
  - Click `Open Anyway`. Provide *TouchID* or *password* to allow it.
  - It may prompt:
    > ```
    > To open this app, you need to install Rosetta. Do you want to install it now?
    > ```

    Make sure you install *Rosetta*. `simulide` needs it.

- Start `simulide`. You will get the main window that looks like this:

  ![simulide main window](./pix/2-simulide-window1.png)

---

- **(1 in picture above)** Click the `⚙ gear icon` on the top left (to the right of `Search Components` box
- **(2 in picture above)** *Settings window* will appear. Select `App` tab. On the bottom there is:
  > ```
  > User Data folder:
  > <blank>            [ ... ]
  > ```
  - Click the `...` button and choose folder: `Documents/BareMetal-C-Labs/sim/subcircuits/`
  - **macOS:** While still in *Settings window*, click `Circuit` and check `☑ Show ScrollBars` 
- Close `simulide` and restart it.
- **1.** On leftmost side, select `Components` tab, a column on components will show, starting from `Meters`, `Sources`, etc.
- **2.** Scroll down all the way to the bottom, you should see `BMC Subcircuits` and `BMC Subblocks`. These are the design used for our class.

  See picture below:

  ![simulide main window](./pix/2-simulide-window2.png)

- You can close `simulide` now. It's ready for use.
 
---

# 3. Test that subcircuit is set correctly

- Run `simulide` and click `Open Circuit`
  
  ![open circuit](./pix/4-open-circuit.png)

- Choose `Documents/BareMetal-C/sim/05_freq_8MHz.sim1`
- The following picture should show up. *Note the area in red rectangle.*

  ![full circuit](./pix/4-full-circuit.png)

## Troubleshooting:

The cause for missing circuit in the red rectangle above is not setting `User Data Folder` (subcircuits) correctly. Go back to [the previous section](#2-set-class-subcircuits) and fix it.

---

## 4. Set up Visual Studio Code (VS Code)

Goto [set up VS Code](./3-setup-vs-code.md).

---

Go back to [home page](../README.md)
