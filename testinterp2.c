#include <stdio.h>
#include "testinterp2.h" 
#include "testbison2.tab.h" 
#include <map>
#include <string.h>
void Way1(int x0, int y0, int z, int n) {
	printf("%s\n", "point");
	printf("%d\n", x0);
	printf("%d\n", y0);
	++z;
	if (x0 == 0)
	{
		if (way > z)
			way = z;
	}
	else
		if ((z<way)&&(z<30)) {
			if ((Lab[x0 - 1][y0] == 0) && (n != 4))
				Way1(x0 - 1, y0, z, 1);
			if ((y0 != Lab[x0].size() - 1) && (Lab[x0][y0 + 1] == 0) && (n != 3))
				Way1(x0, y0 + 1, z, 2);
			if ((y0 != 0) && (Lab[x0][y0 - 1] == 0) && (n != 2))
				Way1(x0, y0 - 1, z, 3);
			if ((x0 != Lab.size() - 1) && (Lab[x0 + 1][y0] == 0) && (n != 1))
				Way1(x0 + 1, y0, z, 4);
		}
}
void Way2(int x0, int y0, int z, int n) {
	printf("%s\n", "point");
	printf("%d\n", x0);
	printf("%d\n", y0);
	++z;
	if (x0 == Lab.size() - 1)
	{
		if (way > z)
			way = z;
	}
	else
		if ((z<way)&&(z<30)) {
			if ((Lab[x0 + 1][y0] == 0) && (n != 4))
				Way2(x0 + 1, y0, z, 1);
			if ((y0 != Lab[x0].size() - 1) && (Lab[x0][y0 + 1] == 0) && (n != 3))
				Way2(x0, y0 + 1, z, 2);
			if ((y0 != 0) && (Lab[x0][y0 - 1] == 0) && (n != 2))
				Way2(x0, y0 - 1, z, 3);
			if ((x0 != 0) && (Lab[x0 - 1][y0] == 0) && (n != 1))
				Way2(x0 - 1, y0, z, 4);
		}
}
void Way3(int x0, int y0, int z, int n) {
	printf("%s\n", "point");
	printf("%d\n", x0);
	printf("%d\n", y0);
	++z;

	if (y0 == Lab[x0].size() - 1)
	{
		if (way > z)
			way = z;
	}
	else
		if ((z < way)&&(z<30))
		{
			if ((Lab[x0][y0 + 1] == 0) && (n != 4))
				Way3(x0, y0 + 1, z, 1);
			if ((x0 != 0) && (Lab[x0 - 1][y0] == 0) && (n != 3))
				Way3(x0 - 1, y0, z, 2);
			if ((x0 != Lab.size() - 1) && (Lab[x0 + 1][y0] == 0) && (n != 2))
				Way3(x0 + 1, y0, z, 3);
			if ((y0 != 0) && (Lab[x0][y0 - 1] == 0) && (n != 1))
				Way3(x0, y0 - 1, z, 4);
		}
}
void Way4(int x0, int y0, int z, int n) {
	printf("%s\n", "point");
	printf("%d\n", x0);
	printf("%d\n", y0);
	++z;
	if (y0 == 0)
	{
		if (way > z)
			way = z;
	}
	else
		if ((z<way)&&(z<30)) {
			if ((Lab[x0][y0 - 1] == 0) && (n != 4))
				Way4(x0, y0 - 1, z, 1);
			if ((x0 != 0) && (Lab[x0 - 1][y0] == 0) && (n != 3))
				Way4(x0 - 1, y0, z, 2);
			if ((x0 != Lab.size() - 1) && (Lab[x0 + 1][y0] == 0) && (n != 2))
				Way4(x0 + 1, y0, z, 3);
			if ((y0 != Lab[x0].size() - 1) && (Lab[x0][y0 + 1] == 0) && (n != 1))
				Way4(x0, y0 + 1, z, 4);
		}
}
int ex(nodeType* p) {
	int k = 0;
	int k1 = 0;
	int k2 = 0;
	int k3 = 0;
	int k4 = 0;
	int k5 = 0;
	int k6 = 0;
	int k7 = 0;
	int i1, i2, i3, i4;
	int x1, y1, z, z1;
	int napr1;
	std::string s;
	nodeType* p1 = new nodeType;
	switch (p->type) {
	case typeAr: if (p != NULL) { printf("%d\n", p->ar.a); return(p->ar.a); }
				 else return NULL;
	case typeLog: if (p != NULL) { printf("%c\n", 'l'); if (p->log.l == true) { printf("%d\n", 0); return 0; }
				  else { printf("%d\n", 1); return 1; }
	          }
				  else return -1;
	case typeId:  if (p != NULL) return ex(Table.find(std::string(p->id_.i))->second); else return NULL;
	case typeOp:
		switch (p->opr.oper) {
		case eq_:
			printf("%s\n", "eq");
			if (p->opr.op[0] != NULL)
			{
				if (((p->opr.op[1])->type == typeMovRob) && ((p->opr.op[1])->type != typePushRob)) {
					nodeType *p2 = new nodeType;
					p2->type = typeLog;
					if (ex(p->opr.op[1]) == 0)
						p2->log.l = true;
					else
						p2->log.l = false;
					Table[std::string((p->opr.op[0])->id_.i)] = p2;
					return 0;
				}
				if ((p->opr.op[1])->type == typeGetRob) {
					if (p->opr.nops = 2) {
						nodeType *p2 = new nodeType;
						p2->type = typeAr;
						p2->ar.a = ex(p->opr.op[1]);
						Table[std::string((p->opr.op[0])->id_.i)] = p2;
					}
					else {
						nodeType *p2 = new nodeType;
						int i = Table.find((p->opr.op[0])->id_.i)->second->m1.mas;
						p2->type = typeAr;
						p2->ar.a = ex(p->opr.op[2]);
						TabMas1[i][ex(p->opr.op[1])] = p2;
					}
					return 0;
				}
				if (p->opr.nops >= 3) {
					if (Table.find((p->opr.op[0])->id_.i)->second->type == typeAMas1) {
						if (not(((p->opr.op[2]->type == typeId) && (Table.find(std::string(p->opr.op[2]->id_.i))->second->type == typeLog)) || (p->opr.op[2]->type == typeLog)))
						{
							int i = Table.find((p->opr.op[0])->id_.i)->second->m1.mas;
							(TabMas1[i][ex(p->opr.op[1])])->type = typeAr;
							(TabMas1[i][ex(p->opr.op[1])])->ar.a = ex(p->opr.op[2]);
						}
						else
							printf("%s\n","Incompatible types");
						return 0;
					}
					if (Table.find((p->opr.op[0])->id_.i)->second->type == typeBMas1) {
						if (not(((p->opr.op[2]->type == typeId) && (Table.find(std::string(p->opr.op[2]->id_.i))->second->type == typeAr))&& (p->opr.op[2]->type == typeAr)))
						{
							int i = Table.find((p->opr.op[0])->id_.i)->second->m2.mas;
							(TabMas1[i][ex(p->opr.op[1])])->type = typeLog;
							if (ex(p->opr.op[2]) == 0)
								(TabMas1[i][ex(p->opr.op[1])])->log.l = true;
							else
								(TabMas1[i][ex(p->opr.op[1])])->log.l = false;
						}
						else
							printf("%s\n", "Incompatible types");
						return 0;
					}
					if (Table.find((p->opr.op[0])->id_.i)->second->type == typeAMas2) {
						if (not(((p->opr.op[2]->type == typeId) && (Table.find(std::string(p->opr.op[2]->id_.i))->second->type == typeLog))&&(p->opr.op[2]->type == typeLog)))
						{
							int i = Table.find((p->opr.op[0])->id_.i)->second->m11.mas;
							(TabMas2[i].find(ex(p->opr.op[1]))->second[ex(p->opr.op[2])])->type = typeAr;
							(TabMas2[i].find(ex(p->opr.op[1]))->second[ex(p->opr.op[2])])->ar.a = ex(p->opr.op[3]);
						}
						else
							printf("%s\n","Incompatible types");
						return 0;
					}
					if (Table.find((p->opr.op[0])->id_.i)->second->type == typeBMas2) {
						if (not(((p->opr.op[2]->type == typeId) && (Table.find(std::string(p->opr.op[2]->id_.i))->second->type == typeAr))&&(p->opr.op[2]->type == typeAr)))
						{
							int i = Table.find((p->opr.op[0])->id_.i)->second->m22.mas;
							(TabMas2[i].find(ex(p->opr.op[1]))->second[ex(p->opr.op[2])])->type = typeLog;
							if (ex(p->opr.op[3]) == 0)
								(TabMas2[i].find(ex(p->opr.op[1]))->second[ex(p->opr.op[2])])->log.l = true;
							else
								(TabMas2[i].find(ex(p->opr.op[1]))->second[ex(p->opr.op[2])])->log.l = false;
						}
						else
							printf("%s\n", "Incompatible types");
						return 0;
					}
				}
				printf("%s\n", (p->opr.op[0])->id_.i);
				k = ex(p->opr.op[1]);
				if (((p->opr.op[1])->type != typeAMas1) && ((p->opr.op[1])->type != typeBMas1) && ((p->opr.op[1])->type != typeAMas2) && ((p->opr.op[1])->type != typeBMas2)) {
					nodeType* p2 = new nodeType;
					if (p->opr.op[1]->type == typeLog) {
						if ((p->opr.op[0]->id_.con < 2) || (((p->opr.op[0])->id_.con == 2) && (Table.find(std::string((p->opr.op[0])->id_.i))->second->type == typeLog)))
						{
							p2->type = typeLog;
							if (k == 0)
								p2->log.l = true;
							else
								p2->log.l = false;
						}
						else
						{
							p2 = NULL;
							printf("%s\n","Incompatible types");
						}
					}
					else {
						if ((p->opr.op[0]->id_.con < 2) || (((p->opr.op[0])->id_.con == 2) && (Table.find(std::string((p->opr.op[0])->id_.i))->second->type == typeAr)))
						{
							p2->type = typeAr;
							p2->ar.a = k;
						}
						else
						{
							p2 = NULL;
							printf("%s\n", "Incompatible types");
						}
					}
					Table[std::string((p->opr.op[0])->id_.i)] = p2;
					if ((p->opr.op[0])->id_.con < 2)
						TabConst[std::string((p->opr.op[0])->id_.i)] = (p->opr.op[0])->id_.con;
				}
				else
					Table[std::string((p->opr.op[0])->id_.i)] = p->opr.op[1];
			}
			return k;
		case while_:
			printf("%s\n", "while");
			while (ex(p->opr.op[0]) == 0) {
				k1 = ex(p->opr.op[1]);
				printf("%d\n", k1);
			}
			return 0;
		case if_:
			printf("%s\n", "if");
			if (ex(p->opr.op[0]) == 0)
				ex(p->opr.op[1]);
			else if (p->opr.nops > 2)
				ex(p->opr.op[2]);
			return 0;
		case '\n':   printf("%c\n", 'k'); if ((p->opr.op[0]) != NULL) ex(p->opr.op[0]); return ex(p->opr.op[1]);
		case '+':	 printf("%s\n", "add"); k2 = ex(p->opr.op[0]) + ex(p->opr.op[1]); printf("%d\n", k2); return k2;
		case '-':    printf("%s\n", "sub"); k3 = ex(p->opr.op[0]) - ex(p->opr.op[1]); printf("%d\n", k3); return k3;
		case '*':    printf("%s\n", "mul"); k4 = ex(p->opr.op[0]) * ex(p->opr.op[1]); printf("%d\n", k4); return k4;
		case '/':    printf("%s\n", "div"); k5 = ex(p->opr.op[0]) / ex(p->opr.op[1]); printf("%d\n", k5); return k5;
		case not_:   printf("%s\n", "not"); if (ex(p->opr.op[0]) == 0) { printf("%d\n", 1); return 1; }
					 else { printf("%d\n", 0); return 0; };
		case gt_:    printf("%s\n", "gt"); if (ex(p->opr.op[0]) > ex(p->opr.op[1])) { printf("%d\n", 0); return 0; }
					 else { printf("%d\n", 1); return 1; };
		case lt_:   printf("%s\n", "lt"); if (ex(p->opr.op[0]) < ex(p->opr.op[1])) { printf("%d\n", 0); return 0; }
					else { printf("%d\n", 1); return 1; };
		case or_:    printf("%s\n", "or"); if (ex(p->opr.op[0]) || ex(p->opr.op[1])) { printf("%d\n", 0); return 0; }
					 else { printf("%d\n", 1); return 1; };
		case extend1_:
			printf("%s\n", "extend1");
			if ((p->opr.op[0]->type == typeId) && (Table.find(std::string((p->opr.op[0])->id_.i))->second != NULL)) {
				if (Table.find(std::string((p->opr.op[0])->id_.i))->second->type == typeAMas1) {
					TabMas1[Table.find(std::string((p->opr.op[0])->id_.i))->second->m1.mas].push_back(p->opr.op[1]);
				}
			}
			else
				printf("%s\n", "Array error");
			return 0;
		case extend2_:
			printf("%s\n", "extend2");
			if ((p->opr.op[0]->type == typeId) && (Table.find(std::string((p->opr.op[0])->id_.i))->second != NULL)) {
				if (Table.find(std::string((p->opr.op[0])->id_.i))->second->type == typeAMas2) {
					for (i1 = 0; i1 < Vec1[Table.find(std::string((p->opr.op[0])->id_.i))->second->m11.mas].size(); ++i1)
						if (ex(Vec1[Table.find(std::string((p->opr.op[0])->id_.i))->second->m11.mas][i1]) == ex(p->opr.op[1]))
							break;
					TabMas2[Table.find(std::string((p->opr.op[0])->id_.i))->second->m11.mas].find(i1)->second.push_back(p->opr.op[2]);
				}
			}
			else
				printf("%s\n", "Array error");
			return 0;
		case '(':
			//nodeType* p1 = Table.find(std::string((p->opr.op[0])->id_.i))->second;
			printf("%s\n", "getzn1");
			if ((p->opr.op[0] != NULL) && (p->opr.op[1] != NULL))
			{
				if (Table.find(std::string((p->opr.op[0])->id_.i))->second->type == typeAMas1)
					return ex(TabMas1[Table.find(std::string((p->opr.op[0])->id_.i))->second->m1.mas][ex(p->opr.op[1])]);
				if (Table.find(std::string((p->opr.op[0])->id_.i))->second->type == typeBMas1)
					return ex(TabMas1[Table.find(std::string((p->opr.op[0])->id_.i))->second->m2.mas][ex(p->opr.op[1])]);
				printf("%s\n", "Array error");
			}
			return 0;
		case ',':
			printf("%s\n", "getzn2");
			if (Table.find(std::string((p->opr.op[0])->id_.i))->second->type == typeAMas2) {
				/*for (i2 = 0; i2 < Vec1[Table.find(std::string((p->opr.op[0])->id_.i))->second->m11.mas].size(); ++i2)
					if (ex(Vec1[Table.find(std::string((p->opr.op[0])->id_.i))->second->m11.mas][i2]) == ex(p->opr.op[1]))
						break;
				return ex(TabMas2[Table.find(std::string((p->opr.op[0])->id_.i))->second->m11.mas].find(i2)->second[ex(p->opr.op[2])]);*/
				if ((ex(p->opr.op[1])<Vec1[Table.find(std::string((p->opr.op[0])->id_.i))->second->m11.mas].size()) && (ex(p->opr.op[2])<TabMas2[Table.find(std::string((p->opr.op[0])->id_.i))->second->m11.mas].find(ex(p->opr.op[1]))->second.size()))
				return ex(TabMas2[Table.find(std::string((p->opr.op[0])->id_.i))->second->m11.mas].find(ex(p->opr.op[1]))->second[ex(p->opr.op[2])]);
			}
			if (Table.find(std::string((p->opr.op[0])->id_.i))->second->type == typeBMas2) {
				/*for (i2 = 0; i2 < Vec1[Table.find(std::string((p->opr.op[0])->id_.i))->second->m22.mas].size(); ++i2)
					if (ex(Vec1[Table.find(std::string((p->opr.op[0])->id_.i))->second->m22.mas][i2]) == ex(p->opr.op[1]))
						break;
				return ex(TabMas2[Table.find(std::string((p->opr.op[0])->id_.i))->second->m22.mas].find(i2)->second[ex(p->opr.op[2])]);*/
				if((ex(p->opr.op[1])<Vec1[Table.find(std::string((p->opr.op[0])->id_.i))->second->m22.mas].size())&&(ex(p->opr.op[2])<TabMas2[Table.find(std::string((p->opr.op[0])->id_.i))->second->m22.mas].find(ex(p->opr.op[1]))->second.size()))
				return ex(TabMas2[Table.find(std::string((p->opr.op[0])->id_.i))->second->m22.mas].find(ex(p->opr.op[1]))->second[ex(p->opr.op[2])]);
			}
			printf("%s\n", "Array error");
			return 0;
		case size1_:
			printf("%s\n", "size1");
			//nodeType* p2 = Table.find(std::string((p->opr.op[0])->id_.i))->second;
			if ((p->opr.op[0]!=NULL)&&((p->opr.op[0])->type == typeId) && (Table.find(std::string((p->opr.op[0])->id_.i))->second != NULL)) {
				if (Table.find(std::string((p->opr.op[0])->id_.i))->second->type == typeAMas1)
					return TabMas1[Table.find(std::string((p->opr.op[0])->id_.i))->second->m1.mas].size();
				if (Table.find(std::string((p->opr.op[0])->id_.i))->second->type == typeBMas1)
					return TabMas1[Table.find(std::string((p->opr.op[0])->id_.i))->second->m2.mas].size();
			}
			printf("%s\n", "Array error");
			return 0;
		case size2_:
			printf("%s\n", "size2");
			if ((p->opr.op[0] != NULL) && ((p->opr.op[0])->type == typeId) && (Table.find(std::string((p->opr.op[0])->id_.i))->second != NULL)) {
				if (Table.find(std::string((p->opr.op[0])->id_.i))->second->type == typeAMas2) {
					for (i3 = 0; i3 < Vec1[Table.find(std::string((p->opr.op[0])->id_.i))->second->m11.mas].size(); ++i3)
						if (ex(Vec1[Table.find(std::string((p->opr.op[0])->id_.i))->second->m11.mas][i3]) == ex(p->opr.op[1]))
							break;
					printf("%d\n", TabMas2[Table.find(std::string((p->opr.op[0])->id_.i))->second->m11.mas].find(i3)->second.size());
					return TabMas2[Table.find(std::string((p->opr.op[0])->id_.i))->second->m11.mas].find(i3)->second.size();
				}
				if (Table.find(std::string((p->opr.op[0])->id_.i))->second->type == typeBMas2) {
					for (i3 = 0; i3 < Vec1[Table.find(std::string((p->opr.op[0])->id_.i))->second->m22.mas].size(); ++i3)
						if (ex(Vec1[Table.find(std::string((p->opr.op[0])->id_.i))->second->m22.mas][i3]) == ex(p->opr.op[1]))
							break;
					return TabMas2[Table.find(std::string((p->opr.op[0])->id_.i))->second->m22.mas].find(i3)->second.size();
				}
			}
			printf("%s\n", "Array error");
			return 0;
		case '[':
			if (ex(p->opr.op[0]) == ex(p->opr.op[1]))
				return 0;
			else return 1;
		case inc_:
			printf("%s\n", "inc");
			if ((p->opr.op[0] != NULL) && ((p->opr.op[0])->type == typeId) && (Table.find(std::string((p->opr.op[0])->id_.i))->second != NULL)) {
				if (TabConst.find(std::string((p->opr.op[0])->id_.i))->second != 0) {
					printf("%s\n", "Id is const");
					return 0;
				}
				++Table.find(std::string((p->opr.op[0])->id_.i))->second->ar.a;
				k6 = ex(p->opr.op[0]);
				printf("%d\n", k6);
			}
			else
				printf("%s\n","Id error");
			return k6;
		case dec_:
			printf("%s\n", "dec");
			if ((p->opr.op[0] != NULL) && ((p->opr.op[0])->type == typeId) && (Table.find(std::string((p->opr.op[0])->id_.i))->second != NULL)) {
				if ((p->opr.op[0])->id_.con == 1) {
					printf("%s\n", "Id is const");
					return 0;
				}
				--Table.find(std::string((p->opr.op[0])->id_.i))->second->ar.a;
				k7 = ex(p->opr.op[0]);
				printf("%d\n", k7);
			}
			else
				printf("%s\n", "Id error");
			return k7;
		}
	return 0;
	case typeAMas1: return 0;
	case typeBMas1: return 0;
	case typeAMas2: return 0;
	case typeBMas2: return 0;
	case typeMovRob:
		printf("%s\n", "mov");
		if (napr == 1)
			napr1 = p->mr.nom;
		if (napr == 3) {
			if (p->mr.nom == 1)
				napr1 = 3;
			else
				if (p->mr.nom == 2)
					napr1 = 4;
				else
					if (p->mr.nom == 3)
						napr1 = 2;
					else
						if (p->mr.nom == 4)
							napr1 = 1;
		}
		if (napr == 2) {
			if (p->mr.nom == 1)
				napr1 = 2;
			else
				if (p->mr.nom == 2)
					napr1 = 1;
				else
					if (p->mr.nom == 3)
						napr1 = 4;
					else
						if (p->mr.nom == 4)
							napr1 = 3;
		}
		if (napr == 4) {
			if (p->mr.nom == 1)
				napr1 = 4;
			else
				if (p->mr.nom == 2)
					napr1 = 3;
				else
					if (p->mr.nom == 3)
						napr1 = 1;
					else
						if (p->mr.nom == 4)
							napr1 = 2;
		}
		switch (napr1) {
		case 1:
			if ((x != 0) && (Lab[x - 1][y] == 0))
			{
				--x;
				printf("%s\n", "point");
				printf("%d\n", x);
				printf("%d\n", y);
				napr = 1;
				if ((x == Lab.size() - 1) || (x == 0) || (y == Lab[x].size() - 1) || (y == 0))
					printf("%s\n","EXIT FIND");
				return 0;
			}
			else
			{
				printf("%s\n", "point");
				printf("%d\n", x);
				printf("%d\n", y);
				napr = 1;
				if ((x == Lab.size() - 1) || (x == 0) || (y == Lab[x].size() - 1) || (y == 0))
					printf("%s\n", "EXIT FIND");
				return 1;
			}
		case 2:
			if ((x != Lab.size() - 1) && (Lab[x + 1][y] == 0))
			{
				++x;
				printf("%s\n", "point");
				printf("%d\n", x);
				printf("%d\n", y);
				napr = 2;
				if ((x == Lab.size() - 1) || (x == 0) || (y == Lab[x].size() - 1) || (y == 0))
					printf("%s\n", "EXIT FIND");
				return 0;
			}
			else
			{
				printf("%s\n", "point");
				printf("%d\n", x);
				printf("%d\n", y);
				napr = 2;
				if ((x == Lab.size() - 1) || (x == 0) || (y == Lab[x].size() - 1) || (y == 0))
					printf("%s\n", "EXIT FIND");
				return 1;
			}
		case 3:
			if ((y != Lab[x].size() - 1) && (Lab[x][y + 1] == 0))
			{
				++y;
				printf("%s\n", "point");
				printf("%d\n", x);
				printf("%d\n", y);
				napr = 3;
				if ((x == Lab.size() - 1) || (x == 0) || (y == Lab[x].size() - 1) || (y == 0))
					printf("%s\n", "EXIT FIND");
				return 0;
			}
			else
			{
				printf("%s\n", "point");
				printf("%d\n", x);
				printf("%d\n", y);
				napr = 3;
				if ((x == Lab.size() - 1) || (x == 0) || (y == Lab[x].size() - 1) || (y == 0))
					printf("%s\n", "EXIT FIND");
				return 1;
			}
		case 4:
			if ((y != 0) && (Lab[x][y - 1] == 0))
			{
				--y;
				printf("%s\n", "point");
				printf("%d\n", x);
				printf("%d\n", y);
				napr = 4;
				if ((x == Lab.size() - 1) || (x == 0) || (y == Lab[x].size() - 1) || (y == 0))
					printf("%s\n", "EXIT FIND");
				return 0;
			}
			else
			{
				printf("%s\n", "point");
				printf("%d\n", x);
				printf("%d\n", y);
				napr = 4;
				if ((x == Lab.size() - 1) || (x == 0) || (y == Lab[x].size() - 1) || (y == 0))
					printf("%s\n", "EXIT FIND");
				return 1;
			}
		}
	case typeGetRob:
		printf("%s\n", "get");
		x1 = x;
		y1 = y;
		way = 3000000;
		z = 0;
		z1 = 0;
		/*if (napr == 3) {
		if (p->gr.nom == 1)
		napr1 = 3;
		else
		if (p->gr.nom == 2)
		napr1 = 4;
		else
		if (p->gr.nom == 3)
		napr1 = 2;
		else
		if (p->gr.nom == 4)
		napr1 = 1;
		}
		if (napr == 2) {
		if (p->gr.nom == 1)
		napr1 = 2;
		else
		if (p->gr.nom == 2)
		napr1 = 1;
		else
		if (p->gr.nom == 3)
		napr1 = 4;
		else
		if (p->gr.nom == 4)
		napr1 = 3;
		}
		if (napr == 4) {
		if (p->gr.nom == 1)
		napr1 = 4;
		else
		if (p->gr.nom == 2)
		napr1 = 3;
		else
		if (p->gr.nom == 3)
		napr1 = 1;
		else
		if (p->gr.nom == 4)
		napr1 = 2;
		}*/
		switch (p->gr.nom) {
		case 1:
			for (int i = 0; i < Lab[0].size(); ++i)
				if (Lab[0][i] == 1)
					++z1;
			if (z1<Lab[0].size())
				Way1(x1, y1, z, -1);
			printf("%d\n", way);
			if (way == 3000000)
				printf("%s\n","EXIT NOT FIND");
			return way;
		case 2:
			for (int i = 0; i < Lab[Lab.size() - 1].size(); ++i)
				if (Lab[Lab.size() - 1][i] == 1)
					++z1;
			if (z1<Lab[Lab.size() - 1].size())
				Way2(x1, y1, z, -1);
			printf("%d\n", way);
			if (way == 3000000)
				printf("%s\n", "EXIT NOT FIND");
			return way;
		case 3:
			for (int i = 0; i < Lab.size(); ++i)
				if (Lab[i][Lab[0].size() - 1] == 1)
					++z1;
			if (z1<Lab.size())
				Way3(x1, y1, z, -1);
			printf("%d\n", way);
			if (way == 3000000)
				printf("%s\n", "EXIT NOT FIND");
			return way;
		case 4:
			for (int i = 0; i < Lab.size(); ++i)
				if (Lab[i][0] == 1)
					++z1;
			if (z1<Lab.size())
				Way4(x1, y1, z, -1);
			printf("%d\n", way);
			if (way == 3000000)
				printf("%s\n", "EXIT NOT FIND");
			return way;
		}
		return 0;
	case typePushRob:
		printf("%s\n", "push");
		if (napr == 1)
			napr1 = p->mr.nom;
		if (napr == 3) {
			if (p->pr.nom == 1)
				napr1 = 3;
			else
				if (p->pr.nom == 2)
					napr1 = 4;
				else
					if (p->pr.nom == 3)
						napr1 = 2;
					else
						if (p->pr.nom == 4)
							napr1 = 1;
		}
		if (napr == 2) {
			if (p->pr.nom == 1)
				napr1 = 2;
			else
				if (p->pr.nom == 2)
					napr1 = 1;
				else
					if (p->pr.nom == 3)
						napr1 = 4;
					else
						if (p->pr.nom == 4)
							napr1 = 3;
		}
		if (napr == 4) {
			if (p->pr.nom == 1)
				napr1 = 4;
			else
				if (p->pr.nom == 2)
					napr1 = 3;
				else
					if (p->pr.nom == 3)
						napr1 = 1;
					else
						if (p->pr.nom == 4)
							napr1 = 2;
		}
		if (p->pr.nom == 5)
			napr1 = 5;
		switch (napr1) {
		case 1:
			if (((x - 1) != 0) && (Lab[x - 1][y] == 1) && (Lab[x - 2][y] == 0)) {
				Lab[x - 1][y] = 0;
				Lab[x - 2][y] = 1;
				--x;
				napr = 1;
				prev = 1;
			}
			printf("%s\n", "point");
			printf("%d\n", x);
			printf("%d\n", y);
			for (int i = 0; i<Lab.size(); ++i)
			{
				for (int j = 0; j<Lab[i].size(); ++j)
					printf("%d", Lab[i][j]);
				printf("\n");
			}
			return 0;
		case 2:
			if (((x + 1) != Lab.size() - 1) && (Lab[x + 1][y] == 1) && (Lab[x + 2][y] == 0)) {
				Lab[x + 1][y] = 0;
				Lab[x + 2][y] = 1;
				++x;
				napr = 2;
				prev = 2;
			}
			printf("%s\n", "point");
			printf("%d\n", x);
			printf("%d\n", y);
			for (int i = 0; i<Lab.size(); ++i)
			{
				for (int j = 0; j<Lab[i].size(); ++j)
					printf("%d", Lab[i][j]);
				printf("\n");
			}
			return 0;
		case 3:
			if (((y + 1) != Lab[x].size() - 1) && (Lab[x][y + 1] == 1) && (Lab[x][y + 2] == 0)) {
				Lab[x][y + 1] = 0;
				Lab[x][y + 2] = 1;
				++y;
				napr = 3;
				prev = 3;
			}
			printf("%s\n", "point");
			printf("%d\n", x);
			printf("%d\n", y);
			for (int i = 0; i<Lab.size(); ++i)
			{
				for (int j = 0; j<Lab[i].size(); ++j)
					printf("%d", Lab[i][j]);
				printf("\n");
			}
			return 0;
		case 4:
			if (((y - 1) != 0) && (Lab[x][y - 1] == 1) && (Lab[x][y - 2] == 0)) {
				Lab[x][y - 1] = 0;
				Lab[x][y - 2] = 1;
				--y;
				napr = 4;
				prev = 4;
			}
			printf("%s\n", "point");
			printf("%d\n", x);
			printf("%d\n", y);
			for (int i = 0; i<Lab.size(); ++i)
			{
				for (int j = 0; j<Lab[i].size(); ++j)
					printf("%d", Lab[i][j]);
				printf("\n");
			}
			return 0;
		case 5:
			if (prev == 1) {
				Lab[x][y] = 1;
				Lab[x - 1][y] = 0;
				++x;
			}
			if (prev == 2) {
				Lab[x][y] = 1;
				Lab[x + 1][y] = 0;
				--x;
			}
			if (prev == 3) {
				Lab[x][y] = 1;
				Lab[x][y + 1] = 0;
				--y;
			}
			if (prev == 4) {
				Lab[x][y] = 1;
				Lab[x][y - 1] = 0;
				++y;
			}
			printf("%s\n", "point");
			printf("%d\n", x);
			printf("%d\n", y);
			for (int i = 0; i<Lab.size(); ++i)
			{
				for (int j = 0; j<Lab[i].size(); ++j)
					printf("%d", Lab[i][j]);
				printf("\n");
			}
			return 0;
		}
		return 0;
	case typeExit:
		if ((x == 0) || (x == Lab.size() - 1) || (y == 0) || (y == Lab[x].size() - 1))
			return 0;
		else
			return 1;
	case typeFunc:
		printf("%s\n", "func");
		if (p != NULL)
		{
			int k = p->f.nom;
			int k1 = 0;
			printf("%d\n", k);
			for (int i = 0; i < FuncName.size(); ++i)
				if (std::string(p->f.name) == FuncName[i]) {
					k1 = i;
					break;
				}
			if (VecValArg[k].size() <= VecIdArgFunc[k1].size())
				for (int i = 0; i < VecValArg[k].size(); ++i)
				{
					if (VecValArg[k][i] == NULL) {
						Table1[std::string(VecIdArgFunc[k1][i]->id_.i)] = VecValArgFunc[k1][i];
						TabConst1[std::string(VecIdArgFunc[k1][i]->id_.i)] = 0;
					}
					else {
						if ((VecValArg[k][i]->type == typeAr) || (VecValArg[k][i]->type == typeLog)) {
							printf("%s\n", VecIdArgFunc[k][i]->id_.i);
							ex(VecValArg[k][i]);
							Table1[std::string(VecIdArgFunc[k1][i]->id_.i)] = VecValArg[k][i];
							TabConst1[std::string(VecIdArgFunc[k1][i]->id_.i)] = 0;
						}
						else {
							nodeType *p1 = new nodeType;
							if (VecValArg[k][i]->type == typeId) {
								if (Table.find(std::string(VecValArg[k][i]->id_.i))->second->type == typeLog)
								{
									p1->type = typeLog;
									if (ex(VecValArg[k][i]) == 0)
										p1->log.l = true;
									else
										p1->log.l = false;
									TabConst1[std::string(VecIdArgFunc[k1][i]->id_.i)] = TabConst.find(std::string(VecValArg[k][i]->id_.i))->second;
								}
								if (Table.find(std::string(VecValArg[k][i]->id_.i))->second->type == typeAr)
								{
									p1->type = typeAr;
									p1->ar.a = ex(VecValArg[k][i]);
									TabConst1[std::string(VecIdArgFunc[k1][i]->id_.i)] = TabConst.find(std::string(VecValArg[k][i]->id_.i))->second;
								}
								if (Table.find(std::string(VecValArg[k][i]->id_.i))->second->type == typeAMas1)
								{
									p1->type = typeAMas1;
									p1->m1.mas = Table.find(std::string(VecValArg[k][i]->id_.i))->second->m1.mas;
								}
								if (Table.find(std::string(VecValArg[k][i]->id_.i))->second->type == typeBMas1)
								{
									p1->type = typeBMas1;
									p1->m2.mas = Table.find(std::string(VecValArg[k][i]->id_.i))->second->m2.mas;
								}
								if (Table.find(std::string(VecValArg[k][i]->id_.i))->second->type == typeAMas2)
								{
									p1->type = typeAMas2;
									p1->m11.mas = Table.find(std::string(VecValArg[k][i]->id_.i))->second->m11.mas;
								}
								if (Table.find(std::string(VecValArg[k][i]->id_.i))->second->type == typeBMas2)
								{
									p1->type = typeBMas2;
									p1->m22.mas = Table.find(std::string(VecValArg[k][i]->id_.i))->second->m22.mas;
								}
							}
							else
							{
								p1->type = typeAr;
								p1->ar.a = ex(VecValArg[k][i]);
								TabConst1[std::string(VecIdArgFunc[k1][i]->id_.i)] = 0;
							}
							Table1[std::string(VecIdArgFunc[k1][i]->id_.i)] = p1;
						}
					}
				}
			//printf("%d\n",Table.size());
			TableVec.push_back(Table);
			TabConstVec.push_back(TabConst);
			Table.clear();
			TabConst.clear();
			Table = Table1;
			TabConst = TabConst1;
			Table1.clear();
			TabConst1.clear();
			ex(TreeVec[k1]);
			if (VecIdZn[k].size() <= VecIdZnFunc[k1].size())
				for (int i = 0; i < VecIdZn[k].size(); ++i) {
					if (VecIdZn[k][i] != NULL)
						if (Table.find(std::string(VecIdZnFunc[k1][i]->id_.i))->second != NULL) {
							if ((Table.find(std::string(VecIdZnFunc[k1][i]->id_.i))->second->type == typeAr) || (Table.find(std::string(VecIdZnFunc[k1][i]->id_.i))->second->type == typeLog))
							{
								if ((Table.find(std::string(VecIdZnFunc[k1][i]->id_.i))->second->type == typeAr) && (TableVec[TableVec.size() - 1].find(std::string(VecIdZn[k][i]->id_.i))->second->type == typeLog))
								{
									printf("%s\n","Incompatible types");
									TableVec[TableVec.size() - 1][std::string(VecIdZn[k][i]->id_.i)] = VecValZnFunc[k][i];
								}
								if ((Table.find(std::string(VecIdZnFunc[k1][i]->id_.i))->second->type == typeLog) && (TableVec[TableVec.size() - 1].find(std::string(VecIdZn[k][i]->id_.i))->second->type == typeAr))
								{
									printf("%s\n", "Incompatible types");
									TableVec[TableVec.size() - 1][std::string(VecIdZn[k][i]->id_.i)] = VecValZnFunc[k][i];
								}
								else
								TableVec[TableVec.size() - 1][std::string(VecIdZn[k][i]->id_.i)] = Table.find(std::string(VecIdZnFunc[k1][i]->id_.i))->second;
							}
							else
							{
								nodeType *p1 = new nodeType;
								if (Table.find(std::string(VecIdZnFunc[k1][i]->id_.i))->second->type == typeId) {
									s = std::string(Table.find(std::string(VecIdZnFunc[k1][i]->id_.i))->second->id_.i);
									if ((Table.find(s)->second->type == typeAr)&&(TableVec[TableVec.size() - 1].find(std::string(VecIdZn[k][i]->id_.i))->second->type !=typeLog)) {
										p1->type = typeAr;
										p1->ar.a = ex(Table.find(s)->second);
									}
									else
									if((Table.find(s)->second->type == typeLog) && (TableVec[TableVec.size() - 1].find(std::string(VecIdZn[k][i]->id_.i))->second->type != typeAr)) {
										p1->type = typeLog;
										if (ex(Table.find(s)->second) == 0)
											p1->log.l = true;
										else
											p1->log.l = false;
									}
									else {
										printf("%s\n", "Incompatible types");
										TableVec[TableVec.size() - 1][std::string(VecIdZn[k][i]->id_.i)] = VecValZnFunc[k][i];
									}
								}
								else
								{
									p1->type = typeAr;
									p1->ar.a = ex(Table.find(std::string(VecIdZnFunc[k1][i]->id_.i))->second);
								}
								TableVec[TableVec.size() - 1][std::string(VecIdZn[k][i]->id_.i)] = p1;
							}
						}
						else
							TableVec[TableVec.size() - 1][std::string(VecIdZn[k][i]->id_.i)] = VecValZnFunc[k][i];
				}
			Table.clear();
			Table = TableVec[TableVec.size() - 1];
			TabConst = TabConstVec[TabConstVec.size() - 1];
			TableVec.erase(TableVec.end());
			TabConstVec.erase(TabConstVec.end());
		}
		return 0;
    }
}
