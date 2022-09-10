#include<stdio.h>
#include<string.h>
char a[10000],b[10000],temp[10000],c[1000][100];
int inde[10000];
int cur = 0;
char str2[10000][10000];
char ar[10000],br[10000];
char d[70][70][500];
int inde[10000];
char str[10000];
int pos =0;
int f = 0;
int sz[1000];


struct data
{
    char * name;
    char * idType;
    char* dataType;
    char* scope;
    char* value;

}v[100];


void user_input()
{
    FILE *p1, *p2, *p3;
    char c,ch1,ch2[10000];
    int i=0;

    p2=fopen("input.txt","w");
    printf("Write the program: \n");
    scanf("%[^\t]s", ch2);
    while(i<strlen(ch2))
    {

        fputc(ch2[i],p2);
        i++;
    }
    fclose(p2);
}


void insert(int ind,char* _name, char* _id,char* _dat,char* _scope,char* _value)
{
    v[ind].name  =_name;
    v[ind].idType= _id;
    v[ind].dataType = _dat;
    v[ind].scope  =_scope;
    v[ind].value  =_value;
}

void display(FILE *fp)
{
    int i=0;
    fprintf(fp,"\nSl. No.\t\tName\t\tId Type\t\tData Type\tScope\t\tValue\n");
    for(i=0;i<cur;i++)
    {
        fprintf(fp,"%d\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\n",i+1,v[i].name,v[i].idType,v[i].dataType,v[i].scope,v[i].value);
    }
}



int search(char* _name,char* _id,char* _scope)
{
    int i=0;

    for(i=0;i<cur;i++)
    {
        if(strcmp(v[i].name,_name)==0 && strcmp(v[i].idType,_id)==0 && (strcmp(v[i].scope,_scope)==0 || strcmp(v[i].scope,"global")==0))
        {
            return i;
        }
    }
    return -1;
}

char* modify(char * x)
{
    if(strlen(x)==0)
        return x;
    if(x[0]>='0' && x[0]<='9')
        return x;
    return "";
}

void update(int cur,char* val)
{
    v[cur].value  = val;
}

int isSep(char c)
{
    if(c==';' || c==',' || c=='\'')
        return 1;
    return 0;
}
int isOp(char c)
{
    if(c=='+' || c=='-' || c=='*' || c=='/' || c=='>' || c=='<' || c=='!' || c=='=' || c=='%')
        return 1;
    return 0;
}
int isDigit(char c)
{
    if(c>='0' && c<='9')
        return 1;
    return 0;
}
int isPar(char c)
{
    if(c==')' || c=='(')
        return 1;
    return 0;
}


int isSepa(char* c)
{
    if(strlen(c)==1 && isSep(c[0]))
        return 1;
    return 0;
}

int isKey(char* c)
{
    if(strlen(c)==3 && c[0]=='i' && c[1]=='n' && c[2]=='t')
        return 1;
    else if(strlen(c)==3 && c[0]=='f' && c[1]=='o' && c[2]=='r')
        return 1;
    else if(strlen(c)==5 && c[0]=='f' && c[1]=='l' && c[2]=='o' && c[3]=='a' && c[4]=='t' )
        return 1;
    else if(strlen(c)==5 && c[0]=='w' && c[1]=='h' && c[2]=='i' && c[3]=='l' && c[4]=='e' )
        return 1;
    else if(strlen(c)==6 && c[0]=='d' && c[1]=='o' && c[2]=='u' && c[3]=='b' && c[4]=='l' && c[5]=='e')
        return 1;
    else if(strlen(c)==6 && c[0]=='p' && c[1]=='r' && c[2]=='i' && c[3]=='n' && c[4]=='t' && c[5]=='f')
        return 1;
    else if(strlen(c)==4 && c[0]=='c' && c[1]=='h' && c[2]=='a' && c[3]=='r')
        return 1;
    else if(strlen(c)==4 && c[0]=='e' && c[1]=='l' && c[2]=='s' && c[3]=='e')
        return 1;
    else if(strlen(c)==4 && c[0]=='v' && c[1]=='o' && c[2]=='i' && c[3]=='d')
        return 1;
    else if(strlen(c)==2 && c[0]=='i' && c[1]=='f')
        return 1;
    else if(strlen(c)==6 && c[0]=='r' && c[1]=='e' && c[2]=='t' && c[3]=='u' && c[4]=='r' && c[5]=='n')
        return 1;
    else if(strlen(c)==2 && c[0]=='d' && c[1]=='0')
        return 1;
    return 0;
}

