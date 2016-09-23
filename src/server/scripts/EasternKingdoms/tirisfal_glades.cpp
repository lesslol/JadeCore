/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "Vehicle.h"

/*######
## npc_aradne
######*/

class npc_aradne : public CreatureScript
{
public:
    npc_aradne() : CreatureScript("npc_aradne") { }

    enum eAradne
    {
        RAISE_UNDEAD = 93446,
    };

    struct npc_aradneAI : public ScriptedAI
    {
        npc_aradneAI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;

        void Reset()
        {
            m_timer = 0;
            m_phase = 0;
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type == WAYPOINT_MOTION_TYPE)
            switch (id)
            {
                case 4:
                    m_phase = 1;
                    m_timer = 100;
                    break;
                case 12:
                    m_phase = 1;
                    m_timer = 100;
                    break;
                case 15:
                    m_phase = 1;
                    m_timer = 100;
                    break;
                case 20:
                    m_phase = 1;
                    m_timer = 100;
                    break;
                case 26:
                    m_phase = 1;
                    m_timer = 100;
                    break;
                case 31:
                    m_phase = 1;
                    m_timer = 100;
                    break;
                case 33:
                    m_phase = 1;
                    m_timer = 100;
                    break;
                case 37:
                    m_phase = 1;
                    m_timer = 100;
                    break;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (m_timer <= diff)
            {
                m_timer = 1000;
                DoWork();
            }
            else m_timer -= diff;
        }

        void DoWork()
        {
            switch (m_phase)
            {
                case 1:
                    if (Creature* npc = me->FindNearestCreature(50373, 15.0f))
                        me->CastSpell(npc, 93446, false);

                    m_phase = 2;
                    break;
                case 2:
                    Talk(0);
                    m_phase = 3;
                    break;
                default:
                    m_timer = 0;
                    m_phase = 0;
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_aradneAI(pCreature);
    }
};

/*######
## npc_deathknell_grave_target
######*/

class npc_deathknell_grave_target : public CreatureScript
{
public:
    npc_deathknell_grave_target() : CreatureScript("npc_deathknell_grave_target") { }

    enum eRisenDead
    {
        SPELL_SUMMON_RISEN_DEAD  = 93447,
        SPELL_DIRT_EXPLOSION     = 89199,
        SPELL_CHURNING_DIRT      = 92788
    };

    struct npc_deathknell_grave_targetAI : public ScriptedAI
    {
        npc_deathknell_grave_targetAI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;

        void Reset()
        {
            m_timer = 0;
            m_phase = 0;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            if (spell->Id == 93446)
            {
                m_timer = 100;
                m_phase = 1;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (m_timer <= diff)
            {
                m_timer = 1000;
                DoWork();
            }
            else m_timer -= diff;
        }

        void DoWork()
        {
            switch (m_phase)
            {
                case 1:
                    me->AddAura(SPELL_DIRT_EXPLOSION, me);
                    DoCast(me, SPELL_CHURNING_DIRT);
                    m_phase = 2;
                    break;
                case 2:
                    me->CastSpell(me, SPELL_SUMMON_RISEN_DEAD, true);
                    m_phase = 3;
                    m_timer = 3000;
                    break;
                case 3:
                    me->RemoveAllAuras();
                    m_phase = 4;
                    break;
                case 4:
                    m_timer = 0;
                    m_phase = 0;
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_deathknell_grave_targetAI(pCreature);
    }
};

/*######
## npc_risen_dead
######*/

class npc_risen_dead : public CreatureScript
{
public:
    npc_risen_dead() : CreatureScript("npc_risen_dead") { }

    struct npc_risen_deadAI : public ScriptedAI
    {
        npc_risen_deadAI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;
        uint32 m_WishToBeDead;

        void Reset()
        {
            m_timer = 2000;
            m_phase = 0;
            m_WishToBeDead = urand(0, 100);
        }

        void UpdateAI(const uint32 diff)
        {
            if (m_timer <= diff)
            {
                m_timer = 1000;
                DoWork();
            }
            else m_timer -= diff;
        }

        void DoWork()
        {
            if (m_WishToBeDead < 33)
                ShowDead();
            else if (m_WishToBeDead < 66)
                ShowLife();
            else
                ShowRunning();
        }

        void ShowDead()
        {
            switch (m_phase)
            {
                case 0:
                    me->HandleEmote(EMOTE_ONESHOT_QUESTION);
                    m_timer = 200;
                    m_phase = 1;
                    break;
                case 1:
                    Talk(7);
                    m_timer = 5000;
                    m_phase = 2;
                    break;
                case 2:
                    Talk(2);
                    m_timer = 5000;
                    m_phase = 3;
                    break;
                case 3:
                    Talk(1);
                    me->Kill(me);
                    m_timer = 5000;
                    m_phase = 4;
                    break;
                case 4:
                    m_timer = 0;
                    m_phase = 5;
                    break;
            }
        }

        void ShowLife()
        {
            switch (m_phase)
            {
                case 0:
                    me->HandleEmote(EMOTE_ONESHOT_QUESTION);
                    m_timer = 200;
                    m_phase = 1;
                    break;
                case 1:
                    Talk(0);
                    m_timer = 5000;
                    m_phase = 2;
                    break;
                case 2:
                    Talk(5);
                    m_timer = 5000;
                    m_phase = 3;
                    break;
                case 3:
                    Talk(4);
                    SetEquipmentSlots(false, 10614, 1984);
                    me->GetMotionMaster()->MovePath(5037401, false);
                    m_timer = 20000;
                    m_phase = 4;
                    break;
                case 4:
                    m_timer = 0;
                    m_phase = 5;
                    break;
            }
        }

        void ShowRunning()
        {
            switch (m_phase)
            {
                case 0:
                    me->HandleEmote(EMOTE_ONESHOT_QUESTION);
                    m_timer = 200;
                    m_phase = 1;
                    break;
                case 1:
                    Talk(0);
                    m_timer = 5000;
                    m_phase = 2;
                    break;
                case 2:
                    Talk(3);
                    m_timer = 5000;
                    m_phase = 3;
                    break;
                case 3:
                    Talk(6);
                    me->CastSpell(me, 44427, true);
                    Talk(8);
                    me->GetMotionMaster()->MovePath(5037400, false);
                    m_timer = 5000;
                    m_phase = 4;
                    break;
                case 4:
                    m_timer = 0;
                    m_phase = 5;
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_risen_deadAI(pCreature);
    }
};

void AddSC_tirisfal_glades()
{
    new npc_aradne();
    new npc_deathknell_grave_target();
    new npc_risen_dead();
}
