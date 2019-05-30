%{
#include <stdlib.h>
#include "testinterp2.h"
#include "testbison2.tab.h"
void yyerror(char *); 
%}
%option yylineno
number [0-9]+
id [A-Za-z][A-Za-z0-9]*
uint_ UINT
boolean_ BOOLEAN
true_ TRUE
false_ FALSE
cuint_ CUINT
cboolean_ CBOOLEAN
d1arrayofbool_ 1DARRAYOFBOOL
d1arrayofuint_ 1DARRAYOFUINT
d2arrayofbool_ 2DARRAYOFBOOL
d2arrayofuint_ 2DARRAYOFUINT
extend1_ EXTEND1
extend2_ EXTEND2
size1_ SIZE1
size2_ SIZE2
inc_ INC
dec_ DEC
not_ NOT
or_ OR
gt_ GT
lt_ LT
if_ IF
else_ ELSE
while_ WHILE
do_ DO
forw_ FORW
back_ BACK
right_ RIGHT
left_ LEFT
getf_ GETF
getb_ GETB
getr_ GETR
getl_ GETL
pushf_ PUSHF
pushb_ PUSHB
pushr_ PUSHR
pushl_ PUSHL
undo_ UNDO
exit_ EXIT
function_ FUNCTION
main_ MAIN
end_ END
eq_ =
%%
{eq_} { yylloc.last_line=yylloc.first_line =yylineno; printf("%d",0);return eq_;}
{true_} {yylloc.last_line=yylloc.first_line =yylineno; return true_;}
{false_} {yylloc.last_line=yylloc.first_line =yylineno; return false_;}
{uint_} {yylloc.last_line=yylloc.first_line =yylineno; printf("%d",0);return uint_;}
{boolean_} {yylloc.last_line=yylloc.first_line =yylineno; return boolean_;}
{cuint_} {yylloc.last_line=yylloc.first_line =yylineno; return cuint_;}
{cboolean_} {yylloc.last_line=yylloc.first_line =yylineno; return cboolean_;}
{d1arrayofbool_} {yylloc.last_line=yylloc.first_line =yylineno; return d1arrayofbool_;}
{d1arrayofuint_} {yylloc.last_line=yylloc.first_line =yylineno; return d1arrayofuint_;}
{d2arrayofbool_} {yylloc.last_line=yylloc.first_line =yylineno; return d2arrayofbool_;}
{d2arrayofuint_} {yylloc.last_line=yylloc.first_line =yylineno; return d2arrayofuint_;}
{extend1_} {yylloc.last_line=yylloc.first_line =yylineno; return extend1_;}
{extend2_} {yylloc.last_line=yylloc.first_line =yylineno; return extend2_;}
{size1_} {yylloc.last_line=yylloc.first_line =yylineno; return size1_;}
{size2_} {yylloc.last_line=yylloc.first_line =yylineno; return size2_;}
{inc_} {yylloc.last_line=yylloc.first_line =yylineno; return inc_;}
{dec_} {yylloc.last_line=yylloc.first_line =yylineno; return dec_;}
{not_} {yylloc.last_line=yylloc.first_line =yylineno; return not_;}
{or_} {yylloc.last_line=yylloc.first_line =yylineno; return or_;}
{gt_} {yylloc.last_line=yylloc.first_line =yylineno; return gt_;}
{lt_} {yylloc.last_line=yylloc.first_line =yylineno; return lt_;}
{if_} {yylloc.last_line=yylloc.first_line =yylineno; return if_;}
{else_} {yylloc.last_line=yylloc.first_line =yylineno; return else_;}
{while_} {yylloc.last_line=yylloc.first_line =yylineno; return while_;}
{do_} {yylloc.last_line=yylloc.first_line =yylineno; return do_;}
{forw_} {yylloc.last_line=yylloc.first_line =yylineno; return forw_;}
{back_} {yylloc.last_line=yylloc.first_line =yylineno; return back_;}
{right_} {yylloc.last_line=yylloc.first_line =yylineno; return right_;}
{left_} {yylloc.last_line=yylloc.first_line =yylineno; return left_;}
{getf_} {yylloc.last_line=yylloc.first_line =yylineno; return getf_;}
{getb_} {yylloc.last_line=yylloc.first_line =yylineno; return getb_;}
{getr_} {yylloc.last_line=yylloc.first_line =yylineno; return getr_;}
{getl_} {yylloc.last_line=yylloc.first_line =yylineno; return getl_;}
{pushf_} {yylloc.last_line=yylloc.first_line =yylineno; return pushf_;}
{pushb_} {yylloc.last_line=yylloc.first_line =yylineno; return pushb_;}
{pushr_} {yylloc.last_line=yylloc.first_line =yylineno; return pushr_;}
{pushl_} {yylloc.last_line=yylloc.first_line =yylineno; return pushl_;}
{undo_} {yylloc.last_line=yylloc.first_line =yylineno; return undo_;}
{exit_} {yylloc.last_line=yylloc.first_line =yylineno; return exit_;}
{function_} {yylloc.last_line=yylloc.first_line =yylineno; return function_; }
{main_} {yylloc.last_line=yylloc.first_line =yylineno; return main_;}
{end_} {yylloc.last_line=yylloc.first_line =yylineno; return end_;}
([+*-/,;()[\]{}\n]) {yylloc.last_line=yylloc.first_line =yylineno; printf("%d",0);return *yytext; }
([ \t]) {}
(\r?\n) {yylloc.last_line=yylloc.first_line =yylineno; return '\n';}
{number} {yylloc.last_line=yylloc.first_line =yylineno; printf("%d",0);sscanf(yytext,"%d",&yylval);return number;}
{id} {yylloc.last_line=yylloc.first_line =yylineno; printf("%d",0);/*sscanf(yytext,"%s",&yylval);return id;*/yylval.str=new char[strlen(yytext)+1];
     strcpy(yylval.str,yytext);return id;}
(.) {yylloc.last_line=yylloc.first_line =yylineno;  yyerror("Unknown character"); }
%%
int yywrap(void){
	return 1;
}