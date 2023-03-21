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
더 이상 게임 실행전에 레벨에서는 어떻게 배치되는지 확인 할 수 없어졌지만, 이제는 정상적으로 동작합니다.<br>
<br>
추가적으로 변환된 좌표값을 토대 말을 클릭 한 상태에서 다른 곳을 누를 경우 이동을 구현합니다.<br>
<img src="https://user-images.githubusercontent.com/91234912/226251420-bb0db18c-3394-4558-b591-c7bbaadc31c0.png" width="800"><br>

처음 클릭시 CkeckMove 함수가 실행되고 두번째 클릭시 처음 클릭한 말을 클릭한 위치로 이동시키는 IsMove 함수가 실행됩니다.<br>
<img src="https://user-images.githubusercontent.com/91234912/221480850-75ba1ac0-669b-4e0c-b3bf-e7141e47cf16.png" width="800"><br>
실행해보면 아직은 서버 클라에서 서로 이동한 것이 보이진 않지만 말이 이동한 것을 확인할 수 있습니다.<br>

## 3 주차<a name='6'></a>
 [목차로 돌아가기](#0)<br>
 
말을 옮기는 것을 토대로 기물의 움직임을 구현합니다. 장기 룰에 따라서 기물을 움직여 줄 것입니다.
이를 구현하기 위해서는 말이 이동가능한 곳을 계산해서 해당 지점만 이동이 가능하게 만들면 됩니다.
<br>
이는 장기 JanggiPieces.cpp의 각 말에 맞는 함수에서 TArray<int32> 형태로 반환 할 것이며, 장기보드에서는 이동가능한 위치를 받아서 해당 위치만 이동할 수 있게 제한해 줄 것입니다.<br><br>

-JanggiPieces.cpp
```c++
// 위쪽부터 반시계 방향 직선 탐색(상좌하우 마, 상, 차, 포를 위한 배열)
	const int32 straightX[4] = { 0, -1, 0, 1 };
	const int32 straightY[4] = { 1, 0, -1, 0 };

	// 왼쪽 위부터 반시계 방향 대각선 탐색(좌상, 좌하, 우하, 우상 마, 상을 위한 배열 straightX, straightY와 맞물리면서 돌아간다.)
	const int32 diagonalX[4] = { -1, -1, 1, 1 };
	const int32 diagonalY[4] = { 1, -1, -1, 1 };
```
<br>
방향이 들어있는 배열을 이용해서 탐색하게 됩니다. 차의 경우 궁에 들어갔을 때만 대각선 이동이 가능하며, 나머지는 직선이동입니다. <br>

```c++
nx = xIndex + straightX[i];
		ny = yIndex + straightY[i];
		curPos = Board_index(nx, ny);
		bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);

		while (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 &&
			curPos >= 0 && curPos < BOARD_SIZE &&
			bisMove) // curPos가 배열을 초과하지 않고 다음 이동할 위치가 비어있으면 이동이 가능하다.
		{

			if (nx >= X_SIZE || ny >= Y_SIZE && nx < 0 || ny < 0)break;

			possibleMove.Add(curPos);
			nx += straightX[i];
			ny += straightY[i];
			curPos = Board_index(nx, ny);
			bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
		}
	}
	return possibleMove;
```	
<br>
배열을 초과하지 않는 선에서 말이 클릭된 지점에서 직선 움직임을 계산합니다. 이를 적용해 보면<br>
<img src="https://user-images.githubusercontent.com/91234912/221480939-421d6aa2-dc93-4def-bd34-78962d4f7adc.png" width="800"><br>

다음과 같이 나옵니다. 아직 앞에 말이 있건 없건 맵의 끝까지 탐색하기 때문입니다. 여기서 추가적으로 차는 궁 안에 들어 갈 경우 대각선 이동이 가능합니다.<br>
<img src="https://user-images.githubusercontent.com/91234912/221480954-8450e3d6-4058-4ee6-b12b-1d2625779f4a.png" width="800"><br>

좌표를 엑셀로 표현해 보았습니다. 궁 위치가 X값은 동일한데 Y값만 달라지는 것을 볼 수 있습니다.<br>
이를 참고해서 차의 대각선 이동을 구현합니다.<br>

|대각 상|대각 하|
|:-----:|:-----:|
|<img src="https://user-images.githubusercontent.com/91234912/221481052-33477776-932e-4772-ad95-4481da503599.png" width="500">|<img src="https://user-images.githubusercontent.com/91234912/221481045-1c2408cf-0ec5-4d78-a07f-83058fdd63ab.png" width="500">|
<br>
한나라, 초나라 궁 범위 내에서만 대각선 이동이 가능해 졌습니다.<br>
이를 활용해서 포도 제작합니다. 포는 차와 비슷하지만 말을 뛰어 넘습니다. 직선 탐색시 말을 만나면 그 말의 뒤쪽부터 이동이 가능하게 만듭니다.<br>

|포 1|포 2|
|:-----:|:-----:|
|<img src="https://user-images.githubusercontent.com/91234912/221480905-39afa258-f774-4ad1-9ddc-61badbf36861.png" width="500">|<img src="https://user-images.githubusercontent.com/91234912/221480946-9e873157-6662-4ca9-b9f2-10e6a0cb57ad.png" width="500">|

포가 말이 없을 때는 이동하지 못하지만 말이 있을 경우에는 이동이 가능해 진것을 볼 수 있습니다.<br>
하지만 포는 포끼리 먹을 수 없고 포끼리 넘을 수 없습니다. 제약을 추가해 줍니다.<br>

|포 제약1|포 제약2|
|:-----:|:-----:|
|<img src="https://user-images.githubusercontent.com/91234912/221480984-a942a963-11d7-4568-a733-a81d47db467d.png" width="500">|<img src="https://user-images.githubusercontent.com/91234912/221480975-bb543e85-9b68-46e5-944c-fa0a3e36e686.png" width="500">|
<br>
더 이상 포는 포끼리 넘을 수도 먹을 수도 없게 되었습니다.<br>
<br>
이제 궁과 사를 구현합니다. 궁과 사는 일정 범위 내에서만 움직일 수 있어야 합니다.<br>
<img src="https://user-images.githubusercontent.com/91234912/221480984-a942a963-11d7-4568-a733-a81d47db467d.png" width="800"><br>

제약을 추가해 봤을 때 궁 범위 바깥으로는 움직일 수 없는 것을 확인 할 수 있습니다. 하지만 궁 과 사는 1칸 범위에서 자유롭게 움직일 수 있는데, 특히 대각선 끝에 위치 한 경우 가운데로 움직일 수 있습니다.<br>
가운데에 있는 경우에는 모든 방향으로 1칸 이동이 가능합니다. 이를 적용합니다.

|궁 1|궁 2|
|:-----:|:-----:|
|<img src="https://user-images.githubusercontent.com/91234912/221481040-a4b2df6a-cc81-4eb3-9646-172bcf1b4888.png" width="500">|<img src="https://user-images.githubusercontent.com/91234912/221481029-d3ce0a1a-92a3-4120-8a05-b4032560dc89.png" width="500">|
|<img src="https://user-images.githubusercontent.com/91234912/221480956-3e75736f-82a4-4823-9c96-805e8ef020c9.png" width="500">|<img src="https://user-images.githubusercontent.com/91234912/221480960-3e396710-300d-41e3-ad53-a07ed803b7c0.png" width="500">|

<br>
마를 구현합니다. 마의 경우 상하좌우 중 한 방향으로 먼저 이동 했을 경우 막혀 있으면 그 방향으로 이동이 불가능합니다. 막혀있지 않으면 진행 방향 대각선으로 이동이 가능합니다. 이를 적용합니다.<br>

|마 1|마 2|
|:-----:|:-----:|
|<img src="https://user-images.githubusercontent.com/91234912/221480932-3d6a31d5-b655-4f10-80d8-324aa5e4a3db.png" width="500">|<img src="https://user-images.githubusercontent.com/91234912/221481008-92214b4d-5b30-45cd-b33c-d1ab80546376.png" width="500">|
<br>
이제 졸을 구현합니다. 졸의 특징은 뒤로 이동할 수 없으며, 궁에 들어 갈 경우 진행방향 대각선으로 이동이 가능합니다. 이를 구현합니다.<br>

|졸 1|졸 2|
|:-----:|:-----:|
|<img src="https://user-images.githubusercontent.com/91234912/221480964-41101024-bfed-4caa-94b7-3a43fa2ba209.png" width="500">|<img src="https://user-images.githubusercontent.com/91234912/221480969-a786b54f-59bc-4453-a390-e2d9d5358af3.png" width="500">|
<br>

-JanggiPieces.cpp
```c++
bool JanggiPieces::IsMove(const TArray<int32>& boardIndexArr, int32 xIndex, int32 yIndex, int32 curPos)
{
	bool bmove = false;
	if (curPos >= 0 && curPos < BOARD_SIZE && // 맵 바깥으로 나가지 말아야 하고
		(boardIndexArr[curPos] == EmptyHere || // 이동할 곳이 비어있거나
		(boardIndexArr[Board_index(xIndex, yIndex)] > RED_TEAM && boardIndexArr[curPos] <= RED_TEAM) || // 현재 눌린 돌이 초나라고 갈 수 있는 위치에 한나라가 없어야 함
		(boardIndexArr[Board_index(xIndex, yIndex)] <= RED_TEAM && boardIndexArr[curPos] > RED_TEAM)))  // 현재 눌린 돌이 한나라고 이동할 위치에 초나라가 있다면
	{
		bmove = true;
	}
		return bmove;
}

bool JanggiPieces::CheckEnemy(const TArray<int32>& boardIndexArr, int32 xIndex, int32 yIndex, int32 curPos)
{
	bool bmove = false;
	if (curPos < 0 || curPos >= BOARD_SIZE) {} // 맵 바깥으로 나가지 말아야 한다.	
	else if(
		boardIndexArr[curPos] != EmptyHere && // 비어 있지 않고
		(boardIndexArr[Board_index(xIndex, yIndex)] > RED_TEAM && boardIndexArr[curPos] <= RED_TEAM) || // 현재 눌린 돌이 초나라고 이동할 위치에 한나라가 있다면
			(boardIndexArr[Board_index(xIndex, yIndex)] <= RED_TEAM && boardIndexArr[curPos] > RED_TEAM))  // 현재 눌린 돌이 한나라고 이동할 위치에 초나라가 있다면
	{
		bmove = true;
	}
	return bmove;
}
```
<br>
IsMove함수에 조건을 추가하고 CheckEnemy 함수를 작성해서 적과 아군을 식별하게 만듭니다. 적일 경우 거기 까지만 이동이 가능하고 아군일 경우 이동이 불가능하게 만들어 줍니다. 이를 적용하면 다음과 같습니다.<br>

|기물 1|기물 2|
|:-----:|:-----:|
|<img src="https://user-images.githubusercontent.com/91234912/221480990-4b061b1e-1144-4f29-9c9d-eae04381153e.png" width="500">|<img src="https://user-images.githubusercontent.com/91234912/221480999-34b509d1-4538-4413-b236-1f0165e6013e.png" width="500">|
|<img src="https://user-images.githubusercontent.com/91234912/221481005-058787d1-894c-4ee4-84e4-53cb5bc258e0.png" width="500">|<img src="https://user-images.githubusercontent.com/91234912/221481016-47f8dbfb-9e26-411a-a06f-85b2d9cf5c79.png" width="500">|
<br>
이제 필드메쉬를 동그랗게 바꿔 줍니다. 또한 선택한 말의 위치에 있는 필드를 확대해 주고 금색의 메테리얼을 바위 메테리얼로 바꿔줍니다..
<br>
<img src="https://user-images.githubusercontent.com/91234912/221481023-b3839ccf-0cd6-4ae8-8287-910a642f7cd1.png" width="800"><br><br>
이렇게 만들어진 필드의 Z좌표를 더해주고 보드를 입히면 다음과 같이 보이게 됩니다.

|보드 1|보드 2|
|:-----:|:-----:|
|<img src="https://user-images.githubusercontent.com/91234912/221480911-b5311188-ecf1-4f85-9111-824926aefe02.png" width="500">|<img src="https://user-images.githubusercontent.com/91234912/221480916-f85e2c20-15ef-4541-8571-0903f3dd0937.png" width="500">|
<br><br>

장기는 상차림을 선택해서 상과 마의 위치를 바꿀 수가 있는데, 이를 위한 위젯을 작성합니다.
|보드 1|보드 2|
|:-----:|:-----:|
|<img src="https://user-images.githubusercontent.com/91234912/221480917-e97c86e5-078b-4311-a678-1d42ae2e8f7a.png" width="500">|<img src="https://user-images.githubusercontent.com/91234912/221480920-69ef294d-2bef-45d0-bd6d-288b5f9860c2.png" width="500">|
<br>
위젯의 경우 버튼을 상차림을 선택하기 전까지 선택완료 버튼이 비활성화 됩니다.

## 4 주차<a name='7'></a>
 [목차로 돌아가기](#0)<br>
상의 경우 마에서 대각선으로 한칸만 더 이동 탐색하면 됩니다.<br>
<img src="https://user-images.githubusercontent.com/91234912/226301415-13958098-24f0-46ea-b47f-a192c12bdc92.PNG" width="500"><br>
구현하면 다음과 같이 보입니다. 이제 모든 말의 이동이 완료되었습니다. 저번주에 만들었던 위젯을 통해서 상차림을 구현합니다.<br>
상차림 구현 전에 서버 클라이언트 모두 선택 완료를 누를 경우에 게임이 시작하게 바꿉니다.<br>

-SelectPositionUserWidget.cpp
```c++
void USelectPositionUserWidget::StartButtonCallback()
{
	SoundManager->PlaySound(ButtonClickSoundEffect, ButtonVol);
	TArray<AActor*> OutActors;
	ABoard* JanggiBoard = nullptr;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABoard::StaticClass(), OutActors);
	for (AActor* a : OutActors)
	{
		JanggiBoard = Cast<ABoard>(a);
	}

	Start_TextBlock->SetText(FText::FromString("Waiting"));
	Start_Button->SetIsEnabled(false);
	Select_Button1->SetVisibility(ESlateVisibility::HitTestInvisible);
	Select_Button2->SetVisibility(ESlateVisibility::HitTestInvisible);
	Select_Button3->SetVisibility(ESlateVisibility::HitTestInvisible);
	Select_Button4->SetVisibility(ESlateVisibility::HitTestInvisible);

	if (GetWorld()->GetFirstPlayerController()->GetLocalRole() == ROLE_Authority)
	{
		Controller->SetServerIsReady();
	}
	else if (GetWorld()->GetFirstPlayerController()->GetRemoteRole() == ROLE_Authority)
	{
		Controller->SetClientIsReady();
	}
}
```
<br>	
선택완료 버튼이 눌리면 RPC를 사용하기 위해 다음과 같이 접근합니다. (플레이어 컨트롤러의 서버 RPC 함수 -> 게임 모드)<br>
게임모드에서 클라와 서버가 준비가 되면, 게임을 시작하며, 둘 중 하나라도 준비가 되지 않았다면 대기합니다.<br>
	
|서버|클라이언트|
|:-----:|:-----:|
|<img src="https://user-images.githubusercontent.com/91234912/221481100-2e8dfe4c-8b7e-4cdd-a9ee-58fea09dd41d.png" width="500">|<img src="https://user-images.githubusercontent.com/91234912/221481095-328f0c1a-137e-42b1-b096-07cc3aad54f0.png" width="500">|
<br>
각각 준비가 되지 않으면 시작하지 않습니다.<br>
	
-SelectPositionUserWidget.cpp<br>

```c++
void USelectPositionUserWidget::SelectButton1_Callback() // 마상마상
{
	Select_Button1->SetIsEnabled(false); Select_Button2->SetIsEnabled(true); Select_Button3->SetIsEnabled(true); Select_Button4->SetIsEnabled(true);
	bSelect = true;
	// 1 : 마, 2 : 상, 6 : 상, 7 : 마
	// 82 : 마, 83 : 상, 87 : 상 88 : 마
	// 이 위치만 바꾸면 됨
	if (GetWorld()->GetFirstPlayerController()->GetLocalRole() == ROLE_Authority)
	{
		Controller->SelectPosition(1, RedKnight); // 상을 마로 바꿈
		Controller->SelectPosition(6, RedKnight);
		Controller->SelectPosition(2, RedElephant); // 상을 마로 바꿈
		Controller->SelectPosition(7, RedElephant);
	}
	else if (GetWorld()->GetFirstPlayerController()->GetRemoteRole() == ROLE_Authority)
	{
		Controller->SelectPosition(83, BlueKnight); // 상을 마로 바꿈
		Controller->SelectPosition(88, BlueKnight);
		Controller->SelectPosition(82, BlueElephant); // 상을 마로 바꿈
		Controller->SelectPosition(87, BlueElephant);
	}
	StartButtonActivate();
}
```
<br>
버튼을 누르면 RPC를 이용해서 서버 클라이언트의 상차림을 변경합니다.<br>

|서버|클라이언트|
|:-----:|:-----:|
|<img src="https://user-images.githubusercontent.com/91234912/221481110-bfd4f941-8856-4d31-95e6-9a1c382764df.png" width="500">|<img src="https://user-images.githubusercontent.com/91234912/221481115-de66fae4-0a47-4f2a-aa91-ba43a60efb99.png" width="500">|
|<img src="https://user-images.githubusercontent.com/91234912/221481118-fed3887a-4541-4c07-b3f0-7e9dd8dde16f.png" width="500">|<img src="https://user-images.githubusercontent.com/91234912/221481124-7bcf09db-c51d-42f4-aad7-00f2fbdfc19a.png" width="500">|
<br>

서로 상차림이 변경된 것을 확인할 수 있습니다. 이제 이동을 동기화 합니다.<br>

|서버|클라이언트|
|:-----:|:-----:|
|<img src="https://user-images.githubusercontent.com/91234912/221481107-91efab6f-67c7-426c-b5d7-76327a7e3978.png" width="500">|<img src="https://user-images.githubusercontent.com/91234912/221481109-af9cf953-a089-4714-8d11-a153e257f6f8.png" width="500">|
<br>
서버는 서버에서 먼저 장기를 두고, 클라이언트에서 서버의 움직임을 재현합니다.<br>
클라이언트는 클라에사 먼저 두고 서버에서 두게합니다. 이렇게 함으로써 서로의 움직임이 동기화 됩니다.
<br>
<img src="https://user-images.githubusercontent.com/91234912/221481139-a5b05888-c5eb-4a55-ad77-340002bb8d31.png" width="800"><br>

이제 서로 움직임이 동기화 되었습니다. 착수 위치까지 보여주는 이유는 나중에 스킬 구현을 위해서 입니다.<br>
<img src="https://user-images.githubusercontent.com/91234912/221481150-7a5c8db1-bd30-4d3f-be93-b43b71a37a26.png" width="800"><br>
서버랑 클라가 한템포 늦게 움직이는 문제가 발생해서 기존에는 **Sleep**을 이용해서 한템포 쉬었다가 움직이게 만들었었는데, 잘못된 방법이었습니다.<br>
오류의 이유는 서버가 먼저 움직일 경우 **서버->클라** 순서대로 동작해서 문제가 없었지만 클라가 움직일 경우 **클라->서버** 순서대로 동작했기 때문에 문제가 생긴것이였습니다.<br>
따라서 구조적으로 무조건 **서버가 움직인 후에 클라가 움직이게** 로직을 변경하여 해결하였습니다.<br>

## 5 주차<a name='8'></a>
 [목차로 돌아가기](#0)<br>
 
 필수 요구조건중 하나인 부활을 구현하려고 합니다. 장기를 꽤나 좋아하는 입장에서 장기를 두다가 답답했던 적을 생각해 봤습니다.<br>
 
 |한 나라|초 나라|
|:-----:|:-----:|
|<img src="https://user-images.githubusercontent.com/91234912/221481192-93a47a0d-0805-443c-bf06-b53dbc92ea90.png" width="500">|<img src="https://user-images.githubusercontent.com/91234912/221481196-046e7339-6c11-44c0-996a-5ea8414376ec.png" width="500">|
<br>
제가 생각했을 때 가장 골치 아픈 상황입니다.<br>
서로 수비적인 장기를 하는 경우 게임이 매우 지루해집니다. 모든 기물을 부활 시킬 수도 있겠지만, 졸과 사만 부활 시키려고 합니다.<br><br>
저런 상황에서 졸이 한칸 뒤에서 부활하고 부활하는 위치에 있는 기물 즉 아군이든 적이든 상관없이 파괴하면 재밌겠다는 생각이 들었습니다. 부활 공격으로 졸이나 사를 죽이면 더 이상 부활하지 못하게 만들어도 좋겠네요.<br><br>
졸이 죽으면 중포를 위협 할 수도 있고 사는 제자리에서 부활하면서 왕을 죽여버릴 수도 있는 상황이 생깁니다. 서로 말이 언제 죽었는지 생각해야 하게됩니다.<br>

<br>
-JanggiGameStateBase.cpp
<br>

```c++
void AJanggiGameStateBase::AddResurrectionPieces(int32 curPosition, int32 resurrectPosition, int32 resurrectTurn)
{
	TMap<int32, int32> temp;
	temp.Empty();
	temp.Add(boardIndexArr[curPosition], resurrectPosition);

	resurrectionPos.Add(temp); // Key = 부활 할 말, value : 부활 장소
	resurrectionTurn.Add(resurrectTurn); // 부활 턴
}
```
<br>

부활 해야 하는 말이 죽으면 일정 턴 뒤에 되살아나는 방식입니다. 말이 죽었을 때 부활 시킬 위치를 받고 해당말을 일정 턴 뒤에 부활 시킵니다.<br> 졸은 15턴 뒤에 사는 10턴 뒤에 살아나게끔 만들었습니다.

<br>
-Board.cpp

```c++
void ABoard::IsMove()
{ 
	...

	if (JanggiState->Resurrection())
	{
		BP_ResurrectionEvent();
	}
}
```
<br>
이 턴은 각자 착수 할 경우 JanggiState->Resurrection() 함수가 실행되면서 턴이 하나씩 줄어듭니다.<br>
턴이 0이 되면 BP_ResurrectionEvent()가 실행되면서 저장된 위치에 말이 부활하고 부활 대기열에서 삭제됩니다.<br><br>

 |한 나라|초 나라|
|:-----:|:-----:|
|<img src="https://user-images.githubusercontent.com/91234912/221481184-ae098c8f-4ae6-4d63-afd6-ff51e5d5ee32.png" width="500">|<img src="https://user-images.githubusercontent.com/91234912/221481190-f776ad8e-fa7b-41de-95c2-9612947b8a34.png" width="500">|
<br>

구현 결과물입니다. 의도한대로 잘 작동합니다.<br><br>
장기의 경우 시간패가 있습니다. 제한시간은 정해져 있으며, 시간을 전부 사용한 경우 즉시 패배합니다.<br>
기존에 만들어 뒀던 시간 위젯을 조금 다듬어서 상대방 시간과 내 시간이 보이게 만듭니다.
<br>
-TimerUserWidget.cpp

```c++
void UTimerUserWidget::StartTimer()
{
	// 타이머 핸들러를 통해 시간을 업데이트한다.
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &UTimerUserWidget::CountDown, 1.f, true, 0.0);
	JanggiState = Cast<AJanggiGameStateBase>(GetWorld()->GetGameState());
}
```
<br>
게임이 시작하면 StartTimer 함수를 호출해서 시간을 세기 시작하고<br>

-TimerUserWidget.cpp

```c++
void UTimerUserWidget::CountDown()
{
	const int Red = 1;
	const int Blue = 2;

	if (GetWorld()->GetFirstPlayerController()->GetLocalRole() == ROLE_Authority) // 서버 전용
	{
		if (enemyMinute == 0 && enemySeconds == 0) // 상대의 시간이 없을 때
		{
			for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; Iter++)
			{
				Cast<AJanggiPlayerController>(Iter->Get())->GameOver(true, Red);
			}
		}
		else if (myMinute == 0 && mySeconds == 0) // 내 시간이 없을 때
		{
			for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; Iter++)
			{
				Cast<AJanggiPlayerController>(Iter->Get())->GameOver(true, Blue);
			}
		}
		else if (JanggiState->GetGameTurn() == Red) // 한 나라 턴일 때
		{
			CountMyTime();
		}
		else // 상대 턴일 때
		{
			CountEnemyTime();
		}
	}
	
	else // 클라일 때
	{
		if (JanggiState->GetGameTurn() == Blue) // 초 나라 턴일 때
		{
			CountMyTime();
		}
		else // 상대 턴일 때
		{
			CountEnemyTime();
		}
	}
}
```

상대의 착수 정보만 받아와서 시간을 따로 셉니다.<br><br>

<img src="https://user-images.githubusercontent.com/91234912/221481197-ad6e222f-85b5-4281-9074-6d9fff85e5e8.png" width="800"><br><br>
이제 서로 착수 할 때마다 시간이 넘어갑니다. 남은 시간이 0이 되었을 때 패배화면을 띄워야 합니다.

## 6 주차<a name='9'></a>
 [목차로 돌아가기](#0)<br>
