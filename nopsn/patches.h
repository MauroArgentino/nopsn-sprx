#pragma once

#include <stdio.h>

#include "nopsn.h"
#include "system.h"
#include "timer.h"

using namespace std;

// A few basic instructions
int nop = 0x60000000;
int bytes_false = 0x66616C7365;
int bytes_true = 0x747275650D;

// Virtual In-Memory Address Base
int offset_base = 0x00010000;


int offset_cid_NPEB02210 = 0x0026E7B1;// Blockbuster
int offset_cid_NPUP10042 = 0x00651EEF;// TuneIn Radio
int offset_cid_NPUP10028 = 0x01059278;// YouTube


const int HEX = 0;
const int STRING = 1;

bool cmp = false;


// List of Regions
enum Region
{
	NPEA,
	NPEB,
	NPHA,
	NPUO,
	NPUP,
};

// List of all PSN Apps by NAME
enum Name
{
	tunein_radio,
	youtube,
};


// List of all PSN Apps by CONTENT_ID
enum ContentID
{
	NPUP10028,// YouTube
	NPUP10042,// TuneIn Radio
	NPEB01831,// TuneIn Radio
	NPEB01229,// YouTube
	NPJB00286,// YouTube
};


struct AppInfo
{
	char* name;
	char* cid;
	int cid_hex;
	int patch_offset;
	int patch_bytes;
	int toc;
	int opd;
	int import_table;
	int export_table;
};


//char* GetCID(int format)
char* GetCID()
{

	for (int i; i < 9; i++)
	{
		contentID_hex[i] = *(char*)(offset_cid_NPUP10028 + i);
	}

	sleep(200);
	
	char buffer[32];
	sprintf(buffer, "%c%c%c%c%c%c%c%c%c", contentID_hex[0], contentID_hex[1], contentID_hex[2], contentID_hex[3], contentID_hex[4], contentID_hex[5], contentID_hex[6], contentID_hex[7], contentID_hex[8]);

	/*
	switch (format)
	{
		case HEX:
			sprintf(buffer, "%X%X%X%X%X%X%X%X%X", contentID_hex[0], contentID_hex[1], contentID_hex[2], contentID_hex[3], contentID_hex[4], contentID_hex[5], contentID_hex[6], contentID_hex[7], contentID_hex[8]);
			break;
		
		case STRING:
			sprintf(buffer, "%c%c%c%c%c%c%c%c%c", contentID_hex[0], contentID_hex[1], contentID_hex[2], contentID_hex[3], contentID_hex[4], contentID_hex[5], contentID_hex[6], contentID_hex[7], contentID_hex[8]);
			break;

		default:
			break;
	}
	*/
	
	return buffer;
}


// NoPSN Main Patch Function
//void Patch(char* cid, bool active)
void Patch(char* cid)
{
	// Blockbuster
	cmp = cstrcmp(cid, "NPEB02210");
	if (cmp)
	{
		// Read Current Values
		//memTemp[0] = *(int*)NPEB02210_a[0];

		// Set App Info In Memory
		appName = "Blockbuster";
		toc = 0x002CB578;

		// Apply Patches
		//sleep(waitPatch);
		//WriteMemoryDirect(NPEB02210_a[0], bytes_false);

		cmp = false;
	}

	// TuneIn Radio
	cmp = cstrcmp(cid, "NPUP10042");
	if (cmp)
	{
		// Read Current Values
		//memTemp[0] = *(int*)NPUP10042_a[0];
		//sleep(200);
		//memTemp[1] = *(int*)NPUP10042_a[1];
		//sleep(200);
		//memTemp[2] = *(int*)NPUP10042_a[2];
		//sleep(200);

		// Set App Info In Memory
		appName = "TuneIn Radio";
		toc = 0x0076E790;

		// Apply Patches
		//sleep(waitPatch);
		//WriteMemoryDirect(NPUP10042_a[0], nop);
		//sleep(500);
		//WriteMemoryDirect(NPUP10042_a[1], nop);
		//sleep(500);
		//WriteMemoryDirect(NPUP10042_a[2], nop);

		cmp = false;
	}
	
	// YouTube
	// NPEB01229 and NPJB00286 also share the same NPUP10028 ID.
	cmp = cstrcmp(cid, "NPUP10028");
	if (cmp)
	{
		// Read Current Values
		//memTemp[0] = *(int*)NPUP10028_a[0];
		//sleep(200);

		// Set App Info In Memory
		appName = "YouTube";
		toc = 0x012A27F8;
		
		// Apply Patches
		sleep(waitPatch);
		WriteMemoryDirect(NPUP10028_a[0], nop);

		cmp = false;

	}

}


