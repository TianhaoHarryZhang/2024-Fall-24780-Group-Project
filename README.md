## Codeemon

### Contributors: 
Tianhao Zhang (tianhao3@andrew.cmu.edu)  
Kaifeng Hu (kaifengh@andrew.cmu.edu)  
Dylan Leong (dylanleo@andrew.cmu.edu)  
Rachell Lee (soojinl2@andrew.cmu.edu)  
Tsung Yeh Hsieh (tsungyeh@andrew.cmu.edu)  

| Developer | Contribution |
|----------|----------|
| Tianhao Zhang    | Software architect and project coordinator. Developed main.cpp script, game-loading & pre-battle animation, python-based image generation and some other utility functions/classes (utility.cpp). Coordinated Github collaboration & code review|
| Kaifeng Hu    | Developed battling logic and animation in battling scene |
| Tsung Yeh Hsieh    | Developed battling logic and animation in battling scene    |
| Dylan Leong    | Developed main scene (village) including trainer moving and conversation with doctor and computer trainer |
| Rachell Lee    | Designed all roles, animals, medicine and village background image. Developed scenes of animal & medicine bags  |

### Introduction
As the group project required by CMU 24780 Engineering Computation, Codeemon is developed by five CMU graduate students. It is a 2D adventure inspired by classic Pokémon, offering a fresh twist with redesigned characters, unique animals, new adventure map and battle scenes. Built primarily using OpenGL/C++ with some Python integration, it blends creativity and technical expertise to provide an experience that is both nostalgic and refreshingly innovative. 




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
