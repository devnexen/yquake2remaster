/*
 * Copyright (C) 1997-2001 Id Software, Inc.
 * Copyright (c) ZeniMax Media Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * =======================================================================
 *
 * Mechanic.
 *
 * =======================================================================
 */

#include "../../header/local.h"
#include "float.h"

static int sound_attack2;
static int sound_attack3;
static int sound_death1;
static int sound_idle;
static int sound_pain1;
static int sound_pain2;
static int sound_sight;

void floater_dead(edict_t *self);
void floater_die(edict_t *self, edict_t *inflictor, edict_t *attacker,
		int damage, vec3_t point);
void floater_run(edict_t *self);
void floater_wham(edict_t *self);
void floater_zap(edict_t *self);

void
floater_sight(edict_t *self, edict_t *other /* unused */)
{
	if (!self)
	{
		return;
	}

	gi.sound(self, CHAN_VOICE, sound_sight, 1, ATTN_NORM, 0);
}

void
floater_idle(edict_t *self)
{
	if (!self)
	{
		return;
	}

	gi.sound(self, CHAN_VOICE, sound_idle, 1, ATTN_IDLE, 0);
}

void
floater_fire_blaster(edict_t *self)
{
	vec3_t start;
	vec3_t forward, right;
	vec3_t end;
	vec3_t dir;
	int effect;

	if (!self || !self->enemy || !self->enemy->inuse)
	{
		return;
	}

	if ((self->s.frame == FRAME_attak104) || (self->s.frame == FRAME_attak107))
	{
		effect = EF_HYPERBLASTER;
	}
	else
	{
		effect = 0;
	}

	AngleVectors(self->s.angles, forward, right, NULL);
	G_ProjectSource(self->s.origin, monster_flash_offset[MZ2_FLOAT_BLASTER_1],
			forward, right, start);

	VectorCopy(self->enemy->s.origin, end);
	end[2] += self->enemy->viewheight;
	VectorSubtract(end, start, dir);

	monster_fire_blaster(self, start, dir, 1, 1000, MZ2_FLOAT_BLASTER_1, effect);
}

static mframe_t floater_frames_stand1[] = {
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL}
};

mmove_t floater_move_stand1 =
{
	FRAME_stand101,
	FRAME_stand152,
	floater_frames_stand1,
	NULL
};

static mframe_t floater_frames_stand2[] = {
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL},
	{ai_stand, 0, NULL}
};

mmove_t floater_move_stand2 =
{
	FRAME_stand201,
	FRAME_stand252,
	floater_frames_stand2,
	NULL
};

void
floater_stand(edict_t *self)
{
	if (!self)
	{
		return;
	}

	if (random() <= 0.5)
	{
		self->monsterinfo.currentmove = &floater_move_stand1;
	}
	else
	{
		self->monsterinfo.currentmove = &floater_move_stand2;
	}
}

static mframe_t floater_frames_activate[] = {
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL}
};

mmove_t floater_move_activate =
{
	FRAME_actvat01,
	FRAME_actvat31,
	floater_frames_activate,
	NULL
};

static mframe_t floater_frames_attack1[] = {
	{ai_charge, 0, NULL}, /* Blaster attack */
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, floater_fire_blaster}, /* BOOM (0, -25.8, 32.5)	-- LOOP Starts */
	{ai_charge, 0, floater_fire_blaster},
	{ai_charge, 0, floater_fire_blaster},
	{ai_charge, 0, floater_fire_blaster},
	{ai_charge, 0, floater_fire_blaster},
	{ai_charge, 0, floater_fire_blaster},
	{ai_charge, 0, floater_fire_blaster},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL} /*	-- LOOP Ends */
};

mmove_t floater_move_attack1 =
{
	FRAME_attak101,
	FRAME_attak114,
	floater_frames_attack1,
	floater_run
};

/* circle strafe frames */
static mframe_t floater_frames_attack1a[] =
{
	{ai_charge, 10, NULL},			// Blaster attack
	{ai_charge, 10, NULL},
	{ai_charge, 10, NULL},
	{ai_charge, 10, floater_fire_blaster},			// BOOM (0, -25.8, 32.5)	-- LOOP Starts
	{ai_charge, 10, floater_fire_blaster},
	{ai_charge, 10, floater_fire_blaster},
	{ai_charge, 10, floater_fire_blaster},
	{ai_charge, 10, floater_fire_blaster},
	{ai_charge, 10, floater_fire_blaster},
	{ai_charge, 10, floater_fire_blaster},
	{ai_charge, 10, NULL},
	{ai_charge, 10, NULL},
	{ai_charge, 10, NULL},
	{ai_charge, 10, NULL}			//							-- LOOP Ends
};

mmove_t floater_move_attack1a =
{
	FRAME_attak101,
	FRAME_attak114,
	floater_frames_attack1a,
	floater_run
};

