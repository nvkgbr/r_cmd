# r_cmd
SAMP parancsfeldogozó.

A működéséhez szükséged lesz YourShadow Regex pluginjára. Link: https://github.com/urShadow/Pawn.Regex/releases


Az include a ZCMD szintaxisát használja így egyszerűen átválthatsz a zcmdről r_cmd-re.

A játékmododból töröld az OnPlayerCommandText callback-et.

Használat:

CMD:test(playerid,params[])
{
  SendClientMessage(playerid,-1,"Beírtam a /teszt parancsot ! ");
	return 1;
}
