
/*! Copyright(c) 1996-2009 Shenzhen TP-LINK Technologies Co. Ltd.
 * \file	nm_lib.c
 * \brief	api functions for NVRAM manager.
 * \author	Meng Qing
 * \version	1.0
 * \date	24/04/2009
 */


/**************************************************************************************************/
/*                                      CONFIGURATIONS                                            */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                      INCLUDE_FILES                                             */
/**************************************************************************************************/
#if 0
#include "lib_types.h"
#include "lib_string.h"
#include "lib_printf.h"
#endif
#include <common.h>

#include "nm_lib.h"
#include "nm_api.h"

#include <asm/byteorder.h> /* ntohl */
/**************************************************************************************************/
/*                                      DEFINES                                                   */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                      TYPES                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                      EXTERN_PROTOTYPES                                         */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                      LOCAL_PROTOTYPES                                          */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                      VARIABLES                                                 */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                      LOCAL_FUNCTIONS                                           */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                      PUBLIC_FUNCTIONS                                          */
/**************************************************************************************************/



/*******************************************************************
 * Name		: nm_api_getOSoffset
 * Abstract	: get OS offset.
 * Input	: 
 * Output	: 
 * Return	: ERROR or offset
 */
int nm_api_getOSoffset(char * pAppBuf)
{
	nflash_partitions *part = (nflash_partitions*)pAppBuf;
	
	while(part->next_offset)
	{
		if(part->name[0] == 0)
		{
			NM_ERROR("no partition name.");
			return -1;
		}

		NM_ERROR("addr %s: startAddr %x, size %x, nextOffset %x.", part->name,
			ntohl(part->start_addr), ntohl(part->size), ntohl(part->next_offset));
		if (ntohl(part->size) + ntohl(part->start_addr) != ntohl(part->next_offset))
		{
			NM_ERROR("error addr %s: startAddr %x, size %x, nextOffset %x.", part->name,
				ntohl(part->start_addr), ntohl(part->size), ntohl(part->next_offset));
			return -1;
		}
		part = (nflash_partitions*)(pAppBuf + ntohl(part->next_offset));
	}

	if(part->name[0] == 0)
	{
		NM_ERROR("no partition name.");
		return -1;
	}	

	NM_ERROR("addr %s: startAddr %x, size %x, nextOffset %x.", part->name,
		ntohl(part->start_addr), ntohl(part->size), ntohl(part->next_offset));
	return ntohl(part->size) + ntohl(part->start_addr);
}

/**************************************************************************************************/
/*                                      GLOBAL_FUNCTIONS                                          */
/**************************************************************************************************/


