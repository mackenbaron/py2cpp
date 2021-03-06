#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#include <stdio.h>
#include "mod.h"
#include "context.h"



enum symtab_entry_kind {
    SE_UNKNOWN_KIND,
    SE_FUNCTION_KIND,
    SE_VARIABLE_KIND,
    SE_PARAMETER_KIND,
    SE_GLOBAL_KIND,
    SE_DEFAULT_KIND,
    SE_CLASS_KIND,
    SE_MODULE_KIND,
    SE_SCOPE_KIND,
    SE_REUSE_KIND
};

enum symtab_kind {
    SK_GLOBAL_KIND,
    SK_MODULE_KIND,
    SK_FUNCTION_KIND,
    SK_SCOPE_KIND,
    SK_CLASS_KIND
};



typedef struct symtab_entry * symtab_entry_ty;
typedef struct symtab * symtab_ty;
typedef struct funcentry* funcentry_ty;

struct symtab_entry {
    symtab_ty se_table;
    char se_name[128];
    char c_name[128];
    enum symtab_entry_kind se_kind;
    type_ty se_type;
    symtab_ty se_scope;
};



struct symtab {
    enum symtab_kind st_kind;
    int st_size;   /* the size of table entry */
    int st_capacity;  /* the whole slot in array */
    symtab_entry_ty * st_symbols;

    /* pointer to out scope*/
    symtab_ty st_parent;

    int n_child;
    int child_capacity;
    symtab_ty * st_children;
};

#include "type_common.h"


symtab_ty get_current_symtab();
symtab_ty get_global_symtab();
symtab_ty get_curfile_symtab();

void install_variable(char* name, type_ty tp, enum symtab_entry_kind kind);
void install_scope_variable(char* name, type_ty tp, enum symtab_entry_kind kind);
type_ty lookup_variable(char* name);
type_ty lookup_scope_variable(char* name);
void change_type(char* name, type_ty tp);


void change_symtab(symtab_ty st);
void change_symtab_back();


int has_constructor();

funcentry_ty functable_insert(char* name, int n, Parameter* args, type_ty tp);
void functable_insert_ret(char* name, type_ty ret,  type_ty tp);
type_ty functable_lookup(char* name, type_ty tp);

type_ty assign_type_to_ast(stmt_seq* ss);

void output_symtab(symtab_ty tp);
void output_symtab_with_prefix(symtab_ty tp, const  char* prefix);

#endif
