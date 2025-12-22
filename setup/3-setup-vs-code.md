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
3.  Follow the prompts. **Important:** On the "Select Additional Tasks" screen, check all 4 boxes. The last box says: **"Add to PATH (requires shell restart)"**.

    ![VS Code Setup Additional Tasks](./pix/3-code-00-win.png)
5.  Click **Install**.

### For macOS
1.  Download the **macOS Universal build** from the official website: [code.visualstudio.com](https://code.visualstudio.com/).
2.  Open the downloaded zip file.
3.  Drag the `Visual Studio Code.app` into your **Applications** folder.
4.  Launch VS Code.
5.  (Optional but Recommended) Open the Command Palette (`Cmd+Shift+P`), type `Shell Command: Install 'code' command in PATH`, and press Enter.

---

## Part 2: Open the Project

1.  Launch **VS Code**.
2.  CLick on the `Explorer` icon.

    ![Explorer](./pix/3-code-02.png)
3.  Click **Open Folder**.

    ![Open Folder](./pix/3-code-03.png)
4.  Select `BareMetal-C` folder:

    **Windows:**

    ![Windows Folder Selection](./pix/3-code-04-win.png)

    **macOS:**

    ![macOS Folder Selection](./pix/3-code-04-mac-small.png)

    Give permission to Visual Studio Code to access your `Documents` folder:

    ![macOS Allow Access to Documents](./pix/3-code-05-mac.png)
    
6.  Click **Yes, I trust the authors**.

    ![trust the authors](./pix/3-code-06.png)
    
7.  Install the recommended `C/C++ Extension`.

    ![install c extension](./pix/3-code-07.png)

8.  **Add `baremetal-c-builder` extension to VS Code:**

    Click on the `Extensions` icon:

    ![extension icon](./pix/3-code-07.1.png)

    Use **Windows File Explorer** or **macOS Finder**, go to `Documents/BareMetal-C/_vscode_extensions` folder.

    Drag file `baremetal-c-builder-0.X.X.vsix` (`X.X` may change) to the *extension area*:

    ![extension area](./pix/3-code-07.2.png)

    Close VS Code. Reopen it. Click the `Extensions` icon again. Now `BareMetal-C-Builder` Extension should show up:

    ![extension shown](./pix/3-code-07.3.png)
    
---

## Part 3: Running the Build Environment

1. Click `Explorer` icon to go back to folder explorer. Then right click on `code` folder:

   ![right click code](./pix/3-code-07.4.png)

2. A context menu opens up, choose `Build BareMetal-C All (Recursive)`

   ![build all](./pix/3-code-07.5.png)

   A lot of text will be printed in the `terminal`, but eventually, you should have all projects built. Look for `(TIME) ------ built PROJECT_NAME.bin -------` like this:

   ![build successful](./pix/3-code-07.6.png)

   **If you got this far, your installation is successful.**

3. Let's try clean up. Right click on folder `code` again, but this time, choose `Clean BareMetal-C All (Recursive)` and you should see `terminal` with the text `(TIME) -------- clean successful --------`

   ![clean successful](./pix/3-code-07.7.png)

---

We will use the **right click on a folder** to `build` and `clean` our programming projects. More instructions later!
