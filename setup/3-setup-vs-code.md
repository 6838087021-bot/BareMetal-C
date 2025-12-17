# to be tested

# VS Code & Build Environment Setup Guide

This guide will help you set up Visual Studio Code (VS Code) and configure it to work with your Docker-based build environment.

## Part 0: Prerequisites: Tools and SimulIDE installation

Before setting up VS Code, ensure the tools (which includes Docker Desktop) and SimulIDE are installed and running, as the sidecar depends on it.

1. Follow instructions to installing tools → [here](./1-setup-tools.md).
2. Follow instructions to install SimulIDE → [here](./2-setup-simulide.md).

---

## Part 1: Install Visual Studio Code

### For Windows
1.  Download the **Windows installer** from the official website: [code.visualstudio.com](https://code.visualstudio.com/).
2.  Run the installer (`VSCodeUserSetup-{version}.exe`).
3.  Follow the prompts. **Important:** On the "Select Additional Tasks" screen, check the box that says **"Add to PATH (requires shell restart)"**.
4.  Click **Install**.

### For macOS
1.  Download the **macOS Universal build** from the official website: [code.visualstudio.com](https://code.visualstudio.com/).
2.  Open the downloaded zip file.
3.  Drag the `Visual Studio Code.app` into your **Applications** folder.
4.  Launch VS Code.
5.  (Optional but Recommended) Open the Command Palette (`Cmd+Shift+P`), type `Shell Command: Install 'code' command in PATH`, and press Enter.

---

## Part 2: Open the Project

1.  Launch **VS Code**.
2.  Go to **File > Open Folder...** (Windows) or **File > Open...** (macOS).
3.  Navigate to the folder where you cloned the instructor's repository.
4.  Click **Select Folder** (or Open).

---

## Part 3: Running the Build Environment

We will use the Integrated Terminal in VS Code to launch the Docker container. This container acts as your "Sidecar" compilation tool.

### Step 1: Open the Integrated Terminal
1.  In the top menu bar, go to **Terminal > New Terminal**.
2.  A terminal window will appear at the bottom of the screen.

### Step 2: Load the Build Tools
Copy and paste the following command into the terminal to start the container.

**Note for Windows Users:** Ensure your terminal is set to **PowerShell** (the default) or Git Bash. Do not use Command Prompt (cmd), as the `${PWD}` syntax may differ.

```bash
docker run --name baremetal-c --rm -it -v ${PWD}:/labs kongkrit/baremetal-c
```

**What this command does:**

  - `--rm`: Automatically removes the container when you exit, keeping your system clean.
  - `-it`: Interactive mode (gives you a command prompt inside the container).
  - `-v ${PWD}:/labs`: Maps your current project folder to the `/labs` folder inside the container. This allows the container to see your code.

### Step 3: Build the Project
Once you run the command above, your terminal prompt will change to
> ```
> [baremetal-c]:/labs #
> ```
, indicating you are now *inside* the Docker container.

1. To build your project, simply type:
   ```Bash
   make
   ```
2. If the build is successful, the output files (executables/binaries) will appear in your project folder.
3. **Do not run the output in VS Code.** The final build result is intended for the **Simulide** simulator.

### Step 4: Exiting
When you are finished building, type `exit` to close the Docker container and return to your local terminal.

---

## Optional: Configure an Automated Build Task
If you do not want to copy-paste the Docker command every time, you can set up a VS Code Task.

1. Create a folder named `.vscode` in the root of your project (if it doesn't exist).
2. Inside that folder, create a file named `tasks.json`.
3. Paste the following content into `tasks.json`:
   ```
   {
       "version": "2.0.0",
       "tasks": [
           {
               "label": "Build with Docker",
               "type": "shell",
               "command": "docker run --name baremetal-c --rm -v \"${workspaceFolder}:/labs\" kongkrit/baremetal-c make",
               "group": {
                   "kind": "build",
                   "isDefault": true
               },
               "problemMatcher": []
           }
       ]
   }
   ```
**How to use:**
- Press `Ctrl+Shift+B` (Windows) or `Cmd+Shift+B` (macOS).
- VS Code will automatically spin up the container, run `make`, and show you the output, then close the container.
