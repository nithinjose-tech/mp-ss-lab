#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct node
{
    char label[10];
    int addr;
    struct node * link;
};
struct node* header=NULL;
struct node* ptr=NULL;
FILE *fp;
FILE *fpass1;
int search(char* line,char* opcode)
{
    int len=strlen(line);
    int i=0;
    int j=0;
    while(i<len)
    {
        if(line[i]==opcode[j])
        {
            //printf("\nfound at i %d at %d",i,j);
            j++;
            if(j==strlen(opcode))
            {
                return i;
            }
        }
        i++;
    }
    return 0;
}
int symbol(char * label)
{
    struct node * ptr=header;
    while(ptr!=NULL)
    {
        if(ptr->label==label)
        {
            return ptr->addr;
        }
        ptr=ptr->link;
    }
}
void symtab(char* labelname,int addr)
{

    if(header==NULL)
    {
        ptr =(struct node *)malloc(sizeof(struct node));
        //ptr->label=labelname;
        ptr->addr=addr;
        ptr->link=NULL;
        strcpy(ptr->label,labelname);
        header=ptr;
        ptr=header;
    }
    else
    {
        struct node * ptr1;
        ptr1 =(struct node *)malloc(sizeof(struct node));
        //ptr->label=labelname;
        ptr1->addr=addr;
        ptr1->link=NULL;
        strcpy(ptr1->label,labelname);
        ptr->link=ptr1;
        ptr=ptr->link;
    }
    printf("%s\n",labelname);

}
int charToNum(int index,char * data)
{
    //printf("%s",data);
    int num,temp,decimal=0,locctr=0;
    index+=1;//reaches to the space
    num=strlen(data)-index-2;
    temp=num;
    int k=0;
    int value;
    index++;
    while(k<num)
    {
        value=data[index]-'0';
        locctr=locctr*10+value;
        decimal+= pow(16,temp-1)*value;
        index++;
        k++;
        temp--;

    }
    return decimal;
}
void pass1()
{
    int locctr=0;
    int i=0,loc;
    unsigned int decimal;
    int found=0;
    char data[25];
    fp=fopen("assembly.txt","r");
    fpass1=fopen("pass1.txt","w+");
    //fprintf(fpass1,"%s","data is");
    if(fp==NULL)
    {
        //printf("File not exist!!");
    }
    else
    {
        while(fgets(data,25,fp)!=NULL)
        {
            if(i==0)//for first line
            {
                int loc = search(data,"START");
                //printf("%s",data);
                //printf("loc is %d\n",loc);
                if(loc!=0)
                {
                    locctr=charToNum(loc,data);
                    decimal=locctr;
                    //printf("%d",decimal);
                }
                else
                {
                    locctr=0;
                    decimal=0;
                    char datacopy[25];
                    strcpy(datacopy,data);
                    char* label=strtok(datacopy," ");
                    if(strcmp(label,"ADD") ==0||strcmp(label,"AND")==0||strcmp(label,"COMP")==0||strcmp(label,"DIV")==0||strcmp(label,"J")==0||strcmp(label,"JEQ")==0||strcmp(label,"JGT")==0||strcmp(label,"JLT")==0||strcmp(label,"JSUB")==0||strcmp(label,"LDA")==0|| strcmp(label,"LDCH")==0 || strcmp(label,"LDL") ==0|| strcmp(label,"LDX") ==0|| strcmp(label,"MUL")==0 || strcmp(label,"OR") ==0||strcmp(label,"RD")==0||strcmp(label,"RSUB")==0|| strcmp(label,"STA")==0 || strcmp(label,"STCH")==0 || strcmp(label,"STL") ==0|| strcmp(label,"STSW")==0 || strcmp(label,"STX")==0 || strcmp(label,"SUB") ==0|| strcmp(label,"TD")==0 || strcmp(label,"TIX") ==0|| strcmp(label,"WD")==0)
                    {
                        //fprintf("pass1.txt",)
                        fprintf(fpass1,"%X %s",decimal,data);
                        decimal+=3;
                        //fputs(data,fpass1);
                        //printf("%s",data);
                    }
                    else
                    {
                        if(loc = (search(data,"WORD")))
                        {
                            struct node* ptr2;
                            ptr2=header;
                            while(ptr2!=NULL)
                            {
                                if(strcmp(ptr2->label,label)==0)
                                {
                                    found=1;
                                    break;
                                }
                                ptr2=ptr2->link;
                            }
                            free(ptr2);
                            if(found==0)
                            {
                                symtab(label,decimal);
                            }
                            else
                            {
                                fprintf(fpass1,"%X %s",decimal,"symbol used aready");//set error flag
                            }
                            fprintf(fpass1,"%x %s",decimal,data);
                            decimal+=3;
                        }
                        else if(loc = search(data,"BYTE"))
                        {
                            //||strcmp(label,"WORD")||strcmp(label,"RESW")||strcmp(label,"RESB")||strcmp(label,"BYTE")
                            struct node* ptr2;
                            ptr2=header;
                            while(ptr2!=NULL)
                            {
                                if(strcmp(ptr2->label,label)==0)
                                {
                                    found=1;
                                    break;
                                }
                                ptr2=ptr2->link;
                            }
                            free(ptr2);
                            if(found==0)
                            {
                                symtab(label,decimal);
                            }
                            else
                            {
                                fprintf(fpass1,"%X %s",decimal,"symbol used aready");//set error flag
                            }
                            fprintf(fpass1,"%x %s",decimal,data);
                            decimal+=1;
                        }
                        else if(loc = search(data,"RESW"))
                        {
                            struct node* ptr2;
                            ptr2=header;
                            while(ptr2!=NULL)
                            {
                                if(strcmp(ptr2->label,label)==0)
                                {
                                    found=1;
                                    break;
                                }
                                ptr2=ptr2->link;
                            }
                            free(ptr2);
                            if(found==0)
                            {
                                symtab(label,decimal);
                            }
                            else
                            {
                                fprintf(fpass1,"%X %s",decimal,"symbol used aready");//set error flag
                            }

                            fprintf(fpass1,"%x %s",decimal,data);
                            decimal+=3*charToNum(loc,data);
                        }
                        else if(loc = search(data,"RESB"))
                        {
                            printf("in resb");
                            struct node* ptr2;
                            ptr2=header;
                            while(ptr2!=NULL)
                            {
                                if(strcmp(ptr2->label,label)==0)
                                {
                                    found=1;
                                    printf("data = date");
                                    break;
                                }
                                ptr2=ptr2->link;
                            }
                            free(ptr2);
                            if(found==0)
                            {
                                symtab(label,decimal);
                            }
                            else
                            {
                                fprintf(fpass1,"%X %s",decimal,"symbol used aready");//set error flag
                            }


                            fprintf(fpass1,"%x %s",decimal,data);
                            decimal+=1*charToNum(loc,data);
                        }





                        //int address=symbol(label);

                    }
                }
                i++;
            }
            else//for rest of lines
            {
                //printf("%s ",data);
                found=0;
                char datacopy[25];
                strcpy(datacopy,data);
                struct node * ptr2=header;
                char* label=strtok(datacopy," ");
                //printf("\label is %s \n",label);
                if(strcmp(label,"ADD") ==0||strcmp(label,"AND")==0||strcmp(label,"COMP")==0||strcmp(label,"DIV")==0||strcmp(label,"J")==0||strcmp(label,"JEQ")==0||strcmp(label,"JGT")==0||strcmp(label,"JLT")==0||strcmp(label,"JSUB")==0||strcmp(label,"LDA")==0|| strcmp(label,"LDCH")==0 || strcmp(label,"LDL") ==0|| strcmp(label,"LDX") ==0|| strcmp(label,"MUL")==0 || strcmp(label,"OR") ==0||strcmp(label,"RD")==0||strcmp(label,"RSUB")==0|| strcmp(label,"STA")==0 || strcmp(label,"STCH")==0 || strcmp(label,"STL") ==0|| strcmp(label,"STSW")==0 || strcmp(label,"STX")==0 || strcmp(label,"SUB") ==0|| strcmp(label,"TD")==0 || strcmp(label,"TIX") ==0|| strcmp(label,"WD")==0)                {
                    //fprintf("pass1.txt",)
                    //printf("%X\n",decimal);
                    //printf("instruction is %s\n",data);
                    fprintf(fpass1,"%X %s",decimal,data);
                    decimal+=3;
                    //fputs(data,fpass1);
                    //printf("%s",data);
                }
                else if(loc = search(data,"WORD"))
                {
                    //found=0;
                    while(ptr2!=NULL)
                    {

                        if(strcmp(ptr2->label,label)==0)
                        {
                            found=1;
                            break;
                        }
                        ptr2=ptr2->link;
                    }
                    free(ptr2);
                    if(found==0)
                    {
                        symtab(label,decimal);
                        fprintf(fpass1,"%x %s",decimal,data);
                    }
                    else
                    {
                        fprintf(fpass1,"%X %s",decimal,"symbol used aready");//set error flag
                    }

                    decimal+=3;
                }
                else if(loc = search(data,"BYTE"))
                {
                    //||strcmp(label,"WORD")||strcmp(label,"RESW")||strcmp(label,"RESB")||strcmp(label,"BYTE")
                    //found=0;
                    while(ptr2!=NULL)
                    {
                        if(strcmp(ptr2->label,label)==0)
                        {
                            found=1;
                            break;
                        }
                        ptr2=ptr2->link;
                    }
                    free(ptr2);
                    if(found==0)
                    {
                        symtab(label,decimal);
                        fprintf(fpass1,"%x %s",decimal,data);
                    }
                    else
                    {
                        fprintf(fpass1,"%X %s",decimal," symbol used aready");//set error flag
                    }
                    decimal+=1;
                }
                else if(loc = search(data,"RESW"))
                {
                    //found=0;
                    while(ptr2!=NULL)
                    {
                        if(strcmp(ptr2->label,label)==0)
                        {
                            found=1;
                            break;
                        }
                        ptr2=ptr2->link;
                    }
                    free(ptr2);
                    if(found==0)
                    {
                        symtab(label,decimal);
                    }
                    else
                    {
                        fprintf(fpass1,"%X %s",decimal,"symbol used aready");//set error flag
                    }

                    fprintf(fpass1,"%x %s",decimal,data);
                    //printf("resw length in instruction is %d",charToNum(loc,data));
                    decimal+=charToNum(loc,data)*3;
                }
                else if(loc = search(data,"RESB"))
                {
                    //found=0;
                    while(ptr2!=NULL)
                    {
                        if(strcmp(ptr2->label,label)==0)
                        {
                            //printf("DATA CMP DATE %d",strcmp("DATA","DATE"));
                            found=1;
                            break;
                        }
                        ptr2=ptr2->link;
                    }
                    free(ptr2);
                    //printf("\n%s  %d value of found",data,found);
                    if(found==0)
                    {
                        symtab(label,decimal);
                    }
                    else
                    {
                        fprintf(fpass1,"%X %s",decimal,"symbol used aready");//set error flag
                    }


                    fprintf(fpass1,"%x %s",decimal,data);
                    decimal+=1*charToNum(loc,data);
                }
                else if(loc = search(data,"END") )
                {
                    fclose(fp);
                    fclose(fpass1);
                    free(ptr);

                }


            }
        }
        //printf("%s",data);

    }
}
int main()
{
    pass1();
    return 0;
}
