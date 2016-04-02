#pragma once

#include "Object.h"
#include "../FlareGameTypes.h"
#include "FlareCompanyAI.generated.h"

class UFlareCompany;


struct ResourceVariation
{
	int32 OwnedFlow;
	int32 FactoryFlow;

	int32 OwnedStock;
	int32 FactoryStock;
	int32 StorageStock;

	int32 OwnedCapacity;
	int32 FactoryCapacity;
	int32 StorageCapacity;

};

UCLASS()
class HELIUMRAIN_API UFlareCompanyAI : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	/*----------------------------------------------------
		Save
	----------------------------------------------------*/

	/** Load the company AI from a save file */
	virtual void Load(UFlareCompany* ParentCompany, const FFlareCompanyAISave& Data);

	/** Save the company AI to a save file */
	virtual FFlareCompanyAISave* Save();




	/*----------------------------------------------------
		Gameplay
	----------------------------------------------------*/

	virtual void Simulate();

	virtual void Tick();

	virtual void SimulateDiplomacy();

	/*----------------------------------------------------
		Command groups
	----------------------------------------------------*/

	/** Set the current ship group to give orders to */
	void SetCurrentShipGroup(EFlareCombatGroup::Type Type);

	/** Set the current order for the currently selected ship group */
	void SetTacticForCurrentShipGroup(EFlareCombatTactic::Type Tactic);

	/** Get the current ship group */
	EFlareCombatGroup::Type GetCurrentShipGroup() const;

	/* Get the current order */
	EFlareCombatTactic::Type GetCurrentTacticForShipGroup(EFlareCombatGroup::Type Type) const;

	/** Get the ship count in this group */
	int32 GetShipCountForShipGroup(EFlareCombatGroup::Type Type) const;

	void ResetControlGroups(UFlareSector* Sector);

	void ResetShipGroup(EFlareCombatTactic::Type Tactic);

protected:

	/*----------------------------------------------------
		Helpers
	----------------------------------------------------*/

	virtual void UnassignShipsFromSector(UFlareSimulatedSector* Sector, uint32 Capacity);

	virtual void AssignShipsToSector(UFlareSimulatedSector* Sector, uint32 Capacity);

	TMap<FFlareResourceDescription*, ResourceVariation> ComputeSectorResourceVariation(UFlareSimulatedSector* Sector);

	void DumpSectorResourceVariation(UFlareSimulatedSector* Sector, TMap<FFlareResourceDescription*, struct ResourceVariation>* Variation);

	TArray<UFlareSimulatedSpacecraft*> FindIdleCargos();

	protected:

	UFlareCompany*			               Company;
	FFlareCompanyAISave					   AIData;
	AFlareGame*                            Game;

	// Command groups
	TEnumAsByte<EFlareCombatGroup::Type>     CurrentShipGroup;
	TArray<TEnumAsByte<EFlareCombatTactic::Type>> CurrentCombatTactics;
	int32                                    CurrentMilitaryShipCount;
	int32                                    CurrentCapitalShipCount;
	int32                                    CurrentFighterCount;
	int32                                    CurrentCivilianShipCount;



	public:

	/*----------------------------------------------------
	  Getters
	----------------------------------------------------*/

	AFlareGame* GetGame() const
	{
	  return Game;
	}

};

