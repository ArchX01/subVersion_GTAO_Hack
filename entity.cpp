/*
	Copyright 2016 sub1to

	This file is part of subVersion GTA:O SC External Hack.

    subVersion GTA:O SC External Hack is free software: you can redistribute
	it and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation, either version 3 of the
	License, or (at your option) any later version.

    subVersion GTA:O SC External Hack is distributed in the hope that it
	will be useful, but WITHOUT ANY WARRANTY; without even the implied
	warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
	the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with subVersion GTA:O SC External Hack.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "stdafx.h"

/*
	ENTITY
*/
entity::entity(){}
entity::~entity(){}
void entity::getPos(){}
void entity::setPos(v3 dest){}
void entity::getHealth(){}
void entity::setHealth(float hp){}

/*
	PLAYER
*/
player::player(){}
player::~player(){}

void player::getPos()
{
	g_pMemMan->readMem<v3>((DWORD_PTR) m_dwpPlayerPosBase + OFFSET_ENTITY_POSBASE_POS, &m_pos);
	return;
}

void player::setPos(v3 dest)
{
	g_pMemMan->writeMem<v3>((DWORD_PTR) m_dwpPlayerPosBase + OFFSET_ENTITY_POSBASE_POS, &dest);
	g_pMemMan->writeMem<v3>((DWORD_PTR) m_dwpPlayerBase + OFFSET_ENTITY_POS, &dest);
	return;
}

void player::getHealth()
{
	g_pMemMan->readMem<float>((DWORD_PTR) m_dwpPlayerBase + OFFSET_ENTITY_HEALTH, &m_hp.cur);
	g_pMemMan->readMem<float>((DWORD_PTR) m_dwpPlayerBase + OFFSET_ENTITY_HEALTH_MAX, &m_hp.max);
	g_pMemMan->readMem<float>((DWORD_PTR) m_dwpPlayerBase + OFFSET_PLAYER_ARMOR, &m_flArmor);
	return;
}

void player::setHealth(float hp, float armor)
{
	g_pMemMan->writeMem<float>((DWORD_PTR) m_dwpPlayerBase + OFFSET_ENTITY_HEALTH, &hp);
	g_pMemMan->writeMem<float>((DWORD_PTR) m_dwpPlayerBase + OFFSET_PLAYER_ARMOR, &armor);
	return;
}

void player::getWanted()
{
	g_pMemMan->readMem<DWORD>((DWORD_PTR) m_dwpPlayerInfo + OFFSET_PLAYER_INFO_WANTED, &m_dwWanted);
	return;
}

void player::setWanted(DWORD stars)
{
	g_pMemMan->writeMem<DWORD>((DWORD_PTR) m_dwpPlayerInfo + OFFSET_PLAYER_INFO_WANTED, &stars);
	return;
}

void player::getInVehicle()
{
	DWORD	dwRead;
	g_pMemMan->readMem<DWORD>((DWORD_PTR) m_dwpPlayerBase + OFFSET_ENTITY_INVEHICLE, &dwRead);
	m_dwInVehicle		= (DWORD) !((dwRead >> 28) & 1);
	return;
}

/*
	VEHICLE
*/

vehicle::vehicle()
{
	m_hp.max = 1000.f;
}
vehicle::~vehicle(){}

void vehicle::getPos()
{
	g_pMemMan->readMem<v3>((DWORD_PTR) m_dwpVehicleBase + OFFSET_ENTITY_POS, &m_pos);
	return;
}

void vehicle::setPos(v3 dest)
{
	g_pMemMan->writeMem<v3>((DWORD_PTR) m_dwpVehiclePosBase + OFFSET_ENTITY_POSBASE_POS, &dest);
	g_pMemMan->writeMem<v3>((DWORD_PTR) m_dwpVehicleBase + OFFSET_ENTITY_POS, &dest);
	return;
}

void vehicle::getHealth()
{
	g_pMemMan->readMem<float>((DWORD_PTR) m_dwpVehicleBase + OFFSET_VEHICLE_HEALTH, &m_hp.cur);
	return;
}

