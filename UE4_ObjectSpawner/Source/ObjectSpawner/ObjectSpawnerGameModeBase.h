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

#include "GameFramework/GameModeBase.h"
#include "ObjectSpawnerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class OBJECTSPAWNER_API AObjectSpawnerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	
	
	
};
