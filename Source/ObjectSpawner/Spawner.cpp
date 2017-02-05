// Copyright Gregory Weiner 2016

#include "ObjectSpawner.h"
#include "Particle.h"
#include "ObjectPooler.h"
#include "Spawner.h"

ASpawner::ASpawner()
	:
	m_origin( 0.f, 0.f, 0.f ),
	m_extent( 100.f, 100.f, 100.f ),
	m_numParticles( 100 ),
	m_minLifetime( 10 ),
	m_maxLifetime( 100 ),
	m_velocityDamper( 0.3f ),
	m_classType(AParticle::StaticClass())
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create object pooler
	m_pPooler = CreateDefaultSubobject<UObjectPooler>( TEXT( "ObjectPooler" ) );
}

void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	// Build bounding box to latest specs set by editor
	m_bounds = FBox::BuildAABB( m_origin, m_extent );

	// Pool will spawn array of reusable objects:
	UWorld* pWorld = GetWorld();
	if ( pWorld )
	{
		m_pPooler->Initialize(
			pWorld,
			m_bounds,
			m_numParticles,
			m_minLifetime,
			m_maxLifetime,
			m_velocityDamper,
			m_classType );
	}
}

// Called every frame
void ASpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	m_pPooler->UpdateAll(DeltaTime); // Update object motion and status
	m_pPooler->SpawnObject(); // Get new object from pool if available
}