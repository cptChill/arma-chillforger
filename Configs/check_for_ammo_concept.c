modded class SCR_PlayerController : PlayerController
{
	override void OnAction(string actionName, float value, EActionTrigger trigger)
	{
		super.OnAction(actionName, value, trigger);

		// "CheckAmmo" must match the name you put inside your .conf file
		if (actionName == "CheckAmmo" && trigger == EActionTrigger.PRESSED)
		{
			// Insert the ammo scanning logic here
			Print("Ammo Scan Started!"); 
		}
	}
}