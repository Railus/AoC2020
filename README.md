# AoC2020
1) Open CMAKE
2) Select Src as source path
3) Select build as build path
4) Click configure and select "x64" for platform for generator
5) Open "Ungrouped Entries" and add "C:/_DevData/Qt/Qt5.12.8/5.12.8/msvc2017_64/lib/cmake/Qt5" to Qt5_DIR Value
6) Click Configure and Generate
7) For debugging or release copy the needed dlls (Qt5Cored.dll/Qt5Guid.dll//Gt5Widgetsd.dll) into "AoC2020-build\AoC2020\Debug"