# 게임명 : 커스텀 장기
## 실행시 주의 사항 
룰이 복잡하니 튜토리얼을 진행해 주시기 바랍니다.<br>
 패키징된 실행파일은 **JanggiEXE**에 분할 압축이 되어 있습니다.<br>
**Content 파일**은 사운드, 메테리얼 등이 포함되어 용량이 크기 때문에 분할 압축이 되어 있으니, 엔진으로 실행하려고 하시는 경우 압축을 꼭 **해제**해 주세요

# [ 목차 ]<a name='0'></a>
#### 1. [요구사항](#1)
#### 2. [사용 모델](#2)
#### 3. [설계](#3)
#### 4. [개발과정]
1. [1주차](#4)
2. [2주차](#5)
3. [3주차](#6)
4. [4주차](#7)
5. [5주차](#8)
6. [6주차](#9)
7. [7주차](#10)
8. [8주차](#11)



## 요구사항<a name='1'></a>
 [목차로 돌아가기](#0)<br>
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
  
  ## 사용 모델<a name='2'></a>
   [목차로 돌아가기](#0)<br>
  - 에픽스토어에는 장기말 에셋이 없었습니다. 무료 3D STL 모델을 찾아서 FBX로 변환해서 사용합니다.
  - 유니티와 언리얼은 모두 FBX기반으로 3D모델을 사용하기 때문에 변환이 가능하면 사용할 수 있습니다.
  <img src="https://user-images.githubusercontent.com/91234912/221480759-eac24139-c3eb-4f50-af17-32e9c8c2c67e.png" width="100%">
  <br>
따라서 이를 FBX로 변환해서 언리얼 엔진에 Import 시키고 레벨에 배치해보면 다음과 같이 나타납니다.
|왕|차|
|:-----:|:-----:|
|<img src="https://user-images.githubusercontent.com/91234912/221480764-19290943-1f85-43cf-ab1d-fb9d04b0f600.png" width="500">|<img src="https://user-images.githubusercontent.com/91234912/221480760-391f45bb-8b7f-46fb-8254-e4dae2db2a33.png" width="500">|

 <br>
스태틱메시로 성공적으로 임포트 되었지만 사진처럼 피벗이 중앙에서 벗어난 것을 볼수 있는데 이는
메시 자체의 중심축이 틀어진 것이므로 3D 툴인 블렌더를 통해서 수정해 줍니다.

 ## 설계<a name='3'></a>
 [목차로 돌아가기](#0)<br><br>
 장기를 제작하기 전에 간단한 설계를 해봅니다. 최종적으로 멀티 플레이 형태로 제작해야 하기 때문에 확장성을 염두에 두고 만들어야 합니다. 
 <img src="https://user-images.githubusercontent.com/91234912/224956410-481037ee-8a0e-4f93-9f99-7b51231c6940.png" width="100%">
 
 서버와 클라이언트 서로의 장기보드의 상태를 알아야 합니다. 따라서 장기보드 자체를 공유하는 형태로 작성하게 될 것입니다.
<br>
하지만 말을 움직이는 로직은 그림처럼 각자 가지고 있으며, 필요한 정보를 주고 받으면서 동기화 하는 형태로 작성합니다

  [![관련동영상1](https://user-images.githubusercontent.com/91234912/224972892-e8bcd537-a228-4a70-8e05-35a795cb9ab5.png)](https://www.youtube.com/watch?v=uN7LySVtRdI)
 <br>
 장기는 어느정도 체스와 유사하므로 해당 동영상을 참고해 필요한 기능을 만듭니다.
<br>
이제 장기를 만들어봅니다.

## 1 주차<a name='4'></a>
 [목차로 돌아가기](#0)<br>
- 기물이 이동할 위치를 표시해 줄 보드를 만들어야 합니다.
장기보드는 9 * 10 크기입니다. 영상을 참고해서 블루프린트로 제작해 봅니다.<br>

|블루프린트|결과|
|:-----:|:-----:|
|<img src="https://user-images.githubusercontent.com/91234912/221480770-1af75dad-dec4-4776-b0f5-12dfa3fa3427.png" width="700">|<img src="https://user-images.githubusercontent.com/91234912/221480744-94a69f57-81ea-4a18-8ebf-be6b0a75be68.png" width="300">|
<br>
이제 만들어진 보드의 위치에 알맞게 장기알을 배치해야 합니다.<br>
하지만 그전에 가져온 모델은 가운데 글자부분이 뚫려있는 형태입니다.<br>
위 에서 볼 경우 잘 보이지 않는다는 단점이 있기 때문에 스타터 팩에 포함된 Plane을 사용해서 구멍을 매꿔줄 예정입니다.
<br>

|에셋|결과|
|:-----:|:-----:|
|<img src="https://user-images.githubusercontent.com/91234912/221480765-e7a01620-a3d2-4852-9e22-93b494087b37.png" width="500">|<img src="https://user-images.githubusercontent.com/91234912/221480767-0a259071-6459-4e4e-a673-c050b370ab7b.png" width="500">|

<br>
보기 편하게 크게 만들었지만 축소시켜서 장기알 내부에 넣어줍니다.<br>
이제 장기알을 배치하기 위해 배열에 장기알 정보를 넣어주고 블루프린트를 작성합니다.<br>
프로퍼티 지정자를 이용해 C++로 이동시킬 예정이지만 일단은 간단하게 블루프린트로 만듭니다.

|배열|결과|
|:-----:|:-----:|
|<img src="https://user-images.githubusercontent.com/91234912/221480748-c2443aa2-7cc2-4acd-8428-cbe19b671924.png" width="500">|<img src="https://user-images.githubusercontent.com/91234912/221480750-95b4adcb-d940-412f-9af0-0ba47231547e.png" width="500">|

<br>
장기알의 가짓수는 총 14가지, 한나라 7개 초나라 7개입니다.<br>
한나라와 초나라의 에셋을 구분지은 이유는 카메라로 봤을 때 바라보는 방향이 달라야 하며, 색이 다르고 본래는 모양또한 같지 않습니다. 나중에 에셋을 바꿀일이 생기면, 간단하게 바꾸기 위해 이렇게 만들었습니다.

|블루프린트|소스코드|
|:-----:|:-----:|
|<img src="https://user-images.githubusercontent.com/91234912/225187327-8f93b8ba-353a-4331-9eaf-9b275bc4ba95.PNG" width="400">|<img src="https://user-images.githubusercontent.com/91234912/225187684-ae08acd6-9849-42a0-a3ee-22d8885c6f24.PNG" width="500">|

select를 이용해 배열을 읽어오고 인덱스에 알맞은 값을 월드에 생성하는 방식으로 작동합니다.<br>
스태틱 메쉬 안쪽에 Plane은 배열 인덱스 값이 0이 아닐때 채워지게 됩니다.<br><br>
그리고 배열을 C++로 이동시킵니다. 배열은 GameState에 있으며, 캡슐화를 위해서 함수 형태로 리턴해 줍니다. 또한 블루프린트에서만 사용할 것이 아니므로 const 지정자를 이용해 다른곳에서 수정이 불가능하게 바꿉니다.
<br><br>
새로운 레벨을 만들고 UMG를 이용해서 호스트로 시작할지 호스트를 찾을지 결정할 수 있는 버튼을 제작합니다.<br>
<img src="https://user-images.githubusercontent.com/91234912/221480754-68601420-cbc8-48ad-853c-9b764d5ebf3e.png" width="800"><br><br>

- ServerUserWidget.cpp 호스트로 시작하는 코드
```c++
void UServerUserWidget::ServerButtonCallback()
{
	UGameplayStatics::OpenLevel(this, FName(TEXT("JanggiMap")), true, FString(TEXT("listen")));
}
```
<br>호스트 버튼이 눌릴경우 레벨이 JanggiMap으로 넘어가면서 리슨서버로 시작하게 됩니다.<br>

- ServerUserWidget.cpp 호스트를 찾는 코드
```c++
void UServerUserWidget::ClientButtonCallback()
{
	FName ip = FName(*ip_EditableTextBox->GetText().ToString());
	UGameplayStatics::OpenLevel(this, ip, true);
}

void UServerUserWidget::IP_EditableTextBoxCallback(const FText& Text)
{
	if (ip_EditableTextBox->GetText().ToString().Len() <= 0)
	{
		ClientButton->SetIsEnabled(false);
	}
	else {
		ClientButton->SetIsEnabled(true);
	}
}
```
ip를 입력하지 않았을 때 버튼이 비활성화 되고, 클라이언트로 시작 버튼이 눌렸을 때, 입력된 ip를 토대로 서버를 찾게 됩니다.<br><br>

-현실에서 장기를 할 경우 서로 바라보는 시점이 다릅니다. 따라서 레벨에 카메라를 2개 배치해 놓고 서버, 클라에 따라서 빙의되는 카메라가 다르게 하면 됩니다.

<img src="https://user-images.githubusercontent.com/91234912/225568327-85e795ea-4ebe-4a76-ae87-b3038638d1a1.png" width="800"><br>
레벨 블루프린트에서 오소리티에 따라서 빙의되는 카메라를 다르게 설정한 후 시점을 살펴보면<br>

<img src="https://user-images.githubusercontent.com/91234912/221480755-df7762f0-7b5d-42c7-ad49-9f858604c36e.png" width="800"><br>

서버와 클라이언트가 바라보는 시점이 다르다는 것을 확인할 수 있습니다. 이로써 요구사항 God view를 완료 했습니다.

## 2 주차<a name='5'></a>
 [목차로 돌아가기](#0)<br>

이제 장기말을 옮기기 위한 준비를 합니다. 이동방식은 마우스 아래에 있는 엑터를 읽고 좌표를 배열에 맞게 변환합니다.<br>

<img src="https://user-images.githubusercontent.com/91234912/225569178-c0dd95a5-e0e7-4c4b-a50c-8e1896647cb9.png" width="800"><br>

해당좌표의 인덱스를 전달하고 이를 통해서 좌표값을 인지합니다.

<img src="https://user-images.githubusercontent.com/91234912/221480753-0605a80a-a09d-457c-b9ac-6a9161879f4c.png" width="800"><br>

마우스를 클릭해서 좌표로그를 찍어보면 잘 출력되는 것을 확인 할 수 있습니다. 이 좌표값을 다음 함수로 1차원 배열에 적용할 수 있게 값을 변환해 줍니다.<br>
<img src="https://user-images.githubusercontent.com/91234912/221480858-72b47071-a8b5-4520-958c-37300ae20f95.png" width="800"><br>

이렇게 변환시킨 좌표의 인덱스 값의 메테리얼을 변환시키는 블루프린트를 작성한 뒤 해당 지점을 마우스로 클릭해 봅니다.

|위치|결과|
|:-----:|:-----:|
|<img src="https://user-images.githubusercontent.com/91234912/221480861-03a6ef56-dc53-45df-a59a-2b0aec8ee000.png" width="500">|<img src="https://user-images.githubusercontent.com/91234912/221480860-55b2c5e3-79a2-4bca-8b24-07ef78a140c0.png" width="500">|
<br>
보이는 것처럼 0, 0 자리를 클릭했을 때 해당 위치의 메테리얼이 바뀐 것을 확인 할 수 있습니다.
<br>
하지만 여러번 클릭할 수 없었는데 이는 블루프린트의 Construction Script를 사용하여 생긴 문제였습니다.<br>
<img src="https://user-images.githubusercontent.com/91234912/221480853-07d0f46b-4216-42ee-b779-d4c591f01bb5.png" width="800">
생성자에서는 성공적으로 초기화되었다고 결과가 나왔고 첫 실행에는 이상이 없었지만 Begin Play 이벤트와는 달리 처음 생성된 이후에는 초기화작업이 진행되지 않았습니다.<br>
이는 레벨에 배치된 이후 초기화가 되지 않고 계속해서 데이터가 쌓였기 때문에 생긴 오류였습니다.

|디버깅1|디버깅2|
|:-----:|:-----:|
|<img src="https://user-images.githubusercontent.com/91234912/221480854-643cd92f-6782-4c83-9fda-26aa365a8533.png" width="500">|<img src="https://user-images.githubusercontent.com/91234912/221480857-8c8e506a-50bd-4bd0-a773-0414da095164.png" width="500" height ="120">|

배열은 0부터 89까지만 있어야 정상이지만 배열의 크기가 초기화되지 않고 엔진이 실행되는 동안 add로 계속해서 쌓이면서 600개가 넘는 쓰래기 값이 만들어졌습니다. <br>
따라서 null로 초기화되어서 없어진 값을 찾으려고 하니 당연히 작동하지 않습니다.<br>
<br>
<img src="https://user-images.githubusercontent.com/91234912/225570511-538beb72-c3cf-4b68-83d2-9c177c0cba94.png" width="800"><br>
이 오류를 해결하기 위해 만든 코드를 Begin Play로 옮깁니다.<br>
더 이상 게임 실행전에 레벨에서는 어떻게 배치되는지 확인 할 수 없어졌지만, 이제는 정상적으로 동작합니다.
