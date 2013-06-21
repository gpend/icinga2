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

#ifndef FILELOGGER_H
#define FILELOGGER_H

#include "base/i2-base.h"
#include "base/streamlogger.h"

namespace icinga
{

/**
 * A logger that logs to a file.
 *
 * @ingroup base
 */
class I2_BASE_API FileLogger : public StreamLogger
{
public:
	typedef shared_ptr<FileLogger> Ptr;
	typedef weak_ptr<FileLogger> WeakPtr;

	explicit FileLogger(const Dictionary::Ptr& serializedUpdate);

private:
	Attribute<String> m_Path;
};

}

#endif /* FILELOGGER_H */