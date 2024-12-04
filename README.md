## Codeemon (2024 Fall 24780 Group Project)

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
| Rachell Lee    | Designed all roles, animals, medicine and background images. Developed scenes of animal & medicine bags  |

### Introduction
As the group project required by CMU 24780 Engineering Computation, Codeemon is developed by five CMU graduate students. It is a 2D adventure inspired by classic Pokémon, offering a fresh twist with redesigned characters, unique animals, new adventure map and battle scenes. Built primarily using OpenGL/C++ with some Python integration, it blends creativity and technical expertise to provide an experience that is both nostalgic and refreshingly innovative. 

![Loading](https://github.com/user-attachments/assets/91e9fe9a-99ff-4be5-a588-8ada27f2ce1f)

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
cl /EHsc /Felauncher.exe main.cpp fssimplewindow.cpp yssimplesound_windows.cpp yspng.cpp yspngenc.cpp ysglfontdata.c BattleScene.cpp Medicine.cpp People.cpp Pokemon.cpp Trainer.cpp Utility.cpp /link opengl32.lib user32.lib gdi32.lib winmm.lib
```

### Windows Compiling and Execution (Using windows powershell)
#### Script.sp1 (Need to define PATH_OF_PROJECT)
```bash
$gppath = "C:\msys64\ucrt64\bin\g++.exe"
$mainfile = "C:\PATH_OF_PROJECT\main.cpp"
$outputFile = "C:\PATH_OF_PROJECT\main.exe"
$libraries = "-L 'C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\um\x86' -lOpenGL32 -lgdi32 -limm32 -lglu32 -ldsound -luuid -lole32"

# Run the compilation
$command = "& `$gppath -fdiagnostics-color=always -g $mainfile fssimplewindow.cpp yssimplesound_windows.cpp BattleScene.cpp Medicine.cpp Pokemon.cpp Trainer.cpp Utility.cpp ysglfontdata.c yspng.cpp yspngenc.cpp People.cpp $libraries -o $outputFile"
Invoke-Expression $command

# Check if the file exists and run it
if (Test-Path $outputFile) {
    Write-Host "Running the program..."
    & $outputFile
} else {
    Write-Host "Compilation failed."
}

```

#### To run script
```bash
.\Script.ps1
```

### How to play (Controls)
#### Village Scene
![image (4)](https://github.com/user-attachments/assets/3505a663-d5ce-4fda-8e43-95dae27cca41)

The game's first scene is where you can see the trainer, doctor, and the rival character(computer). To navigate the trainer, use `<⌃>⌄`. The trainer can initiate a talk with the doctor or the rival by pressing space key. You only need to press space key ONCE as the all messages will continuously be displayed in the box

#### Battle Scene
![image (1)](https://github.com/user-attachments/assets/24e0b2ab-3005-4eb5-81dc-6eb455107cf8)

Once the battle starts, there are 3 options that the trainer can make, `Fight`, `Bag`, or `Pokemon`. To make a selection, click on the button using the mouse.
`Fight` button will attack the opponent using the pokemon's special skill. `Bag` button shows the list of medicines that the trainer can use to heal the Pokemon. `Pokemon` shows Pokemons that the trainer currently has. 

#### Animal Bag
![image (2)](https://github.com/user-attachments/assets/4f6c7b9a-b970-44d9-a9fe-b6eec3cd6107)

This scene shows the Pokemon that the trainer has and the Pokemon's current HP and features. Either Pokemon can be selected by clicking on it and it will return to the battle scene.

#### Medicine Bag
![image (3)](https://github.com/user-attachments/assets/f97ac890-e8ea-41eb-9ab1-c8a70db5a2d5)

This scene shows the medicine that the trainer can use to heal the Pokemon. Click on the potion for usage. It will heal the Pokemon by its recovery point.