int isOper(char* c)
{
    if(strlen(c)>2)
        return 0;
    if(strlen(c)==1)
    {
        if(isOp(c[0]))
            return 1;
        return 0;
    }
    if(isOp(c[0]) && c[1]=='=')
        return 1;
    if(c[0]=='+' && c[1]=='+')
        return 1;
    if(c[0]=='-' && c[1]=='-')
        return 1;
    return 0;
}

int isParen(char* c)
{
    if(strlen(c)==1 && isPar(c[0]))
        return 1;
    return 0;
}
int isBrc(char c)
{
    if(c=='}' || c=='{')
        return 1;
    return 0;
}
int isBrace(char* c)
{
    if(strlen(c)==1 && isBrc(c[0]))
        return 1;
    return 0;
}

int isNum(char *lex)
{
    int i, l, s;
    i=0;
    if(isDigit(lex[i]))
    {
        s=1;
        i++;
    }
    else if(lex[i]=='.')
    {
        s=2;
        i++;
    }
    else s=0;
    l=strlen(lex);
    if(s==1)
        for(; i<l; i++)
        {
            if(isDigit(lex[i]))  s=1;
            else if(lex[i]=='.')
            {
                s=2;
                i++;
                break;
            }
            else
            {
                s=0;
                break;
            }
        }
    if(s==2)
        if(isDigit(lex[i]))
        {
            s=3;
            i++;
        }
        else
            s=0;
    if(s==3)
        for(; i<l; i++)
        {
            if(isDigit(lex[i]))  s=3;
            else
            {
                s=0;
                break;
            }
        }
    if(s==3) s=1;
    return s;
}

int isId(char* c)
{
    int i=0;
    int x = 0;
    for(i=0; i<strlen(c); i++)
    {
        if((c[i]>='a' && c[i]<='z') || (c[i]>='A' && c[i]<='Z') || c[i]=='_')
        {

            x = 1;
            // printf("x = %d\n",x);
            continue;
        }
        else if(isDigit(c[i])==1)
        {
            if(x==0)
                return 0;
        }
        else return 0;
    }
    return 1;
}


int isHeader(char *a)
{
    int i=0;
    if(i+8<strlen(a) && a[i+1]=='i' && a[i+2]=='n' && a[i+3]=='c' && a[i+4]=='l' && a[i+5]=='u' && a[i+6]=='d' && a[i+7]=='e' && a[i+8]=='<')
    {
        while(i<strlen(a))
        {
            if(a[i]=='>')
                return 1;
            i++;

        }
    }
    return 0;
}



