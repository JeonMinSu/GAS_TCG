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

#define PGTAG_CARD_TYPE_MONSTER FGameplayTag::RequestGameplayTag(FName("Card.Type.Monster"))
#define PGTAG_CARD_TYPE_ENERGY FGameplayTag::RequestGameplayTag(FName("Card.Type.Energy"))

#define PGTAG_CARD_STATUS FGameplayTag::RequestGameplayTag(FName("Card.Status"))
#define PGTAG_CARD_STATUS_BATTLE FGameplayTag::RequestGameplayTag(FName("Card.Status.InBattle"))
#define PGTAG_CARD_STATUS_BENCH FGameplayTag::RequestGameplayTag(FName("Card.Status.InBench"))
#define PGTAG_CARD_STATUS_DECK FGameplayTag::RequestGameplayTag(FName("Card.Status.InDeck"))
#define PGTAG_CARD_STATUS_FIELD FGameplayTag::RequestGameplayTag(FName("Card.Status.InField"))
#define PGTAG_CARD_STATUS_HAND FGameplayTag::RequestGameplayTag(FName("Card.Status.InHand"))
#define PGTAG_CARD_STATUS_PRIZE FGameplayTag::RequestGameplayTag(FName("Card.Status.InPrize"))
#define PGTAG_CARD_STATUS_TRASH FGameplayTag::RequestGameplayTag(FName("Card.Status.InTrash"))
#define PGTAG_CARD_ACTION_2BATTLE FGameplayTag::RequestGameplayTag(FName("Card.Action.MoveToBattle"))
#define PGTAG_CARD_ACTION_2BENCH FGameplayTag::RequestGameplayTag(FName("Card.Action.MoveToBench"))
#define PGTAG_CARD_ACTION_2DECK FGameplayTag::RequestGameplayTag(FName("Card.Action.MoveToDeck"))
#define PGTAG_CARD_ACTION_2FIELD FGameplayTag::RequestGameplayTag(FName("Card.Action.MoveToField"))
#define PGTAG_CARD_ACTION_2HAND FGameplayTag::RequestGameplayTag(FName("Card.Action.MoveToHand"))
#define PGTAG_CARD_ACTION_2PRIZE FGameplayTag::RequestGameplayTag(FName("Card.Action.MoveToPrize"))
#define PGTAG_CARD_ACTION_2TRASH FGameplayTag::RequestGameplayTag(FName("Card.Action.MoveToTrash"))

#define PGTAG_CARD_MONSTER_ACTION_ATTACK1 FGameplayTag::RequestGameplayTag(FName("Card.Monster.Action.Attack1"))
#define PGTAG_CARD_MONSTER_ACTION_ATTACK2 FGameplayTag::RequestGameplayTag(FName("Card.Monster.Action.Attack2"))

#define PGTAG_CARD_MONSTER_ENERGY FGameplayTag::RequestGameplayTag(FName("Card.Monster.Energy"))
#define PGTAG_CARD_MONSTER_ENERGY_DARK FGameplayTag::RequestGameplayTag(FName("Card.Monster.Energy.Dark"))
#define PGTAG_CARD_MONSTER_ENERGY_ELECTRIC FGameplayTag::RequestGameplayTag(FName("Card.Monster.Energy.Electric"))
#define PGTAG_CARD_MONSTER_ENERGY_FIGHT FGameplayTag::RequestGameplayTag(FName("Card.Monster.Energy.Fight"))
#define PGTAG_CARD_MONSTER_ENERGY_FIRE FGameplayTag::RequestGameplayTag(FName("Card.Monster.Energy.Fire"))
#define PGTAG_CARD_MONSTER_ENERGY_GRASS FGameplayTag::RequestGameplayTag(FName("Card.Monster.Energy.Grass"))
#define PGTAG_CARD_MONSTER_ENERGY_WATER FGameplayTag::RequestGameplayTag(FName("Card.Monster.Energy.Water"))