void vehicle::setHealth(float hp)
{
	g_pMemMan->writeMem<float>((DWORD_PTR) m_dwpVehicleBase + OFFSET_VEHICLE_HEALTH, &hp);
	return;
}

/*
	WEAPON
*/

weapon::weapon() : m_dwHash(0) {};
weapon::~weapon(){};

bool weapon::findAmmoBase()
{
	DWORD_PTR	dwpBase	= m_dwpAmmoInfo,
				dwpBase2;
	DWORD		dwTmp;
	do
	{
		g_pMemMan->readMem<DWORD_PTR>((DWORD_PTR) dwpBase	+ OFFSET_WEAPON_AMMOINFO_CUR_1, &dwpBase);
		g_pMemMan->readMem<DWORD_PTR>((DWORD_PTR) dwpBase	+ OFFSET_WEAPON_AMMOINFO_CUR_2, &dwpBase2);
		g_pMemMan->readMem<DWORD>	((DWORD_PTR) dwpBase2	+ OFFSET_WEAPON_AMMOINFO_TYPE, &dwTmp);
		if(dwpBase == 0 || dwpBase2 == 0)
			return 0;
	}
	while(dwTmp == 0);
	m_dwpCurAmmoBase	= dwpBase2;
	return 1;
}

void weapon::getCurAmmo()
{
	g_pMemMan->readMem<DWORD>((DWORD_PTR) m_dwpCurAmmoBase + OFFSET_WEAPON_AMMOINFO_CURAMMO, &m_dwCurAmmo);
	return;
}

void weapon::setCurAmmo(DWORD ammo)
{
	g_pMemMan->writeMem<DWORD>((DWORD_PTR) m_dwpCurAmmoBase + OFFSET_WEAPON_AMMOINFO_CURAMMO, &ammo);
	return;
}

void weapon::getMaxAmmo()
{
	g_pMemMan->readMem<DWORD>((DWORD_PTR) m_dwpAmmoInfo + OFFSET_WEAPON_AMMOINFO_MAX, &m_dwMaxAmmo);
	return;
}

void weapon::restoreWeapon()
{
	g_pMemMan->writeMem<float>((DWORD_PTR) m_weapDataRestore.m_dwpWeapon + OFFSET_WEAPON_SPREAD, &m_weapDataRestore.m_fSpread);
	g_pMemMan->writeMem<float>((DWORD_PTR) m_weapDataRestore.m_dwpWeapon + OFFSET_WEAPON_RECOIL, &m_weapDataRestore.m_fRecoil);
	g_pMemMan->writeMem<float>((DWORD_PTR) m_weapDataRestore.m_dwpWeapon + OFFSET_WEAPON_BULLET_DMG, &m_weapDataRestore.m_fDamage);
	g_pMemMan->writeMem<float>((DWORD_PTR) m_weapDataRestore.m_dwpWeapon + OFFSET_WEAPON_RELOAD_MULTIPLIER, &m_weapDataRestore.m_fReload);
	g_pMemMan->writeMem<float>((DWORD_PTR) m_weapDataRestore.m_dwpWeapon + OFFSET_WEAPON_RELOAD_VEHICLE, &m_weapDataRestore.m_fReloadVeh);
	g_pMemMan->writeMem<float>((DWORD_PTR) m_weapDataRestore.m_dwpWeapon + OFFSET_WEAPON_RANGE, &m_weapDataRestore.m_fRange);
	g_pMemMan->writeMem<float>((DWORD_PTR) m_weapDataRestore.m_dwpWeapon + OFFSET_WEAPON_SPINUP, &m_weapDataRestore.m_fSpinUp);
	g_pMemMan->writeMem<float>((DWORD_PTR) m_weapDataRestore.m_dwpWeapon + OFFSET_WEAPON_SPIN, &m_weapDataRestore.m_fSpin);
	return;
}

void weapon::getReloadSpeed()
{
	g_pMemMan->readMem<float>((DWORD_PTR) m_weapDataCur.m_dwpWeapon	+ OFFSET_WEAPON_RELOAD_MULTIPLIER, &m_weapDataCur.m_fReload);
	return;
}

