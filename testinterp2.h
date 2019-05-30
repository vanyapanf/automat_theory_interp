#pragma once
#include <stdio.h>
#include <vector>
#include <map>
#include <string.h>
typedef enum {typeAr,typeLog,typeId,typeOp,typeAMas1,typeBMas1,typeAMas2,typeBMas2,typeFunc,typeMovRob, typeGetRob, typePushRob, typeExit
} nodeEnum;
typedef struct {
	int a;
}arNodeType;
typedef struct {
	bool l;
}logNodeType;
typedef struct {
    char* i;
	int con;
}idNodeType;
typedef struct {
	int oper;
	int nops;
	struct NodeTypeTag* op[3];
}oprNodeType;
typedef struct {
	int mas;
}AMas1;
typedef struct {
	int mas;
}BMas1;
typedef struct {
	int mas;
}AMas2;
typedef struct {
	int mas;
}BMas2;
typedef struct {
	char* name;
	int nom;
}Func;
typedef struct {
	int nom;
}MovRob;
typedef struct {
	int nom;
}GetRob;
typedef struct {
	int nom;
}PushRob;
typedef struct NodeTypeTag {
	nodeEnum type;
	union {
		arNodeType ar;
		logNodeType log;
		idNodeType id_;
		oprNodeType opr;
		AMas1 m1;
		BMas1 m2;
		AMas2 m11;
		BMas2 m22;
		Func f;
		MovRob mr;
		GetRob gr;
		PushRob pr;
	};
} nodeType;

extern std::map<std::string, nodeType*> Table;
extern std::map<std::string, nodeType*> Table1;
extern std::vector<std::vector<nodeType*>> TabMas1;
extern std::map<std::string, int> TabConst;
extern std::map<std::string, int> TabConst1;
extern std::vector<std::map<int, std::vector<nodeType*>>> TabMas2;
extern std::vector<std::vector<nodeType*>> Vec1;
extern std::vector<std::map<std::string, nodeType*>> TableVec;
extern std::vector<std::map<std::string, int>> TabConstVec;
extern std::vector<nodeType*> TreeVec;
extern std::vector<std::string> FuncName;
extern std::vector<std::vector<nodeType*>> VecIdZnFunc;
extern std::vector<std::vector<nodeType*>> VecValZnFunc;
extern std::vector<std::vector<nodeType*>> VecIdArgFunc;
extern std::vector<std::vector<nodeType*>> VecValArgFunc;
extern std::vector<std::vector<nodeType*>> VecIdZn;
extern std::vector<std::vector<nodeType*>> VecValArg;
extern std::vector<std::vector<int>> Lab;
extern int x;
extern int y;
extern int napr;
extern int way;
extern int prev;