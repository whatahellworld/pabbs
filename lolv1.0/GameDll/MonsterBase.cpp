#include "stdafx.h"
#include "MonsterBase.h"
#include "BaseAddr.h"
#include <cmath>
MonsterBase::MonsterBase(DWORD dwNodeBase): base(dwNodeBase)
{

}


MonsterBase::~MonsterBase()
{
}

char* MonsterBase::GetName() const
{
	__try
	{
		auto stringSize = utils::GetInstance()->read<DWORD>(GetNodeBase() + 0x30);
		auto maxSize = utils::GetInstance()->read<DWORD>(GetNodeBase() + 0x34);
		if (stringSize < 0x10)
		{
			return (char*)(GetNodeBase() + 0x20);
		}
		else
		{
			return (char*)(utils::GetInstance()->read<DWORD>(GetNodeBase() + 0x20));
		}
	}
	__except (1) {
		return nullptr;
	}
}

float MonsterBase::GetCurHp() const
{
	__try {
		return utils::GetInstance()->read<float>(GetNodeBase() + pSharedMemoryPointer->Base_MonsterCurrentHpOffset);
	}
	__except (1)
	{
		utils::GetInstance()->log("ERROR: MonsterBase::GetCurHp() 出现异常！\n");
		return 0;
	}
}

float MonsterBase::GetMaxHp() const
{
	__try {
		return utils::GetInstance()->read<float>(GetNodeBase() + pSharedMemoryPointer->Base_MonsterCurrentHpOffset+0x10);
	}
	__except (1)
	{
		utils::GetInstance()->log("ERROR: MonsterBase::GetMaxHp() 出现异常！\n");
		return 0;
	}
}

float MonsterBase::GetCurMp() const
{
	__try {
		return utils::GetInstance()->read<float>(GetNodeBase() + pSharedMemoryPointer->Base_MonsterCurrentMpOffset);
	}
	__except (1)
	{
		utils::GetInstance()->log("ERROR: MonsterBase::GetCurMp() 出现异常！\n");
		return 0;
	}
}

float MonsterBase::GetMaxMp() const
{
	__try {
		return utils::GetInstance()->read<float>(GetNodeBase() + pSharedMemoryPointer->Base_MonsterCurrentMpOffset+0x10);
	}
	__except (1)
	{
		utils::GetInstance()->log("ERROR: MonsterBase::GetMaxMp() 出现异常！\n");
		return 0;
	}

}

EM_POINT_3D MonsterBase::GetPoint() const
{
	EM_POINT_3D temp = { 0 };
	__try
	{
		//读取坐标
		temp.x = utils::GetInstance()->read<float>(GetNodeBase() + 0x50);
		temp.z = utils::GetInstance()->read<float>(GetNodeBase() + 0x54);
		temp.y = utils::GetInstance()->read<float>(GetNodeBase() + 0x58);
	}
	__except (1)
	{
		utils::GetInstance()->log("ERROR: MonsterBase::GetPoint() 出现异常！\n");
	}
	return temp;
}

EM_CAMP MonsterBase::GetCamp() const
{
	__try {
		return (EM_CAMP)utils::GetInstance()->read<DWORD>(GetNodeBase() + 0x14);
	}
	__except (1) {
		utils::GetInstance()->log("ERROR: MonsterBase::GetCamp()出现异常！\n");
		return EM_CAMP::CAM_UNKNOW;
	}
}

DWORD MonsterBase::GetType() const
{
	__try {
		return utils::GetInstance()->read<DWORD>(GetNodeBase() + 0x18);
	}
	__except (1) {
		utils::GetInstance()->log("ERROR: MonsterBase::GetType()出现异常！\n");
		return 0;
	}
}



bool MonsterBase::BVisableSee() const
{
	__try
	{

		auto temp = utils::GetInstance()->read<DWORD>(GetNodeBase() + pSharedMemoryPointer->Base_MonsterBVisableOffset);
		if (temp)
		{
			return utils::GetInstance()->read<bool>(temp + 0x18);
		}
	}
	__except (1)
	{
		utils::GetInstance()->log("ERROR: MonsterBase::BVisableSee() 出现异常！\n");
	}
	return false;
}

bool MonsterBase::BDead() const
{
	__try {
		return utils::GetInstance()->read<bool>(GetNodeBase() + 0x10c) || GetCurHp() < 2 ;
	}
	__except (1)
	{
		utils::GetInstance()->log("ERROR: MonsterBase::BDead()出现异常！\n");
		return false;
	}
}

float MonsterBase::GetDistance(EM_POINT_3D* mon)
{
	return sqrt((GetPoint().x - mon->x)*(GetPoint().x - mon->x) + (GetPoint().y - mon->y)*(GetPoint().y - mon->y));
}

EM_POINT_3D MonsterBase::GetMonsterOrientation() const
{
	EM_POINT_3D temp = { 0 };
	__try {
		
		temp.x = utils::GetInstance()->read<float>(GetNodeBase() + pSharedMemoryPointer->Base_MonsterOrientationXOffset);
		temp.z = utils::GetInstance()->read<float>(GetNodeBase() + pSharedMemoryPointer->Base_MonsterOrientationXOffset + 0x4);
		temp.y = utils::GetInstance()->read<float>(GetNodeBase() + pSharedMemoryPointer->Base_MonsterOrientationXOffset + 0x8);
	}
	__except (1)
	{
		memset(&temp, 0, sizeof(EM_POINT_3D));
	}
	return temp;
}



bool MonsterBase::GetBMoving() const
{
	__try
	{
		return utils::GetInstance()->read<bool>(GetNodeBase() + pSharedMemoryPointer->Base_MonsterBMovingOffset);
	}
	__except (1)
	{
		utils::GetInstance()->log("ERROR: MonsterBase::GetBMoving()出现异常！\n");
	}
	return false;
}
