modded class SCR_PlayerController : PlayerController
{
    override void OnAction(string actionName, float value, EActionTrigger triggerKind)
    {
        super.OnAction(actionName, value, triggerKind);
        
        if (actionName == "AmmoScanner" && triggerKind == EActionTrigger.DOWN)
        {
            MyAmmoScannerLogic.ScanForRelevantAmmo();
        }
    }

    // Ensure our custom input context is actually active
    override void OnPostInit(IEntity owner)
    {
        super.OnPostInit(owner);
        
        // This makes sure the engine is actually listening for your specific .conf setup
        GetInputManager().AddContext("IngameContext");
    }
}