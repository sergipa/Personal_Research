#ifndef __Collision_H__
#define __Collision_H__

#include "Module.h"
#include "PerfTimer.h"

class QuadTree;

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_FRIENDLY_UNIT,

	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	Module* callback = nullptr;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class Collision : public Module
{
public:

	Collision();
	virtual ~Collision();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = nullptr);
	void DeleteCollider(Collider* collider);
	void DebugDraw();

private:

	list<Collider*> colliders;
	bool debug = false;
	int bruteForceChecks = 0;
	int quadTreeChecks = 0;
	PerfTimer bruteForceTimer;
	PerfTimer quadTreeTimer;

	//TODO 3: Declare variables

public:
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
};

#endif // __ModuleCollision_H__

