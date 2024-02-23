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

#include "kasludolib.h"

int esconder(char *arq, char *foto, char *novaFoto)
{
  FILE *fs, *fd, *texto;
  if (!(fs = fopen(foto,"rb")))
    return 3;
  if (!(texto = fopen(arq,"rb")))
    return 2;
  fd = fopen(novaFoto,"wb");
  char header[70], size[16], nSize[4], ponto[4], letra;
  char *auxArq, *narq;
  int i,j;
  fpos_t pos;
  int iSize = 0, nameSize;
  narq = (char *)malloc(strlen(arq)+1);
  strcpy(narq,arq);
  auxArq = strtok(narq,"/");
  while (auxArq) {
    narq = auxArq;
    auxArq = strtok(NULL,"/");
  }
  nameSize = strlen(narq);
  fread(&header,70,1,fs);
  fwrite(&header,70,1,fd);
  fgetpos(fs,&pos);
  fread(&size,16,1,fs);
  fwrite(&size,16,1,fd);
  fread(&nSize,4,1,fs);
  for (i=0;i<4;i++)
    nSize[i] = nSize[i] & 0xFC | (nameSize >> (6-2*i) & 0x00000003);
  fwrite(&nSize,4,1,fd);
  for (j=0;j<nameSize;j++) {
    fread(&ponto,4,1,fs);
    for (i=0;i<4;i++)
      ponto[i] = ponto[i] & 0xFC | (narq[j] >> (6-2*i) & 0x03);
    fwrite(&ponto,4,1,fd);
  }
  while (!feof(texto)) {
    fread(&letra,1,1,texto);
    fread(&ponto,4,1,fs);
    for (i=0;i<4;i++)
      ponto[i] = ponto[i] & 0xFC | (letra >> (6-2*i) & 0x03);
    fwrite(&ponto,4,1,fd);
    iSize++;
  }
  fsetpos(fd,&pos);
  fread(&size,16,1,fd);
  for (i=0;i<16;i++) 
    size[i] = size[i] & 0xFC | (iSize >> (30-2*i) & 0x00000003);
  fsetpos(fd,&pos);
  fwrite(&size,16,1,fd);
  fseek(fd,0,SEEK_END);
  while (!feof(fs)) {
    fread(&ponto,4,1,fs);
    fwrite(&ponto,4,1,fd);
  }
  fclose(fs);
  fclose(fd);
  fclose(texto);
  return 0;
}

int mostrar(char *foto)
{
  FILE *fs, *texto;
  if (!(fs = fopen(foto,"rb")))
    return 2;
  char header[70], size[16], nSize[4], ponto[4], letra, *arq;
  int i,j;
  int iSize = 0,nameSize;
  fread(&header,70,1,fs);
  fread(&size,16,1,fs);
  iSize = 0;
  for (i=0;i<16;i++)
    iSize = (iSize << 2) | (size[i] & 0x03);
  nameSize = 0;
  fread(&nSize,4,1,fs);
  for (i=0;i<4;i++)
    nameSize = (nameSize << 2) | (nSize[i] & 0x03);
  arq = (char *)malloc(nameSize+1);
  for (i=0;i<nameSize;i++) {
    fread(&ponto,4,1,fs);
    letra = 0;
    for (j=0;j<4;j++)
      letra = (letra << 2) | (ponto[j] & 0x03);
    arq[i] = letra;
  }
  arq[nameSize] = 0;
  texto = fopen(arq,"wb");
  for (i=0;i<iSize;i++) {
    fread(&ponto,4,1,fs);
    letra = 0;
    for (j=0;j<4;j++)
      letra = (letra << 2) | (ponto[j] & 0x03);
    fwrite(&letra,1,1,texto);
  }
  fclose(fs);
  fclose(texto);
  return 0;
}

// int main(int argc, char *argv[])
// {
//   char arg1[10], arg2[500], arg3[500];
//   int res;
//   if ((argc > 2) && (argc <5)) {
//     strncpy(arg1,argv[1],9);
//     strncpy(arg2,argv[2],499);
//     if (argc == 4)
//       strncpy(arg3,argv[3],499);
//     if (!strcmp(arg1,"-c")) {
//       if (argc == 4) {
//         if ((res=encript(arg2, arg3)))
//           printf("Arquivo %s não encontrado.\n",res==2?arg2:arg3);
//         return 0;
//       }
//     } else if (!strcmp(arg1,"-u")) {
//       if (argc == 3) {
//         decript(arg2)!=0?printf("Arquivo %s não encontrado.\n",arg2):1;
//         return 0;
//       }
//     }
//   }
//   printf("Uso:\n  cripto -c arquivo imagem\n  cripto -u imagem\n");
//   return 0;
// }
