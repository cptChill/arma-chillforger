void ScanForRelevantAmmo()
{
    // 1. Get the player and their current weapon
    IEntity player = GetGame().GetPlayerController().GetControlledEntity();
    if (!player) return;

    CharacterControllerComponent charCtrl = CharacterControllerComponent.Cast(player.FindComponent(CharacterControllerComponent));
    BaseWeaponManagerComponent weaponMgr = BaseWeaponManagerComponent.Cast(player.FindComponent(BaseWeaponManagerComponent));
    
    if (!weaponMgr) return;
    
    // Get the currently selected weapon
    WeaponComponent currentWeapon = weaponMgr.GetCurrentWeapon();
    if (!currentWeapon) return;

    // Get the class name of the magazine this weapon needs
    // This is the "Key" we use to find matching items on the ground
    string requiredMagClassName = currentWeapon.GetDefaultMagazinePrefabName();

    string report = "Scanning for: " + requiredMagClassName + "\n";
    bool foundMatch = false;

    // 2. Spatial Query (10m radius)
    GetGame().GetWorld().QueryEntitiesBySphere(player.GetOrigin(), 10.0,  void(IEntity ent)
    {
        // Check if the item is a magazine
        MagazineComponent magComp = MagazineComponent.Cast(ent.FindComponent(MagazineComponent));
        if (magComp)
        {
            // Does this ammo match our gun?
            if (ent.GetPrefabData().GetPrefabName() == requiredMagClassName)
            {
                foundMatch = true;
                report += "[MATCH] Found at: " + ent.GetOrigin().ToString() + "\n";
            }
        }
        return true;
    }, null, EQueryEntitiesFlags.DYNAMIC);

    if (!foundMatch) report += "No matching ammo nearby.";

    // 3. Popup result
    SCR_HintManagerComponent.GetInstance().ShowCustomHint(report, "Ammo Scanner", 7.0);
}