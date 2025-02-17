# Mini Creator

**Mini Creator**는 C++과 OpenGL을 기반으로 개발된 **경량 3D 엔진**으로, <br>
**3D 모델 로드 및 렌더링, 카메라 조작, 조명 설정** 등의 기능을 제공합니다.
<br>

![Image](https://github.com/user-attachments/assets/ea811bbd-77a2-402c-a081-65ffa3538ebc)

---
<br><br>

## 🚀 주요 기능

### 🖼️ 3D 모델 로드 및 렌더링
- Assimp 라이브러리를 이용하여 다양한 **3D 모델 포맷**을 로드하고 렌더링
- **텍스처**가 있는 모델과 없는 모델 모두 지원

### 🛠️ 변환(Transform) 및 애니메이션(Animation)
- 모델의 **위치, 크기, 회전(Transform)** 조절 가능
- **360도 회전 애니메이션**을 적용하여 모델을 다양한 각도에서 확인 가능

### 🎥 카메라 조작
- **키보드 및 마우스**를 사용하여 카메라 이동 및 회전(FOV, Yaw, Pitch) 조절 가능
- **마우스 드래그 및 휠 스크롤**로 직관적인 조작 가능

### 💡 조명 시스템
- **광원(Light)의 위치 및 색상(Ambient, Diffuse, Specular)** 조절 가능
- 실시간으로 조명 값을 변경하여 장면의 **조명 효과**를 조정할 수 있음

<br><br>
### 🆕 Mini Creator v2.0 신규 기능
✅ **Qt 기반 UI 적용** (v1.0의 ImGui에서 변경)  
✅ **바운딩 박스 기반 초기 카메라 위치 자동 조정 기능 추가**  
   - 모델 크기를 계산하여 **적절한 카메라 포지션**을 자동 설정
   - 모델이 항상 화면에 잘 보이도록 자동 조절됨
---
<br><br>

## 🛠️ 기술 스택

| 기술 | 역할 |
|------------|---------|
| **C++** | 핵심 로직 및 엔진 구현 |
| **OpenGL (GLFW + GLAD)** | 그래픽 렌더링 처리 |
| **Assimp** | 3D 모델 로드 |
| **STB** | 이미지 로드 및 처리 |
| **Qt (v2.0)** | UI 프레임워크 (v1.0에서는 ImGui 사용) |

---
<br><br>

## 📌 설치 및 실행 방법

1️⃣ **레포지토리 클론**
```bash
git clone https://github.com/yourusername/minicreator.git
cd minicreator
```
<br>

2️⃣ **Build with CMake**
```bash
mkdir build
cd build
cmake ..
```
<br><br>

---

## 📚 참고 자료
- 🔗 [Khronos OpenGL 공식 문서](https://www.khronos.org/opengl)  
- 🔗 [LearnOpenGL](https://learnopengl.com)  
- 🔗 [Assimp GitHub](https://github.com/assimp/assimp)  
- 🔗 [STB GitHub](https://github.com/nothings/stb)  
- 🔗 [Dear ImGui GitHub](https://github.com/ocornut/imgui)  
- 🔗 [JoeyDeVries의 OpenGL 강좌](https://github.com/JoeyDeVries/LearnOpenGL/tree/master)  
- 🔗 [rinthel의 OpenGL 강좌](https://github.com/rinthel/opengl_course)  

---
<br><br>

## 📌 To-Do 리스트
✅ **[v2.0] Qt 기반 UI 적용 (ImGui 제거)**

✅ **[v2.0] 바운딩 박스 기반 카메라 위치 자동 조정**

🔲 **PBR(Physically Based Rendering)**을 적용하여 더 현실적인 재질 표현

🔲 **충돌 감지** 및 물리 연산을 통한 **시뮬레이션**

🔲 **Shadow Mapping**을 사용한 실시간 그림자 구현


---
<br><br>

### 🚀 Mini Creator는 실시간 3D 모델 시각화를 목표로 발전하는 프로젝트입니다.  
### 더 나은 기능을 위해 지속적으로 개선 중이며, 피드백과 기여를 환영합니다! 😊


