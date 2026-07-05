// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

int TestFunction(float MyParam1, int MyParam2, FString MyString)
{
	UE_LOG(LogTemp, Display, TEXT("My parameter 1: %f"), MyParam1);
	UE_LOG(LogTemp, Display, TEXT("My parameter 2: %d"), MyParam2);
	UE_LOG(LogTemp, Display, TEXT("My string: %s"), *MyString);

	return 40;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	FString Name = GetName();
	int ReturnValue = TestFunction(4.3f, 10, Name);
	UE_LOG(LogTemp, Display, TEXT("Return value is %d"), ReturnValue);


	StartLocation = GetActorLocation();

}

// Called every frames
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);

}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	DistanceMoved = GetDistanceMoved();

	//fixed overshoot by using vectors
	if (DistanceMoved >= MoveDistance)
	{
		float Overshoot = DistanceMoved - MoveDistance;
		FString Platform = GetName();
		UE_LOG(LogTemp, Error, TEXT("%s overshot by %f"), *Platform, Overshoot);
		
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		FVector NewStartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(NewStartLocation);
		StartLocation = NewStartLocation;

		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		FVector CurrentLocation = GetActorLocation();


		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);

		SetActorLocation(CurrentLocation);

	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	FRotator RotationToAdd = RotationVelocity * DeltaTime;
	AddActorLocalRotation(RotationToAdd);
}

float AMovingPlatform::GetDistanceMoved()
{
	return FVector::Dist(StartLocation,GetActorLocation());
}
