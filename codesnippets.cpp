AYourClassHere::AYourClassHere()
{
	auto ParentChild = CreateDefaultSubobject<USceneComponent>(TEXT("Parent"));
	
	// Remember to always set a root component or your components won't be attached to blueprint parent
	RootComponent = ParentChild;

	auto SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SkeletalMesh->SetupAttachment(ParentChild);
	SkeletalMesh->SetGenerateOverlapEvents(false);
	SkeletalMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SkeletalMesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
}

void AYourClassHere::BeginPlay()
{
	// Get a component on the blueprint/actor (Similar to unity's GetComponent)
	auto MovementComponent = FindComponentByClass(UCharacterMovementComponent::StaticClass());
	if(MovementComponent != nullptr)
	{
		CharacterMovement = Cast<UCharacterMovementComponent>(MovementComponent);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Character Movement Component Found on Player"));
	}

	// Get all child actors of this actor
	TArray<AActor*> FoundActors;
	GetAllChildActors(FoundActors);

	// Get all actors of specific type
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawnerManager::StaticClass(), FoundActors);

	// Converting types
	int IntValue = 0;
	auto StringValue = FString::FromInt(IntValue);
}

void AYourClassHere::Tick(float DeltaTime)
{
	// Logging
	UE_LOG(LogTemp, Display, TEXT("Hello"));
	UE_LOG(LogTemp, Error, TEXT("Error"));
	UE_LOG(LogTemp, Warning, TEXT("Warning"));

	// Look at (Similar to unity's look at functions)
	auto UpDirection = FVector(0, 0, 1);
	auto Normal = FVector(1, 0, 0);
	auto Rotation = UKismetMathLibrary::MakeRotFromXZ(Normal, FVector::CrossProduct(Normal, UpDirection));

	// Reflect (Similar to unity's reflect functions)
	auto UpDirection = FVector(0, 0, 1);
	auto Normal = FVector(1, 0, 0);
	auto ReflectVector = FMath::GetReflectionVector(UpDirection, Normal);

	// Debug drawing
	auto DebugPosition = FVector(0, 0, 0);
	DrawDebugPoint(GetWorld(), DebugPosition, 200, FColor(255, 0, 0));
	DrawDebugLine(GetWorld(), DebugPosition, DebugPosition + FVector(0, 0, 1), FColor::Emerald);
	
	// Spawning actors 
	UPROPERTY(EditDefaultsOnly, Category = Effects) // This goes in header
	TSubclassOf<class AActor> BlueprintToSpawn;  // This goes in header
	
	auto SpawnPosition = FVector(1, 0, 0);
	auto SpawnRotation = FRotator::RotatorZero;
	auto SpawnActor = World->SpawnActor<ATypeHere>(BlueprintToSpawn,
		SpawnPos, SpawnRotation, ActorSpawnParams);
	
	// Line tracing / raycasting
	auto RayOrigin = FVector(0, 0, 0);
	auto RayEnd = FVector(0, 1, 0);
	
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, this->GetOwner());
	TraceParams.AddIgnoredActor(Character);

	FCollisionObjectQueryParams CollisionObjectTypes;
	CollisionObjectTypes.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
	CollisionObjectTypes.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);

	FHitResult Hit;
	World->LineTraceSingleByObjectType(
		OUT Hit,
		RayOrigin,
		RayEnd,
		CollisionObjectTypes,
		TraceParams
	);

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* ActorHit = Hit.GetActor();
	if(ActorHit != nullptr)
	{
	}
	
	// Sweep testing
	FCollisionShape SweepCollision = FCollisionShape::MakeSphere(CollisionSize);

	FHitResult Hit;
	World->SweepSingleByObjectType(
		OUT Hit,
		RayOrigin,
		RayEnd,
		FQuat::Identity,
		CollisionObjectTypes,
		SweepCollision,
		TraceParams
	);
	
	AActor* ActorHit = Hit.GetActor();
	if(ActorHit != nullptr)
	{
	}
}