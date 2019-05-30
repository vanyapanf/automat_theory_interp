%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdarg.h>
	#include "testinterp2.h"
	#include <cstdlib>
	#include <string.h>
	#include <fstream>
	extern FILE * yyin;
	int line=0;
	nodeType *ar(int val);
	nodeType *log(bool val);
	nodeType* id_(char* val,int c);
	nodeType *opr(int oper, int nops, ...);
	nodeType *m1();
	nodeType *m2();
	nodeType *m11();
	nodeType *m22();
	nodeType *f( char* str);
	nodeType *mr(int act);
	nodeType *gr(int act);
	nodeType *pr(int act);
	nodeType *exit();
	void newEl(nodeType* val); 
	void newEl1(nodeType* val);
	void newZnachF(nodeType* idval,nodeType *val);
	void newArgF(nodeType* idval,nodeType *val);
	void newZnach(nodeType* idval);
	void newArg(nodeType* val);
	void newTreeEl(char* name,nodeType* p);
	void freeNode(nodeType *p);
	void freeTreeVec(); 
	int ex(nodeType *p); 
	int yylex(void); 
 	void yyerror(char *s);
	std::vector<nodeType*> Vec;
	std::map<int,std::vector<nodeType*>> Matr;  
	std::map<std::string, nodeType*> Table;
	std::map<std::string,nodeType*> Table1;
	std::map<std::string,int> TabConst;
	std::map<std::string,int> TabConst1;
	std::vector<std::map<std::string, nodeType*>> TableVec;
        std::vector<std::map<std::string, int>> TabConstVec;
	std::vector<std::vector<nodeType*>> TabMas1;
	std::vector<std::map<int,std::vector<nodeType*>>> TabMas2;
	std::vector<nodeType*> Vec0;
	std::vector<std::vector<nodeType*>> Vec1;
	std::vector<nodeType*> TreeVec;
	std::vector<std::vector<nodeType*>> VecIdZnFunc;
	std::vector<std::vector<nodeType*>> VecValZnFunc;
	std::vector<std::vector<nodeType*>> VecIdArgFunc;
	std::vector<std::vector<nodeType*>> VecValArgFunc;	
	std::vector<std::vector<nodeType*>> VecIdZn;
	std::vector<std::vector<nodeType*>> VecValArg;
	std::vector<std::string> FuncName;
	std::vector<std::vector<int>> Lab;
	std::vector<std::string> Err1;
	std::vector<int> Err2;
	int ind=0;
	int ind1=0;
	int ind2=0;
	int ind3=0;
	int x ;
	int y ;
	int napr;
	int way;
	int prev;
%}
%union {
	char* str;
	int intg;
	nodeType *nPtr; 
}
%token<intg> number
%token<str> id
%token uint_
%token cuint_
%token boolean_
%token cboolean_
%token true_
%token false_
%token inc_ 
%token dec_
%token if_ 
%token while_ 
%token do_
%token forw_
%token back_
%token right_
%token left_
%token getf_
%token getb_
%token getr_
%token getl_
%token pushf_
%token pushb_
%token pushr_
%token pushl_
%token undo_
%token exit_
%token d1arrayofbool_
%token d2arrayofbool_
%token d1arrayofuint_ 
%token d2arrayofuint_
%token extend1_ 
%token extend2_
%token size1_ 
%token size2_ 
%token function_
%token main_
%token end_
%nonassoc IFX 
%nonassoc else_ 
%left or_ eq_ gt_ lt_ not_
%left '+' '-'
%left '*' '/'
%destructor {printf("call destructor for: "); puts ($$); delete $$;} id
%type <nPtr> function stmt gr_stmt expr igr_expr1 bgr_expr1 igr_expr2 bgr_expr2
%type <void> igr_expr11 bgr_expr11 igr_expr21 bgr_expr21 znachf argf znach arg
%%
program:
	program main_ '\n' function end_ '\n' {/*int a;*/printf("%d\n",1);if(yynerrs==0) ex($4);printf ("Total number of strings with errors: %d\n", yynerrs);freeNode($4);freeTreeVec();/*scanf("%d\n",a);*/}
	| program '[' znachf ']' function_ id '(' argf ')' '\n' '{' gr_stmt '}' '\n'  {newTreeEl($6,$12);}
	| '[' znachf ']' function_ id '(' argf ')' '\n' '{' gr_stmt '}' '\n'  {newTreeEl($5,$11);}
	| '\n' {}
	;
