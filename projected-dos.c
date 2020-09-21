/*BY FILIPE MATUSALEM, SEP 2020     filipematus@gmail.com version 1*/
/*compilation: g++ -o projected-dos.x projected-dos.c*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int main(int argc, char *argv[])
{
FILE *dos,*pdos,*aux;
double efermi,lixo,ref,s,px,py,pz,d1,d2,d3,d4,d5,x;
int natom,pts,i,j,k;
char ch;


printf("\nPROGRAM TO SUM PDOS CONTRIBUTIONS FROM VASP RESULTS (NO-SPIN OR SPIN-ORBIT)\n\n");
printf("The reference energy can be entered as argument to the program. DEFAULT = Fermi energy\n");
printf("by Filipe Matusalem - September 2020 (at home!!!)\n");

printf("-----------------------------------------------------------------------------------------------\n\n");

dos = fopen("DOSCAR","r"); /* Arquivo ASCII */
if(!dos)
{printf( "Erro na abertura do arquivo DOSCAR\n");
exit(0);
}

pdos = fopen("pdos.dat","w"); /* Arquivo ASCII */
if(!pdos)
{printf( "Erro na criacao do arquivo pdos.dat \n");
exit(0);
}

aux = fopen("aux.dat","w"); /* Arquivo ASCII, para escrita */
if(!aux)
{
printf( "Erro na criacao do arquivo aux.dat\n");
exit(0);
}



fscanf(dos,"%d",&natom);

for(i=0;i<5;i++){
do
ch = getc(dos);              /*pula 5 linhas*/
while(ch!='\n');}


fscanf(dos,"%lf",&efermi);
fscanf(dos,"%lf",&efermi);
fscanf(dos,"%d",&pts);
fscanf(dos,"%lf",&efermi);


if(argc > 1){ref=atof(argv[1]);}
else{ref=efermi;}


do
ch = getc(dos);              /*pula 1 linhas*/
while(ch!='\n');


 

for(i=0;i<pts;i++){
do
ch = getc(dos);              /*pula 1 linhas*/
while(ch!='\n');
}



double mtx[pts][37];

for(j=0;j<pts;j++)for(k=0;k<37;k++)mtx[j][k]=0;

for(i=0;i<natom;i++){
do
ch = getc(dos);              /*pula 1 linhas*/
while(ch!='\n');

for(j=0;j<pts;j++){
fscanf(dos,"%lf",&mtx[j][0]);
for(k=1;k<37;k++){fscanf(dos,"%lf",&x);mtx[j][k]=mtx[j][k]+x;}
do
ch = getc(dos);              /*pula 1 linhas*/
while(ch!='\n');
}

}

for(j=0;j<pts;j++){fprintf(aux,"%8.4lf ",mtx[j][0]-ref); for(k=1;k<37;k++)fprintf(aux,"%12.4lE ",mtx[j][k]); fprintf(aux,"\n");}


fclose(dos);
fclose(aux);

aux = fopen("aux.dat","r"); /* Arquivo ASCII, para leitura */
if(!aux)
{printf( "Erro na abertura do arquivo aux.dat\n");
exit(0);
}


fprintf(pdos,"#Energy(eV)  s+p+d            s             p          d\n");


for(j=0;j<pts;j++){

fscanf(aux,"%lf",&x);
fprintf(pdos,"%lf ",x);


fscanf(aux,"%lf",&s);
fscanf(aux,"%lf",&lixo);
fscanf(aux,"%lf",&lixo);
fscanf(aux,"%lf",&lixo);


fscanf(aux,"%lf",&px);
fscanf(aux,"%lf",&lixo);
fscanf(aux,"%lf",&lixo);
fscanf(aux,"%lf",&lixo);

fscanf(aux,"%lf",&py);
fscanf(aux,"%lf",&lixo);
fscanf(aux,"%lf",&lixo);
fscanf(aux,"%lf",&lixo);

fscanf(aux,"%lf",&pz);
fscanf(aux,"%lf",&lixo);
fscanf(aux,"%lf",&lixo);
fscanf(aux,"%lf",&lixo);



fscanf(aux,"%lf",&d1);
fscanf(aux,"%lf",&lixo);
fscanf(aux,"%lf",&lixo);
fscanf(aux,"%lf",&lixo);

fscanf(aux,"%lf",&d2);
fscanf(aux,"%lf",&lixo);
fscanf(aux,"%lf",&lixo);
fscanf(aux,"%lf",&lixo);

fscanf(aux,"%lf",&d3);
fscanf(aux,"%lf",&lixo);
fscanf(aux,"%lf",&lixo);
fscanf(aux,"%lf",&lixo);

fscanf(aux,"%lf",&d4);
fscanf(aux,"%lf",&lixo);
fscanf(aux,"%lf",&lixo);
fscanf(aux,"%lf",&lixo);

fscanf(aux,"%lf",&d5);
fscanf(aux,"%lf",&lixo);
fscanf(aux,"%lf",&lixo);
fscanf(aux,"%lf",&lixo);


fprintf(pdos,"%.6lE ",s+px+py+pz+d1+d2+d3+d4+d5);
fprintf(pdos,"%.6lE ",s);
fprintf(pdos,"%.6lE ",px+py+pz);
fprintf(pdos,"%.6lE \n",d1+d2+d3+d4+d5);
}