static mframe_t floater_frames_attack2[] = {
	{ai_charge, 0, NULL}, /* Claws */
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, floater_wham},  /* WHAM (0, -45, 29}.6) -- LOOP Starts */
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL}, /* -- LOOP Ends */
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL}
};

mmove_t floater_move_attack2 =
{
	FRAME_attak201,
	FRAME_attak225,
	floater_frames_attack2,
	floater_run
};

static mframe_t floater_frames_attack3[] = {
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, floater_zap}, /*	-- LOOP Starts */
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL}, /* -- LOOP Ends */
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL},
	{ai_charge, 0, NULL}
};

mmove_t floater_move_attack3 =
{
	FRAME_attak301,
	FRAME_attak334,
	floater_frames_attack3,
	floater_run
};

static mframe_t floater_frames_death[] = {
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL}
};

mmove_t floater_move_death =
{
	FRAME_death01,
	FRAME_death13,
	floater_frames_death,
	floater_dead
};

static mframe_t floater_frames_pain1[] = {
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL}
};

mmove_t floater_move_pain1 =
{
	FRAME_pain101,
	FRAME_pain107,
	floater_frames_pain1,
	floater_run
};

static mframe_t floater_frames_pain2[] = {
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL}
};

mmove_t floater_move_pain2 =
{
	FRAME_pain201,
	FRAME_pain208,
	floater_frames_pain2,
	floater_run
};

static mframe_t floater_frames_pain3[] = {
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL},
	{ai_move, 0, NULL}
};

mmove_t floater_move_pain3 =
{
	FRAME_pain301,
	FRAME_pain312,
	floater_frames_pain3,
	floater_run
};

static mframe_t floater_frames_walk[] = {
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL},
	{ai_walk, 5, NULL}
};

mmove_t floater_move_walk =
{
	FRAME_stand101,
	FRAME_stand152,
	floater_frames_walk,
	NULL
};

static mframe_t floater_frames_run[] = {
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL},
	{ai_run, 13, NULL}
};

mmove_t floater_move_run =
{
	FRAME_stand101,
	FRAME_stand152,
	floater_frames_run,
	NULL
};

void
floater_run(edict_t *self)
{
	if (!self)
	{
		return;
	}

	if (self->monsterinfo.aiflags & AI_STAND_GROUND)
	{
		self->monsterinfo.currentmove = &floater_move_stand1;
	}
	else
	{
		self->monsterinfo.currentmove = &floater_move_run;
	}
}

void
floater_walk(edict_t *self)
{
	if (!self)
	{
		return;
	}

	self->monsterinfo.currentmove = &floater_move_walk;
}

void
floater_wham(edict_t *self)
{
	static vec3_t aim = {MELEE_DISTANCE, 0, 0};

	if (!self)
	{
		return;
	}

	gi.sound(self, CHAN_WEAPON, sound_attack3, 1, ATTN_NORM, 0);
	fire_hit(self, aim, 5 + randk() % 6, -50);
}

void
floater_zap(edict_t *self)
{
	vec3_t forward, right;
	vec3_t origin;
	vec3_t dir;
	vec3_t offset;

	if (!self)
	{
		return;
	}

	VectorSubtract(self->enemy->s.origin, self->s.origin, dir);

	AngleVectors(self->s.angles, forward, right, NULL);
	VectorSet(offset, 18.5, -0.9, 10);
	G_ProjectSource(self->s.origin, offset, forward, right, origin);

	gi.sound(self, CHAN_WEAPON, sound_attack2, 1, ATTN_NORM, 0);

	gi.WriteByte(svc_temp_entity);
	gi.WriteByte(TE_SPLASH);
	gi.WriteByte(32);
	gi.WritePosition(origin);
	gi.WriteDir(dir);
	gi.WriteByte(1); /* sparks */
	gi.multicast(origin, MULTICAST_PVS);

	if (range(self, self->enemy) == RANGE_MELEE && infront(self, self->enemy) &&
			visible(self, self->enemy))
	{
		T_Damage(self->enemy, self, self, dir, self->enemy->s.origin,
				vec3_origin, 5 + randk() % 6, -10, DAMAGE_ENERGY,
				MOD_UNKNOWN);
	}
}

void
floater_attack(edict_t *self)
{
	float chance;

	if (!self)
	{
		return;
	}

	// 0% chance of circle in easy
	// 50% chance in normal
	// 75% chance in hard
	// 86.67% chance in nightmare
	if (skill->value == SKILL_EASY)
	{
		chance = 0;
	}
	else
	{
		chance = 1.0 - (0.5/(float)(skill->value));
	}

	if (random() > chance)
	{
		self->monsterinfo.attack_state = AS_STRAIGHT;
		self->monsterinfo.currentmove = &floater_move_attack1;
	}
	else // circle strafe
	{
		if (random () <= 0.5) // switch directions
		{
			self->monsterinfo.lefty = 1 - self->monsterinfo.lefty;
		}

		self->monsterinfo.attack_state = AS_SLIDING;
		self->monsterinfo.currentmove = &floater_move_attack1a;
	}
}

