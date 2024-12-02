## 2024-Fall-24780-Group-Project

### Contributors: 
Tianhao Zhang (tianhao3@andrew.cmu.edu)  
Kaifeng Hu (kaifengh@andrew.cmu.edu)  
Dylan Leong (dylanleo@andrew.cmu.edu)  
Rachell Lee (soojinl2@andrew.cmu.edu)  
Tsung Yeh Hsieh (tsungyeh@andrew.cmu.edu)  

### Installation (Python 3.11 recommended)
```bash
pip install Pillow==9.4.0
```

### MacOS Compiling Commands

```bash
mkdir -p test.app/Contents/MacOS
clang -c fssimplewindowobjc.m
clang++ -w main.cpp fssimplewindowcpp.cpp fssimplewindowobjc.m ysglfontdata.c yssimplesound.cpp yssimplesound_macosx_objc.m yspng.cpp yspngenc.cpp BattleScene.cpp Medicine.cpp People.cpp Pokemon.cpp Trainer.cpp Utility.cpp -framework Cocoa -framework OpenGL -framework AVFoundation -o test.app/Contents/MacOS/exe
test.app/Contents/MacOS/exe
```

### Windows Compiling Commands (Using Microsoft Visual C++ Compiler)
```bash
cl /EHsc /Felauncher.exe main.cpp fssimplewindow.cpp yssimplesound.cpp yspng.cpp yspngenc.cpp ysglfontdata.c BattleScene.cpp Medicine.cpp People.cpp Pokemon.cpp Trainer.cpp Utility.cpp /link opengl32.lib user32.lib gdi32.lib winmm.lib
```
