// Copyright Gregory Weiner 2016

#include "ObjectSpawner.h"
#include <time.h>
#include "ObjectPooler_ON.h"

// Sets default values for this component's properties
UObjectPooler_ON::UObjectPooler_ON()
	:
m_minLife(10),
m_maxLife(100),
m_velocityDamper(0.5)
{
	PrimaryComponentTick.bCanEverTick = false;

	// Seed random number generator with current time
	srand(time(NULL));
}

void UObjectPooler_ON::BeginPlay()
{
	Super::BeginPlay();
}

void UObjectPooler_ON::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void UObjectPooler_ON::Initialize( 
	UWorld* pWorld, 
	const FBox& bounds, 
	const int objectCount, 
	const int minLife, 
	const int maxLife, 
	const float velocityDamper, 
	UClass* classType)
{
	// Init bounds
	m_bounds = bounds;
	m_minBound = bounds.Min;
	m_maxBound = bounds.Max;
	m_center = bounds.GetCenter();

	// Init lifetime limits
	m_minLife = minLife;
	m_maxLife = maxLife;
	
	// Set initial object count
	m_poolSize = objectCount;

	// Used for adjusting particle velocities
	m_velocityDamper = velocityDamper;
		
	// Avoid multiple allocations while iterating
	m_objectInfo.Reserve( m_poolSize ); 
	m_objectPool.Reserve( m_poolSize );

	/// POPULATE OBJECT POOL AND PARALLEL OBJINFO ARRAY ///
	for ( int i = 0; i < m_poolSize; i++ )
	{
		int lifeTime = 0;
		//	NOTE - for SPARKLER Effect, set lifetime = 0
		//		   For BASIC VERSION, start it with a random lifetime.
		//  int lifeTime = RandomInt( m_minLife, m_maxLife );	
		
		// Populate array of structs with pooling and movement info about objects
		FObjInfo2 info;
		info.init( lifeTime );
		m_objectInfo.Add( info );

		// Spawn actual objects into world for reuse in pool
		AActor* pParticle = pWorld->SpawnActor(classType);
		m_objectPool.Add( pParticle );		  
		// NOTE - For BASIC VERSION, should give actor a random location.
		// pParticle->SetActorLocation( RandomLocation() );
	}
}

//////////// SPAWNING RELATED FUNCTIONS /////////////
	// Search the pool for the first available (dead) particle, and respawn it
	void UObjectPooler_ON::SpawnObject()
	{
		for ( int i = 0; i < m_poolSize; i++ )
		{
			if ( !m_objectInfo[ i ].alive() ) // find the FIRST DEAD PARTICLE
			{
				//////// SPECIFIC TO SPARKLER VERSION ////////
				m_objectInfo[ i ].init(RandomInt( m_minLife, m_maxLife ), RandomTrajectory() );
				m_objectPool[ i ]->SetActorLocation( m_center );

				//////// SPECIFIC TO BASIC VERSION ///////////
				//m_objectInfo[ i ].init(RandomInt( m_minLife, m_maxLife ) );
				//m_objectPool[ i ]->SetActorLocation( RandomLocation() );

				m_objectPool[ i ]->SetActorHiddenInGame( false );
				return;
			}
		}
	}
	
	// Constantly check for objects that have died, hide them if they have
	void UObjectPooler_ON::UpdateAll( float DeltaTime )
	{
		for ( int i = 0; i < m_poolSize; i++ )
		{
			// DEAD
			if ( !m_objectInfo[ i ].alive() )
			{
				m_objectPool[ i ]->SetActorHiddenInGame( true );
			}			
			else // ALIVE
			{
				m_objectInfo[ i ].update( DeltaTime );

				//////// SPECIFIC TO SPARKLER VERSION ////////
				FVector pos = m_objectPool[ i ]->GetActorLocation();
				if ( m_bounds.IsInside( pos ) )
				{
					FVector newLocation = pos + m_objectInfo[ i ].velocity * DeltaTime;
					m_objectPool[ i ]->SetActorLocation( newLocation );
				}
				else
				{
					m_objectPool[ i ]->SetActorHiddenInGame( true );
					m_objectInfo[ i ].kill();
				}
			}
		}
	}

///////////////// MOVEMENT RELATED ///////////////////
FVector UObjectPooler_ON::RandomTrajectory()
{
	FVector randomPoint = RandomLocation();
	FVector velo = randomPoint - m_center;
	return velo *= m_velocityDamper; // damp velocity
}

///////////// RANDOM VALUE GENERATORS ////////////////
FVector UObjectPooler_ON::RandomLocation()
{
	// get random spawn position within bounds
	FVector newPosition = 
	{ RandomFloat( m_minBound.X, m_maxBound.X ), RandomFloat( m_minBound.Y, m_maxBound.Y ), RandomFloat( m_minBound.Z, m_maxBound.Z ) };

	return newPosition;
}

int UObjectPooler_ON::RandomInt(const int min, const int max)
{
	return rand() % (max - min) + min + 1;
}

float UObjectPooler_ON::RandomFloat(const float min, const float max)
{
    // NOTE - assumes max > min
    float random = ((float) rand()) / (float) RAND_MAX;

    // Generate a float between min and max values, then add min
    float range = max - min;  
	return ( random*range ) + min;
}