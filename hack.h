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

#pragma once
#ifndef HACK_H
#define HACK_H

class trainer
{
	public:
		clock_t		m_keyTmr;

						trainer();
						~trainer();
		bool			checkKeyState(int key, int mod);
		virtual void	checkKeys();
};

class hack : public trainer
{
	public:
		v2		m_v2Waypoint;
		player	m_player;
		vehicle m_vehicle;
		weapon	m_weapon;

		HMODULE	m_hModule;

				hack();
				~hack();
		void	checkKeys();
		bool	initPointers();
		void	teleport(v3 v);
		bool	teleportWaypoint();
		void	restoreHealth();
		void	restoreVehicleHealth();
		void	notWanted();
		void	killNpc();
		void	fillAmmo();
		void	noSpread(bool restore);
		void	noRecoil(bool restore);
		void	quickReload(bool restore);
		void	bulletDamage(bool restore);
		void	weaponRange(bool restore);
		void	weaponSpin(bool restore);
		bool	loadWeapon();

	private:
		DWORD_PTR	m_dwpWorldBase,
					m_dwpPlayerBase,
					m_dwpVehicleBase,
					m_dwpAttackerBase,
					m_dwpWeaponManager,
					m_dwpWeaponCur,
					m_dwpAmmoInfo;

		void	getWaypoint();
};

extern hack*		g_pHack;

#endif