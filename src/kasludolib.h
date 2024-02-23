/***************************************************************************
 *   Copyright (C) 2007 by Rodrigo Bronzelle   *
 *   bronzelle@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef KASLUDOLIB_H
#define KASLUDOLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
	@author Rodrigo Bronzelle <bronzelle@gmail.com>
*/
class kasludolib{
public:
    static int mostrar(char *foto, char *arquivo);
    static int esconder(char *arq, char *foto, char *novaFoto);
};

#endif
