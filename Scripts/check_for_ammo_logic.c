class MyAmmoScannerLogic
{
    static void ScanForRelevantAmmo()
    {
        IEntity player = GetGame().GetPlayerController().GetControlledEntity();
        if (!player) return;

        BaseWeaponManagerComponent weaponMgr = BaseWeaponManagerComponent.Cast(player.FindComponent(BaseWeaponManagerComponent));
        if (!weaponMgr) return;
        
        WeaponComponent currentWeapon = weaponMgr.GetCurrentWeapon();
        if (!currentWeapon) return;

        // Get the magazine well to see what we CAN fit, not just the default
        // Or stick to currentWeapon.GetDefaultMagazinePrefabName() for simplicity
        ResourceName requiredMagResource = currentWeapon.GetDefaultMagazinePrefabName();
        if (requiredMagResource.IsEmpty()) return;

        string report = "Scanning for: " + requiredMagResource + "\n";
        int foundCount = 0;

        // Use a wider flag set to catch items in more states
        EQueryEntitiesFlags flags = EQueryEntitiesFlags.DYNAMIC | EQueryEntitiesFlags.ALL;

        GetGame().GetWorld().QueryEntitiesBySphere(player.GetOrigin(), 10.0,  bool(IEntity ent)
        {
            // Ignore the player themselves
            if (ent == player) return true;

            MagazineComponent magComp = MagazineComponent.Cast(ent.FindComponent(MagazineComponent));
            if (magComp)
            {
                // Compare ResourceNames directly
                if (ent.GetPrefabData().GetPrefabName() == requiredMagResource)
                {
                    foundCount++;
                    vector pos = ent.GetOrigin();
                    report += string.Format("- Found at %1, %2\n", pos[0].ToString(), pos[2].ToString());
                }
            }
            return true;
        }, null, flags);

        if (foundCount == 0) 
            report += "No matching ammo nearby.";
        else
            report = string.Format("Found %1 matches:\n", foundCount) + report;

        SCR_HintManagerComponent.ShowCustomHint(report, "Ammo Scanner", 7.0);
    }
}