void weapon::setReloadSpeed(float value)
{
	g_pMemMan->writeMem<float>((DWORD_PTR) m_weapDataCur.m_dwpWeapon + OFFSET_WEAPON_RELOAD_MULTIPLIER, &value);
	return;
}

void weapon::getReloadVehicle()
{
	g_pMemMan->readMem<float>((DWORD_PTR) m_weapDataCur.m_dwpWeapon	+ OFFSET_WEAPON_RELOAD_VEHICLE, &m_weapDataCur.m_fReloadVeh);
	return;
}

void weapon::setReloadVehicle(float value)
{
	g_pMemMan->writeMem<float>((DWORD_PTR) m_weapDataCur.m_dwpWeapon + OFFSET_WEAPON_RELOAD_VEHICLE, &value);
	return;
}

void weapon::getBulletDamage()
{
	g_pMemMan->readMem<float>((DWORD_PTR) m_weapDataCur.m_dwpWeapon	+ OFFSET_WEAPON_BULLET_DMG, &m_weapDataCur.m_fDamage);
	return;
}

void weapon::setBulletDamage(float value)
{
	g_pMemMan->writeMem<float>((DWORD_PTR) m_weapDataCur.m_dwpWeapon + OFFSET_WEAPON_BULLET_DMG, &value);
	return;
}

void weapon::getRecoil()
{
	g_pMemMan->readMem<float>((DWORD_PTR) m_weapDataCur.m_dwpWeapon	+ OFFSET_WEAPON_RECOIL, &m_weapDataCur.m_fRecoil);
	return;
}

void weapon::setRecoil(float value)
{
	g_pMemMan->writeMem<float>((DWORD_PTR) m_weapDataCur.m_dwpWeapon + OFFSET_WEAPON_RECOIL, &value);
	return;
}

void weapon::getSpread()
{
	g_pMemMan->readMem<float>((DWORD_PTR) m_weapDataCur.m_dwpWeapon	+ OFFSET_WEAPON_SPREAD, &m_weapDataCur.m_fSpread);
	return;
}

void weapon::setSpread(float value)
{
	g_pMemMan->writeMem<float>((DWORD_PTR) m_weapDataCur.m_dwpWeapon + OFFSET_WEAPON_SPREAD, &value);
	return;
}

void weapon::getRange()
{
	g_pMemMan->readMem<float>((DWORD_PTR) m_weapDataCur.m_dwpWeapon	+ OFFSET_WEAPON_RANGE, &m_weapDataCur.m_fRange);
	return;
}

void weapon::setRange(float value)
{
	g_pMemMan->writeMem<float>((DWORD_PTR) m_weapDataCur.m_dwpWeapon + OFFSET_WEAPON_RANGE, &value);
	return;
}

void weapon::getSpinUp()
{
	g_pMemMan->readMem<float>((DWORD_PTR) m_weapDataCur.m_dwpWeapon	+ OFFSET_WEAPON_SPINUP, &m_weapDataCur.m_fSpinUp);
	return;
}

void weapon::setSpinUp(float value)
{
	g_pMemMan->writeMem<float>((DWORD_PTR) m_weapDataCur.m_dwpWeapon + OFFSET_WEAPON_SPINUP, &value);
	return;
}

void weapon::getSpin()
{
	g_pMemMan->readMem<float>((DWORD_PTR) m_weapDataCur.m_dwpWeapon	+ OFFSET_WEAPON_SPIN, &m_weapDataCur.m_fSpin);
	return;
}

void weapon::setSpin(float value)
{
	g_pMemMan->writeMem<float>((DWORD_PTR) m_weapDataCur.m_dwpWeapon + OFFSET_WEAPON_SPIN, &value);
	return;
}

void weapon::getHash()
{
	g_pMemMan->readMem<DWORD>((DWORD_PTR) m_weapDataCur.m_dwpWeapon	+ OFFSET_WEAPON_NAME_HASH, &m_weapDataCur.m_dwHash);
	return;
}