fclose(pdos);
fclose(aux);

int del = remove("aux.dat");



printf("Use: xmgrace -batch dosOrbital.bfile\n\n");

aux = fopen("dosOrbital.bfile","w"); /* Arquivo ASCII, para escrita */
if(!aux)
{
printf( "Erro na criacao do arquivo dosOrbital.bfile\n");
exit(0);
}

fputs("# Grace project file\n",aux);
fputs("#\n",aux);
fputs("READ NXY \"pdos.dat\"\n",aux);
fputs("page size 792, 612\n",aux);
fputs("page scroll 5%\n",aux);
fputs("page inout 5%\n",aux);
fputs("link page off\n",aux);
fputs("map font 14 to \"Times-Roman\", \"Times-Roman\"\n",aux);
fputs("map color 0 to (255, 255, 255), \"white\"\n",aux);
fputs("map color 1 to (0, 0, 0), \"black\"\n",aux);
fputs("map color 2 to (255, 0, 0), \"red\"\n",aux);
fputs("map color 3 to (0, 255, 0), \"green\"\n",aux);
fputs("map color 4 to (0, 0, 255), \"blue\"\n",aux);
fputs("map color 5 to (255, 255, 0), \"yellow\"\n",aux);
fputs("map color 6 to (188, 143, 143), \"brown\"\n",aux);
fputs("map color 7 to (220, 220, 220), \"grey\"\n",aux);
fputs("map color 8 to (148, 0, 211), \"violet\"\n",aux);
fputs("map color 9 to (0, 255, 255), \"cyan\"\n",aux);
fputs("map color 10 to (255, 0, 255), \"magenta\"\n",aux);
fputs("map color 11 to (255, 165, 0), \"orange\"\n",aux);
fputs("map color 12 to (114, 33, 188), \"indigo\"\n",aux);
fputs("map color 13 to (103, 7, 72), \"maroon\"\n",aux);
fputs("map color 14 to (64, 224, 208), \"turquoise\"\n",aux);
fputs("map color 15 to (0, 139, 0), \"green4\"\n",aux);
fputs("reference date 0\n",aux);
fputs("date wrap off\n",aux);
fputs("date wrap year 1950\n",aux);
fputs("default linewidth 1.0\n",aux);
fputs("default linestyle 1\n",aux);
fputs("default color 1\n",aux);
fputs("default pattern 1\n",aux);
fputs("default font 14\n",aux);
fputs("default char size 1.000000\n",aux);
fputs("default symbol size 1.000000\n",aux);
fputs("default sformat \"%.8g\"\n",aux);
fputs("background color 0\n",aux);
fputs("page background fill on\n",aux);
fputs("timestamp off\n",aux);
fputs("timestamp 0.03, 0.03\n",aux);
fputs("timestamp color 1\n",aux);
fputs("timestamp rot 0\n",aux);
fputs("timestamp font 14\n",aux);
fputs("timestamp char size 1.000000\n",aux);
fputs("timestamp def \"Wed Sep 16 03:02:24 2020\"\n",aux);
fputs("r0 off\n",aux);
fputs("link r0 to g0\n",aux);
fputs("r0 type above\n",aux);
fputs("r0 linestyle 1\n",aux);
fputs("r0 linewidth 1.0\n",aux);
fputs("r0 color 1\n",aux);
fputs("r0 line 0, 0, 0, 0\n",aux);
fputs("r1 off\n",aux);
fputs("link r1 to g0\n",aux);
fputs("r1 type above\n",aux);
fputs("r1 linestyle 1\n",aux);
fputs("r1 linewidth 1.0\n",aux);
fputs("r1 color 1\n",aux);
fputs("r1 line 0, 0, 0, 0\n",aux);
fputs("r2 off\n",aux);
fputs("link r2 to g0\n",aux);
fputs("r2 type above\n",aux);
fputs("r2 linestyle 1\n",aux);
fputs("r2 linewidth 1.0\n",aux);
fputs("r2 color 1\n",aux);
fputs("r2 line 0, 0, 0, 0\n",aux);
fputs("r3 off\n",aux);
fputs("link r3 to g0\n",aux);
fputs("r3 type above\n",aux);
fputs("r3 linestyle 1\n",aux);
fputs("r3 linewidth 1.0\n",aux);
fputs("r3 color 1\n",aux);
fputs("r3 line 0, 0, 0, 0\n",aux);
fputs("r4 off\n",aux);
fputs("link r4 to g0\n",aux);
fputs("r4 type above\n",aux);
fputs("r4 linestyle 1\n",aux);
fputs("r4 linewidth 1.0\n",aux);
fputs("r4 color 1\n",aux);
fputs("r4 line 0, 0, 0, 0\n",aux);
fputs("g0 on\n",aux);
fputs("g0 hidden false\n",aux);
fputs("g0 type XY\n",aux);
fputs("g0 stacked false\n",aux);
fputs("g0 bar hgap 0.000000\n",aux);
fputs("g0 fixedpoint off\n",aux);
fputs("g0 fixedpoint type 0\n",aux);
fputs("g0 fixedpoint xy 0.000000, 0.000000\n",aux);
fputs("g0 fixedpoint format general general\n",aux);
fputs("g0 fixedpoint prec 6, 6\n",aux);
fputs("with g0\n",aux);
fputs("    world -3, 0, 3, 40\n",aux);
fputs("    stack world 0, 0, 0, 0\n",aux);
fputs("    znorm 1\n",aux);
fputs("    view 0.150000, 0.150000, 0.850000, 0.850000\n",aux);
fputs("    title \"\"\n",aux);
fputs("    title font 14\n",aux);
fputs("    title size 1.500000\n",aux);
fputs("    title color 1\n",aux);
fputs("    subtitle \"\"\n",aux);
fputs("    subtitle font 14\n",aux);
fputs("    subtitle size 1.000000\n",aux);
fputs("    subtitle color 1\n",aux);
fputs("    xaxes scale Normal\n",aux);
fputs("    yaxes scale Normal\n",aux);
fputs("    xaxes invert off\n",aux);
fputs("    yaxes invert off\n",aux);
fputs("    xaxis  on\n",aux);
fputs("    xaxis  type zero false\n",aux);
fputs("    xaxis  offset 0.000000 , 0.000000\n",aux);
fputs("    xaxis  bar on\n",aux);
fputs("    xaxis  bar color 1\n",aux);
fputs("    xaxis  bar linestyle 1\n",aux);
fputs("    xaxis  bar linewidth 1.0\n",aux);
fputs("    xaxis  label \"Energy (eV)\"\n",aux);
fputs("    xaxis  label layout para\n",aux);
fputs("    xaxis  label place auto\n",aux);
fputs("    xaxis  label char size 2.000000\n",aux);
fputs("    xaxis  label font 14\n",aux);
fputs("    xaxis  label color 1\n",aux);
fputs("    xaxis  label place normal\n",aux);
fputs("    xaxis  tick on\n",aux);
fputs("    xaxis  tick major 1\n",aux);
fputs("    xaxis  tick minor ticks 1\n",aux);
fputs("    xaxis  tick default 6\n",aux);
fputs("    xaxis  tick place rounded true\n",aux);
fputs("    xaxis  tick in\n",aux);
fputs("    xaxis  tick major size 1.000000\n",aux);
fputs("    xaxis  tick major color 1\n",aux);
fputs("    xaxis  tick major linewidth 1.0\n",aux);
fputs("    xaxis  tick major linestyle 1\n",aux);
fputs("    xaxis  tick major grid off\n",aux);
fputs("    xaxis  tick minor color 1\n",aux);
fputs("    xaxis  tick minor linewidth 1.0\n",aux);
fputs("    xaxis  tick minor linestyle 1\n",aux);
fputs("    xaxis  tick minor grid off\n",aux);
fputs("    xaxis  tick minor size 0.500000\n",aux);
fputs("    xaxis  ticklabel on\n",aux);
fputs("    xaxis  ticklabel format general\n",aux);
fputs("    xaxis  ticklabel prec 5\n",aux);
fputs("    xaxis  ticklabel formula \"\"\n",aux);
fputs("    xaxis  ticklabel append \"\"\n",aux);
fputs("    xaxis  ticklabel prepend \"\"\n",aux);
fputs("    xaxis  ticklabel angle 0\n",aux);
fputs("    xaxis  ticklabel skip 0\n",aux);
fputs("    xaxis  ticklabel stagger 0\n",aux);
fputs("    xaxis  ticklabel place normal\n",aux);
fputs("    xaxis  ticklabel offset auto\n",aux);
fputs("    xaxis  ticklabel offset 0.000000 , 0.010000\n",aux);
fputs("    xaxis  ticklabel start type auto\n",aux);
fputs("    xaxis  ticklabel start 0.000000\n",aux);
fputs("    xaxis  ticklabel stop type auto\n",aux);
fputs("    xaxis  ticklabel stop 0.000000\n",aux);
fputs("    xaxis  ticklabel char size 1.500000\n",aux);
fputs("    xaxis  ticklabel font 14\n",aux);
fputs("    xaxis  ticklabel color 1\n",aux);
fputs("    xaxis  tick place both\n",aux);
fputs("    xaxis  tick spec type none\n",aux);
fputs("    yaxis  on\n",aux);
fputs("    yaxis  type zero false\n",aux);
fputs("    yaxis  offset 0.000000 , 0.000000\n",aux);
fputs("    yaxis  bar on\n",aux);
fputs("    yaxis  bar color 1\n",aux);
fputs("    yaxis  bar linestyle 1\n",aux);
fputs("    yaxis  bar linewidth 1.0\n",aux);
fputs("    yaxis  label \"DOS (a.u.)\"\n",aux);
fputs("    yaxis  label layout para\n",aux);
fputs("    yaxis  label place auto\n",aux);
fputs("    yaxis  label char size 2.000000\n",aux);
fputs("    yaxis  label font 14\n",aux);
fputs("    yaxis  label color 1\n",aux);
fputs("    yaxis  label place normal\n",aux);
fputs("    yaxis  tick on\n",aux);
fputs("    yaxis  tick major 10\n",aux);
fputs("    yaxis  tick minor ticks 1\n",aux);
fputs("    yaxis  tick default 6\n",aux);
fputs("    yaxis  tick place rounded true\n",aux);
fputs("    yaxis  tick in\n",aux);
fputs("    yaxis  tick major size 1.000000\n",aux);
fputs("    yaxis  tick major color 1\n",aux);
fputs("    yaxis  tick major linewidth 1.0\n",aux);
fputs("    yaxis  tick major linestyle 1\n",aux);
fputs("    yaxis  tick major grid off\n",aux);
fputs("    yaxis  tick minor color 1\n",aux);
fputs("    yaxis  tick minor linewidth 1.0\n",aux);
fputs("    yaxis  tick minor linestyle 1\n",aux);
fputs("    yaxis  tick minor grid off\n",aux);
fputs("    yaxis  tick minor size 0.500000\n",aux);
fputs("    yaxis  ticklabel on\n",aux);
fputs("    yaxis  ticklabel format general\n",aux);
fputs("    yaxis  ticklabel prec 5\n",aux);
fputs("    yaxis  ticklabel formula \"\"\n",aux);
fputs("    yaxis  ticklabel append \"\"\n",aux);
fputs("    yaxis  ticklabel prepend \"\"\n",aux);
fputs("    yaxis  ticklabel angle 0\n",aux);
fputs("    yaxis  ticklabel skip 0\n",aux);
fputs("    yaxis  ticklabel stagger 0\n",aux);
fputs("    yaxis  ticklabel place normal\n",aux);
fputs("    yaxis  ticklabel offset auto\n",aux);
fputs("    yaxis  ticklabel offset 0.000000 , 0.010000\n",aux);
fputs("    yaxis  ticklabel start type auto\n",aux);
fputs("    yaxis  ticklabel start 0.000000\n",aux);
fputs("    yaxis  ticklabel stop type auto\n",aux);
fputs("    yaxis  ticklabel stop 0.000000\n",aux);
fputs("    yaxis  ticklabel char size 1.500000\n",aux);
fputs("    yaxis  ticklabel font 14\n",aux);
fputs("    yaxis  ticklabel color 1\n",aux);
fputs("    yaxis  tick place both\n",aux);
fputs("    yaxis  tick spec type none\n",aux);
fputs("    altxaxis  off\n",aux);
fputs("    altyaxis  off\n",aux);
fputs("    legend on\n",aux);
fputs("    legend loctype view\n",aux);
fputs("    legend 0.65, 0.8\n",aux);
fputs("    legend box color 1\n",aux);
fputs("    legend box pattern 1\n",aux);
fputs("    legend box linewidth 1.0\n",aux);
fputs("    legend box linestyle 1\n",aux);
fputs("    legend box fill color 0\n",aux);
fputs("    legend box fill pattern 1\n",aux);
fputs("    legend font 14\n",aux);
fputs("    legend char size 1.000000\n",aux);
fputs("    legend color 1\n",aux);
fputs("    legend length 4\n",aux);
fputs("    legend vgap 1\n",aux);
fputs("    legend hgap 1\n",aux);
fputs("    legend invert false\n",aux);
fputs("    frame type 0\n",aux);
fputs("    frame linestyle 1\n",aux);
fputs("    frame linewidth 1.0\n",aux);
fputs("    frame color 1\n",aux);
fputs("    frame pattern 1\n",aux);
fputs("    frame background color 0\n",aux);
fputs("    frame background pattern 0\n",aux);
fputs("    s0 hidden false\n",aux);
fputs("    s0 type xy\n",aux);
fputs("    s0 symbol 0\n",aux);
fputs("    s0 symbol size 1.000000\n",aux);
fputs("    s0 symbol color 1\n",aux);
fputs("    s0 symbol pattern 1\n",aux);
fputs("    s0 symbol fill color 1\n",aux);
fputs("    s0 symbol fill pattern 0\n",aux);
fputs("    s0 symbol linewidth 1.0\n",aux);
fputs("    s0 symbol linestyle 1\n",aux);
fputs("    s0 symbol char 65\n",aux);
fputs("    s0 symbol char font 14\n",aux);
fputs("    s0 symbol skip 0\n",aux);
fputs("    s0 line type 1\n",aux);
fputs("    s0 line linestyle 1\n",aux);
fputs("    s0 line linewidth 1.0\n",aux);
fputs("    s0 line color 1\n",aux);
fputs("    s0 line pattern 1\n",aux);
fputs("    s0 baseline type 0\n",aux);
fputs("    s0 baseline off\n",aux);
fputs("    s0 dropline off\n",aux);
fputs("    s0 fill type 0\n",aux);
fputs("    s0 fill rule 0\n",aux);
fputs("    s0 fill color 7\n",aux);
fputs("    s0 fill pattern 1\n",aux);
fputs("    s0 avalue off\n",aux);
fputs("    s0 avalue type 2\n",aux);
fputs("    s0 avalue char size 1.000000\n",aux);
fputs("    s0 avalue font 14\n",aux);
fputs("    s0 avalue color 1\n",aux);
fputs("    s0 avalue rot 0\n",aux);
fputs("    s0 avalue format general\n",aux);
fputs("    s0 avalue prec 3\n",aux);
fputs("    s0 avalue prepend \"\"\n",aux);
fputs("    s0 avalue append \"\"\n",aux);
fputs("    s0 avalue offset 0.000000 , 0.000000\n",aux);
fputs("    s0 errorbar on\n",aux);
fputs("    s0 errorbar place both\n",aux);
fputs("    s0 errorbar color 1\n",aux);
fputs("    s0 errorbar pattern 1\n",aux);
fputs("    s0 errorbar size 1.000000\n",aux);
fputs("    s0 errorbar linewidth 1.0\n",aux);
fputs("    s0 errorbar linestyle 1\n",aux);
fputs("    s0 errorbar riser linewidth 1.0\n",aux);
fputs("    s0 errorbar riser linestyle 1\n",aux);
fputs("    s0 errorbar riser clip off\n",aux);
fputs("    s0 errorbar riser clip length 0.100000\n",aux);
fputs("    s0 comment \"pdos.dat\"\n",aux);
fputs("    s0 legend  \"Total\"\n",aux);
fputs("    s1 hidden false\n",aux);
fputs("    s1 type xy\n",aux);
fputs("    s1 symbol 0\n",aux);
fputs("    s1 symbol size 1.000000\n",aux);
fputs("    s1 symbol color 2\n",aux);
fputs("    s1 symbol pattern 1\n",aux);
fputs("    s1 symbol fill color 2\n",aux);
fputs("    s1 symbol fill pattern 0\n",aux);
fputs("    s1 symbol linewidth 1.0\n",aux);
fputs("    s1 symbol linestyle 1\n",aux);
fputs("    s1 symbol char 65\n",aux);
fputs("    s1 symbol char font 14\n",aux);
fputs("    s1 symbol skip 0\n",aux);
fputs("    s1 line type 1\n",aux);
fputs("    s1 line linestyle 1\n",aux);
fputs("    s1 line linewidth 1.0\n",aux);
fputs("    s1 line color 2\n",aux);
fputs("    s1 line pattern 1\n",aux);
fputs("    s1 baseline type 0\n",aux);
fputs("    s1 baseline off\n",aux);
fputs("    s1 dropline off\n",aux);
fputs("    s1 fill type 1\n",aux);
fputs("    s1 fill rule 0\n",aux);
fputs("    s1 fill color 2\n",aux);
fputs("    s1 fill pattern 1\n",aux);
fputs("    s1 avalue off\n",aux);
fputs("    s1 avalue type 2\n",aux);
fputs("    s1 avalue char size 1.000000\n",aux);
fputs("    s1 avalue font 14\n",aux);
fputs("    s1 avalue color 1\n",aux);
fputs("    s1 avalue rot 0\n",aux);
fputs("    s1 avalue format general\n",aux);
fputs("    s1 avalue prec 3\n",aux);
fputs("    s1 avalue prepend \"\"\n",aux);
fputs("    s1 avalue append \"\"\n",aux);
fputs("    s1 avalue offset 0.000000 , 0.000000\n",aux);
fputs("    s1 errorbar on\n",aux);
fputs("    s1 errorbar place both\n",aux);
fputs("    s1 errorbar color 2\n",aux);
fputs("    s1 errorbar pattern 1\n",aux);
fputs("    s1 errorbar size 1.000000\n",aux);
fputs("    s1 errorbar linewidth 1.0\n",aux);
fputs("    s1 errorbar linestyle 1\n",aux);
fputs("    s1 errorbar riser linewidth 1.0\n",aux);
fputs("    s1 errorbar riser linestyle 1\n",aux);
fputs("    s1 errorbar riser clip off\n",aux);
fputs("    s1 errorbar riser clip length 0.100000\n",aux);
fputs("    s1 comment \"pdos.dat\"\n",aux);
fputs("    s1 legend  \"s\"\n",aux);
fputs("    s2 hidden false\n",aux);
fputs("    s2 type xy\n",aux);
fputs("    s2 symbol 0\n",aux);
fputs("    s2 symbol size 1.000000\n",aux);
fputs("    s2 symbol color 4\n",aux);
fputs("    s2 symbol pattern 1\n",aux);
fputs("    s2 symbol fill color 4\n",aux);
fputs("    s2 symbol fill pattern 0\n",aux);
fputs("    s2 symbol linewidth 1.0\n",aux);
fputs("    s2 symbol linestyle 1\n",aux);
fputs("    s2 symbol char 65\n",aux);
fputs("    s2 symbol char font 14\n",aux);
fputs("    s2 symbol skip 0\n",aux);
fputs("    s2 line type 1\n",aux);
fputs("    s2 line linestyle 1\n",aux);
fputs("    s2 line linewidth 1.0\n",aux);
fputs("    s2 line color 4\n",aux);
fputs("    s2 line pattern 1\n",aux);
fputs("    s2 baseline type 0\n",aux);
fputs("    s2 baseline off\n",aux);
fputs("    s2 dropline off\n",aux);
fputs("    s2 fill type 1\n",aux);
fputs("    s2 fill rule 0\n",aux);
fputs("    s2 fill color 4\n",aux);
fputs("    s2 fill pattern 1\n",aux);
fputs("    s2 avalue off\n",aux);
fputs("    s2 avalue type 2\n",aux);
fputs("    s2 avalue char size 1.000000\n",aux);
fputs("    s2 avalue font 14\n",aux);
fputs("    s2 avalue color 1\n",aux);
fputs("    s2 avalue rot 0\n",aux);
fputs("    s2 avalue format general\n",aux);
fputs("    s2 avalue prec 3\n",aux);
fputs("    s2 avalue prepend \"\"\n",aux);
fputs("    s2 avalue append \"\"\n",aux);
fputs("    s2 avalue offset 0.000000 , 0.000000\n",aux);
fputs("    s2 errorbar on\n",aux);
fputs("    s2 errorbar place both\n",aux);
fputs("    s2 errorbar color 4\n",aux);
fputs("    s2 errorbar pattern 1\n",aux);
fputs("    s2 errorbar size 1.000000\n",aux);
fputs("    s2 errorbar linewidth 1.0\n",aux);
fputs("    s2 errorbar linestyle 1\n",aux);
fputs("    s2 errorbar riser linewidth 1.0\n",aux);
fputs("    s2 errorbar riser linestyle 1\n",aux);
fputs("    s2 errorbar riser clip off\n",aux);
fputs("    s2 errorbar riser clip length 0.100000\n",aux);
fputs("    s2 comment \"pdos.dat\"\n",aux);
fputs("    s2 legend  \"p\"\n",aux);
fputs("    s3 hidden false\n",aux);
fputs("    s3 type xy\n",aux);
fputs("    s3 symbol 0\n",aux);
fputs("    s3 symbol size 1.000000\n",aux);
fputs("    s3 symbol color 10\n",aux);
fputs("    s3 symbol pattern 1\n",aux);
fputs("    s3 symbol fill color 10\n",aux);
fputs("    s3 symbol fill pattern 0\n",aux);
fputs("    s3 symbol linewidth 1.0\n",aux);
fputs("    s3 symbol linestyle 1\n",aux);
fputs("    s3 symbol char 65\n",aux);
fputs("    s3 symbol char font 14\n",aux);
fputs("    s3 symbol skip 0\n",aux);
fputs("    s3 line type 1\n",aux);
fputs("    s3 line linestyle 1\n",aux);
fputs("    s3 line linewidth 1.0\n",aux);
fputs("    s3 line color 10\n",aux);
fputs("    s3 line pattern 1\n",aux);
fputs("    s3 baseline type 0\n",aux);
fputs("    s3 baseline off\n",aux);
fputs("    s3 dropline off\n",aux);
fputs("    s3 fill type 1\n",aux);
fputs("    s3 fill rule 0\n",aux);
fputs("    s3 fill color 10\n",aux);
fputs("    s3 fill pattern 1\n",aux);
fputs("    s3 avalue off\n",aux);
fputs("    s3 avalue type 2\n",aux);
fputs("    s3 avalue char size 1.000000\n",aux);
fputs("    s3 avalue font 14\n",aux);
fputs("    s3 avalue color 1\n",aux);
fputs("    s3 avalue rot 0\n",aux);
fputs("    s3 avalue format general\n",aux);
fputs("    s3 avalue prec 3\n",aux);
fputs("    s3 avalue prepend \"\"\n",aux);
fputs("    s3 avalue append \"\"\n",aux);
fputs("    s3 avalue offset 0.000000 , 0.000000\n",aux);
fputs("    s3 errorbar on\n",aux);
fputs("    s3 errorbar place both\n",aux);
fputs("    s3 errorbar color 10\n",aux);
fputs("    s3 errorbar pattern 1\n",aux);
fputs("    s3 errorbar size 1.000000\n",aux);
fputs("    s3 errorbar linewidth 1.0\n",aux);
fputs("    s3 errorbar linestyle 1\n",aux);
fputs("    s3 errorbar riser linewidth 1.0\n",aux);
fputs("    s3 errorbar riser linestyle 1\n",aux);
fputs("    s3 errorbar riser clip off\n",aux);
fputs("    s3 errorbar riser clip length 0.100000\n",aux);
fputs("    s3 comment \"pdos.dat\"\n",aux);
fputs("    s3 legend  \"d\"\n",aux);



fclose(aux);
}
