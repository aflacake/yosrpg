# YosRPG
Simple RPG game

## Instalation
Install the ninja path: https://www.msys2.org/, a classic MinGW-w64 trap on Windows

Steps:
- Install -> Next -> Next -> Finish
   `C:\msys64`, leave the default folder

Update the system:
- `pacman -Syu`
> If prompted to close -> close the terminal -> reopen -> repeat

Install the compiler:
- In MSYS
- `pacman -S mingw-w64-x86_64-gcc` or the full package: `pacman -S mingw-w64-x86_64-toolchain`

Find the application's output location in the root of the C:\msys64 folder:
- Also check: `C:\msys64\mingw64\bin`
- In that folder, there WILL be:
   - `g++.exe`
   - `gcc.exe`
   - `ld.exe`

`User variables for <username>`:
- Open Environment Variables
   - Win + Search -> type: Environment Variables
   - Select: Edit the system environment variables
   - Click the Environment Variables… button
- Click Edit for Path Variable -> Click **New**, then paste EXACTLY this:
   C:\msys64\mingw64\bin
   - OK -> OK -> OK

> MANDATORY: Close CMD / PowerShell
> (PATH is not active in an already open terminal)

Final step:
- `g++ --version`
If it appears, you're done.