#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct keyword{  // keywords
    char k[100];
}kw[32];

struct operator{  // operators
    char op[10];
}o[10];

struct output{
    int sr;
    char name[100];
    char type[100];
}out[500];   // tabular form

int main()
{
    FILE* ptr;  // file pointer
    int i,j, a=1, idflag=0;    //i and j are loop counters.
    //a is used to keep track of the serial number in the output table.
    //idflag is a flag to determine if a word has been categorized.
    //str is a character array used to read words from the input file.
    char str[100];
    ptr=fopen("input2.c","r");

    // Predefined values for keywords
    strcpy(kw[0].k, "auto");
    strcpy(kw[1].k, "break");
    strcpy(kw[2].k, "case");
    strcpy(kw[3].k, "char");
    strcpy(kw[4].k, "const");
    strcpy(kw[5].k, "continue");
    strcpy(kw[6].k, "default");
    strcpy(kw[7].k, "do");
    strcpy(kw[8].k, "double");
    strcpy(kw[9].k, "else");
    strcpy(kw[10].k, "enum");
    strcpy(kw[11].k, "extern");
    strcpy(kw[12].k, "float");
    strcpy(kw[13].k, "for");
    strcpy(kw[14].k, "goto");
    strcpy(kw[15].k, "if");
    strcpy(kw[16].k, "int");
    strcpy(kw[17].k, "long");
    strcpy(kw[18].k, "register");
    strcpy(kw[19].k, "return");
    strcpy(kw[20].k, "short");
    strcpy(kw[21].k, "signed");
    strcpy(kw[22].k, "sizeof");
    strcpy(kw[23].k, "static");
    strcpy(kw[24].k, "struct");
    strcpy(kw[25].k, "switch");
    strcpy(kw[26].k, "typedef");
    strcpy(kw[27].k, "union");
    strcpy(kw[28].k, "unsigned");
    strcpy(kw[29].k, "void");
    strcpy(kw[30].k, "volatile");
    strcpy(kw[31].k, "while");

    // Predefined values for operators
    strcpy(o[0].op, "*");
    strcpy(o[1].op, "+");
    strcpy(o[2].op, "=");
    strcpy(o[3].op, "-");

    // Read the file and compare the strings
    if(ptr==NULL)
    {
        printf("File is empty");
    }
    else
    {
        while(fscanf(ptr, "%s",str)!= EOF)
        {
            idflag=0;

            // Check if the string starts with a digit followed by letters (invalid token)
            if (isdigit(str[0])) {
                for (i = 1; i < strlen(str); i++) {
                    if (isalpha(str[i])) {
                        out[a].sr = a;
                        strcpy(out[a].name, str);
                        strcpy(out[a].type, "Invalid Token");
                        a++;
                        idflag = 1;
                        break;
                    }
                }
            }

            // Keywords check 
            if (idflag == 0) {
                for(i = 0; i < 32; i++)  
                {  
                    if(strcmp(str, kw[i].k) == 0)
                    {
                        out[a].sr = a;
                        strcpy(out[a].name, str);
                        strcpy(out[a].type, "Keyword");
                        a++;
                        idflag = 1;		  	
                        break;
                    }
                }
            }

            // Special symbols check
            if (idflag == 0 && (str[0] == '#' || str[0] == '(' || str[0] == ')' || 
                                str[0] == '{' || str[0] == '}' || str[0] == ';' || 
                                str[0] == '<' || str[0] == '>'))
            {
                out[a].sr = a;
                strcpy(out[a].name, str);
                strcpy(out[a].type, "Special Symbol");
                a++;
                idflag = 1;	  
            }

            // Constants check (if string starts with a digit and no letters after)
            if (idflag == 0 && isdigit(str[0])) {
                out[a].sr = a;
                strcpy(out[a].name, str);
                strcpy(out[a].type, "Constant");
                a++;
                idflag = 1;
            }

            // Operators check
            if (idflag == 0) {
                for(i = 0; i < 10; i++)
                {
                    if(strcmp(str, o[i].op) == 0)
                    {
                        out[a].sr = a;
                        strcpy(out[a].name, str);
                        strcpy(out[a].type, "Operator");
                        a++;
                        idflag = 1;
                    }
                }
            }

            // If no match, classify as Identifier
            if(idflag == 0)
            {
                out[a].sr = a;
                strcpy(out[a].name, str);
                strcpy(out[a].type, "Identifier");
                a++;
                idflag = 1;
            }
        }
    }

    // Display output
    printf("Sr.No.\tName\tType\t\n");
    for(j = 1; j < a; j++)
    {
        printf("%d\t%s\t%s\t\n", out[j].sr, out[j].name, out[j].type);
    }

    fclose(ptr);
}

