/*
 * Copyright (C) 2009 Niek Linnenbank
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <API/VMCopy.h>
#include <string.h>
#include "ProcFile.h"

ProcFile::ProcFile(char *str)
{
    size   = strlen(str);
    buffer = new char[size + 1];
    strlcpy(buffer, str, size + 1);
}

ProcFile::~ProcFile()
{
    delete buffer;
}

Error ProcFile::read(IOBuffer *buffer, Size size, Size offset)
{
    /* Bounds checking. */
    if (offset >= this->size)
    {
	return 0;
    }
    else
    {
	/* How much bytes to copy? */
	Size bytes = this->size - offset > size ?
		    			   size : this->size - offset;
    
	/* Copy the buffers. */
	return buffer->write(this->buffer + offset, bytes);
    }
}
