// Copyright Gregory Weiner 2016

#include "ObjectSpawner.h"
#include <time.h>
#include "ObjectPooler.h"

// Sets default values for this component's properties
UObjectPooler::UObjectPooler()
	:
m_minLife(10),
m_maxLife(100),
m_velocityDamper(0.5)
{
	PrimaryComponentTick.bCanEverTick = false;

	// Seed random number generator with current time
	srand(time(NULL));
}

void UObjectPooler::BeginPlay()
{
	Super::BeginPlay();
}

void UObjectPooler::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void UObjectPooler::Initialize( 
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
	m_objectPool.Reserve( m_poolSize ); 

	/// POPULATE OBJECT POOL AND PARALLEL OBJINFO ARRAY ///
	for ( int i = 0; i < m_poolSize; i++ )
	{
		int lifeTime = 0;

		// Populate array of structs with pooling and movement info about objects
		FObjInfo info;
		info.init( lifeTime, m_center );

		// Spawn actual objects into world for reuse in pool
		AActor* pActor = pWorld->SpawnActor(classType);
		info.pActor = pActor;
		m_objectPool.Add( info );
	}

	/// SET UP LINKS BETWEEN ELEMENTS IN OBJINFO ARRAY ///
	m_pFirstAvailable = &(m_objectPool[ 0 ]);

	// Link the array of objectInfos together
	for ( int i = 0; i < m_poolSize - 1; i++ )
	{
		m_objectPool[ i ].setNext( &(m_objectPool[ i + 1 ]) );
	}

	// The last one terminates the list.
	int nextToLast = m_poolSize - 1;
	m_objectPool[ nextToLast ].setNext( NULL );
}

//////////// SPAWNING RELATED FUNCTIONS /////////////
	// Search the pool for the first available (dead) particle, and respawn it
	void UObjectPooler::SpawnObject()
	{
		if ( m_pFirstAvailable != NULL )
		{
			  FObjInfo* pNew = m_pFirstAvailable;
			  m_pFirstAvailable = pNew->getNext();

			  pNew->init(RandomInt( m_minLife, m_maxLife ), m_center, RandomTrajectory());
		}
	}
	
	// Constantly check for objects that have died, hide them if they have
	void UObjectPooler::UpdateAll( float DeltaTime )
	{
		for ( int i = 0; i < m_poolSize; i++ )
		{
			// IF DEAD
			if ( !m_objectPool[ i ].alive() )
			{
				m_objectPool[ i ].deactivate();

				// Add this object to the front of the list.
				m_objectPool[ i ].setNext( m_pFirstAvailable );
				m_pFirstAvailable = &( m_objectPool[ i ] );
			}
			else // IF ALIVE
			{
				m_objectPool[ i ].update( m_bounds, DeltaTime );
			}
		}
	}

///////////////// MOVEMENT RELATED ///////////////////
FVector UObjectPooler::RandomTrajectory()
{
	FVector randomPoint = RandomLocation();
	FVector velo = randomPoint - m_center;
	return velo *= m_velocityDamper; // damp velocity
}

///////////// RANDOM VALUE GENERATORS ////////////////
FVector UObjectPooler::RandomLocation()
{
	// get random spawn position within bounds
	FVector newPosition = 
	{ RandomFloat( m_minBound.X, m_maxBound.X ), RandomFloat( m_minBound.Y, m_maxBound.Y ), RandomFloat( m_minBound.Z, m_maxBound.Z ) };

	return newPosition;
}

int UObjectPooler::RandomInt(const int min, const int max)
{
	return rand() % (max - min) + min + 1;
}

float UObjectPooler::RandomFloat(const float min, const float max)
{
    // NOTE - assumes max > min
    float random = ((float) rand()) / (float) RAND_MAX;

    // Generate a float between min and max values, then add min
    float range = max - min;  
	return ( random*range ) + min;
}