function:
	function stmt {line = @1.first_line;printf("%d",1);$$=opr('\n',2,$1,$2);}
	|  {printf("%d",1);$$=NULL;}
	| function error {line = @2.first_line; yyerror("Statement error");yyerrok;}
	;
stmt:
	'\n' {line = @1.first_line;$$=opr('\n',2,NULL,NULL);}
	| uint_ id eq_ expr '\n' {line = @1.first_line;$$=opr(eq_,2,id_($2,0),$4);}
	| cuint_ id eq_ expr '\n' {line = @1.first_line;$$=opr(eq_,2,id_($2,1),$4);}
	| boolean_ id eq_ expr '\n' {line = @1.first_line;$$=opr(eq_,2,id_($2,0),$4);}
	| cboolean_ id eq_ expr '\n' {line = @1.first_line;$$=opr(eq_,2,id_($2,1),$4);}
	| d1arrayofuint_ id eq_ igr_expr1 '\n' {line = @1.first_line;$$=opr(eq_,2,id_($2,2),$4);}
	| d1arrayofbool_ id eq_ bgr_expr1 '\n' {line = @1.first_line;$$=opr(eq_,2,id_($2,2),$4);}
	| d2arrayofuint_ id eq_ igr_expr2 '\n' {line = @1.first_line;$$=opr(eq_,2,id_($2,2),$4);}
	| d2arrayofbool_ id eq_ bgr_expr2 '\n' {line = @1.first_line;$$=opr(eq_,2,id_($2,2),$4);}
	| id eq_ expr '\n' {line = @1.first_line;$$=opr(eq_,2,id_($1,2),$3);}
	| id '(' expr ')' eq_ expr '\n' {line = @1.first_line;$$=opr(eq_,3,id_($1,2),$3,$6);}
	| id '(' expr ',' expr ')' eq_ expr '\n' {line = @1.first_line;$$=opr(eq_,4,id_($1,2),$3,$5,$8);}
	| inc_ id '\n' {line = @1.first_line;$$=opr(inc_,1,id_($2,2));}
	| dec_ id '\n' {line = @1.first_line;$$=opr(dec_,1,id_($2,2));}
	| if_ '(' expr ')' '\n' stmt %prec IFX {line = @1.first_line;$$=opr(if_,2,$3,$6);}
	| if_ '(' expr ')' '\n' stmt else_ stmt {line = @1.first_line;$$=opr(if_,3,$3,$6,$8);}
	| extend1_ id expr '\n' {line = @1.first_line;$$=opr(extend1_,2,id_($2,2),$3);}
	| extend2_ id expr expr '\n' {line = @1.first_line;$$=opr(extend2_,3,id_($2,2),$3,$4);}
	| while_ '(' expr ')' do_ '\n' stmt {line = @1.first_line;$$=opr(while_,2,$3,$7);}
	| pushf_ '\n' {line = @1.first_line;$$=pr(1);}
	| pushb_ '\n' {line = @1.first_line;$$=pr(2);}
	| pushr_ '\n' {line = @1.first_line;$$=pr(3);}
	| pushl_ '\n' {line = @1.first_line;$$=pr(4);}
	| undo_ '\n' {line = @1.first_line;$$=pr(5);}
	| '[' znach ']' eq_ id '(' arg ')' '\n' {line = @1.first_line;$$=f($5);} 
	| '{' '\n' gr_stmt '}' '\n' {line = @1.first_line;$$=$3;}
	| uint_ id eq_ error '\n' {line = @1.first_line;yyerror("Expr error");delete($2);$$=opr(eq_,2,NULL,NULL);yyerrok;}
	| cuint_ id eq_ error '\n' {line = @1.first_line;yyerror("Expr error");delete($2);$$=opr(eq_,2,NULL,NULL);yyerrok;}
	| boolean_ id eq_ error '\n' {line = @1.first_line;yyerror("Expr error");delete($2);$$=opr(eq_,2,NULL,NULL);yyerrok;}
	| cboolean_ id eq_ error '\n' {line = @1.first_line;yyerror("Expr error");delete($2);$$=opr(eq_,2,NULL,NULL);yyerrok;}
	| uint_ error eq_ expr '\n' {line = @1.first_line;yyerror("Id error");$$=opr(eq_,2,NULL,NULL);yyerrok;}
	| cuint_ error eq_ expr '\n' {line = @1.first_line;yyerror("Id error");$$=opr(eq_,2,NULL,NULL);yyerrok;}
	| boolean_ error eq_ expr '\n' {line = @1.first_line;yyerror("Id error");$$=opr(eq_,2,NULL,NULL);yyerrok;}
	| cboolean_ error eq_ expr '\n' {line = @1.first_line;yyerror("Id error");$$=opr(eq_,2,NULL,NULL);yyerrok;}
	| d1arrayofuint_ id eq_ error '\n' {line = @1.first_line;yyerror("GrExpr error");delete($2);$$=opr(eq_,2,NULL,NULL);yyerrok;}
	| d1arrayofbool_ id eq_ error '\n' {line = @1.first_line;yyerror("GrExpr error");delete($2);$$=opr(eq_,2,NULL,NULL);yyerrok;}
	| d2arrayofuint_ id eq_ error '\n' {line = @1.first_line;yyerror("GrExpr error");delete($2);$$=opr(eq_,2,NULL,NULL);yyerrok;}
	| d2arrayofbool_ id eq_ error '\n' {line = @1.first_line;yyerror("GrExpr error");delete($2);$$=opr(eq_,2,NULL,NULL);yyerrok;}
	| d1arrayofuint_ error eq_ igr_expr1 '\n' {line = @1.first_line;yyerror("Id error");$$=opr(eq_,2,NULL,NULL);yyerrok;}
	| d1arrayofbool_ error eq_ bgr_expr1 '\n' {line = @1.first_line;yyerror("Id error");$$=opr(eq_,2,NULL,NULL);yyerrok;}
	| d2arrayofuint_ error eq_ igr_expr2 '\n' {line = @1.first_line;yyerror("Id error");$$=opr(eq_,2,NULL,NULL);yyerrok;}
	| d2arrayofbool_ error eq_ bgr_expr2 '\n' {line = @1.first_line;yyerror("Id error");$$=opr(eq_,2,NULL,NULL);yyerrok;}
	| inc_ error '\n' {line = @2.first_line;yyerror("Id error");$$=opr(inc_,1,NULL);yyerrok;}
	| dec_ error '\n' {line = @2.first_line;yyerror("Id error");$$=opr(dec_,1,NULL);yyerrok;}
	| id eq_ error '\n' {line = @3.first_line;yyerror("Expr error");delete($1);$$=opr(eq_,2,NULL,NULL);}
	| id '(' expr ')' eq_ error '\n' {line = @6.first_line;yyerror("Expr error");delete($1);$$=opr(eq_,3,NULL,NULL,NULL);yyerrok;}
	| id '(' expr ',' expr ')' eq_ error '\n' {line = @8.first_line;yyerror("Expr error");delete($1);$$=opr(eq_,4,NULL,NULL,NULL,NULL);yyerrok;}	
	| '[' znach ']' eq_ id '(' error ')' '\n' {line = @7.first_line;yyerror("FuncArg error");delete($5);$$=f(NULL);yyerrok;} 	
	;
