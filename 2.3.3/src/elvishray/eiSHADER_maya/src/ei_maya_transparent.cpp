/**************************************************************************
 * Copyright (C) 2011 Elvic Liang<len3dev@gmail.com>
 * All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************/

#include <eiAPI/ei_shaderx.h>

SHADOW(maya_transparent)

	PARAM(scalar, myopacity);

	void parameters(int pid)
	{
		DECLARE_SCALAR(myopacity, 1.0f);
	}

	void init()
	{
	}

	void exit()
	{
	}

	void main(void *arg)
	{
		scalar op = myopacity();

		// the same with opaque shader
		if (op == 1.0f)
		{
			Cl() = color(0.0f);
			Ol() = color(1.0f);
			return;
		}

		// reduce the length of ray direction to limit the maximum distance
		Cl() = trace_shadow(P(), I() - (P() - E()), Cl()) * (1.0f - op);
		Ol() = op;
	}

END(maya_transparent)
