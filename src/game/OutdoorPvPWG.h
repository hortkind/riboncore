/*
 * Copyright (C) 2008-2009 MaNGOS <http://www.getmangos.com/>
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

#ifndef OUTDOOR_PVP_WG_
#define OUTDOOR_PVP_WG_

#include "OutdoorPvPImpl.h"

#define ZONE_WINTERGRASP    4197
#define POS_X_CENTER        4700

#define SPELL_RECRUIT       37795
#define SPELL_CORPORAL      33280
#define SPELL_LIEUTENANT    55629

#define SPELL_TENICITY      58549
#define SPELL_TENICITY_VEHICLE  59911

enum TeamId
{
    TEAM_ALLIANCE = 0,
    TEAM_HORDE,
    TEAM_NEUTRAL,
};

enum DamageState
{
    DAMAGE_INTACT,
    DAMAGE_DAMAGED,
    DAMAGE_DESTROYED,
};

const uint32 AreaPOIIconId[3][3] = {{7,8,9},{4,5,6},{1,2,3}};

struct BuildingState
{
    explicit BuildingState(uint32 _worldState, uint32 _health)
        : worldState(_worldState), health(_health), team(TEAM_NEUTRAL), damageState(DAMAGE_INTACT)
    {}
    uint32 worldState;
    uint32 health;
    TeamId team;
    DamageState damageState;
};

class OutdoorPvPWG : public OutdoorPvP
{
    protected:
        typedef std::list<const AreaPOIEntry *> AreaPOIList;
        typedef std::map<uint32, BuildingState *> BuildingStateMap;
    public:
        bool SetupOutdoorPvP();
        void HandlePlayerEnterZone(Player *plr, uint32 zone);
        void HandlePlayerLeaveZone(Player *plr, uint32 zone);
        void HandleKill(Player *killer, Unit *victim);
    protected:
        TeamId m_defender, m_attacker;
        AreaPOIList areaPOIs;
        BuildingStateMap buildingStates;
};

#endif