void
floater_melee(edict_t *self)
{
	if (!self)
	{
		return;
	}

	if (random() < 0.5)
	{
		self->monsterinfo.currentmove = &floater_move_attack3;
	}
	else
	{
		self->monsterinfo.currentmove = &floater_move_attack2;
	}
}

void
floater_pain(edict_t *self, edict_t *other /* unused */,
		float kick /* unused */, int damage)
{
	int n;

	if (!self)
	{
		return;
	}

	if (self->health < (self->max_health / 2))
	{
		self->s.skinnum = 1;
	}

	if (level.time < self->pain_debounce_time)
	{
		return;
	}

	self->pain_debounce_time = level.time + 3;

	if (skill->value == SKILL_HARDPLUS)
	{
		return; /* no pain anims in nightmare */
	}

	n = (randk() + 1) % 3;

	if (n == 0)
	{
		gi.sound(self, CHAN_VOICE, sound_pain1, 1, ATTN_NORM, 0);
		self->monsterinfo.currentmove = &floater_move_pain1;
	}
	else
	{
		gi.sound(self, CHAN_VOICE, sound_pain2, 1, ATTN_NORM, 0);
		self->monsterinfo.currentmove = &floater_move_pain2;
	}
}

void
floater_dead(edict_t *self)
{
	if (!self)
	{
		return;
	}

	VectorSet(self->mins, -16, -16, -24);
	VectorSet(self->maxs, 16, 16, -8);
	self->movetype = MOVETYPE_TOSS;
	self->svflags |= SVF_DEADMONSTER;
	self->nextthink = 0;
	gi.linkentity(self);
}

void
floater_die(edict_t *self, edict_t *inflictor /* unused */, edict_t *attacker /* unused */,
		int damage /* unused */, vec3_t point /* unused */)
{
	if (!self)
	{
		return;
	}

	gi.sound(self, CHAN_VOICE, sound_death1, 1, ATTN_NORM, 0);
	BecomeExplosion1(self);
}

qboolean
floater_blocked(edict_t *self, float dist)
{
	return false;
}

/*
 * QUAKED monster_floater (1 .5 0) (-16 -16 -24) (16 16 32) Ambush Trigger_Spawn Sight
 */

/*
 * QUAKED monster_floaterv (1 .5 0) (-16 -16 -24) (16 16 32) Ambush Trigger_Spawn Sight
 */
void
SP_monster_floater(edict_t *self)
{
	if (!self)
	{
		return;
	}

	if (deathmatch->value)
	{
		G_FreeEdict(self);
		return;
	}

	sound_attack2 = gi.soundindex("floater/fltatck2.wav");
	sound_attack3 = gi.soundindex("floater/fltatck3.wav");
	sound_death1 = gi.soundindex("floater/fltdeth1.wav");
	sound_idle = gi.soundindex("floater/fltidle1.wav");
	sound_pain1 = gi.soundindex("floater/fltpain1.wav");
	sound_pain2 = gi.soundindex("floater/fltpain2.wav");
	sound_sight = gi.soundindex("floater/fltsght1.wav");

	gi.soundindex("floater/fltatck1.wav");

	self->s.sound = gi.soundindex("floater/fltsrch1.wav");

	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;
	if (!strcmp(self->classname, "monster_floaterv"))
	{
		self->s.modelindex = gi.modelindex("models/vault/monsters/float/tris.md2");
	}
	else
	{
		self->s.modelindex = gi.modelindex("models/monsters/float/tris.md2");
	}
	VectorSet(self->mins, -24, -24, -24);
	VectorSet(self->maxs, 24, 24, 32);

	self->health = 200 * st.health_multiplier;
	self->gib_health = -80;
	self->mass = 300;

	self->pain = floater_pain;
	self->die = floater_die;

	self->monsterinfo.stand = floater_stand;
	self->monsterinfo.walk = floater_walk;
	self->monsterinfo.run = floater_run;
	self->monsterinfo.attack = floater_attack;
	self->monsterinfo.melee = floater_melee;
	self->monsterinfo.sight = floater_sight;
	self->monsterinfo.idle = floater_idle;

	gi.linkentity(self);

	if (random() <= 0.5)
	{
		self->monsterinfo.currentmove = &floater_move_stand1;
	}
	else
	{
		self->monsterinfo.currentmove = &floater_move_stand2;
	}

	self->monsterinfo.scale = MODEL_SCALE;

	flymonster_start(self);
}
