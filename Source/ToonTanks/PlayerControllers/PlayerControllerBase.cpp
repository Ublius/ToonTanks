// Fill out your copyright notice in the Description page of Project Settings.

/* --< Includes >-- */
#include "PlayerControllerBase.h"

/* --< Functions >-- */
void APlayerControllerBase::SetPlayerEnableState(bool SetPlayerEnabled)
{
    if(SetPlayerEnabled)
    {
        GetPawn()->EnableInput(this);
        APlayerControllerBase::bShowMouseCursor = true;
    }
    else
    {
        GetPawn()->DisableInput(this);
        APlayerControllerBase::bShowMouseCursor = false;
    }
}
