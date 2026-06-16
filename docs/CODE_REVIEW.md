# 코드 리뷰 결과 / 후속 작업

> 2026-06-16 전체 구조 리뷰. macOS에는 빌드 환경(cmake/qt)이 없어 **빌드·런타임 검증 없이**
> 안전·국소 수정만 적용했다. 아래 "후속(윈도우)" 항목은 빌드 가능한 환경에서 진행.

## 이미 수정·커밋됨 (브랜치 `fix/code-review-issues`)

- **[Bug]** `ProcessMesh` 인덱스/UV 버퍼가 2배로 부풀고 앞 절반이 0 → `reserve`/인덱스 대입으로 수정.
- **[Bug]** import 진행률 `50 / mNumChildren` 0 나누기(단일 메시 모델 크래시) → 가드 + 100% 완료 emit.
- **[Bug]** Diffuse/Specular 컬러 라벨이 "Ambient:"로 표기되던 복붙 버그.
- **[Bug]** `~Mesh`가 `texture_`(raw QOpenGLTexture)를 해제 안 해 누수 → 소멸자에서 delete.
- **[Bug]** `Mesh`/`ShaderProgram` 복사 금지(raw GL 핸들 이중 해제 방지, Rule of 5).
- **[Bug]** `ObjectControlWidget`의 QColor 멤버 미초기화 → 흰색으로 초기화(라벨과 일치).
- **[Bug]** `MainWindow` 멤버 초기화 순서 불일치(-Wreorder) 정정.
- **[Refactor]** model matrix 3중 복붙 → `Model::GetModelMatrix()` 단일화(동작 불변).
- **[Refactor]** CMake: assimp `v5.4.3` 핀 + 빌드 트림, `PROJECT_LINK_LIBS`의 PRIVATE 키워드 정리, GLOB `CONFIGURE_DEPENDS`.
- **[Refactor]** 죽은 `MenuBar::Render()/CreateMenu()` 선언 제거, `ToolBar`에 누락된 `Q_OBJECT` 추가.

## 후속 (윈도우에서 빌드·테스트하며 진행)

### 🔴 구조 (USD/PhysX 착수 전 권장)
1. **GL 리소스 소유권·컨텍스트 수명 정리.** 생성자에서 GL 자원 생성 + `makeCurrent()` 부재 →
   명시적 `Initialize()` 단계로 분리하고 import 경로에서 컨텍스트 보장. 종료 시 전역 모델 소멸이
   GL 컨텍스트 파괴 이후 일어나는 문제도 함께.
2. **셰이더 공유 캐시.** 현재 모델마다 동일 셰이더를 새로 컴파일 → `ShaderCache`/렌더러 소유로.
3. **`ModelManager` 전역 static → 인스턴스화 + 의존성 주입.** `App`/`MainWindow`가 `Scene`을
   소유하고 위젯·Raycast·Import에 주입. 멀티씬/테스트/리셋 가능해짐.
4. **모델 제거/초기화 API.** `RemoveModel`/`Clear` 추가(현재 Add만 존재, "New" 메뉴가 씬을 못 비움).
   선택 모델 제거 시 `selected_model_` 무효화. `GetAllModels()`는 const/스냅샷으로.

### 🟡 성능·기능
5. **VAO 도입.** 현재 VAO 0개, Draw마다 attribute 재바인딩(코어 프로파일에선 사실상 필수).
6. **import 워커 스레드 분리.** Assimp 파싱은 워커, GL 업로드만 메인 → 진행률 바가 실제로 그려짐
   (지금은 동기 블로킹이라 0→100만 보임). 분리 시 `CommandImport` 멤버 상태를 무상태로(레이스 방지).
7. **dirty-flag 렌더링.** 16ms 무조건 풀 리페인트 → 변경 시에만 `update()`.
8. **selection-changed 시그널.** 뷰포트에서 선택 변경 시 `ObjectControlWidget` 슬라이더/라벨 동기화.
9. **Light direction 핸들러 구현.** `HandleDirectionX/Y/ZChanged`가 빈 함수 + light 접근 경로 부재
   (light는 RenderWidget 소유) → 결합 정리와 함께.
10. **ToolBar import 동작 통일.** `ToolBar::HandleImport`가 메시지박스만 띄움(FileMenu와 불일치).
    현재 ToolBar는 비활성(LoadToolBar 주석). 활성화 시 공통 커맨드로 일원화.

### 🟢 정리(여유 시)
- raycast 선택에 `tmin >= 0`(카메라 뒤 박스 제외) — 동작 변화라 테스트 후.
- `Light::Draw`의 attribute stride `sizeof(float)` 의도 확인(vec3여야).
- 슬라이더 핸들러 9개 중복 → 축 enum + 헬퍼로 압축.
- `CreateSlider`의 `setSingleStep(float)` 무효 인자, 매직 넘버 상수화, `keyPressEvent` 문자열 비교 → `Qt::Key_*`.
- 모델 이름(파일경로) 유일성 미보장 → 고유 ID.
