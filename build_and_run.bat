@echo off
pushd %~dp0
pushd MainApp
..\premake5.exe vs2022
popd
pushd SharedCode
..\premake5.exe vs2022
popd
popd
