// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/BaseUnit.h"

/**
 * A Handler Object for controlling all the units moving, grouping and attacking (potentially in the future).
 */
class PAPALEADER_API UnitsHandler
{
public:
	UnitsHandler();
	~UnitsHandler();

protected:
	std::vector<ABaseUnit*> Units;
};
