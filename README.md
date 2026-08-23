# 때려쳐 : 샷건 시뮬레이터


## 프로젝트 소개
- 개발엔진: Unreal Engine 5(5.3.2)
- 개발기간: 2023.11 ~ 2024.12(예정)
- 출시: 2024.12(예정)
- 게임설명 : 직장생활에 지친 직장인들에게 주변 사물을 때려 부수며 스트레스를 풀 수 있는 게임으로, 사실적인 사물표현과 사물파괴를 기반으로 쾌감과 즐거움을 제공하는 게임


## 담당 파트
메인 클라이언트 프로그래머
- 플레이어 조작
- 현실적인 사물 표현 및 사물간 상호작용


## 기술설명

구현 기술에 대한 설명이 필요한 주된 메커니즘들을 설명합니다
- [기반시스템](https://github.com/mw08081/projectD/blob/dev/README.md#%EA%B8%B0%EB%B0%98-%EC%8B%9C%EC%8A%A4%ED%85%9C)
- [Chaos Physics Engine]()
- [Procedural Mesh]()

### 기반 시스템

#### I. 오브젝트 풀링

구현목표 
- 자주 사용하는 Actor를 미리 생성하여 게임을 최적화
  
구현방법 
- TArray<T>를 이용하여 미리 생성후 활성화/비활성화를 통한 Actor 배치
  
코드
```cpp

/// <summary>
/// 풀 초기화, 나이아가라 시스템 풀
/// </summary>
/// <param name="_PoolTargetClass_NsDisplay"></param>
/// <param name="_PoolSize_NsDisplay"></param>
void AObjectPoolSystem::InitializePool_NsDisplay(TSubclassOf<ANsDisplay> _PoolTargetClass_NsDisplay, int32 _PoolSize_NsDisplay)
{
    PoolTargetClass_NsDisplay = _PoolTargetClass_NsDisplay;
    PoolSize_NsDisplay = _PoolSize_NsDisplay;

    for (int32 i = 0; i < PoolSize_NsDisplay; ++i)
    {
        ANsDisplay* NewActor = GetWorld()->SpawnActor<ANsDisplay>(PoolTargetClass_NsDisplay);
        NewActor->SetActorHiddenInGame(true);
        ObjectPool_NsDisplay.Add(NewActor);
    }
}

/// <summary>
/// 풀 받아오기
/// </summary>
/// <returns>사용가능한 액터</returns>
ANsDisplay* AObjectPoolSystem::GetPooledObject_NsDisplay()
{
    for (ANsDisplay* nsDisplay : ObjectPool_NsDisplay)
    {
        if (nsDisplay->IsHidden())
        {
            nsDisplay->SetActorHiddenInGame(false);
            nsDisplay->SetActorTickEnabled(true);
            return nsDisplay;
        }
    }

    return GetAddtionalObject_NsDisplay();
}

/// <summary>
/// 사용가능한 풀이 없을 경우
/// </summary>
/// <returns>추가 액터</returns>
ANsDisplay* AObjectPoolSystem::GetAddtionalObject_NsDisplay()
{
		// 추가 생성
    ANsDisplay* addtionalNewNsDisplay =
			     GetWorld()->SpawnActor<ANsDisplay>(PoolTargetClass_NsDisplay);
			     
		// 비활성화 하여 제공
    addtionalNewNsDisplay->SetActorHiddenInGame(false);
    addtionalNewNsDisplay->SetActorTickEnabled(true);
    return addtionalNewNsDisplay;
}

/// <summary>
/// 액터 사용완료 후, 풀로 반환
/// </summary>
/// <param name="Ns_Display"></param>
void AObjectPoolSystem::ReturnPooledObject_NsDisplay(ANsDisplay* Ns_Display)
{
    Ns_Display->SetActorHiddenInGame(true);
}
```

구현결과

<img width="250" height="210" alt="image" src="https://github.com/user-attachments/assets/ffd070cf-a045-42c2-a139-437ecff5b3fa" />

게임 시작 시, 미리 풀이 형성    
  
<img width="816" height="378" alt="image" src="https://github.com/user-attachments/assets/6159439b-2dca-4e9a-8e01-18b26bea442e" />

액터 요청 시 레벨에 표시 ➡️ 일정시간 이후 회수  

---

### II. 점수증가 feat. Lerp


구현목표 
- 점수 증가의 표현을 시각적으로 표현

구현방법 
- Lerp함수를 이용하여 점수 증가를 시각적으로 표현
- 최대/최소값을 기반으로 작은 값은 최솟값으로, 큰 값은 최댓값으로 제한

코드

```csharp
/// <summary>
/// 점수 획득, 보간 트리거 
/// </summary>
/// <param name="price">획득점수</param>
void AProjectD_DefaultGameMode::GetScore(int32 price)
{
	// 새로운 보간의 시작 (시작 : 현재점수, 목표 : 현재점수 + price)
	ScoreInterpolStartVal = CurScore;
	InterpolTargetScore += price;

	// 보간값 초기화
	ElapsedScoreInterpolTime = 0;
	// 보간 소요시간 기본 설정
	ScoreInterpolDuration = FMath::Abs(ScoreInterpolStartVal - InterpolTargetScore)
															* SCORE_INTERPOL_DURATION_RATE
	// 보간 소요시간 최댓값 필터
	ScoreInterpolDuration = 
						FMath::Min(ScoreInterpolDuration, SOCRE_INTERPOL_MAX_DURATION);
	// 보간 소요시간 최솟값 필터						
	ScoreInterpolDuration = 
						FMath::Max(ScoreInterpolDuration, SCORE_INTERPOL_MIN_DURATION);

	CountSlowStack();
}

/// <summary>
/// Tick함수에서 실행
/// CurScore이 InterpolTargetScore보다 작을때만 실행(GetScore 실행시 Trigger)
/// </summary>
/// <param name="dt">DeltaTime</param>
void AProjectD_DefaultGameMode::InterpolateScore(float dt)
{
	if (CurScore >= InterpolTargetScore) { 
		CurScore = InterpolTargetScore;
		return; 
	}
	ElapsedScoreInterpolTime += dt;

	// 고정된 A to B의 Lerp
	CurScore = FMath::Lerp(ScoreInterpolStartVal, 
												InterpolTargetScore, 
												ElapsedScoreInterpolTime / ScoreInterpolDuration);
}
```

구현결과  
<img width="763" height="394" alt="image" src="https://github.com/user-attachments/assets/baa21806-874d-4c50-ad87-32769581c0df" />
<img width="763" height="394" alt="image" src="https://github.com/user-attachments/assets/e4c5c43a-0ca4-4099-8e73-e3486eff7ad8" />


### III. 벡터의 내적을 이용하여 액터를 던지는 각도 계산

구현목표 
- 액터를 던지는 각도에 따라 Directinal Mag의 크기 조절 구현

구현방법 
- 플레이어의 Forward Vector와 카메라 Forward Vector의 내적을 이용하여 던지는 각도 계산
- 각도에 따라 Directional Mag 감소 여부 확인

코드

<img width="639" height="253" alt="image" src="https://github.com/user-attachments/assets/2923be71-903f-4ca9-8903-d04fd204f113" />

플레이어의 Forward Vector와 카메라 Forward Vector의 내적을 이용하여 던지는 각도 계산

<img width="468" height="238" alt="image" src="https://github.com/user-attachments/assets/150909a4-58d5-4217-98da-4a6eebc80aaf" />

<img width="588" height="286" alt="image" src="https://github.com/user-attachments/assets/fd576d55-eb44-48af-ac57-cb16b9c7d491" />

각도에 따라 Directional Mag 감소 여부 확정

구현결과

<img width="654" height="407" alt="image" src="https://github.com/user-attachments/assets/aad7f2eb-6321-4bc5-b96e-62839c7af0a7" />

파편 분산 정도(Directional Magnitude) 정상적용

<img width="654" height="407" alt="image" src="https://github.com/user-attachments/assets/78206b39-1866-48b7-8501-bd4be5c9b08c" />

파편 분산 정도(Directional Magnitude) 감소

---

### Chaos Physics Engine

#### I. Fracture System

구현목표 
- Static Mesh와 다르게 부숴지는 액터를 카오스 물리엔진으로 표현

구현방법 
- 프렉쳐 시스템을 이용하여 Geometry Collection 생성
- Convex 콜리전을 세밀하게 조정

<img width="885" height="558" alt="image" src="https://github.com/user-attachments/assets/3acf918c-478d-4206-8045-d022238edc63" />

총 23조각으로 Fracture 적용, Geometry Collection의 엉성한 Convex 콜리젼

<img width="624" height="227" alt="image" src="https://github.com/user-attachments/assets/a5ef981c-b7d4-4d8c-b370-4b99c5c9a06e" />

구현결과  

- 머그컵 데미지 임계점 : 3,000
<img width="451" height="313" alt="image" src="https://github.com/user-attachments/assets/b027b5f5-ad7d-4cf5-ac3c-304190e63aca" />

좌 데미지: 2000, 우 데미지: 5000


---

#### II. Geometry Collecion - Set Actor Location 의 한계

구현목표 
- Set Actor Location 이 안 되기 때문에, 물건을 집어 던지는 행위에 제한 발생
    ➡️ 던질 수 있도록 구현
    

구현방법 
- 액터 이동 필요 시 Static Mesh 모델 사용
- 던져서 충돌 시 Geometry Collection과 Master Field를 생성하여 파괴

코드

<img width="866" height="426" alt="image" src="https://github.com/user-attachments/assets/09e52e82-c5dc-4201-aeba-dcc212d749ac" />

Master Field 생성 (추후 오브젝트 풀링 적용)

---
<img width="692" height="547" alt="image" src="https://github.com/user-attachments/assets/0193f9e4-3017-4289-80ca-47668b61e395" />

Geometry Collection 생성

구현결과  

<img width="451" height="313" alt="image" src="https://github.com/user-attachments/assets/7ae99be8-45ca-4487-928c-bcbcf3554e8b" />

던져지는 순간 Static Mesh 사용 ➡️ 부딪히는 순간부터 Geometry Collection 사용


---

#### III. Field System - Bomb Field


구현목표 
- Fracture System 뿐만 아니라 Static Mesh에도 영향을 줄 수 있도록 구현

구현방법 
- Static Mesh 액터와 Geometry Collection액터에 Field System에 대한 Overlap Event 추가
- 피직스 바디 깨우기(수정)
- Geomoetry Collection과의 콜리젼 발생(수정)

코드
<img width="719" height="300" alt="image" src="https://github.com/user-attachments/assets/e3dff8d2-1524-4125-bfdb-24ec1e68c97e" />

구현결과
<img width="816" height="378" alt="image" src="https://github.com/user-attachments/assets/4cf0cfbf-f711-40eb-929c-4e47228f2622" />

---

### Procedural Mesh

#### I. Procedural Mesh

<aside>
✨

구현목표 

- Static Mesh와 실시간으로 변형되어 찌그러짐을 표현

구현방법 

- 기본 Static Mesh로 부터 Procedural Mesh 생성
- player Tag를 가진 액터와의 충돌에서 계산된 충격량에 따라 찌그러짐구현

코드

![충돌 부분의 인근 정점 수집 →  정점 위치 변형](%EB%95%8C%EB%A0%A4%EC%B3%90%20%EC%83%B7%EA%B1%B4%20%EC%8B%9C%EB%AE%AC%EB%A0%88%EC%9D%B4%ED%84%B0/image%2010.png)

충돌 부분의 인근 정점 수집 →  정점 위치 변형

![변경된 정점에 따라 Procedural Mesh와 Convex Mesh 업데이트](%EB%95%8C%EB%A0%A4%EC%B3%90%20%EC%83%B7%EA%B1%B4%20%EC%8B%9C%EB%AE%AC%EB%A0%88%EC%9D%B4%ED%84%B0/image%2011.png)

변경된 정점에 따라 Procedural Mesh와 Convex Mesh 업데이트

- 전체코드 : [https://blueprintue.com/render/heumgs78/](https://blueprintue.com/render/heumgs78/)
- Get Points In Sphere : [https://blueprintue.com/blueprint/__0gkx4p/](https://blueprintue.com/blueprint/__0gkx4p/)
- Update Vertex Position 코드 : [https://blueprintue.com/blueprint/ak95lnla/](https://blueprintue.com/blueprint/ak95lnla/)

구현결과

![실시간으로 변형되는 Procedural Mesh](%EB%95%8C%EB%A0%A4%EC%B3%90%20%EC%83%B7%EA%B1%B4%20%EC%8B%9C%EB%AE%AC%EB%A0%88%EC%9D%B4%ED%84%B0/pc.gif)

실시간으로 변형되는 Procedural Mesh

![변형된 컨벡스 메시](%EB%95%8C%EB%A0%A4%EC%B3%90%20%EC%83%B7%EA%B1%B4%20%EC%8B%9C%EB%AE%AC%EB%A0%88%EC%9D%B4%ED%84%B0/image%2012.png)

변형된 컨벡스 메시

</aside>
