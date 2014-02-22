%{
#include <stdio.h>
#include <interprete_query.tab.h>
#include <tipos_basicos.h>
void set_tipo_string_yytext(void);
static unsigned int par_der=0,par_izq=0;
%}

espaciador 		(\t|" "|\n)+				
id 			(([a-zA-Z]+("."([a-zA-Z]+))*)|("*"))
path_xml		("/"|"./"|"../")?([a-zA-Z]+)("/"[a-zA-Z]+)*(".xml")
valor_textual		([a-zA-Z0-9]|á|é|í|ó|ú|"/"|"-"|"."|":"|"#")+
literal			("\"")([a-zA-Z0-9]|á|é|í|ó|ú|"_"|" "|"/"|"-"|"."|":"|"#"|" ")+("\"")
select			(s|S)(e|E)(l|L)(e|E)(c|C)(t|T)
from 			(f|F)(r|R)(o|O)(m|M)
where			(w|W)(h|H)(e|E)(r|R)(e|E)
create			(c|C)(r|R)(e|E)(a|A)(t|T)(e|E)
drop			(d|D)(r|R)(o|O)(p|P)
root			(r|R)(o|O)(o|O)(t|T)("=")
node			(n|N)(o|O)(d|D)(e|E)("=")
exit			(e|E)(x|X)(i|I)(t|T)
source			(s|S)(o|O)(u|U)(r|R)(c|C)(e|E)
insert			(i|I)(n|N)(s|S)(e|E)(r|R)(t|T)
delete			(d|D)(e|E)(l|L)(e|E)(t|T)(e|E)
order			(o|O)(r|R)(d|D)(e|E)(r|R)
by			(b|B)(y|Y)
page			(p|P)(a|A)(g|G)(e|E)
system			(s|S)(y|Y)(s|S)(t|T)(e|E)(m|M)
attributes		(a|A)(t|T)(t|T)(r|R)(i|I)(b|B)(u|U)(t|T)(e|E)(s|S)("=")
eq			("==")
asign			("=")
may			(">")
men			("<")
may_eq			(">=")
men_eq			("<=")
pnt_cm			(";")
coma			(",")
neq			("!=")
par_izq			("(")
par_der			(")")
negar			("!")
and			("&&")
or			("||")

cierre			"/"
tag_xml			{men}"?xml version=\"1.0\"?"{may}
tag_generico		{men}{id}{may}
cierre_tag_generico	{men}{cierre}{id}{may}

%%

{select}		{yylval.tipo.tipo_string="select";return SELECT;}
{where}			{printf("wh\n");yylval.tipo.tipo_string="where";return  WHERE;}
{create}		{yylval.tipo.tipo_string="create";return  CREATE;}
{drop}			{yylval.tipo.tipo_string="drop";return DROP;}
{from}			{yylval.tipo.tipo_string="from";return  FROM;}
{root}			{yylval.tipo.tipo_string="root=";return  ROOT;}
{node}			{yylval.tipo.tipo_string="node=";return  NODE;}
{exit}			{yylval.tipo.tipo_string="exit";return  EXIT;}
{source}		{yylval.tipo.tipo_string="source";return  SOURCE;}
{insert}		{yylval.tipo.tipo_string="insert";return  INSERT;}
{delete}		{yylval.tipo.tipo_string="delete";return  DELETE;}
{order}			{yylval.tipo.tipo_string="order";return  ORDER;}
{by}			{yylval.tipo.tipo_string="by";return BY;}
{page}			{yylval.tipo.tipo_string="page";return PAGE;}
{system}		{yylval.tipo.tipo_string="system";return  SYSTEM;}
{attributes}		{yylval.tipo.tipo_string="attributes=";return  ATTRIBUTES;}
{asign}			{yylval.tipo.tipo_string="=";return  ASIGN;}
{path_xml}		{set_tipo_string_yytext();return  PATH_XML;}
{id}			{set_tipo_string_yytext();return  ID;}
{valor_textual}		{set_tipo_string_yytext();return  VAL_TXT;}
{literal}		{yytext[strlen(yytext)-1]=0;yytext++;set_tipo_string_yytext();return  LITERAL;}
{espaciador}		{set_tipo_string_yytext();return  ESPS;}
{pnt_cm}		{return  PNT_COMA;}
{coma}			{return  COMA;}
{may}			{printf(">\n");yylval.tipo.tipo_int=CMP_GT;return  MAYOR;}
{men}			{yylval.tipo.tipo_int=CMP_LT;return  MENOR;}
{may_eq}		{yylval.tipo.tipo_int=CMP_GEQ;return  MAYOR_EQ;}
{men_eq}		{yylval.tipo.tipo_int=CMP_LEQ;return  MENOR_EQ;}
{eq}			{yylval.tipo.tipo_int=CMP_EQ;return  EQ;}
{neq}			{yylval.tipo.tipo_int=CMP_NEQ;return  NEQ;}
{par_izq}		{par_der++;return  PAR_IZQ;}
{par_der}		{par_izq++;return  PAR_DER;}
{negar}			{printf("negando\n");yylval.tipo.tipo_int=CNN_NO;return  NEGAR;}
{and}			{yylval.tipo.tipo_int=CNN_AND;return  AND;}
{or}			{yylval.tipo.tipo_int=CNN_OR;return  OR;}


{tag_xml}		{set_tipo_string_yytext();return TAG_XML;}
{cierre_tag_generico}	{yytext[strlen(yytext)-1]=0;yytext+=2;set_tipo_string_yytext();return CIERRE_TAG_GENERICO;}
{tag_generico}		{yytext[strlen(yytext)-1]=0;yytext++;set_tipo_string_yytext();return TAG_GENERICO;}

. 			{return LEX_ERROR;};
%%
char * yy__obtiene_yytext(void)
{
	//printf("holaaaaaaaaaaaaBIEEEN\n");
	static char * texto;
	if((yytext==NULL)||(strlen(yytext)==0))
	{
		//printf("abur");
		//fflush(stdout);		
		return "";
	}
	//printf("no abur");
	//fflush(stdout);
	texto=malloc(sizeof(char)*(strlen(yytext)+1));
	strncpy(texto,yytext,strlen(yytext));	
	texto[strlen(yytext)]=0;
	return texto;
}
void	yy__redirecciona_entrada(FILE *fich)
{
	yyin=fich;
}

void set_tipo_string_yytext(void)
{
	yylval.tipo.tipo_string=malloc((strlen(yytext)+1)*sizeof(char));
	//strncpy(yylval.tipo.tipo_string,yytext,strlen(yytext));
	//yylval.tipo.tipo_string[strlen(yytext)]=0;
	snprintf(yylval.tipo.tipo_string,strlen(yytext)+1,"%s",yytext);
}
unsigned int get_par_der()
{
	return par_der;
}
unsigned int get_par_izq()
{
	return par_izq;
}
void reset_par()
{
	par_izq=0;
	par_der=0;
}
