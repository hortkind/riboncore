/*
 * Copyright (C) 2008 - 2009 Ribon <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "precompiled.h"
#include "def_ulduar.h"

//boss_auriaya
#define SPELL_TERRIFYING_SCREECH    64386
#define SPELL_SONIC_BOOM            38897
#define SAY_AGGRO                   -2615016
#define SAY_SLAY_1                  -2615017

struct RIBON_DLL_DECL boss_auriaya_AI : public ScriptedAI
{
    boss_auriaya_AI(Creature *c) : ScriptedAI(c) {}

    uint32 TERRIFYING_SCREECH_Timer;
    uint32 SONIC_BOOM_Timer;

    void Reset()
    {
        TERRIFYING_SCREECH_Timer = 0;
        SONIC_BOOM_Timer = 2000;
    }

    void EnterCombat(Unit* who)
    {
        DoScriptText(SAY_AGGRO,m_creature);
    }
    void KilledUnit(Unit* victim)
    {
        DoScriptText(SAY_SLAY_1, m_creature);
    }

    void JustDied(Unit *victim)
    {
        DoScriptText(SAY_SLAY_1, m_creature);
    }

    void MoveInLineOfSight(Unit* who) {}

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (TERRIFYING_SCREECH_Timer < diff)
        {
            DoCast(m_creature,SPELL_TERRIFYING_SCREECH);
            DoScriptText(SAY_SLAY_1, m_creature);
            TERRIFYING_SCREECH_Timer = 360000;
        } else TERRIFYING_SCREECH_Timer -= diff;

        if (SONIC_BOOM_Timer < diff)
        {
            DoCast(m_creature->getVictim(),SPELL_SONIC_BOOM);
            SONIC_BOOM_Timer = 20000;
        } else SONIC_BOOM_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_auriaya(Creature* pCreature)
{
    return new boss_auriaya_AI (pCreature);
}
void AddSC_boss_auriaya()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_auriaya";
    newscript->GetAI = &GetAI_boss_auriaya;
    newscript->RegisterSelf();
}