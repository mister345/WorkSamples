/*******************************************************************************************************
* Copyright Gregory Weiner 2016																		   *
*																									   *
* This is a basic object spawner that can be dragged into an scene in Unreal Engine 4.				   *
* Objects "spawn" at the center of an axis-alligned bounding box with an outward velocity. 			   *
* They will disappear after their lifetime (randomly set for each object) has expired, 				   *
* or if they reach the bounds of the box. The default object spawned is a simple sphere with 		   *
* a point light attached, creating a "sparkler" effect.												   *
*  																									   *
* This system uses an object pooling pattern, in which the objects are initially spawned using	       *
* Unreal's Spawn() function, then simply hidden and unhidden to avoid the performance burden of 	   *
* actually creating and deleting the objects each time the "spawn" and "die." 					       *
*																									   *
* The object pooler itself is implemented using a linked list with O(1) complexity for "spawning"      *
* objects. The linked list implementation shows a roughly 30% performance increase on my machine 	   *
* compared to an older O(n) implementation that iterates through the entire pool in search of an 	   *
* available object.																					   *
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
#include "ObjectPooler.generated.h"

// Struct for holding pooling and movement related data about the object
USTRUCT(Blueprintable)
struct FObjInfo
	{
	 GENERATED_USTRUCT_BODY()
		 
	public:
		int lifeTime;
		FVector velocity;
		float gravity = 35.0f;

		AActor* pActor;
		FObjInfo* pNext;

		FObjInfo() {}

		void init( int lifetime, const FVector& pos, const FVector& veloc = { 0.0f, 0.0f, 0.0f } )
		{
			lifeTime = lifetime;
			velocity = veloc;

			pActor->SetActorLocation( pos );
			pActor->SetActorHiddenInGame( false );
		}

		void deactivate()
		{
			lifeTime = 0;
			pActor->SetActorHiddenInGame( true );
			velocity = {0.0f,0.0f,0.0f};
		}

		void update( const FBox& bounds, float DeltaTime = 0.16f )
		{
			FVector pos = pActor->GetActorLocation();
			if ( bounds.IsInside( pos ) )
			{
				lifeTime--;
				velocity.Z -= gravity*DeltaTime;
				pActor->SetActorLocation( pos + velocity * DeltaTime );
			}
			else
			{
				deactivate();
			}
		}
		
		bool alive() const 
		{ 
			return lifeTime > 0; 
		}

		FObjInfo* getNext() 
		{ 
			return pNext; 
		}
		
		void setNext(FObjInfo* next)
		{ 
			pNext = next; 
		}
	};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OBJECTSPAWNER_API UObjectPooler : public UActorComponent
{
	GENERATED_BODY()

public:	
	UObjectPooler();
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
	TArray<FObjInfo> m_objectPool;

	int	m_minLife;
	int m_maxLife;
	float m_velocityDamper;

	// Used for O(1) access when spawning
	FObjInfo* m_pFirstAvailable;
};
