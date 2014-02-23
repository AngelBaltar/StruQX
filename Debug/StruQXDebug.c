/* StruQX - SQL XML DATABASE
 * StruQXDebug.c
 * Copyright (C)  Angel Baltar Diaz
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
static unsigned char debug_enabled=0;

/*
 * enables de debug macro execution
 */
void enable_debug()
{
    debug_enabled=1;
}

/*
 * disables de debug macro execution
 */
void disable_debug()
{
    debug_enabled=0;
}

/**
 * gets if debug is enabled
 */
unsigned char is_debug_enabled()
{
    return debug_enabled;
}