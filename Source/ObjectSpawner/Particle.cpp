// Copyright Gregory Weiner 2016

#include "ObjectSpawner.h"
#include "Particle.h"

AParticle::AParticle()
	:
	m_bobHeight( 50.f ),
	m_sphereRadius(0.009f),
	m_lightIntensity(50.f)
{
	// Must turn on for floating animation
	PrimaryActorTick.bCanEverTick = false;

	// Set visual sphere as the root component
    SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
    RootComponent = SphereVisual;
	
	// NOTE - Shape_Sphere.uasset must be located in the following directory at compile time (will be automatically created for projects with starter content)
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));

	// Otherwise, the Shape_Sphere.uasset file must be physically located in the project's "Content" folder at compile time for it to show up
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/Shape_Sphere.Shape_Sphere"));
	
	if (SphereVisualAsset.Succeeded())
    {
        SphereVisual->SetStaticMesh(SphereVisualAsset.Object);	
        SphereVisual->SetWorldScale3D(FVector(m_sphereRadius));
    }

	// Create and attach point light
	PointLight1 = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight1"));
	PointLight1->Intensity = m_lightIntensity;
	PointLight1->bVisible = true;
	PointLight1->SetupAttachment(SphereVisual);
}

void AParticle::BeginPlay()
{
	Super::BeginPlay();
}

void AParticle::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	//Oscillate( DeltaTime );
}

// Make the actor bob up and down
void AParticle::Oscillate( float DeltaTime )
{
	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(m_runningTime + DeltaTime) - FMath::Sin(m_runningTime));
	NewLocation.Z += DeltaHeight * m_bobHeight; //Scale height by a factor of m_bobHeight
	m_runningTime += DeltaTime*10.0;
	SetActorLocation(NewLocation);
}

// Reflect changes in editor
void AParticle::UpdateValues()
{
	SphereVisual->SetWorldScale3D(FVector(m_sphereRadius));
}

#if WITH_EDITOR
void AParticle::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UpdateValues();
    Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif