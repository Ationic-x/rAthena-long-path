// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

/**
 * Custom Script Commands
 * Place the body of custom script commands in this file.
 * Format:
 *	BUILDIN_FUNC(command_name)
 *	{
 *		<code>;
 *	}
 **/

//BUILDIN_FUNC(example)
//{
//	ShowInfo("buildin_example: It works!\n");
//	script_pushint(st,1);
//	return 0;
//}


/**
 * Copy of npcwalkto with minor changes
 * 
 * Make an npc walk to a position.
 * npclongwalkto <x>,<y> {,"<npc name>"} };
 * 
 * This function is only used in long walks
 * Where isn't know the track to save time creating the array
 * Dont recommended abuse of this function cuz consume more memory
 * 
 */
BUILDIN_FUNC(npclongwalkto)
{
	npc_data* nd;

	if (script_hasdata(st, 4))
		nd = npc_name2id(script_getstr(st, 4));
	else
		nd = map_id2nd(st->oid);

	if (nd == nullptr) {
		if (script_hasdata(st, 4))
			ShowError("buildin_npcwalkto: %s is a non-existing NPC.\n", script_getstr(st, 4));
		else
			ShowError("buildin_npcwalkto: non-existing NPC.\n");
		return SCRIPT_CMD_FAILURE;
	}

	if( nd->bl.m < 0 ){
		ShowError( "buildin_npcwalkto: NPC is not on a map.\n" );
		return SCRIPT_CMD_FAILURE;
	}

	struct map_data* mapdata = map_getmapdata( nd->bl.m );
	int x = script_getnum(st, 2);
	int y = script_getnum(st, 3);

	if( x < 0 || x >= mapdata->xs || y < 0 || y >= mapdata->ys ){
		ShowWarning( "buildin_npcwalkto: coordinates %d/%d are out of bounds in map %s(%dx%d).\n", x, y, mapdata->name, mapdata->xs, mapdata->ys );
		return SCRIPT_CMD_FAILURE;
	}

	if (!nd->status.hp)
		status_calc_npc(nd, SCO_FIRST);
	else
		status_calc_npc(nd, SCO_NONE);

	unit_walktoxy(&nd->bl,x,y,16); // Special flag 16 = long walk

	return SCRIPT_CMD_SUCCESS;
}
