/**
 * Copyright (C) <2011> <Syracuse System Security (Sycure) Lab>
 *
 * This library is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.  *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

/*
 * DS_Init.cpp
 *
 *  Created on: Oct 6, 2011
 *      Author: lok
 */

#include "DroidScope/DS_Init.h"
#include "DroidScope/DS_Common.h"
#include <stdlib.h>

void DS_init()
{
  DECAF_linux_vmi_init();

	/**
	 * register a DECAF_BLOCK_BEGIN and a PGD_WRITE_BACK callback,
	 * construct the shadow processes list
	 */
  context_init();

	/* NDROID START */
  //DalvikMterpOpcodes_init();
  //DalvikDisableJit_init();
  //DalvikPrinter_init();

  atexit(DS_close);
	/* NDROID END */
}

void DS_close()
{
	/* NDROID START */
  //DalvikMterpOpcodes_close();
  //DalvikDisableJit_close();
	context_close();
	/* NDROID END */
}
