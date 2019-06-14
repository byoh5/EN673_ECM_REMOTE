@echo off
echo Usage:
echo  Generate 1.htb and 1.stb first using JtagController: run
echo.
@echo on
profiler.exe -hz 199800000 -dis D:\virtualbox_share\rc016\180917\output\module\cpu1_vf.dis -htb D:\2018\ECM_Remote\ECM_client\HTB\180917\Release\cpu1.htb -o output.prf
pause



