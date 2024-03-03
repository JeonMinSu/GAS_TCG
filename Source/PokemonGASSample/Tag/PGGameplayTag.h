#pragma once

#include "GameplayTagContainer.h"

#define PGTAG_GAME FGameplayTag::RequestGameplayTag(FName("Game"))
#define PGTAG_GAME_STATE FGameplayTag::RequestGameplayTag(FName("Game.State"))
#define PGTAG_GAME_STATE_NONE FGameplayTag::RequestGameplayTag(FName("Game.State.None"))

#define PGTAG_GAME_FLIPCOIN FGameplayTag::RequestGameplayTag(FName("Game.Action.FlipCoin"))
#define PGTAG_GAME_SELECTDECK FGameplayTag::RequestGameplayTag(FName("Game.Action.SelectDeck"))
#define PGTAG_GAME_WAITFORREADY FGameplayTag::RequestGameplayTag(FName("Game.State.WaitForReady"))
#define PGTAG_GAME_GAMESTART FGameplayTag::RequestGameplayTag(FName("Game.Action.GameStart"))
#define PGTAG_GAME_FIRSTTURN FGameplayTag::RequestGameplayTag(FName("Game.Event.FirstTurn"))

#define PGTAG_PLAYER FGameplayTag::RequestGameplayTag(FName("Player"))
#define PGTAG_PLAYER_HUD FGameplayTag::RequestGameplayTag(FName("Player.HUD"))

#define PGTAG_PLAYER_SETTINGFORPLAY FGameplayTag::RequestGameplayTag(FName("Player.Action.SettingForPlay"))

#define PGTAG_PLAYER_DRAWDECK FGameplayTag::RequestGameplayTag(FName("Player.Action.DrawDeck"))
#define PGTAG_PLAYER_DRAWPRICES FGameplayTag::RequestGameplayTag(FName("Player.Action.DrawPrices"))

#define PGTAG_MONSTER_TYPE_FIRE FGameplayTag::RequestGameplayTag(FName("Monster.Type.Fire"))
#define PGTAG_MONSTER_TYPE_WATER FGameplayTag::RequestGameplayTag(FName("Monster.Type.Water"))
#define PGTAG_MONSTER_TYPE_GRASS FGameplayTag::RequestGameplayTag(FName("Monster.Type.Grass"))