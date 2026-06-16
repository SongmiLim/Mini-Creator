# Mini Creator → OpenUSD + PhysX 통합 계획 / 인수인계 문서

> 작성일: 2026-06-16 (맥에서 환경 점검) · **실제 구현은 윈도우에서 이어서 진행**

## 목적

기존 Qt/OpenGL 3D 뷰어 **Mini Creator** 에 **OpenUSD SDK(.usd 로드)** 와
**NVIDIA PhysX SDK(물리 시뮬레이션)** 를 직접 연동하여
**"OpenUSD + PhysX 기반 Qt 디지털 트윈 에디터"** 로 확장한다.

핵심 원칙: **렌더 경로(`graphics::Mesh` / `Model` / `core::ModelManager`)는 그대로 두고,
입력(USD 로더)과 업데이트(PhysX 스텝)만 새로 끼워 넣는다.**

---

## 1. 환경 점검 결과 (2026-06-16, macOS)

| 항목 | 상태 |
|---|---|
| Apple clang 17, git, Homebrew, 12코어/18GB | ✅ |
| CMake | ❌ 미설치 |
| Qt 6 | ❌ 미설치 |

- 기존 프로젝트는 `brew install cmake qt` 만 하면 맥에서도 빌드·실행 가능
  (셰이더가 `#version 330 core` 라 macOS OpenGL에서도 동작).
- ⚠️ **PhysX 5 는 애플 실리콘 맥을 공식 지원하지 않음.** 맥에서 끝까지 가려면 물리 엔진을
  Jolt/Bullet 로 대체해야 함. **→ 윈도우로 가면 PhysX 공식 지원되어 이 문제 없음.**

---

## 2. 윈도우 첫 단계 — 기존 프로젝트 빌드 확인

USD/PhysX 붙이기 전에 **기존 프로젝트가 윈도우에서 빌드·실행되는지부터** 확인한다.

1. 설치: **Visual Studio 2019**, **CMake 3.29+**, **Qt 6.7.1 (MSVC)**
2. 빌드:
   ```bash
   mkdir build && cd build
   cmake .. -DCMAKE_PREFIX_PATH="C:/Qt/6.7.1/msvc2019_64"
   cmake --build . --config Release
   ```
   (첫 configure 때 Assimp 가 소스 빌드되어 몇 분 소요)
3. `samples/` 의 .obj 를 import 해서 렌더링 확인 → 여기까지 되면 본 작업 시작.

---

## 3. 목표 아키텍처

```
Mini Creator (Qt/OpenGL 엔진)
 ├ OpenUSD SDK
 │   └ UsdStage / UsdPrim / UsdGeomMesh / UsdGeomXformable / UsdPhysics schema 읽기
 ├ 기존 OpenGL 렌더러  (graphics::Mesh / Model / ShaderProgram — 변경 거의 없음)
 └ PhysX SDK
     └ RigidBody / Collider / Simulation step → 결과 transform 을 Model 에 반영
```

---

## 4. 코드베이스 연결 지점 (정확한 위치)

### 4-1. 모델 임포트 — USD 로더가 들어갈 곳
- `src/commands/command_import.{h,cpp}` — `CommandImport` 싱글톤, Assimp 로 로드.
  `ProcessNode/ProcessMesh` 가 vertices/normals/indices/texcoords 추출 →
  `graphics::Mesh` 채우고 `ModelManager::AddModel()` 등록. `ProgressUpdated(int)` 시그널로 진행률.
- → **`CommandImportUsd` 를 같은 패턴으로 신규 추가.** Mesh/Model/ModelManager 재사용(수정 불필요).

### 4-2. 메시 데이터 구조 — USD·PhysX 입력 매핑
- `src/graphics/mesh.{h,cpp}` — 정점/법선/UV/인덱스를 **분리된 VBO/EBO(GPU)** 로 업로드.
  - 입력 setter: `SetVertices/SetNormals/SetIndices/SetTexCoords`.
  - ⚠️ **CPU 측에 보존되는 건 `vertices_`(std::vector<glm::vec3>) 뿐.** 법선/인덱스는 VBO/EBO
    로 올린 뒤 폐기되고, 남는 건 `index_count_` 와 접근자 `GetVertices()` 뿐(`GetIndices()` 없음).
  - `UsdGeomMesh.GetPointsAttr()` / `GetFaceVertexIndicesAttr()` 결과는 위 setter 에 바로 매핑.
  - PhysX collider: **convex/box 는 `GetVertices()`/AABB 로 OK.** 단 **triangle mesh 콜라이더는
    인덱스가 필요**하므로, 먼저 `Mesh` 에 인덱스를 보존(또는 `GetIndices()` 추가)하는 선행 작업 필요.

### 4-3. 트랜스폼 — PhysX 결과를 쓰는 곳
- `src/graphics/model.{h,cpp}` — `translation_/rotation_(degrees)/scale_` (glm::vec3),
  `SetTranslation/SetRotation/SetScale`. `Draw()` 에서 매 프레임 model matrix 재구성(T·Rx·Ry·Rz·S).
  - PhysX body 위치/쿼터니언 → Euler(deg) 변환 → `SetTranslation/SetRotation` 호출이면 끝.

