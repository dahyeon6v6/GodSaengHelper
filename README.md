# 갓생헬퍼 (GodSaengHelper): 2024-04 KB C Project

### 1️⃣ 프로젝트 수행 기간: 2024-04-17 ~ 2024-04-30 (2주) <br>

### 2️⃣ 프로젝트 인원: 4명 <br>

### 3️⃣ 기술스택: C, Visual Studio (Visual Studio 콘솔창에서 동작하는 프로그램 구상) <br>

### 4️⃣ 주요 기능<br>
1. 현재 날짜를 기준으로 달력 자동 생성, 그 외 원하는 날짜의 달력을 화면에 띄움<br>
2. 날짜별 파일 등록 여부를 달력에 출력함 (`To Do List`: ♥, `일기`: ★로 표시)<br>
3. 사용자의 `To Do List`, `일기`를 입력 받아 파일로 저장함<br>
   a. `To Do List` 파일의 추가, 완료, 삭제가 가능함<br>
   b. `일기` 파일의 추가, 수정, 삭제가 가능함<br>
4. 일기 편집 시 비밀번호 설정이 가능함<br>
   a. 비밀번호 추가, 수정, 삭제가 가능함<br>

### 5️⃣ 실행 방법<br>
1. Visual Studio 설치 후, c++ 패키지 설치<br>
2. `choiceDay.c`, `diary.c`, `password.c`, `showCalender.c` 코드 최상단의 파일 경로 설정<br>
   (기본 설정 경로: #define TODOFILE_FORMAT "C:\Users\a\Documents\Test")<br>