gr_stmt:
	gr_stmt stmt {line = @1.first_line;$$=opr('\n',2,$1,$2);}
	| stmt {line = @1.first_line;$$=$1;}
	| gr_stmt error {line = @2.first_line; yyerror("Statement error");yyerrok;}
	| error {line = @1.first_line; yyerror("Statement error");yyerrok;} 
	;
expr:
	 expr '+' expr {line = @1.first_line;$$=opr('+',2,$1,$3);}
	| expr '-' expr {line = @1.first_line;$$=opr('-',2,$1,$3);}
	| expr '*' expr {line = @1.first_line;$$=opr('*',2,$1,$3);}
	| expr '/' expr {line = @1.first_line;$$=opr('/',2,$1,$3);}
	| true_ {line = @1.first_line;$$=log(true);}
	| false_ {line = @1.first_line;$$=log(false);}
	| inc_ id {line = @1.first_line;$$=opr(inc_,1,id_($2,2));}
	| dec_ id {line = @1.first_line;$$=opr(dec_,1,id_($2,2));}
	| expr or_ expr {line = @1.first_line;$$=opr(or_,2,$1,$3);}
	| not_ expr {line = @1.first_line;$$=opr(not_,1,$2);} 
	| expr gt_ expr {line = @1.first_line;$$=opr(gt_,2,$1,$3);}
	| expr lt_ expr {line = @1.first_line;$$=opr(lt_,2,$1,$3);}
	| expr eq_ expr {line = @1.first_line;$$=opr(eq_,2,$1,$3);}
	| expr eq_ eq_ expr {$$=opr('[',2,$1,$4);}
	| id '(' expr ',' expr ')' {line = @1.first_line;$$=opr(',',3,id_($1,2),$3,$5);}
	| id '(' expr ')' {line = @1.first_line;$$=opr('(',2,id_($1,2),$3);}
	| size1_ id {line = @1.first_line;$$=opr(size1_,1,id_($2,2));}
	| size2_ '(' id  expr ')' {line = @1.first_line;$$=opr(size2_,2,id_($3,2),$4);}
	| forw_ {line = @1.first_line;$$=mr(1);}
	| back_ {line = @1.first_line;$$=mr(2);}
	| right_ {line = @1.first_line;$$=mr(3);}
	| left_ {line = @1.first_line;$$=mr(4);}
	| getf_ {line = @1.first_line;$$=gr(1);}
	| getb_ {line = @1.first_line;$$=gr(2);} 
	| getr_ {line = @1.first_line;$$=gr(3);}
	| getl_ {line = @1.first_line;$$=gr(4);}
	| exit_ {line = @1.first_line;$$=exit();}
	| number {line = @1.first_line;$$=ar($1);}
	| id {line = @1.first_line;$$=id_($1,2);}
	| id '(' error ')' {line = @3.first_line; yyerror("Indx error");delete ($1);$$=opr('(',2,NULL,NULL);yyerrok;}
	| inc_ error {line = @2.first_line;yyerror("Id error");$$=opr(inc_,1,NULL);yyerrok;}
	| dec_ error {line = @2.first_line;yyerror("Id error");$$=opr(dec_,1,NULL);yyerrok;}
	| error '(' expr ',' expr ')' {line = @1.first_line;yyerror("Id error");$$=opr(',',3,NULL,NULL,NULL);yyerrok;}
	| error '(' expr ')' {line = @1.first_line;yyerror("Id error");$$=opr('(',2,NULL,NULL);yyerrok;}
	| size1_ error {line = @2.first_line;yyerror("Id error");$$=opr(size1_,1,NULL);yyerrok;}
	| size2_ '(' error  expr ')' {line = @3.first_line;yyerror("Id error");$$=opr(size2_,2,NULL,NULL);yyerrok;}
	;
