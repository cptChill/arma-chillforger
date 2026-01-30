modded class SCR_PlayerController : PlayerController
{
	// This function intercepts inputs mapped in your .conf file
	override void OnAction(string actionName, float value, EActionTrigger triggerKind)
	{
		super.OnAction(actionName, value, triggerKind);
		
		// This string must match the 'Action Name' in your AmmoscannerInputs.conf
		if (actionName == "AmmoScanner" && triggerKind == EActionTrigger.DOWN)
		{
			MyAmmoScannerLogic.ScanForRelevantAmmo();
		}
	}
}