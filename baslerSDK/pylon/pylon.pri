#指明Basler库所对应的头文件所在的目录
INCLUDEPATH += $$PWD/include

#指明依赖库关系，及所依赖的库所在的位置
win32: LIBS += -L$$PWD/lib/Win32/ -lGCBase_MD_VC141_v3_1_Basler_pylon_v5_1
win32: LIBS += -L$$PWD/lib/Win32/ -lGenApi_MD_VC141_v3_1_Basler_pylon_v5_1
win32: LIBS += -L$$PWD/lib/Win32/ -lPylonBase_v5_1
win32: LIBS += -L$$PWD/lib/Win32/ -lPylonC
#win32: LIBS += -L$$PWD/lib/Win32/ -lPylonC_BCC55
win32: LIBS += -L$$PWD/lib/Win32/ -lPylonGUI_v5_1
win32: LIBS += -L$$PWD/lib/Win32/ -lPylonUtility_v5_1
