# Mini Creator

<br>

**Mini Creator**는 C++과 OpenGL, Qt 기반으로 개발된 경량 3D 렌더링 엔진입니다.
여러 개의 3D 모델을 불러오고, 실시간 렌더링과 사용자 중심의 카메라 조작, 모델 선택 및 변환 기능을 제공합니다.
<br><br>

<img width="1918" height="1016" alt="Image" src="https://github.com/user-attachments/assets/e17a34b2-662f-403a-9298-a48517b93989" />

---
<br><br>

## 주요 기능

### 다중 3D 모델 로드 및 렌더링
- Assimp 라이브러리를 이용하여 다양한 **3D 모델 포맷**을 로드하고 렌더링
- **텍스처**가 있는 모델과 없는 모델 모두 지원
- 다수의 모델을 동시에 로딩하고 개별적으로 제어 가능

### 개별 모델 변환(Transform)
- 각 모델별로 **위치, 크기, 회전(Transform)** 조절 가능
- UI에서 직접 모델을 선택하고 속성을 수정할 수 있음

### 카메라 기능
- 1인칭 / 3인칭 카메라 모드 지원
- **키보드 및 마우스**를 사용하여 카메라 이동 및 회전(Yaw, Pitch, Zoom ) 조절
- 바운딩 박스를 기준으로 모델 크기를 계산하여 카메라 초기 위치 자동 조정

### Selection Highlight
- 선택된 모델에 바운딩 박스 표시
- 다중 모델 환경에서도 사용자 시선에 따라 선택된 모델 식별 가능

---
<br><br>

## 기술 스택

| 기술 | 역할 |
|------------|---------|
| C++ | 렌더링 로직 및 엔진 전반 구현 |
| OpenGL (GLFW + GLAD)** | 그래픽 렌더링 처리 |
| Assimp | 3D 모델 로드 (OBJ, FBX 등 지원) |
| STB | 텍스처 이미지 로딩 |
| Qt | UI 프레임워크 (v2.0에서 ImGui → Qt) |

---
<br><br>

## 개발 환경

| 항목 | 내용 |
|------------|---------|
| 운영체제 | Windows 11 |
| 언어 | C++17 |
| 빌드 도구 | CMake 3.29 |
| UI 프레임워크 | Qt 6.7.1 |
| IDE | Visual Studio 2019, VS Code |

---
<br><br>

## 설치 및 실행 방법

**레포지토리 클론**
```bash
git clone https://github.com/yourusername/minicreator.git
cd minicreator
```
<br>

**Build with CMake**
```bash
mkdir build
cd build
cmake ..
```
❗ Qt 설치 및 환경변수 설정이 필요합니다.

---
<br><br>


## Qt 미설치 사용자를 위한 실행 파일 제공 (Window 사용자)

Qt가 설치되어 있지 않은 사용자도 실행할 수 있도록, 실행 파일과 필요한 DLL이 포함된 `.zip` 파일을 제공합니다.<br>
[mini_creator.zip (Releases)](https://drive.google.com/file/d/1JL1q2tUycnJ7cRIlrcDMU_R7aQQDYmUv/view?usp=sharing)

압축을 푼 후 `mini_creator.exe`를 실행하면 바로 사용할 수 있습니다.<br>
`/samples` 폴더에 포함된 테스트용 3D OBJ 파일들을 import 해서 기능을 직접 확인해보세요.


📁 파일 구성
```bash
mini_creator/
├── mini_creator.exe
├── Qt6Core.dll
├── Qt6Widgets.dll
├── ...
├── samples/
```
---
<br><br>

## 참고 자료
- 🔗 [Khronos OpenGL 공식 문서](https://www.khronos.org/opengl)  
- 🔗 [LearnOpenGL](https://learnopengl.com)  
- 🔗 [Assimp GitHub](https://github.com/assimp/assimp)  
- 🔗 [STB GitHub](https://github.com/nothings/stb)  
- 🔗 [Dear ImGui GitHub](https://github.com/ocornut/imgui)  
- 🔗 [JoeyDeVries의 OpenGL 강좌](https://github.com/JoeyDeVries/LearnOpenGL/tree/master)  
- 🔗 [rinthel의 OpenGL 강좌](https://github.com/rinthel/opengl_course)  

---
<br><br>

## 향후 개발 예정 기능 (To-Do)
✅ **[v2.0] Qt 기반 UI 적용 (ImGui 제거)**

✅ **[v2.0] 바운딩 박스 기반 카메라 위치 자동 조정**

🔲 v1.0에 포함되어 있던 Light 위치 및 색상 조절 기능(Ambient, Diffuse, Specular) 통합

🔲 **PBR(Physically Based Rendering)**을 적용하여 더 현실적인 재질 표현

🔲 **충돌 감지** 및 물리 연산을 통한 **시뮬레이션**

🔲 **Shadow Mapping**을 사용한 실시간 그림자 구현


---
<br><br>



