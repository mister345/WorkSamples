/*******************************************************************************************************
* Copyright Gregory Weiner 2016																		   *
*																									   *
* This is a basic object spawner that can be dragged into an scene in Unreal Engine 4.				   *
* The default implementation "spawns" the objects at the center of a an axis alligned 				   *
* bounding box with an outward velocity. They will disappear after their lifetime 					   *
* (randomly set for each object) has expired, or if they reach the bounds of the box.				   *
* The object spawned is a simple sphere with a point light attached, creating a "sparkler" effect.	   *
*																									   *
* NOTES: 																							   *
*	1. An alternative implementation simply spawns the objects at random locations within the bounds   *
*	of the AABB. The code for that implementation is commented out inside the ObjectPooler file, 	   *
*	referred to as "BASIC VERSION."																	   *
* 																									   *
*	2. This system uses an object pooling pattern, in which the objects are initially spawned using	   *
*	Unreal's Spawn() function, then simply hidden and unhidden to avoid the performance burden of 	   *
*	actually creating and deleting the objects each time the "spawn" and "die." 					   *
*																									   *
*	3. The object pooler itself is implemented using a linked list with O(1) complexity for "spawning" *
*	objects, and alternately implemented by iterating through an array with O(n) complexity for the    *
*	same task. The alternate implementation is titled "ObjectPooler_ON." The linked list version seems *
*	to run about 30% faster on my machine, but results may vary by system.							   *
*																									   *
* REQUIREMENTS: 																					   *
*	Unreal Engine Version 4.14.3																	   *
*	"Shape_Sphere.uasset", "M_Basic_Wall.uasset"													   *
*		these asset files are included in the source folder, and must be placed in the appropriate 	   *
*		directories for the Particle object to render properly, otherwise, start an empty project with *
*		starter content in Unreal Editor, and they will be generated automatically.					   *
*																									   *
********************************************************************************************************/

#pragma once

#include "Components/ActorComponent.h"
#include "ObjectPooler_ON.generated.h"

// Struct for holding pooling and movement related data about the object
USTRUCT(Blueprintable)
struct FObjInfo2
	{
	 GENERATED_USTRUCT_BODY()
		 
	public:
		int lifeTime;
		FVector velocity;
		float gravity = 35.0f;

		FObjInfo2() {}

		void init( int lifetime, const FVector& veloc = { 0.0f, 0.0f, 0.0f } )
		{
			lifeTime = lifetime;
			velocity = veloc;
		}

		void kill()
		{
			lifeTime = 0;
			velocity = {0.0f,0.0f,0.0f};
		}

		void update(float DeltaTime = 0.16f)
		{
			lifeTime--;
			velocity.Z -= gravity*DeltaTime; 
		}
		
		bool alive() const 
		{ 
			return lifeTime > 0; 
		}
	};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OBJECTSPAWNER_API UObjectPooler_ON : public UActorComponent
{
	GENERATED_BODY()

public:	
	UObjectPooler_ON();
	virtual void BeginPlay() override;
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	void Initialize(
		UWorld* pWorld, 
		const FBox& bounds, 
		const int objectCount, 
		const int minLife, 
		const int maxLife, 
		const float velocityDamper, 
		UClass* classType);
	
	// Search the pool for the first available (dead particle), and respawn it
	void SpawnObject();

	// Constantly check for objects that have died, hide them if they have
	void UpdateAll( float DeltaTime = 0.16f );

private:
	FVector RandomTrajectory();	
	FVector RandomLocation();
	int RandomInt( const int min, const int max );
	float RandomFloat( const float min, const float max );

private:
	FBox m_bounds;
	FVector m_minBound;
	FVector m_maxBound;
	FVector m_center;
	
	int m_poolSize;
	TArray<FObjInfo2> m_objectInfo;
	TArray<AActor*> m_objectPool;

	int	m_minLife;
	int m_maxLife;
	float m_velocityDamper;
};
