Mini Creator
------------------------------------------------------------------------------
Mini Creator는 C++, OpenGL 등을 이용하여 만든 "간단한 3D 엔진"입니다.<br> 
3D 모델을 로드하고 렌더링하며, 카메라 조작 및 조명 설정 등 다양한 기능을 제공합니다.
<br>
<br>
![스크린샷 2024-04-28 190217](https://github.com/SongmiLim/Mini-Creator/assets/99317323/22e4181b-47af-49e9-a548-bf8f92b2dadd)
<br>
<br>

Features
------------------------------------------------------------------------------
3D 모델 로드 및 렌더링: 사용자가 선택한 3D 모델을 로드하고 렌더링합니다.<br> 
Animation: 로드된 3D 모델에 대해 360도 회전하는 애니메이션을 적용하여 모델을 모든 각도에서 확인할 수 있습니다.<br> 
Camera 조작: 키보드 및 마우스를 사용하여 사용자는 camera의 position, fov, yaw, pitch를 조절할 수 있습니다.<br> 
Light 설정: 사용자는 light의 position, ambient, diffuse, specular를 조절하여 장면의 조명을 변경할 수 있습니다.
<br>
<br>
![GIFMaker_me](https://github.com/SongmiLim/Mini-Creator/assets/99317323/b17fbe43-3add-4ac3-aa36-3de0a4839a55)
<br>
<br>

Skills
------------------------------------------------------------------------------
C++: 프로젝트의 주요 언어로 사용되며, 엔진의 핵심 로직을 구현<br> 
OpenGL: 3D 그래픽스 라이브러리로 사용되며, 모델 렌더링 및 그래픽스 파이프라인을 구현<br> 
Assimp: 3D 모델을 로드하기 위한 라이브러리<br> 
STB: 이미지 로딩 및 처리를 위한 라이브러리<br> 
ImGui: 사용자 인터페이스를 위한 라이브러리
<br>
<br>

Requirement
------------------------------------------------------------------------------
OS: Windows 10<br> 
IDE: Visual Studio Code<br> 
Compiler: Visual C++ 컴파일러 (MSVC)<br> 
CMake: CMake v3.13<br> 
OpenGL: glfw v3.3.10, glad: v0.1.36<br> 
Assimp: Assimp v5.0.1<br> 
STB: https://github.com/nothings/stb<br> 
ImGui: Dear ImGui v1.90.5<br> 
<br>
<br>

References
------------------------------------------------------------------------------
https://www.khronos.org/opengl<br>
https://learnopengl.com<br>
https://github.com/assimp/assimp<br> 
https://github.com/nothings/stb<br> 
https://github.com/ocornut/imgui<br> 
<br>
<br>

To Do
------------------------------------------------------------------------------
사용자가 원하는 3d오브젝트를 로드할 수 있도록 파일 탐색기 기능 추가<br>
(좀 더 개선된 GUI를 위해 QT Framework를 사용하는 버전 추가)

<br>
<br>
<br>
<br>