### 4-4. 렌더 루프 — PhysX 스텝이 들어갈 곳 ★
- `src/ui/widgets/render_widget.cpp` — 생성자에서 **16ms QTimer** 가 `update()` 호출 → `paintGL()`.
  - `paintGL()`(대략 43~69행)은 현재 **그리기만** 하고 per-frame 업데이트 훅이 없음.
  - → `glClear` 직후에 `PhysicsWorld::Step(dt)` 삽입하는 게 가장 깔끔.

### 4-5. 시뮬레이션 UI — Play/Pause/Step
- `src/ui/menu_bar/animation_menu.{h,cpp}` — `LoadActions()/AddActionsToMenu()` 가 **빈 stub**.
  - → Play/Pause/Step/Reset 액션을 채워 시뮬레이션 상태 제어.

### 4-6. 빌드 통합
- `CMakeLists.txt` — C++17, `qt_add_executable`, 디렉토리별 `file(GLOB_RECURSE)`,
  `PROJECT_LINK_LIBS` 변수에 라이브러리 누적.
- `cmake/3rdparty/` — `qt.cmake`(find_package), `assimp.cmake`/`glm.cmake`(FetchContent),
  `3rdparty.cmake` 가 이들을 `include()`.
- → `physx.cmake`, `openusd.cmake` 신규 추가 후 `3rdparty.cmake` 에 `include()` 한 줄씩.
  - **권장: prebuilt 바이너리 + `find_package`** (USD 는 소스 빌드가 수 시간).
  - assimp 가 GIT_TAG 핀이 없으니, 이참에 모든 FetchContent 에 버전 핀 추가 권장.

---

## 5. 단계별 구현 계획 (윈도우 기준)

### Phase 0 — 기존 프로젝트 윈도우 빌드 확인 *(위 2번)*

### Phase 1 — PhysX 통합 (물리 먼저, 가시적 성과 빠름)
1. `cmake/3rdparty/physx.cmake` 추가 (NVIDIA-Omniverse/PhysX, 버전 핀). `PROJECT_LINK_LIBS` 연결.
2. `src/graphics/physics/physics_world.{h,cpp}` 신규: `PxFoundation/PxPhysics/PxScene` 초기화,
   `Step(float dt)`, `Reset()`.
3. 모델당 RigidBody 생성: AABB(`GetMinBound/MaxBound`) 기반 box collider 또는 `GetVertices()`
   로 convex mesh. (triangle mesh 콜라이더가 필요하면 §4-2 의 인덱스 보존 선행 작업 먼저.)
   바닥용 static plane 1개.
4. `render_widget.cpp paintGL()` 에 `PhysicsWorld::Step(dt)` 삽입 → 결과를 `Model::SetTranslation/SetRotation`.
5. `animation_menu` 에 Play/Pause/Step/Reset 연결.
6. **검증**: 모델 import → Play → 중력으로 낙하·충돌하면 성공.

### Phase 2 — OpenUSD 임포트
1. `cmake/3rdparty/openusd.cmake` 추가 (prebuilt + `find_package(pxr CONFIG)`).
2. `src/commands/command_import_usd.{h,cpp}` 신규: `UsdStage::Open()` → `Traverse()` →
   `UsdGeomMesh` 에서 points/faceVertexIndices/normals/UV 추출 → 기존 `Mesh` 채우기 →
   `UsdGeomXformable` 로 transform → `ModelManager::AddModel()`.
3. `file_menu` 에 `.usd/.usda/.usdc` import 항목 추가 (확장자로 Assimp/USD 분기).
4. **검증**: 샘플 .usd 로드 → 기존 .obj 와 동일하게 렌더링되면 성공.

### Phase 3 — USD Physics ↔ PhysX 연결 + Bake
1. `UsdPhysicsRigidBodyAPI` / `UsdPhysicsCollisionAPI` 읽어 PhysX actor 자동 생성.
2. 시뮬레이션 결과 transform 을 USD Prim(또는 timeline)으로 Bake → `Save()`.
3. (선택) Scene Graph Viewer / USD Prim Inspector 위젯, Gizmo 편집, USD Layer override 저장.

---

## 6. 리스크 / 메모

- **PhysX 플랫폼**: 윈도우 ✅ / 애플 실리콘 맥 ❌(공식 미지원). 맥 필수면 Jolt/Bullet 대안.
- **OpenUSD 빌드**: 무겁다. prebuilt 바이너리 강력 권장. pip `usd-core` 는 Python 전용이라 C++ 엔 부적합 — 빌드된 C++ 라이브러리 필요.
- **C++ 표준**: PhysX(C++11+), OpenUSD(C++17) 모두 현재 C++17 과 호환 — 블로커 없음.
- **스레딩**: 현재 import 는 메인 스레드 동기 실행. 대형 USD 는 추후 워커 스레드 고려(지금은 불필요).

---

## 7. 참고 링크

- PhysX SDK: https://github.com/NVIDIA-Omniverse/PhysX
- OpenUSD: https://openusd.org/release/apiDocs.html
- Omni Physics(Kit 의존, 참고용): https://docs.omniverse.nvidia.com/kit/docs/omni_physics/latest/extensions/index.html
