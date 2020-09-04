#include "Swept_AABB.h"
#include <limits>
#include <algorithm>
#include "PhysicsObject.h"
#include <iostream>

constexpr float EPSILON = 0.00001f;

// d�nd� = collision time , normal info
CollisionInfo SweptAABB(const PhysicsObject& dynamic, const HitBox& staTHICC)
{
	float xDisEntry, yDisEntry, zDisEntry;
	float xDisExit,  yDisExit,  zDisExit;

	glm::vec3 v = dynamic.getVelocity();
	HitBox dynaMHICC = dynamic.getHitBox();

	// find the distance between the objects on the near and far sides for both x and y 
	if (v.x > 0.0f)
	{
		xDisEntry = staTHICC.x - (dynaMHICC.x + dynaMHICC.w);
		xDisEntry = abs(xDisEntry) < EPSILON ? 0 : xDisEntry;
		xDisExit  = (staTHICC.x + staTHICC.w) - dynaMHICC.x;
		xDisExit = abs(xDisExit) < EPSILON ? 0 : xDisExit;
	}
	else
	{
		xDisEntry = (staTHICC.x + staTHICC.w) - dynaMHICC.x;
		xDisEntry = abs(xDisEntry) < EPSILON ? 0 : xDisEntry;
		xDisExit  = staTHICC.x - (dynaMHICC.x + dynaMHICC.w);
		xDisExit = abs(xDisExit) < EPSILON ? 0 : xDisExit;
		if (v.x == 0.0f)
		{
			if(!(xDisEntry > 0 && xDisExit < 0))
			{
				//std::cout << "exit by x\n";
				return { 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(staTHICC.x + staTHICC.w / 2, staTHICC.y + staTHICC.h / 2, staTHICC.z + staTHICC.d / 2) };
			}
		}
	}
	
	if (v.y > 0.0f)
	{
		yDisEntry = staTHICC.y - (dynaMHICC.y + dynaMHICC.h);
		yDisEntry = abs(yDisEntry) < EPSILON ? 0 : yDisEntry;
		yDisExit  = (staTHICC.y + staTHICC.h) - dynaMHICC.y;
		yDisExit = abs(yDisExit) < EPSILON ? 0 : yDisExit;
	}
	else
	{
		yDisEntry = (staTHICC.y + staTHICC.h) - dynaMHICC.y;   
		yDisEntry = abs(yDisEntry) < EPSILON ? 0 : yDisEntry;
		yDisExit  = staTHICC.y - (dynaMHICC.y + dynaMHICC.h);  
		yDisExit = abs(yDisExit) < EPSILON ? 0 : yDisExit;
		if (v.y == 0.0f)
		{
			if (!(yDisEntry > 0 && yDisExit < 0))
			{
				//std::cout << "exit by y\n";
				return { 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(staTHICC.x + staTHICC.w / 2, staTHICC.y + staTHICC.h / 2, staTHICC.z + staTHICC.d / 2) };
			}
		}
	}

	if (v.z > 0.0f)
	{
		zDisEntry = staTHICC.z - (dynaMHICC.z + dynaMHICC.d);
		zDisEntry = abs(zDisEntry) < EPSILON ? 0 : zDisEntry;
		zDisExit  = (staTHICC.z + staTHICC.d) - dynaMHICC.z;
		zDisExit = abs(zDisExit) < EPSILON ? 0 : zDisExit;
	}
	else
	{
		zDisEntry = (staTHICC.z + staTHICC.d) - dynaMHICC.z;
		zDisEntry = abs(zDisEntry) < EPSILON ? 0 : zDisEntry;
		zDisExit  = staTHICC.z - (dynaMHICC.z + dynaMHICC.d);
		zDisExit = abs(zDisExit) < EPSILON ? 0 : zDisExit;
		if (v.z == 0.0f)
		{
			if (!(zDisEntry > 0 && zDisExit < 0))
			{
				//std::cout << "exit by z\n";
				return { 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(staTHICC.x + staTHICC.w / 2, staTHICC.y + staTHICC.h / 2, staTHICC.z + staTHICC.d / 2) };
			}
		}
	}

	//calculate times 

	float xEntry, yEntry, zEntry;
	float xExit,  yExit,  zExit;

	if (v.x == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit  =  std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xDisEntry / v.x;
		xExit  = xDisExit  / v.x;
	}

	if (v.y == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit  =  std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yDisEntry / v.y;
		yExit  = yDisExit  / v.y;
	}

	if (v.z == 0.0f)
	{
		zEntry = -std::numeric_limits<float>::infinity();
		zExit  =  std::numeric_limits<float>::infinity();
	}	
	else
	{
		zEntry = zDisEntry / v.z;
		zExit  = zDisExit  / v.z;
	}

	//calculate last entry time and first exit time

	float entryTime = std::max({ xEntry, yEntry, zEntry });

	float exitTime = std::min({ xExit, yExit, zExit });
	float normalx, normaly, normalz;

	// if there was no collision

	//std::cout << std::endl;
	//std::cout << staTHICC.x << " " << staTHICC.y << " " << staTHICC.z << std::endl;
	//std::cout << entryTime << std::endl;
	//std::cout << exitTime << std::endl;
	//std::cout << xEntry << std::endl;
	//std::cout << yEntry << std::endl;
	//std::cout << zEntry << std::endl;

	if (entryTime > exitTime || (xEntry < 0.0f && yEntry < 0.0f && zEntry < 0.0f) || 
		xEntry > 1.0f || yEntry > 1.0f || zEntry > 1.0f) 
	{
		normalx = 0.0f;
		normaly = 0.0f;
		normalz = 0.0f;

		return { 1.0f, glm::vec3(normalx, normaly, normalz), glm::vec3(staTHICC.x + staTHICC.w / 2, staTHICC.y + staTHICC.h / 2, staTHICC.z + staTHICC.d / 2) };
	}
	else // if there was a collision 
	{
		// calculate normal of collided surface
		if (xEntry == entryTime)
		{
			if (xDisEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
				normalz = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
				normalz = 0.0f;
			}
		}
		else if (yEntry == entryTime)
		{
			if (yDisEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
				normalz = 0.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
				normalz = 0.0f;
			}
		} 
		else
		{
			if (zDisEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = 0.0f;
				normalz = 1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = 0.0f;
				normalz = -1.0f;
			}
		}

		return { entryTime, glm::vec3(normalx, normaly, normalz), glm::vec3(staTHICC.x + staTHICC.w / 2, staTHICC.y + staTHICC.h / 2, staTHICC.z + staTHICC.d / 2) };
	}
}