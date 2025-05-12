# US
## 🖥️ 프로젝트 소개
대규모로 몰려오는 적을 처치하는 싱글 액션 게임

#### ⚙️ 개발 환경
- 사용 언어 : `C++`, `Blueprint`
- 사용 엔진 : `Unreal Engine 5.1`

##### 🧑‍🤝‍🧑 참여 인원 및 담당 분야
 - 참여 인원 : 1인
 - 담당 분야 : `캐릭터` | `아이템/무기` | `애니메이션 최적화` | `메일 시스템` | `UI`

#### 🎯 목표
 - 100마리의 적 캐릭터 생성에도 끊김없는 플레이 구현
 - 10만 개의 메일 데이터 송•수신 구현

## 📌 핵심 기능
#### 1. 커스텀 애니메이션 공유 시스템을 통한 100마리의 적 성능 개선 (31fps→73fps, 135% 개선)
- Update Rate Optimization : 애니메이션 업데이트 빈도 조정으로 **24fps → 28fps (16% 향상)**
- VisibilityBasedAnimTickOption : 보이지 않는 적의 애니메이션 틱을 중지시켜 **28fps → 31fps (10% 향상)**
- 커스텀 애니메이션 공유 시스템 **31fps → 73fps (135% 향상)**<br/><br/>
![Image](https://github.com/user-attachments/assets/835f385f-7d52-4ec1-8ec0-7fcb43895c58)<br/><br/>
    - Unreal Insights를 통해 분석한 결과, 각 적이 개별적으로 애니메이션을 실행하면서 CPU 부하가 급증
    - 동일한 Skeletal Mesh와 Animation State를 가진 적들을 그룹화
    - 각 그룹의 대표 캐릭터(Leader)를 생성해 애니메이션을 실행하고, 나머지 적들은 해당 데이터를 공유 받아 재생하도록 설계
- 결론적으로 애니메이션 개선으로 **FPS : 24 ~ 25 fps → 73 fps (204% 개선)**
#### 2. Unreal Insights 디버깅을 통한 10만개 메일 송신 성능 개선 (처리 시간 : 3.79s → 0.23s) - <a href="https://github.com/highstar97/US/wiki/Unreal-Insights" >상세보기 - WIKI 이동</a>
- 시스템 성능 저하 원인 추적 및 분석
- 총 처리 시간 : 최대 93.9% 단축
- 최저 FPS : 최대 70배 개선
- 한 프레임에서 걸린 최대 시간 : 최대 98.6% 개선

## 😊 추가 구현 내용
#### 전투 시스템 개발
- 발사체 시스템 개발
    - Object Pooling 기법을 사용하여 생성/삭제 비용을 최소화
- 기획 친화적 개발
    - Data Validator 매크로 생성하여 Editor에서 제대로 할당되지 않은 경우, 경고 창 출력 혹은 프로그램 종료되도록 설계
    - 무기, 발사체 Data Asset 기반 관리
    - 캐릭터/적 스텟 Data Talbe 기반 관리
- AI 캐릭터의 로직
    - 탐색 → 공격 → 추격 → 순찰
#### 메일 시스템 개발
- GameInstance의 Subsystem으로 설계
- Round Robin 스케줄링 방식의 메일 전송
