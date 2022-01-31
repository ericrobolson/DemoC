#include "g_physics.h"
#include "g_malloc.h"
#include "utest.h"
#include <stdint.h>
#include <stdbool.h>

#define MAX_COLLIDEABLES 128

struct GPhysics *g_physics_new()
{
	struct GPhysics *physics;
	physics = g_malloc(sizeof(struct GPhysics));

	if (physics)
	{
		physics->capacity = MAX_COLLIDEABLES;
		physics->count = 0;
		physics->collideables = (struct GCollideable *)g_malloc(MAX_COLLIDEABLES * sizeof(struct GCollideable));

		if (physics->collideables)
		{
			int i = 0;
			for (i = 0; i < MAX_COLLIDEABLES; i++)
			{
				struct GCollideable *p = &physics->collideables[i];
				int64_t entity_id = 0;
				p->entity_id = entity_id;
			}
		}
	}

	return physics;
}

void g_physics_reset(struct GPhysics *physics)
{
	if (physics)
	{
		physics->count = 0;
	}
}

struct GCollideable *g_physics_add_collideable(struct GPhysics *physics)
{
	if (physics && physics->count < physics->capacity)
	{
		struct GCollideable *collideable;
		collideable = &physics->collideables[physics->count];
		collideable->idx = physics->count;
		physics->count += 1;
		return collideable;
	}

	return NULL;
}

struct GCollision *overlaps(const struct GCollideable *a, const struct GCollideable *b)
{
	struct GCollision *collision = NULL;
	// TODO: tests
	//collision.other_idx = 0; // TODO: nuke this. just passing compiler for now.

	// don't collide if same entity or null
	if (!a || !b || a->entity_id == b->entity_id)
	{
		return false;
	}

	// TODO:!!
	// - [ ] aabb + global position

	return collision;
}

bool add_collision(struct GCollideable *c, struct GCollision *collision)
{
	// TODO: tests

	if (c && collision && c->collision_count < c->max_collisioins)
	{
		c->collisions[c->collision_count] = *collision;
		c->collision_count += 1;
		return true;
	}

	return false;
}

void g_physics_tick(struct GPhysics *physics)
{
	if (!physics)
	{
		return;
	}

	// TODO: tests

	int idx1;
	int idx2;

	struct GCollideable *c1 = NULL;
	struct GCollideable *c2 = NULL;

	// Iterate over all collideables, checking for collisions
	int physics_count = physics->count;

	for (idx1 = 0; idx1 < physics_count; idx1++)
	{
		// Get first entity
		c1 = &physics->collideables[idx1];

		// Check others for collisions
		for (idx2 = idx1 + 1; idx2 < physics_count; idx2++)
		{
			// If same, don't compare the two
			if (idx1 == idx2)
			{
				continue;
			}

			// Get second entity
			c2 = &physics->collideables[idx1];

			// If there was a collision, add a new one to the entities
			// and link the collision manifold
			struct GCollision *collision = overlaps(c1, c2);
			if (collision)
			{
				// Add collision to c1
				collision->other_idx = idx2;
				add_collision(c1, collision);

				// Add inverted collision to c2
				collision->other_idx = idx1;
				collision->vector.x = -collision->vector.x;
				collision->vector.y = -collision->vector.y;

				add_collision(c2, collision);
			}
		}
	}
}

//
// g_physics_new
//
UTEST(g_physics, g_physics_new_has_count_0)
{
	struct GPhysics *physics;
	physics = g_physics_new();

	ASSERT_EQ(0, physics->count);
}

UTEST(g_physics, g_physics_new_has_capacity_MAX)
{
	struct GPhysics *physics;
	physics = g_physics_new();

	ASSERT_EQ(MAX_COLLIDEABLES, physics->capacity);
}

UTEST(g_physics, g_physics_new_has_non_null_collideables)
{
	struct GPhysics *physics;
	physics = g_physics_new();

	int j = 0;
	for (j = 0; j < MAX_COLLIDEABLES; j++)
	{
		ASSERT_FALSE(&physics->collideables[j] == NULL);
		ASSERT_EQ(physics->collideables[j].entity_id, 0);
	}
}

//
// g_physics_reset
//
UTEST(g_physics, g_physics_reset_sets_count_to_0)
{
	struct GPhysics *physics;
	physics = g_physics_new();
	physics->count = 123;

	g_physics_reset(physics);

	ASSERT_EQ(0, physics->count);
}

//
// g_physics_tick
//
UTEST(g_physics, g_physics_tick)
{
	ASSERT_TRUE(false);
}

//
// g_physics_add_collideable
//
UTEST(g_physics, g_physics_add_collideable_returns_collideable)
{
	struct GPhysics *physics;
	physics = g_physics_new();

	struct GCollideable *c1 = g_physics_add_collideable(physics);
	ASSERT_TRUE(c1 != NULL);
	ASSERT_TRUE(c1->idx == 0);
	ASSERT_EQ(1, physics->count);

	struct GCollideable *c2 = g_physics_add_collideable(physics);
	ASSERT_TRUE(c2 != NULL);
	ASSERT_TRUE(c2->idx == 1);
	ASSERT_EQ(2, physics->count);
}

UTEST(g_physics, g_physics_add_collideable_null_physics_returns_null)
{
	struct GPhysics *physics = NULL;

	struct GCollideable *c1 = g_physics_add_collideable(physics);
	ASSERT_TRUE(c1 == NULL);
}

UTEST(g_physics, g_physics_add_collideable_max_collideables_returns_null)
{
	struct GPhysics *physics = g_physics_new();

	int i = 0;
	for (i = 0; i < MAX_COLLIDEABLES; i++)
	{

		struct GCollideable *c1 = g_physics_add_collideable(physics);
		ASSERT_TRUE(c1 != NULL);
	}

	// Any more should return null
	struct GCollideable *c = g_physics_add_collideable(physics);
	ASSERT_TRUE(c == NULL);
}

//
// overlaps
//
UTEST(g_physics, overlaps_null_ab_returns_false)
{
	struct GCollideable *a = NULL;
	struct GCollideable *b = NULL;

	struct GCollision *c = overlaps(a, b);
	ASSERT_FALSE(c);
}

UTEST(g_physics, overlaps_null_a_returns_false)
{

	struct GPhysics *physics;
	physics = g_physics_new();

	struct GCollideable *a = NULL;
	struct GCollideable *b = g_physics_add_collideable(physics);

	struct GCollision *c = overlaps(a, b);
	ASSERT_FALSE(c);
}

UTEST(g_physics, overlaps_null_b_returns_false)
{

	struct GPhysics *physics;
	physics = g_physics_new();

	struct GCollideable *a = g_physics_add_collideable(physics);
	struct GCollideable *b = NULL;

	struct GCollision *c = overlaps(a, b);
	ASSERT_FALSE(c);
}

UTEST(g_physics, overlaps_same_entity_id_returns_false)
{
	struct GPhysics *physics;
	physics = g_physics_new();

	struct GCollideable *a = g_physics_add_collideable(physics);
	struct GCollideable *b = g_physics_add_collideable(physics);

	struct GCollision *c = overlaps(a, b);
	ASSERT_FALSE(c);
}

UTEST(g_physics, overlaps_other_tests)
{
	ASSERT_TRUE(false);
}

//
// add_collision
//
UTEST(g_physics, add_collision_all_tests)
{
	ASSERT_TRUE(false);
}
