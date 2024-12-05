#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// MNEUMONIC AND OPCODE TABLE
struct table 
{
    char mname[10];
    char mop[5];
} mot[10];

// SYMBOL TABLE
struct sym
{
    int srno;
    char sn[10];
    int saddr;
} SYMTAB[10];

// LITERAL TABLE
struct lit
{
    int lrno;
    char ln[10];
    int laddr;
} LITTAB[10];

// MAIN FUNCTION
int main()
{
    FILE *fp;
    fp = fopen("input.asm", "r");
    int n;
    int lc = 0, sptr = 0, lptr = 0;
    int isflag = 0, symfound = 0, litfound = 0, DLflag = 0;
    char str[10], str1[10];
    int i;

    // MNEUMONIC TABLE IS DEFINED HERE
    strcpy(mot[0].mname, "STOP");
    strcpy(mot[0].mop, "00");
    strcpy(mot[1].mname, "ADD");
    strcpy(mot[1].mop, "01");
    strcpy(mot[2].mname, "SUB");
    strcpy(mot[2].mop, "02");
    strcpy(mot[3].mname, "MULT");
    strcpy(mot[3].mop, "03");
    strcpy(mot[4].mname, "MOVEM");
    strcpy(mot[4].mop, "04");
    strcpy(mot[5].mname, "MOVER");
    strcpy(mot[5].mop, "05");

    if(fp == NULL)
    {
        printf("ERROR: Unable to open file.\n");
        return -1;
    }
    else
    {
        while(fscanf(fp, "%s", str) != EOF)
        {
            isflag = 0;
            symfound = 0;
            litfound = 0;
            DLflag = 0;
            
            // START ASSEMBLER DIRECTIVE
            if(strcmp(str, "START") == 0)
            {
                isflag = 1;
                DLflag = 1;
                printf("\n (AD , 01)");
                fscanf(fp, "%s", str);
                lc = atoi(str);
                printf("  (C %d)", lc);
            }
            // END ASSEMBLER DIRECTIVE
            if(strcmp(str, "END") == 0)
            {
                isflag = 1;
                DLflag = 1;
                printf("\n%d) (AD , 02)", lc);
                // AFTER END STATEMENT LITERALS ARE PROCESSED
                for(i = 0; i < lptr; i++)
                {
                    printf("\n%d) Literal %s is processed", lc, LITTAB[i].ln);
                    LITTAB[i].laddr = lc;
                    lc++;
                }
            }
            // IMPERATIVE STATEMENT
            if(isflag == 0)
            {
                for(i = 0; i < 6; i++)
                {
                    if(strcmp(str, mot[i].mname) == 0)
                    {
                        DLflag = 1;
                        printf("\n%d) (IS , %s)", lc, mot[i].mop);
                        lc++;

                        // OPERAND 1 ALWAYS A REGISTER
                        fscanf(fp, "%s", str);
                        if(strcmp(str, "AREG,") == 0)
                            printf(" (R, 1)");
                        else if(strcmp(str, "BREG,") == 0)
                            printf(" (R, 2)");
                        else if(strcmp(str, "CREG,") == 0)
                            printf(" (R, 3)");
                        else if(strcmp(str, "DREG,") == 0)
                            printf(" (R, 4)");

                        // OPERAND 2 can be LITERAL or SYMBOL
                        fscanf(fp, "%s", str);

                        // Check if it is SYMBOL
                        if(str[0] != '=')
                        {
                            // Check if SYMBOL is present in ST
                            symfound = 0;
                            for(i = 0; i < sptr; i++)
                            {
                                if(strcmp(str, SYMTAB[i].sn) == 0)
                                {
                                    printf(" (S, %d)", i+1);
                                    symfound = 1;
                                    break;
                                }
                            }

                            // If SYMBOL not found, add it to ST
                            if(symfound == 0)
                            {
                                strcpy(SYMTAB[sptr].sn, str);
                                SYMTAB[sptr].srno = sptr + 1;
                                printf(" (S, %d)", sptr + 1);
                                sptr++;
                            }
                        }
                        // Check if it is LITERAL
                        else if(str[0] == '=')
                        {
                            // Check if LITERAL is present in LITTAB
                            litfound = 0;
                            for(i = 0; i < lptr; i++)
                            {
                                if(strcmp(str, LITTAB[i].ln) == 0)
                                {
                                    printf(" (L, %d)", i+1);
                                    litfound = 1;
                                    break;
                                }
                            }

                            // If LITERAL not found, add it to LITTAB
                            if(litfound == 0)
                            {
                                strcpy(LITTAB[lptr].ln, str);
                                LITTAB[lptr].lrno = lptr + 1;
                                printf(" (L, %d)", lptr + 1);
                                lptr++;
                            }
                        }
                    }
                }
            }

            // CODE FOR DL STATEMENT
            if(DLflag == 0)
            {
                // Search whether that symbol is present in ST
                symfound = 0; // Reset symfound flag

                for(i = 0; i < sptr; i++)
                {
                    if(strcmp(str, SYMTAB[i].sn) == 0)
                    {
                        SYMTAB[i].saddr = lc;
                        symfound = 1;
                        break;
                    }
                }

                // If the symbol is not found in the symbol table, add it
                if(symfound == 0)
                {
                    strcpy(SYMTAB[sptr].sn, str);
                    SYMTAB[sptr].srno = sptr + 1;
                    SYMTAB[sptr].saddr = lc;
                    printf(" (S, %d)", sptr + 1);
                    sptr++;
                }

                fscanf(fp, "%s", str);  // DC DS
                fscanf(fp, "%s", str1); // Const
                if(strcmp(str, "DS") == 0)
                {
                    printf("\n%d) (DL , 01) (C, %s)", lc, str1);
                    lc++;
                }
                else if(strcmp(str, "DC") == 0)
                {
                    n = atoi(str1);
                    printf("\n%d) (DL , 02) (C, %s)", lc, str1);
                    lc += n; // Increment lc by the specified size
                }
            }
        } // while end
    }

    printf("\n----------------------------------------------");
    printf("\n \t SYMBOL TABLE ");
    printf("\n SRNO. \t SNAME \tSADDR");
    for(i = 0; i < sptr; i++)
    {
        printf("\n %d \t %s \t%d", SYMTAB[i].srno, SYMTAB[i].sn, SYMTAB[i].saddr);
    }
    printf("\n----------------------------------------------");
    
    printf("\n \t LITERAL TABLE ");
    printf("\n LRNO. \t LNAME \tLADDR");
    for(i = 0; i < lptr; i++)
    {
        printf("\n %d \t %s \t%d", LITTAB[i].lrno, LITTAB[i].ln, LITTAB[i].laddr);
    }

    fclose(fp);
    return 0;
}
