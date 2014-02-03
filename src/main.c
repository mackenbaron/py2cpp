#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parsetok.h"
#include "node.h"
#include "mod.h"
#include "code.h"

#define Py_single_intput 256
#define Py_file_input 257

extern grammar _PyParser_Grammar;
extern void PyNode_ListTree(node* n);
extern stmt_seq* ast_from_node(const node* n);

FILE* fdef = NULL;

int main() {
    char* filename = "test.py";
    FILE* fp = fopen(filename, "r");
    perrdetail err_ret;
    int flag = 0;
    node *n = PyParser_ParseFileFlagsEx(fp, filename, &_PyParser_Grammar, Py_file_input, NULL, NULL, &err_ret, &flag);
    fclose(fp);
    stmt_seq* ss = ast_from_node(n);
    assign_type_to_ast(ss);
    generate_cpp_code(ss, NULL);
    /*
    printf("#include <iostream>\n"
            "#include <vector>\n"
            "#include <algorithm>\n"
            "#include <cassert>\n"
            "#include <cmath>\n"
            "using namespace std;\n"
            "#include \"definition.h\"\n\n");

    fdef = fopen("definition.h", "w");
    fprintf(fdef, "template <ostream& out, class T>\n"
            "void output(T x) { out<< x;}\n\n");
    fprintf(fdef, "template <ostream& out, class T>\n"
            "void output(vector<T> & v) {\n"
            "\tout<<\"[\";\n"
            "\tfor(int i = 0; i < v.size(); i ++ ) {\n"
            "\t\toutput<out>(v[i]);\n"
            "\t\tif(i != v.size() - 1)\n"
            "\t\t\tout<<\", \";\n"
            "\t}\n"
            "\tout<<\"]\";\n"
            "}\n\n");
    fclose(fdef);

    printf("int main(int argc, char** argv) {\n");

    
    printf("\treturn 0;\n}");
    */
    //PyNode_Free(n);
    return 0;
}