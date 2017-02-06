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

#include "Engine.h"

