@echo off
echo Usage:
echo  Generate 1.htb and 1.stb first using JtagController: run
echo.
@echo on
profiler.exe -hz 199800000 -dis C:\Users\KimSH\Desktop\Release\cpu0_vf.dis -htb C:\Users\KimSH\Documents\Visual Studio 2013\Projects\HTB\HTB\cpu0.htb -o output.prf
pause