znachf:
	znachf ',' id eq_ expr {line = @1.first_line;newZnachF(id_($3,2),$5);}
	| id eq_ expr {line = @1.first_line;newZnachF(id_($1,2),$3);}
	;
argf:
	argf ',' id eq_ expr {line = @1.first_line;newArgF(id_($3,2),$5);}
	| id eq_ expr {line = @1.first_line;newArgF(id_($1,2),$3);}
	;
znach:
	znach ',' id {line = @1.first_line;newZnach(id_($3,2));}
	| id {line = @1.first_line;newZnach(id_($1,2));}
	| znach ',' {line = @1.first_line;newZnach(NULL);}
	;
arg:
	arg ',' expr {line = @1.first_line;newArg($3);}
	| expr {line = @1.first_line;newArg($1);}
	| arg ',' {line = @1.first_line;newArg(NULL);}
	;
igr_expr1:
    	'[' igr_expr11 ']' {line = @1.first_line;$$=m1();} 
	;
igr_expr11:
	igr_expr11 ',' expr {line = @1.first_line;printf("%d",1);newEl($3);}
	| expr {line = @1.first_line;printf("%d",1);newEl($1);}
	| igr_expr11 ',' error {line = @3.first_line;yyerror("Expr error");newEl(NULL);yyerrok;}
	| error {line = @1.first_line;yyerror("Expr error");newEl(NULL);yyerrok;}
	;
