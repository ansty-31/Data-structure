#include "..\sqstack.cpp"

static bool match(char * expr)
{
    bool match=true;
    SqStack *s;
    InitStack(s);
    while (*expr!=0&&match)
    {
        char e= *expr;
        if (e=='{'||e=='['||e=='('||e=='<')
        {
            Push(s,e);
        }
        else if (e == '"' || e == '\'')
        {
            // 引号特殊处理：检查栈顶是否已经是同种引号,即引号之间不能有单个的括号就行
            char topElem;
            if (GetTop(s, topElem) && topElem == e)
            {
                // 栈顶是同种引号，说明是闭合引号
                Pop(s, topElem);
            }
            else
            {
                // 栈顶不是同种引号，说明是开始引号
                Push(s, e);
            }
        }
        else if (e=='}'||e==']'||e==')'||e=='>')
        {
            char t=e;
            if(GetTop(s,e)==true)
            {
                switch (e)
                {
                case '{': match=(t=='}'); break;
                case '[': match=(t==']'); break;
                case '(': match=(t==')'); break;
                case '<': match=(t=='>'); break;   
                default: match = false; break;  // 栈顶是引号但遇到右括号，不匹配
                }
            }
            else match=false;
            if(match) Pop(s,e);
        }
        expr++;
    }
    if(s->top!=-1)
    {
        match=false;
    }
    DestroyStack(s);
    return match;
}
//该函数只能处理不考虑转义情况下的表达式

int main() {
    char testExpr[] =  " 'She said, \"Hello'";
    bool result = match(testExpr);
    printf("result=%d",result);
    return 0;
}