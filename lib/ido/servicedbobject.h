/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012 Icinga Development Team (http://www.icinga.org/)        *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License                *
 * as published by the Free Software Foundation; either version 2             *
 * of the License, or (at your option) any later version.                     *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program; if not, write to the Free Software Foundation     *
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ******************************************************************************/

#ifndef SERVICEDBOBJECT_H
#define SERVICEDBOBJECT_H

#include "ido/dbobject.h"
#include "base/dynamicobject.h"

namespace icinga
{

/**
 * A Service database object.
 *
 * @ingroup ido
 */
class ServiceDbObject : public DbObject
{
public:
	DECLARE_PTR_TYPEDEFS(ServiceDbObject);

	ServiceDbObject(const String& name1, const String& name2);

	virtual Dictionary::Ptr GetFields(void) const;
};

}

#endif /* SERVICEDBOBJECT_H */