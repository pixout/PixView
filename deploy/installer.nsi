/*
Copyright (c) 2013-2015, SIA "Pixout". All rights reserved.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation.

There are special exceptions to the terms and conditions of the GPL as it
is applied to this software.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA 
*/


Name "PixView"
OutFile "pixview-setup.exe"
InstallDir C:\PixView
RequestExecutionLevel user

Page directory
Page instfiles
UninstPage uninstConfirm
UninstPage instfiles

Section ""

  SetOutPath $INSTDIR
  File /r "data\*"

;  ${EnvVarUpdate} $0 "PATH" "A" "HKLM" "$INSTDIR\bin"

  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\LedC "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LedC" "DisplayName" "PixView"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LedC" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LedC" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LedC" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  
SectionEnd

Section "Uninstall"
 
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\PixView"
  DeleteRegKey HKLM SOFTWARE\LedC

  Delete $INSTDIR\pixview.exe
  RMDir "$INSTDIR"

SectionEnd
