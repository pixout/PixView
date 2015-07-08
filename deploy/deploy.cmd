SET BUILD_DIR=..\..\PixView-build
SET MINGW_DIR=C:\Qt\5.4\mingw491_32

rmdir /S /Q data
mkdir data
copy %BUILD_DIR%\pixview.exe data\
cd data
rem windeployqt.exe --no-translations --no-webkit2 --no-system-d3d-compiler --no-angle --release --force --qmldir ../qml pixview.exe
windeployqt.exe --no-translations --no-webkit2 --no-system-d3d-compiler --no-angle --release --force pixview.exe
del Qt5Svg.*
del Qt5Webkit.*
del imageformats\qdds.*
del imageformats\qgif.*                                                                        
del imageformats\qicns.*
del imageformats\qjp2.*
del imageformats\qmng.*
del imageformats\qsvg.*
del imageformats\qtga.*
del imageformats\qtiff.*
del imageformats\qwbmp.*
del imageformats\qwebp.*
rmdir /Q /S bearer
rmdir /Q /S iconengines
rmdir /Q /S qmltooling
copy %MINGW_DIR%\bin\libstdc*.* .
copy %MINGW_DIR%\bin\libgcc_s*.* .
copy %MINGW_DIR%\bin\libwinp*.* .