int main()
{
    //Assignment 1
    user_input();
    char * main_file = "input.txt";
    FILE *fp = fopen(main_file,"r");
    FILE *fp2 = fopen("assignment1.txt","w");
    int m=0,i;
    int sp = 0;
    while(fgets(a,1000,fp))
    {
        int s = 0;
        for(i=0;i<strlen(a);i++)
        {
            if(s==1)
            {

                continue;
            }
            else if(i+1<strlen(a) && a[i]=='/' && a[i+1]=='*')
            {

                m  =1;
            }
            else if(i+1<strlen(a) && a[i]=='*' && a[i+1]=='/')
            {
                m  =0;
                i++;
            }
            else if(m==1)
            {
                continue;
            }
            else if(a[i]==' ' || a[i]=='\t')
            {
                if(sp==0)
                    fputc(' ',fp2);
                int j = i;
                while(j<strlen(a) && (a[j]==' ' || a[j]=='\t'))
                {
                    j++;
                }
                i =j-1;
                sp = 1;
            }
            else if(i+1<strlen(a) && a[i]=='/' && a[i+1]=='/')
            {
                s = 1;
                i++;
            }
            else if(a[i]!='\n')
            {
                sp  = 0;
                fputc(a[i],fp2);
            }
            else
            {
                if(sp==0)
                {
                    sp = 1;
                    fputc(' ',fp2);
                }
            }
        }
    }


    fclose(fp);
    fclose(fp2);


    //Assignment 2

    fp = fopen("assignment1.txt","r");

    i =0;
    while(fscanf(fp,"%c",&a[i])!=EOF)
    {
        i++;
    }
    fclose(fp);
    fp = fopen("assignment2.txt","w");

    a[i] = '\0';
    int flag  =0;
    int n = strlen(a),j=0;
    int sepOn = 0;
    for(i=0; i<n; i++)
    {
        if(isSep(a[i])==1)
        {
            if(a[i]=='\'')
            {
                if(sepOn)
                {
                    sepOn = 0;
                    b[j++]  = ' ';
                    b[j++]  = a[i];
                }
                else
                {
                    b[j++]  = a[i];
                    b[j++]  = ' ';
                    sepOn = 1;
                }
            }
            else
            {
                b[j++]  = ' ';
                b[j++]  = a[i];
            }


        }
        else if(isOp(a[i])==1)
        {
            if(a[i+1]=='=')
            {
                b[j++]  = ' ';
                b[j++]  = a[i];
                b[j++]  = a[i+1];
                i++;
                b[j++]  = ' ';
            }
            else if(a[i]=='+')
            {
                if(a[i+1]=='+')
                {
                    b[j++]  = ' ';
                    b[j++]  = a[i];
                    b[j++]  = a[i+1];
                    i++;
                    b[j++]  = ' ';
                }
                else
                {
                    b[j++]  = ' ';
                    b[j++]  = a[i];
                    b[j++]  = ' ';
                }
            }
            else if(a[i]=='-')
            {
                if(a[i+1]=='-')
                {
                    b[j++]  = ' ';
                    b[j++]  = a[i];
                    b[j++]  = a[i+1];
                    i++;
                    b[j++]  = ' ';
                }
                else
                {
                    b[j++]  = ' ';
                    b[j++]  = a[i];
                    b[j++]  = ' ';
                }
            }
            else
            {
                b[j++]  = ' ';
                b[j++]  = a[i];
                b[j++]  = ' ';
            }
            flag  =1;
        }
        else if(isDigit(a[i])==1)
        {
            if(flag==0)
            {
                flag = 1;
                b[j++]  = ' ';
            }
            b[j++]  = a[i];
        }
        else if(isPar(a[i])==1)
        {
            b[j++]  = ' ';
            b[j++]  = a[i];
            if(a[i]!=')' && a[i]!='}')
                b[j++]  = ' ';
        }
        else if(a[i]=='#')
        {
            if(i+8<strlen(a) && a[i+1]=='i' && a[i+2]=='n' && a[i+3]=='c' && a[i+4]=='l' && a[i+5]=='u' && a[i+6]=='d' && a[i+7]=='e' && a[i+8]=='<')
            {
                while(i<strlen(a))
                {
                    b[j++] = a[i];

                    if(a[i]=='>')
                        break;
                    i++;

                }
                b[j++] = ' ';
            }
        }
        else
        {
            flag  =1;
            b[j++]  = a[i];
        }
    }
    b[j] = '\0';




    a[0] = '\0';
    j = 0;
    for(i=0; i<strlen(b); i++)
    {
        if(b[i]==' ')
        {
            if(f==1)
            {
                a[j++] = ' ';
                continue;
            }
            a[j++] = '\0';
            if(strlen(a)==0)
            {
                j  =0;
                continue;
            }
            if(isSepa(a)==1)
            {
                fprintf(fp,"[sep %s] ",a);
            }
            else if(isKey(a)==1)
            {
                fprintf(fp,"[kw %s] ",a);
            }
            else if(isId(a)==1)
            {
                fprintf(fp,"[id %s] ",a);
            }
            else if(isOper(a)==1)
            {
                fprintf(fp,"[op %s] ",a);
            }
            else if(isParen(a)==1)
            {
                fprintf(fp,"[par %s] ",a);
            }
            else if(isNum(a)==1)
            {
                fprintf(fp,"[num %s] ",a);
            }
            else if(isHeader(a)==1)
            {
                fprintf(fp,"[header %s] ",a);
            }
            else
            {
                fprintf(fp,"[unkn %s] ",a);
            }
            j= 0;
        }
        else
        {
            if(b[i]=='"')
                f  = (f ^ 1);
            a[j++]  = b[i];
        }

    }
    a[j++] = '\0';
    if(strlen(a)>0)
    {
        //fprintf(fp,"%s\n",a);
        if(isSepa(a)==1)
        {
            fprintf(fp,"[sep %s] ",a);
        }
        else if(isKey(a)==1)
        {
            fprintf(fp,"[kw %s] ",a);
        }
        else if(isId(a)==1)
        {
            fprintf(fp,"[id %s] ",a);
        }
        else if(isOper(a)==1)
        {
            fprintf(fp,"[op %s] ",a);
        }
        else if(isParen(a)==1)
        {
            fprintf(fp,"[par %s] ",a);
        }
        else if(isNum(a)==1)
        {
            fprintf(fp,"[num %s] ",a);
        }
        else if(isHeader(a)==1)
        {
            fprintf(fp,"[header %s] ",a);
        }
        else
        {
            fprintf(fp,"[unkn %s] ",a);
        }
    }
    fclose(fp);


    //Assignment 3

    fp = fopen("assignment2.txt","r");
    i =0;
    while(fscanf(fp,"%c",&a[i])!=EOF)
    {
        i++;
    }
    a[i]  = '\0';
    fclose(fp);
    fp2 = fopen("assignment3.txt","w");
    int k  =0;
    for(i=0;i<strlen(a);i++)
    {
        if(a[i]=='[')
        {
            b[k++]  = a[i++];
            j = 0;
            while(a[i]!=' ')
            {
                temp[j++]  = a[i];
                i++;

            }
            temp[j]  = '\0';
            if(strcmp(temp,"id")==0)
            {
                b[k++]  = 'i';
                b[k++]  = 'd';
                b[k++]  = ' ';
            }
            i++;
            while(a[i]!=']')
            {
                b[k++]  = a[i];
                i++;

            }
            b[k++] =  a[i];

        }
    }
    b[k]  = '\0';
    fprintf(fp2,"\nStep 1: \n");
    fputs(b,fp2);
    k = 0;
    for(i=0;i<strlen(b);i++)
    {
        if(b[i]=='[')
        {
            j= 0;
            i++;
            while(b[i]!=']' && b[i]!=' ')
            {
                c[k][j++]  = b[i++];
            }
            c[k][j]  = '\0';
            k++;
            if(b[i]==' ')
            {
                j= 0;
                i++;
                while(b[i]!=']')
                {
                    c[k][j++]  = b[i++];
                }
                c[k][j]  = '\0';
                k++;
            }

        }
    }
    fprintf(fp2,"\nStep 2: \n");
    int it = 0;
    char * scope = "global";
    int curp = 0;
    for(i=0;i<k;i++)
    {
        if(strcmp(c[i],"id")==0)
        {
            if(strcmp(c[i+2],"(")==0)
            {
                if(strcmp(c[i-1],"int")==0 || strcmp(c[i-1],"double")==0 || strcmp(c[i-1],"float")==0 || strcmp(c[i-1],"char")==0 )
                {
                    inde[it++]  = cur;
                    insert(cur++,c[i+1],"func",c[i-1],scope,"");
                    scope = c[i+1];
                    i+= 2;
                }
                else
                {
                    int pq  = search(c[i+1],"func","global");
                    if(pq!=-1)
                        inde[it++] = pq;
                    else fprintf(fp2,"\nID %s is not declared in global scope\n",c[i+1]);
                    i+= 2;
                }
            }
            else if(strcmp(c[i+2],"=")==0)
            {
                if(strcmp(c[i-1],"int")==0 || strcmp(c[i-1],"double")==0 || strcmp(c[i-1],"float")==0 || strcmp(c[i-1],"char")==0 )
                {
                    if(search(c[i+1],"var",scope)==-1)
                    {
                        inde[it++]  = cur;
                        insert(cur++,c[i+1],"var",c[i-1],scope,modify(c[i+3]));
                    }
                    else
                    {
                        fprintf(fp2,"\nID %s already declared in %s scope\n",c[i+1],scope);
                    }
                }
                else
                {
                    int pq = search(c[i+1],"var",scope);
                    if(pq==-1)
                    {
                        fprintf(fp2,"\nID %s is not declared in %s scope\n",c[i+1],scope);
                    }
                    else
                    {
                        update(pq,modify(c[i+3]));
                        inde[it++]  = pq;
                    }
                }
                i+=2;
            }
            else if(strcmp(c[i+2],";")==0 || strcmp(c[i+2],",")==0 || strcmp(c[i+2],")")==0 )
            {
                if(strcmp(c[i-1],"int")==0 || strcmp(c[i-1],"double")==0 || strcmp(c[i-1],"float")==0 || strcmp(c[i-1],"char")==0 )
                {
                    if(search(c[i+1],"var",scope)==-1)
                    {
                        inde[it++]  = cur;
                        insert(cur++,c[i+1],"var",c[i-1],scope,"");
                    }
                    else fprintf(fp2,"\nID %s already declared in %s scope\n",c[i+1],scope);
                    i+= 2;
                }
                else
                {
                    if(search(c[i+1],"var",scope)==-1)
                    {
                        fprintf(fp2,"\nID %s is not declared in %s scope\n",c[i+1],scope);
                    }
                    else inde[it++]  = search(c[i+1],"var",scope);
                    i+= 2;
                }
            }
        }
        else if(strcmp(c[i],"}")==0)
        {
            curp--;
            if(curp<0)
                curp=0;
            if(curp==0)
                scope = "global";
        }
        else if(strcmp(c[i],"{")==0)
        {
            curp++;
        }
    }
    fprintf(fp2,("\nStep 3: \n"));
    display(fp2);
    fprintf(fp2,("\nStep 4: \n"));
    it =0;
    for(i=0;i<strlen(b);i++)
    {
        if(b[i]=='[')
        {
            fprintf(fp2,"%c",b[i]);
            i++;
            while(b[i]!=']' && b[i]!=' ')
            {
                fprintf(fp2,"%c",b[i]);
                i++;
            }
            if(b[i]==' ')
            {
                fprintf(fp2,"%c",b[i]);
                j= 0;
                i++;
                while(b[i]!=']')
                {
                    i++;
                }

                fprintf(fp2,"%d",inde[it++]+1);
            }
            fprintf(fp2,"%c",b[i]);

        }
        else
        {
            fprintf(fp2,"%c",b[i]);
        }
    }
    fclose(fp);
    fclose(fp2);


    //Assignment 4
    fp = fopen(main_file,"r");
    fp2 = fopen("assignment4_intermediate_output.txt","w");
    FILE *fp3 = fopen("assignment4_error_output.txt","w");
    i = 1;
    curp = 0;
    cur = 0;

    int c1 = 0, c2  = 0;
    while(fgets(str2[i],500,fp))
    {
        int sz = strlen(str2[i]);
        c1 = 0;
        for(j=0; j<sz; j++)
        {

            if(j+1<sz && str2[i][j]=='/' && str2[i][j+1]=='/')
            {
                c1 = 1;
                str2[i][j]  = str2[i][j+1]  = ' ';
                j++;
            }
            else if(j+1<sz && str2[i][j]=='/' && str2[i][j+1]=='*')
            {
                c2 = 1;
                str2[i][j] = str2[i][j+1]  =' ';
                j++;
            }
            else if(j+1<sz && str2[i][j]=='*' && str2[i][j+1]=='/')
            {
                c2 = 0;
                str2[i][j]  = str2[i][j+1] = ' ';
                j++;
            }
            else if(c1 || c2)
            {
                str2[i][j]  = ' ';
            }

        }
        i++;
    }
    int totalsz = i;



    f =0;
    for(k=1; k<totalsz; k++)
    {

        int flag  =0;
        int n = strlen(str2[k]);
        strcpy(ar,str2[k]);
        j = 0;
        int sepOn = 0;
        for(i=0; i<n; i++)
        {
            if(isSep(ar[i])==1)
            {
                if(ar[i]=='\'')
                {
                    if(sepOn)
                    {
                        sepOn = 0;
                        br[j++]  = ' ';
                        br[j++]  = ar[i];
                    }
                    else
                    {
                        br[j++]  = ar[i];
                        br[j++]  = ' ';
                        sepOn = 1;
                    }
                }
                else
                {
                    br[j++]  = ' ';
                    br[j++]  = ar[i];
                }
                br[j++]  = ' ';


            }
            else if(isOp(ar[i])==1)
            {
                if(ar[i+1]=='=')
                {
                    br[j++]  = ' ';
                    br[j++]  = ar[i];
                    br[j++]  = ar[i+1];
                    i++;
                    br[j++]  = ' ';
                }
                else if(ar[i]=='+')
                {
                    if(ar[i+1]=='+')
                    {
                        br[j++]  = ' ';
                        br[j++]  = ar[i];
                        br[j++]  = ar[i+1];
                        i++;
                        br[j++]  = ' ';
                    }
                    else
                    {
                        br[j++]  = ' ';
                        br[j++]  = ar[i];
                        br[j++]  = ' ';
                    }
                }
                else if(ar[i]=='-')
                {
                    if(ar[i+1]=='-')
                    {
                        br[j++]  = ' ';
                        br[j++]  = ar[i];
                        br[j++]  = ar[i+1];
                        i++;
                        br[j++]  = ' ';
                    }
                    else
                    {
                        br[j++]  = ' ';
                        br[j++]  = ar[i];
                        br[j++]  = ' ';
                    }
                }
                else
                {
                    br[j++]  = ' ';
                    br[j++]  = ar[i];
                    br[j++]  = ' ';
                }
                flag  =1;
            }
            else if(isDigit(ar[i])==1)
            {
                if(flag==0)
                {
                    flag = 1;
                    br[j++]  = ' ';
                }
                br[j++]  = ar[i];
            }
            else if(isPar(ar[i])==1)
            {
                br[j++]  = ' ';
                br[j++]  = ar[i];
                if(ar[i]!=')')
                    br[j++]  = ' ';
            }
            else if(isBrc(ar[i])==1)
            {
                br[j++]  = ' ';
                br[j++]  = ar[i];
                if(ar[i]!='}')
                    br[j++]  = ' ';
            }
            else if(ar[i]=='#')
            {
                if(i+8<strlen(ar) && ar[i+1]=='i' && ar[i+2]=='n' && ar[i+3]=='c' && ar[i+4]=='l' && ar[i+5]=='u' && ar[i+6]=='d' && ar[i+7]=='e' && ar[i+8]=='<')
                {
                    while(i<strlen(ar))
                    {
                        br[j++] = ar[i];

                        if(ar[i]=='>')
                            break;
                        i++;

                    }
                    br[j++] = ' ';
                }
            }
            else
            {


                flag  =1;
                br[j++]  = ar[i];
            }
        }
        br[j-1]  = ' ';
        br[j] = '\0';

        strcpy(str2[k],br);
    }





    for(k=1; k<totalsz; k++)
    {
        strcpy(ar,str2[k]);
        br[0]  = '\0';
        j = 0;
        for(i=0; i<strlen(ar); i++)
        {
            if(ar[i]==' ' || ar[i]=='\t')
            {
                br[j++]  = ' ';
                while(i<strlen(ar) && (ar[i]==' ' || ar[i]=='\t'))
                    i++;
                i--;
            }
            else br[j++]  =ar[i];

        }
        br[j]  = '\0';
        strcpy(str2[k],br);
    }



    int fb = 0,sb = 0;
    int isIf = 0,semicolonIf=0;
    f = 0;
    for(k=1; k<=totalsz; k++)
    {
        j = 0;
        int forloop = 0;
        int pt = 0;
        fprintf(fp2,"%d ",k);
        strcpy(br,str2[k]);
        char pre[100] = {'-','1'};
        for(i=0; i<strlen(br); i++)
        {
            if(br[i]==' ')
            {
                if(f==1)
                {
                    ar[j++]  = br[i];
                    continue;
                }
                ar[j++] = '\0';
                if(strlen(ar)==0)
                {
                    j  =0;
                    continue;
                }

                if(isSepa(ar)==1)
                {
                    fprintf(fp2,"sep %s ",ar);
                    if(strcmp(ar,";")==0)
                    {
                        semicolonIf++;
                        if(forloop==2 || forloop==3)
                            forloop++;
                        else if(forloop>=4)
                        {
                            fprintf(fp3,"Only two semicolon in for loop at line %d\n",k);
                        }
                        else if(strcmp(ar,pre)==0)
                        {
                            fprintf(fp3,"Duplicate token at line %d\n",k);
                        }
                    }
                    else if(strcmp(ar,pre)==0)
                    {
                        fprintf(fp3,"%Duplicate token at line %d\n",k);
                    }
                    strcpy(d[k][pt++],ar);

                }
                else if(isKey(ar)==1)
                {
                    fprintf(fp2,"kw %s ",ar);
                    if(strcmp(ar,"if")==0)
                    {
                        isIf  = 1;
                        semicolonIf = 0;
                    }
                    else if(strcmp(ar,"else")==0)
                    {
                        if(isIf==0 || semicolonIf!=1)
                        {
                            fprintf(fp3,"'else' without a previous 'if' at line %d\n",k);
                        }
                        else isIf  = 0;
                    }
                    else if(strcmp(ar,"for")==0)
                    {
                        forloop = 1;
                    }
                    if(strcmp(ar,pre)==0)
                    {
                        fprintf(fp3,"Duplicate token at line %d\n",k);
                    }
                    strcpy(d[k][pt++],ar);

                }
                else if(isId(ar)==1)
                {

                    fprintf(fp2,"id %s ",ar);
                    if(strcmp(ar,pre)==0)
                    {
                        fprintf(fp3,"Duplicate token at line %d\n",k);
                    }
                    strcpy(d[k][pt++],"id");
                    strcpy(d[k][pt++],ar);
                }
                else if(isOper(ar)==1)
                {
                    fprintf(fp2,"op %s ",ar);
                    strcpy(d[k][pt++],ar);
                }
                else if(isParen(ar)==1)
                {
                    fprintf(fp2,"par %s ",ar);
                    if(strcmp(ar,"(")==0)
                    {
                        fb++;
                        if(forloop==1)
                            forloop++;
                    }
                    else
                    {
                        if(forloop>0 && forloop<4)
                        {
                            fprintf(fp3,"Expected ‘;’ in for loop at line %d\n",k);
                        }
                        else if(fb==0)
                            fprintf(fp3,"Misplaced ‘)’ at line %d\n",k);
                        else
                        {
                            fb--;
                            if(forloop>0)
                                forloop = 0;
                        }
                    }
                    strcpy(d[k][pt++],ar);

                }
                else if(isBrace(ar)==1)
                {
                    fprintf(fp2,"brc %s ",ar);
                    if(strcmp(ar,"{")==0)
                        sb++;
                    else
                    {

                        if(sb==0)
                            fprintf(fp3,"Misplaced ‘}’ at line %d\n",k);
                        else sb--;
                    }
                    strcpy(d[k][pt++],ar);
                }
                else if(isNum(ar)==1)
                {
                    fprintf(fp2,"num %s ",ar);
                    strcpy(d[k][pt++],ar);
                }
                else if(isHeader(ar)==1)
                {
                    fprintf(fp2,"header %s ",ar);
                    strcpy(d[k][pt++],ar);
                }
                else
                {


                    fprintf(fp2,"unkn %s ",ar);
                    fprintf(fp3,"Undeclared/Unknown %s at line %d\n",ar,k);
                    strcpy(d[k][pt++],ar);
                }
                j= 0;
                strcpy(pre,ar);
            }
            else
            {
                if(br[i]=='"')
                {
                    ar[j++]  = br[i];
                    f  = (f ^ 1);
                    if(f==0)
                    {
                        j =0;
                    }
                }
                else
                    ar[j++]  = br[i];
            }

        }
        fprintf(fp2,"\n");
        sz[k] =  pt;
    }
    if(sb>0)
        fprintf(fp3,"Expected ‘}’ at line %d\n",k-1);
    if(fb>0)
        fprintf(fp3,"Expected ‘)’ at line %d\n",k-1);




    it = 0;
    scope = "global";
    for(k=1; k<totalsz; k++)
    {
        for(i=0; i<sz[k]; i++)
        {
            if(strcmp(d[k][i],"id")==0)
            {
                if(strcmp(d[k][i+2],"(")==0)
                {
                    if(strcmp(d[k][i-1],"int")==0 || strcmp(d[k][i-1],"double")==0 || strcmp(d[k][i-1],"float")==0 || strcmp(d[k][i-1],"char")==0 || strcmp(d[k][i-1],"void")==0)
                    {
                        inde[it++]  = cur;
                        insert(cur++,d[k][i+1],"func",d[k][i-1],scope,"");
                        scope = d[k][i+1];
                        i+= 2;
                    }
                    else
                    {
                        int pq  = search(d[k][i+1],"func","global");
                        if(pq!=-1)
                            inde[it++] = pq;
                        else fprintf(fp3,"Expected declaration of function %s at line %d\n",d[k][i+1],k);
                        i+= 2;
                    }
                }
                else if(strcmp(d[k][i+2],"=")==0)
                {
                    if(strcmp(d[k][i-1],"int")==0 || strcmp(d[k][i-1],"double")==0 || strcmp(d[k][i-1],"float")==0 || strcmp(d[k][i-1],"char")==0 )
                    {
                        if(search(d[k][i+1],"var",scope)==-1)
                        {
                            inde[it++]  = cur;
                            insert(cur++,d[k][i+1],"var",d[k][i-1],scope,modify(d[k][i+3]));
                        }
                        else
                        {
                            fprintf(fp3,"ID %s at line %d already declared in %s scope\n",d[k][i+1],k,scope);
                        }
                    }
                    else
                    {
                        int pq = search(d[k][i+1],"var",scope);
                        if(pq==-1)
                        {
                            fprintf(fp3,"Expected declaration of %s at line %d\n",d[k][i+1],k);
                        }
                        else
                        {
                            update(pq,modify(d[k][i+3]));
                            inde[it++]  = pq;
                        }
                    }
                    i+=2;
                }
                else if(strcmp(d[k][i+2],";")==0 || strcmp(d[k][i+2],",")==0 || strcmp(d[k][i+2],")")==0 )
                {
                    if(strcmp(d[k][i-1],"int")==0 || strcmp(d[k][i-1],"double")==0 || strcmp(d[k][i-1],"float")==0 || strcmp(d[k][i-1],"char")==0 )
                    {
                        if(search(d[k][i+1],"var",scope)==-1)
                        {
                            inde[it++]  = cur;
                            insert(cur++,d[k][i+1],"var",d[k][i-1],scope,"");
                        }
                        else fprintf(fp3,"ID %s at line %d already declared in %s scope\n",d[k][i+1],k,scope);
                        i+= 2;
                    }
                    else
                    {
                        if(search(d[k][i+1],"var",scope)==-1)
                        {
                            fprintf(fp3,"Expected declaration of %s at line %d\n",d[k][i+1],k);
                        }
                        else inde[it++]  = search(d[k][i+1],"var",scope);
                        i+= 2;
                    }
                }
            }
            else if(strcmp(d[k][i],"}")==0)
            {
                curp--;
                if(curp<0)
                    curp=0;
                if(curp==0)
                    scope = "global";
            }
            else if(strcmp(d[k][i],"{")==0)
            {
                curp++;
            }
        }
    }

    fclose(fp);
    fclose(fp2);
    fclose(fp3);
    printf("\n");
    printf("\n");

    FILE *f1,*f2,*f3,*f4,*f5;

    char filename[100], c;
    printf("Assignment 1:");
    printf("\n");
    printf("\n");
    f1 = fopen("assignment1.txt", "r");
    if (f1 == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    c = fgetc(f1);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(f1);
    }

    fclose(f1);

    printf("\n");
    printf("\n");
    printf("Assignment 2:");
    printf("\n");
    printf("\n");

    f2 = fopen("assignment2.txt", "r");
    if (f2 == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }


    c = fgetc(f2);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(f2);
    }

    fclose(f2);


    printf("\n");
    printf("\n");
    printf("Assignment 3:");
    printf("\n");
    printf("\n");

    f3 = fopen("assignment3.txt", "r");
    if (f3 == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }


    c = fgetc(f3);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(f3);
    }

    fclose(f3);


    printf("\n");
    printf("\n");
    printf("Assignment 4:");
    printf("\n");
    printf("Intermediate Output:");
    printf("\n");
    printf("\n");

    f4 = fopen("assignment4_intermediate_output.txt", "r");
    if (f4 == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }


    c = fgetc(f4);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(f4);
    }

    fclose(f4);


    printf("\n");
    printf("\n");
    printf("Error Output:");
    printf("\n");
    printf("\n");

    f5 = fopen("assignment4_error_output.txt", "r");
    if (f5 == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }


    c = fgetc(f5);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(f5);
    }

    fclose(f5);



    return 0;



}

