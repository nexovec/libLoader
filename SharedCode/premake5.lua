-- premake5.lua
workspace "LibLoader"
    configurations { "Debug", "Release" }
    platforms { "Win32", "Win64", "Xbox360" }

project "SharedCode"
   kind "SharedLib"
   language "C++"
   cppdialect "C++latest"
   targetdir "bin/%{cfg.buildcfg}"
   files { "**.hpp", "**.cpp" }
filter "configurations:Release"
defines { "NDEBUG" }
optimize "On"