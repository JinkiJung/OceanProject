// 2016 - Community based open project

#include "OceanProject.h"
#include "TopViewCameraPawn.h"


// Sets default values
ATopViewCameraPawn::ATopViewCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �� ���� ���� ���� ��ȣ�� �÷��̾ �����ϵ��� �����մϴ�
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// ���𰡸� ���� ���� ��Ʈ ������Ʈ�� ����ϴ�
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// ī�޶�� ���̴� ������Ʈ�� ����ϴ�
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	//OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	// ��Ʈ ������Ʈ�� ī�޶�� ���̴� ������Ʈ�� ���Դϴ�. ī�޶� �̰� �� ȸ����ŵ�ϴ�.
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 2500.0f));
	OurCamera->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	//OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATopViewCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATopViewCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// "Grow" �׼ǿ� ���� Ű��� ���̴� ���� ó���մϴ�
	{
		float CurrentScale = OurVisibleComponent->GetComponentScale().X;
		if (bGrowing)
		{
			// 1 �ʿ� ���� �� �� ũ��� Ű��ϴ�
			CurrentScale += DeltaTime;
		}
		else
		{
			// Ű�� �ӵ���� �������� ���Դϴ�
			CurrentScale -= (DeltaTime * 0.5f);
		}
		// ���� ũ�� �Ʒ��� ���̰ų� �� �� �̻����� Ű���� �ʵ��� �մϴ�.
		CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
		OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));
	}

	// "MoveX" �� "MoveY" �࿡ ���� �̵��� ó���մϴ�
	{
		if (!CurrentVelocity.IsZero())
		{
			FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
			SetActorLocation(NewLocation);
		}
	}
}

// Called to bind functionality to input
void ATopViewCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// "Grow" Ű�� �����ų� �� �� �����մϴ�
	//InputComponent->BindAction("Grow", IE_Pressed, this, &ATopViewCameraPawn::StartGrowing);
	//InputComponent->BindAction("Grow", IE_Released, this, &ATopViewCameraPawn::StopGrowing);

	// "MoveX" �� "MoveY" �� �̵� ���� ���� �� ������ �����մϴ�
	//InputComponent->BindAxis("MoveX", this, &ATopViewCameraPawn::Move_XAxis);
	//InputComponent->BindAxis("MoveY", this, &ATopViewCameraPawn::Move_YAxis);

}

void ATopViewCameraPawn::Move_XAxis(float AxisValue)
{
	// �ʴ� 100 ������ �� �Ǵ� �ڷ� �����Դϴ�
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void ATopViewCameraPawn::Move_YAxis(float AxisValue)
{
	// �ʴ� 100 ������ ������ �Ǵ� �������� �����Դϴ�
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void ATopViewCameraPawn::StartGrowing()
{
	bGrowing = true;
}

void ATopViewCameraPawn::StopGrowing()
{
	bGrowing = false;
}