bgr_expr1:
    	'[' bgr_expr11 ']' {line = @1.first_line;$$=m2();}
	;
bgr_expr11:
	bgr_expr11 ',' expr {line = @1.first_line;newEl($3);}
	| expr {line = @1.first_line;newEl($1);}
	| bgr_expr11 ',' error {line = @3.first_line;yyerror("Expr error");newEl(NULL);yyerrok;}
	| error {line = @1.first_line;yyerror("Expr error");newEl(NULL);yyerrok;}
	;
igr_expr2:
	'[' igr_expr21 ']' {line = @1.first_line;$$=m11();}
	;
igr_expr21:
	igr_expr21 ';' expr '[' igr_expr11 ']' {line = @1.first_line;newEl1($3);}
	| expr '[' igr_expr11 ']' {line = @1.first_line;newEl1($1);}
	| igr_expr21 ';' error {line = @3.first_line;yyerror("Expr error");newEl1(NULL);yyerrok;}
	| error '[' igr_expr11 ']' {line = @1.first_line;yyerror("Expr error");newEl1(NULL);yyerrok;}
	;
bgr_expr2:
	'[' bgr_expr21 ']' {line = @1.first_line;$$=m22();}
	;
bgr_expr21:
	bgr_expr21 ';' expr '[' bgr_expr11 ']' {line = @1.first_line;newEl1($3);}
	| expr '[' bgr_expr11 ']' {line = @1.first_line;newEl1($1);}
	| bgr_expr21 ';' error {line = @3.first_line;yyerror("Expr error");newEl1(NULL);yyerrok;}
	| error '[' bgr_expr11 ']' {line = @1.first_line;yyerror("Expr error");newEl1(NULL);yyerrok;}
	;
