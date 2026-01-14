#include "..\sqstack.cpp"

void trans(char *exp,char postexp[])
{
    char e;
    SqStack *Optr;
    InitStack(Optr);
    int i = 0;
    while (*exp!='\0')
    {
        switch (*exp)
        {
        case '(':
                Push(Optr, '(');
                exp++;
                break;
        case ')':
                Pop(Optr,e);
                while (e!='(')
                {
                    postexp[i++]=e;
                    Pop(Optr,e);
                }
                exp++;
                break;
        case '+':
        case '-':
                while (!StackEmpty(Optr))
                {
                    GetTop(Optr,e);
                    if(e!='(')
                    {
                        postexp[i++]=e;
                        Pop(Optr,e);
                    }
                    else break;
                }
                Push(Optr,*exp);
                exp++;
                break;
        case '*':
        case '/':
                while (!StackEmpty(Optr))
                {
                    GetTop(Optr,e);
                    if(e=='*'||e=='/'||e=='.')
                    {
                        postexp[i++]=e;
                        Pop(Optr,e);
                    }
                }
                Push(Optr,*exp);
                exp++;
                break;
        case '.':Push(Optr,'.');
                exp++;
                break;        
        default:
                while(*exp>='0'&&*exp<='9')
                {
                    postexp[i++]=*exp;
                    exp++;
                }
                postexp[i++]='#';
                break;
        }
    }
    while (!StackEmpty(Optr))
    {
        Pop(Optr,e);
        postexp[i++]=e;
    }
    postexp[i]='\0';
    DestroyStack(Optr);
}

double compvalue(char * postexp)
{
    double d,a,b,c,e;
    SqStack1 *Opend;
    InitStack1(Opend);
    while (*postexp!='\0')
    {
        switch(*postexp)
        {
            case '+':
                    Pop1(Opend,a);
                    Pop1(Opend,b);
                    c=b+a;
                    Push1(Opend,c);
                    break;
            case '-':
                    Pop1(Opend,a);
                    Pop1(Opend,b);
                    c=b-a;
                    Push1(Opend,c);
                    break;
            case '*':
                    Pop1(Opend,a);
                    Pop1(Opend,b);
                    c=b*a;
                    Push1(Opend,c);
                    break;
            case '/':
                    Pop1(Opend,a);
                    Pop1(Opend,b);
                    if(a!=0)
                    {
                        c=b/a;
                        Push1(Opend,c);
                        break;
                    }
                    else
                    {
                        printf("\n\t除零错误!\n");
                        exit(0);
                    }
                    break;
            case '.':
                    Pop1(Opend,a);
                    while(a>=1) a=a/10;
                    Pop1(Opend,b);
                    c=a+b;
                    Push1(Opend,c);
                    break;
            default:
                    d=0;
                    while(*postexp>='0'&&*postexp<='9')
                    {
                        d=10*d+*postexp-'0';
                        postexp++;
                    }
                    Push1(Opend,d);
                    break;        
        }
        postexp++;
    }
    GetTop1(Opend,e);
    DestroyStack1(Opend);
    return e;
}

int main()
{
    char exp[]="(2.5-1.5)/(0.46+0.54)*14.13";
    char postexp[MaxSize];
    trans(exp,postexp);
    printf("表达式为：%s\n",exp);
    printf("后缀表达式为: %s\n",postexp);
    printf("表达式结果为：%g\n",compvalue(postexp));
    return 1;
}