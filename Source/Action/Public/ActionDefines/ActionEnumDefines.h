#pragma once

UENUM()
enum class EActionConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class EActionValidType : uint8
{
	Valid,
	Invalid
};

UENUM()
enum class EToggleDmgType : uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand
};
