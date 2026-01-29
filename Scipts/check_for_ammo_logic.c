void CheckNearbyAmmo()
{
    IEntity player = GetGame().GetPlayerController().GetControlledEntity();
    if (!player) return;

    vector center = player.GetOrigin();
    float radius = 10.0;
    
    // 1. Get current weapons
    InventoryStorageManagerComponent storage = InventoryStorageManagerComponent.Cast(player.FindComponent(InventoryStorageManagerComponent));
    array<IEntity> weapons = {};
    storage.GetItems(weapons); // Simplified: you'd filter for WeaponEntities
    
    bool foundAmmo = false;
    string report = "Nearby Ammo Check:\n";

    // 2. Search the area
    GetGame().GetWorld().QueryEntitiesBySphere(center, radius,  void(IEntity ent)
    {
        // Check if entity is a magazine
        MagazineComponent magComp = MagazineComponent.Cast(ent.FindComponent(MagazineComponent));
        if (magComp)
        {
            // Logic to compare magComp.GetUIInfo().GetName() with weapon requirements
            foundAmmo = true;
            report += "- Found: " + ent.GetPrefabData().GetPrefabName() + "\n";
        }
        return true; // Continue search
    }, null, EQueryEntitiesFlags.DYNAMIC | EQueryEntitiesFlags.STATIC);

    // 3. Output to UI
    SCR_HintManagerComponent.GetInstance().ShowCustomHint(report, "Ammo Scanner", 5.0);
}