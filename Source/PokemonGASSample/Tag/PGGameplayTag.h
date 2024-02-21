#pragma once

#include "GameplayTagContainer.h"

#define PGTAG_GAME FGameplayTag::RequestGameplayTag(FName("Game"))
#define PGTAG_GAME_STATE FGameplayTag::RequestGameplayTag(FName("Game.State"))

#define PGTAG_GAME_FLIPCOIN FGameplayTag::RequestGameplayTag(FName("Game.State.FlipCoin"))
#define PGTAG_GAME_SELECTDECK FGameplayTag::RequestGameplayTag(FName("Game.State.SelectDeck"))
#define PGTAG_GAME_WAITFORREADY FGameplayTag::RequestGameplayTag(FName("Game.State.WaitForReady"))
#define PGTAG_GAME_GAMESTART FGameplayTag::RequestGameplayTag(FName("Game.State.GameStart"))

#define PGTAG_PLAYER FGameplayTag::RequestGameplayTag(FName("Player"))
#define PGTAG_PLAYER_HUD FGameplayTag::RequestGameplayTag(FName("Player.HUD"))

#define PGTAG_PLAYER_DRAWDECK FGameplayTag::RequestGameplayTag(FName("Player.Action.DrawDeck"))
#define PGTAG_PLAYER_DRAWPRICES FGameplayTag::RequestGameplayTag(FName("Player.Action.DrawPrices"))

