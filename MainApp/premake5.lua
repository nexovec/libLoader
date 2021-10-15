-- premake5.lua
workspace "LibLoaderMainApp"
    configurations { "Debug", "Release" }
    platforms { "Win32", "Win64", "Xbox360" }

project "MainApp"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++latest"
   targetdir "bin/%{cfg.buildcfg}"

   files { "**.hpp", "**.cpp" }

   filter "configurations:Debug"
   defines { "DEBUG" }
   symbols "On"