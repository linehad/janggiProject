# 게임명 : 커스텀 장기
## 실행시 주의 사항 
룰이 복잡하니 튜토리얼을 진행해 주시기 바랍니다.<br>
 패키징된 실행파일은 **JanggiEXE**에 분할 압축이 되어 있습니다.<br>
**Content 파일**은 사운드, 메테리얼 등이 포함되어 용량이 크기 때문에 분할 압축이 되어 있으니, 엔진으로 실행하려고 하시는 경우 압축을 꼭 **해제**해 주세요

# ~~[ 목차 ]~~
#### 1. [요구사항](#1)
#### 2. [사용 모델](#2)
#### 3. [1 주차](#3)


## 요구사항<a name='1'></a>

- UMG와 RPC, 리플리케이트에 대한 이해가 거의 됐을 쯤 과제가 내려왔습니다.
  <img src="https://user-images.githubusercontent.com/91234912/221451388-949656de-5ce6-4640-ad2e-d7beef33cb83.PNG" width="100%">
  
  1. 각 말에 체력 공격력이 있을 것
  2. 상대방 말의 체력이 0일 때만 이동 가능할 것
  3. 장기의 움직임 등 기본 룰을 지킬것
  4. 멀티 게임으로 만들 것
  5. 튜토리얼이 있을 것
  6. God View로 카메라를 배치할 것
  7. 배포용으로 패키징 할 것
  <br>
  위 사항을 우선적으로 구현한 뒤 옵션을 생각하도록 합니다. <br>
  멀티로 만들어야 하는 점을 생각하며 일반적인 장기를 먼저 제작합니다.
  
  ## 사용 모델<a name='1'></a>
  
  - 에픽스토어에는 장기말 에셋이 없었습니다. 무료 3D STL 모델을 찾아서 FBX로 변환해서 사용합니다.
  - 유니티와 언리얼은 모두 FBX기반으로 3D모델을 사용하기 때문에 변환이 가능하면 사용할 수 있습니다.
  <img src="https://user-images.githubusercontent.com/91234912/221480759-eac24139-c3eb-4f50-af17-32e9c8c2c67e.png" width="100%">