%%
void newEl(nodeType* val){
	Vec.push_back(val);
}
void newEl1(nodeType* val){
	Vec0.push_back(val);
	Matr[Vec0.size()-1]=Vec;
	Vec.clear();
}
void newZnachF(nodeType *idval,nodeType *val){
	if((ind==0)||(ind!=ind2)){
	std::vector<nodeType*> v;
	VecIdZnFunc.push_back(v);
	VecValZnFunc.push_back(v);
	VecIdArgFunc.push_back(v);
	VecValArgFunc.push_back(v);
	if (ind!=ind2)
		++ind2;
	}
	VecIdZnFunc[ind].push_back(idval);
	VecValZnFunc[ind].push_back(val);
}
void newArgF(nodeType *idval,nodeType *val){
	VecIdArgFunc[ind].push_back(idval);
	VecValArgFunc[ind].push_back(val);
}
void newZnach(nodeType *idval){
	if((ind1==0)||(ind1!=ind3)){
	std::vector<nodeType*> v;
	VecIdZn.push_back(v);
	VecValArg.push_back(v);
	if (ind1!=ind3)
		++ind3;
	}
	VecIdZn[ind1].push_back(idval);
	printf("%d",ind1);
}
void newArg(nodeType* val){
	VecValArg[ind1].push_back(val);
}
void newTreeEl(char* name,nodeType* p){
	TreeVec.push_back(p);
	FuncName.push_back(std::string(name));
	++ind;
}
nodeType *ar(int val){
	nodeType *p;
	printf("%d",3);
	if((p=new nodeType)==NULL)
		yyerror("out of memory");
	p->type=typeAr;
	p->ar.a=val;
	return p;
}
nodeType *log(bool val){
	nodeType *p;
	printf("%d",4);
	if((p=new nodeType)==NULL)
		yyerror("out of memory");
	p->type=typeLog;
	p->log.l=val;
	return p;
}
nodeType *id_(char* val,int c){
	nodeType *p;
	printf("%d",5);
	if((p=new nodeType)==NULL)
		yyerror("out of memory");
	p->type=typeId;
	p->id_.i=val;
	printf("%s",p->id_.i);
	p->id_.con=c;
	return p;
}
nodeType *m1(){
	nodeType *p;
	if((p= new nodeType)==NULL)
		yyerror("out of memory");
	p->type=typeAMas1;
	TabMas1.push_back(Vec);
	p->m1.mas=TabMas1.size()-1;
	Vec.clear();
	printf("%d",9);
	return p;	
}
nodeType *m2(){
	nodeType *p;
	if((p= new nodeType)==NULL)
		yyerror("out of memory");
	p->type=typeBMas1;
	TabMas1.push_back(Vec);
	p->m2.mas=TabMas1.size()-1;
	Vec.clear();
	printf("%d",9);
	return p;	
}
nodeType *m11(){
	nodeType *p;
	if((p=new nodeType)==NULL)
		yyerror("out of memory");
	p->type=typeAMas2;
	TabMas2.push_back(Matr);
	Vec1.push_back(Vec0);
	p->m11.mas=TabMas2.size()-1;
	Matr.clear();
	Vec0.clear();
	printf("%d",9);
	return p;	
}
nodeType *m22(){
	nodeType *p;
	if((p=new nodeType)==NULL)
		yyerror("out of memory");
	p->type=typeBMas2;
	TabMas2.push_back(Matr);
	Vec1.push_back(Vec0);
	p->m22.mas=TabMas2.size()-1;
	Matr.clear();
	Vec0.clear();
	printf("%d",9);
	return p;	
}
nodeType *opr(int oper,int nops,...){
	va_list ap;
	nodeType *p;
	int i;
	printf("%d",6);
	if((p=new nodeType)==NULL)
		yyerror("out of memory");
	p->type=typeOp;
	p->opr.oper=oper;
	p->opr.nops=nops;
	va_start(ap,nops);
	for(int i=0;i<nops;++i)
		p->opr.op[i]=va_arg(ap,nodeType*);
	va_end(ap);
	return p;
}
nodeType *f(char* str){
	nodeType *p;
	if((p=new nodeType)==NULL)
		yyerror("out of memory");
	p->type=typeFunc;
	p->f.name=str;
	p->f.nom=ind1;
	++ind1;
	return p;
}
nodeType *mr(int act){
	nodeType *p;
	if((p=new nodeType)==NULL)
		yyerror("out of memory");
	p->type=typeMovRob;
	p->mr.nom=act;
	return p;
}
nodeType *gr(int act){
	nodeType *p;
	if((p=new nodeType)==NULL)
		yyerror("out of memory");
	p->type=typeGetRob;
	p->gr.nom=act;
	return p;
}
nodeType *pr(int act){
	nodeType *p;
	if((p=new nodeType)==NULL)
		yyerror("out of memory");
	p->type=typePushRob;
	p->pr.nom=act;
	return p;
}
nodeType *exit(){
	nodeType *p;
	if((p=new nodeType)==NULL)
		yyerror("out of memory");
	p->type=typeExit;
	return p;
}
void freeNode(nodeType *p){
	int i;
	if(!p) return;
	if(p->type==typeOp)
		for (i = 0; i < p->opr.nops; i++) 
                  freeNode(p->opr.op[i]); 
	free(p);
	printf("%d",7);
}
void freeTreeVec(){
 	int i;
	for(i=0;i<TreeVec.size();++i){
		printf("%d",0);
		freeNode(TreeVec[i]);
	}
}
void yyerror(char *s) { 
    printf("%d",8);
    if(s!="syntax error"){
    Err1.push_back(std::string(s));
    Err2.push_back(line);
    }
    else
    fprintf(stderr, "%s at line %d\n", s, line); 
} 
int main(void) { 
    int a,b,c;
    std::vector<int> v;
    yydebug=1; 
    std::ifstream fin("labirint.txt");
    std::ofstream fout("error.txt");
    fin>>a;
    fin>>b;    
    for(int i=0;i<b;++i){
	for(int j=0;j<a;++j){
	   fin>>c;
	   v.push_back(c);
	}
	Lab.push_back(v);
        v.clear();
    }
    fin>>x;
    fin>>y;
    fin>>napr;
    for(int i=0;i<Lab.size();++i)
    {
	for(int j=0;j<Lab[i].size();++j)
	   printf("%d",Lab[i][j]);
        printf("\n");
    }
    yyin = fopen ("input.txt", "r"); 
    yyparse();
    for(int i=0;i<Err1.size();++i)
      fout<<Err1[i]<<" at line "<<Err2[i]<<"\n\r"<<std::endl;
    fclose (yyin); 
    fin.close();
    fout.close();
    return 0;
}

