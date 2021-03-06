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
#ifndef ENTITY_H
#define ENTITY_H

struct health
{
	float cur, max;
};

class entity
{
	public:
		health	m_hp;
		v3		m_pos;

						entity();
						~entity();
		virtual void	getPos();
		virtual void	setPos(v3 dest);
		virtual void	getHealth();
		virtual void	setHealth(float hp);
};

class player : public entity
{
	public:
		float	m_flArmor;
		DWORD	m_dwWanted,
				m_dwInVehicle;

						player();
						~player();
		virtual	void	getPos();
		virtual	void	setPos(v3 dest);
		virtual	void	getHealth();
		virtual	void	setHealth(float hp, float armor);
				void	getWanted();
				void	setWanted(DWORD stars);
				void	getInVehicle();


		DWORD_PTR	m_dwpPlayerBase,
					m_dwpPlayerPosBase,
					m_dwpPlayerInfo;
};

class vehicle : public entity
{
	public:
						vehicle();
						~vehicle();
		virtual void	getPos();
		virtual void	setPos(v3 dest);
		virtual void	getHealth();
		virtual void	setHealth(float hp);

		DWORD_PTR	m_dwpVehicleBase,
					m_dwpVehiclePosBase;
};

class weapon
{
	public:
		DWORD		m_dwCurAmmo,
					m_dwMaxAmmo,
					m_dwHash;		//name hash
		struct weaponData
		{
			DWORD		m_dwHash;
			DWORD_PTR	m_dwpWeapon	= 0;
			float		m_fSpread,		
						m_fRecoil,
						m_fDamage,
						m_fReload,
						m_fReloadVeh,
						m_fRange,
						m_fSpinUp,
						m_fSpin;
		};

		weaponData	m_weapDataRestore,//the original values will be stored here.
					m_weapDataCur;
				
				weapon();
				~weapon();
		void	restoreWeapon();
		void	getReloadSpeed();
		void	setReloadSpeed(float value);
		void	getReloadVehicle();
		void	setReloadVehicle(float value);
		void	getBulletDamage();
		void	setBulletDamage(float value);
		void	getRecoil();
		void	setRecoil(float value);
		void	getSpread();
		void	setSpread(float value);
		void	getRange();
		void	setRange(float value);
		void	getSpinUp();
		void	setSpinUp(float value);
		void	getSpin();
		void	setSpin(float value);
		void	getHash();
		bool	findAmmoBase();
		void	getCurAmmo();
		void	setCurAmmo(DWORD ammo);
		void	getMaxAmmo();

		DWORD_PTR	m_dwpAmmoInfo,
					m_dwpCurAmmoBase;
};

#endif