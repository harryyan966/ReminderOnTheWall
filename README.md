# Reminder On The Wall

This program generates a schedule about which group of a certain day is on duty (do the cleaning job). Each group is numbered, and the program will automatically generates a sequential schedule.

## Dependencies

| Name      | Version   |
| :---:     | :---:     |
| OpenCV    | 4.2       |
| libconfig | 1.7.3     |

You can install OpenCV using NuGet.

You may install libconfig using NuGet or Vcpkg. However, I have put the source code in this repository as a sub-module; you can pull the source code down and compile it using whether Visual Studio (.sln file) or CMake (CMakeLists.txt).

> If you directly install libconfig library, please place ***libconfig++.lib*** under directory:
> ***src/lib/libconfig/build/x64/*** for x86_64 Windows (64 bit machine) or
> ***src/lib/libconfig/build/Win32/*** for x86 Windows (32 bit machine)

---

# Compile

This tutorial help you to compile this program using Visual Studio
Your Visual Studio need to support C++17 for compiling `Reminder-On-The-Wall_static`

1. Open solution `src/lib/libconfig/libconfig_vs2017.sln`
2. Build `libconfig++`
3. Open solution `Reminder-On-The-Wall_static.sln`
4. Build `Reminder-On-The-Wall_static`, keep `libconfig++` and `Reminder-On-The-Wall_static` built on the same platform.

## About the idea...

> [Cynthia7979](https://github.com/Cynthia7979) had this idea before me
> Her implementation [Cynthia7979/on_duty_noticer](https://github.com/Cynthia7979/on_duty_noticer). 
> 
> July 23, 2021

---

## TODO

* [ ] Add a preview before the wallpaper is set
* [ ] A GUI
* [ ] If someone is punished to be on-duty, make it easy to add them in
* [ ] DIY content (This would need a complex GUI...)
* [ ] Set a video as the wallpaper's background (This would be a long way)
