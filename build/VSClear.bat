@echo off
cd \
@echo on
@REG Delete HKEY_CURRENT_USER\Software\Microsoft\VisualStudio\8.0\FileMRUList /va /f
@REG Delete HKEY_CURRENT_USER\Software\Microsoft\VisualStudio\8.0\ProjectMRUList /va /f
@REG Delete HKEY_CURRENT_USER\Software\Microsoft\VisualStudio\9.0\FileMRUList /va /f
@REG Delete HKEY_CURRENT_USER\Software\Microsoft\VisualStudio\9.0\ProjectMRUList /va /f
@REG Delete HKEY_CURRENT_USER\Software\Microsoft\VisualStudio\10.0\FileMRUList /va /f
@REG Delete HKEY_CURRENT_USER\Software\Microsoft\VisualStudio\10.0\ProjectMRUList /va /f
@REG Delete HKEY_CURRENT_USER\Software\Microsoft\VPDExpress\11.0\FileMRUList /va /f
@REG Delete HKEY_CURRENT_USER\Software\Microsoft\VPDExpress\11.0\ProjectMRUList /va /f
@REG Delete HKEY_CURRENT_USER\Software\Microsoft\VisualStudio\12.0\FileMRUList /va /f
@REG Delete HKEY_CURRENT_USER\Software\Microsoft\VisualStudio\12.0\ProjectMRUList /va /f
@REG Delete HKEY_CURRENT_USER\Software\Microsoft\VisualStudio\14.0\MRUItems /va /f
@echo off
pause