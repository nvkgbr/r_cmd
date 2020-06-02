#include <pawn.regex>

#if defined _r_cmd_included
	#endinput
#endif
#define _r_cmd_included

#define MAX_FUNC_NAME (32)

#define COMMAND:%1(%2)          \
			forward cmd_%1(%2); \
			public cmd_%1(%2)

#define CMD:%1(%2) \
			COMMAND:%1(%2)

#define command(%1,%2,%3) \
			COMMAND:%1(%2, %3)

#define cmd(%1,%2,%3) \
			COMMAND:%1(%2, %3)

static bool:r_OPCP = false;

forward OnPlayerCommandPerformed(playerid, cmdtext[], success);

public OnGameModeInit(){
    r_OPCP = funcidx("OnPlayerCommandPerformed") != -1;
	return true;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit r_cmd_OnGameModeInit
#if defined r_cmd_OnGameModeInit
	forward r_cmd_OnGameModeInit();
#endif

public OnPlayerCommandText(playerid, cmdtext[])
{
	new Regex:r_with_param = Regex_New("\\/\\s*(\\w{1,15})\\s+(.+)"),RegexMatch:m,cmd[16], params[256],cmd_length, params_length,funcname[MAX_FUNC_NAME];
    	if (Regex_Match(cmdtext, r_with_param, m))
	{
        	Match_GetGroup(m, 1, cmd, cmd_length);
        	Match_GetGroup(m, 2, params, params_length);
        	Match_Free(m);
    	}
    	else
    	{
        	new Regex:r = Regex_Match("\\/\\s*(\\w{1,15})\\s*");
        	if (regex_match(cmdtext, r, m))
        	{
            		Match_GetGroup(m, 1, cmd, cmd_length);
            		Match_Free(m);
        	}
        	Regex_Delete(r);
    	}
    	Regex_Delete(r_with_param);
    	UncapitalizeString(cmd);
    	format(funcname, sizeof(funcname), "cmd_%s", cmd);
	if(params_length == 0)
	{
		if (r_OPCP)
		{
			return CallLocalFunction("OnPlayerCommandPerformed", "isi", playerid, cmdtext, CallLocalFunction(funcname, "is", playerid,"\1"));
		}
		return CallLocalFunction(funcname, "is", playerid, "\1");
	}
    	if (r_OPCP)
	{
		return CallLocalFunction("OnPlayerCommandPerformed", "isi", playerid, cmdtext, CallLocalFunction(funcname, "is", playerid,params));
	}
	return CallLocalFunction(funcname, "is", playerid, params);
}

#if defined _ALS_OnPlayerCommandText
	#undef OnPlayerCommandText
#else
	#define _ALS_OnPlayerCommandText
#endif
#define OnPlayerCommandText r_cmd_OnPlayerCommandText
#if defined r_cmd_OnPlayerCommandText
	forward r_cmd_OnPlayerCommandText(playerid, cmdtext[]);
#endif

stock UncapitalizeString(string[])
{
	for(new i = 0, j = strlen(string); i < j; i ++)
	{
		string[i] = tolower(string[i]);
	}
	return 1;
}
