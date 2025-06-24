// Fill out your copyright notice in the Description page of Project Settings.


#include "UniqueCollisionInterface.h"

bool IUniqueCollisionInterface::IsOneSided()
{
	return oneSided;
}

// Add default functionality here for any IUniqueCollisionInterface functions that are not pure virtual.

void IUniqueCollisionInterface::SetOneSidedCollision(bool sided)
{
	oneSided = sided;
}
