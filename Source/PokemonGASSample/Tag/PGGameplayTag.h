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

#define PGTAG_CARD_STATUS FGameplayTag::RequestGameplayTag(FName("Card.Status"))
#define PGTAG_CARD_ACTION_2BATTLE FGameplayTag::RequestGameplayTag(FName("Card.Action.MoveToBattle"))
#define PGTAG_CARD_ACTION_2BENCH FGameplayTag::RequestGameplayTag(FName("Card.Action.MoveToBench"))
#define PGTAG_CARD_ACTION_2DECK FGameplayTag::RequestGameplayTag(FName("Card.Action.MoveToDeck"))
#define PGTAG_CARD_ACTION_2FIELD FGameplayTag::RequestGameplayTag(FName("Card.Action.MoveToField"))
#define PGTAG_CARD_ACTION_2HAND FGameplayTag::RequestGameplayTag(FName("Card.Action.MoveToHand"))
#define PGTAG_CARD_ACTION_2PRIZE FGameplayTag::RequestGameplayTag(FName("Card.Action.MoveToPrize"))
#define PGTAG_CARD_ACTION_2TRASH FGameplayTag::RequestGameplayTag(FName("Card.Action.MoveToTrash"))