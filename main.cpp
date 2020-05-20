#include <iostream>
#include<cstdlib>
#include<fstream>
using namespace std;
int i=0;
template <typename T>
struct stek
{
    T id;
    stek* next;
};
template <typename T>
void push(stek<T>* &ptr, T x)
{
    stek<T>* tmp=new stek<T>;
    tmp->id=x;
    tmp->next=ptr;
    ptr=tmp;
}
template <typename T>
T pop(stek<T>* &ptr)
{
    stek<T>* tmp=ptr;
    T x=tmp->id;
    ptr=ptr->next;
    delete(tmp);
    return x;
}
stek<double>* X=NULL;
stek<char>* Y=NULL;
char s[100];
int priority(char x)
{
    if(x=='=')return 1;
    if(x=='(')return 2;
    if(x=='-'||x=='+')return 3;
    if(x=='*'||x=='/')return 4;
    if(x=='0'||x=='1'||x=='2'||x=='3'||x=='4'||x=='5'||x=='6'||x=='7'||x=='8'||x=='9')return 0;
    else return -1;
}
int konets()
{
    int j=i;
    if(s[j]=='+'||s[j]=='-')j++;
    while(priority(s[j])==0)j++;
    if(s[j]=='.')j++;
    if(s[j]=='e')j+=2;
    while(priority(s[j])==0)j++;
    return j-1;
}
int main()
{   ifstream fin("input.txt");
     fin.getline(s,100);
     fin.close();
    cout<<"iskhodnoe vyrazhenie: "<<s<<endl;
    cout<<"OPN: ";
    int m;
    char n[50];
    double v,w;
    int k;
    k=konets();
    for(m=i; m<=k; m++) n[m-i]=s[m];
    n[k-i+1]='\0';
    cout<<n<<" ";
    i=k+1;
    push(X, atof(n));
    while(s[i]!='\0')
    {
        if(priority(s[i])==0||(priority(s[i])==3&&s[i-1]=='('))
        {
            k=konets();
            for(m=i; m<=k; m++) n[m-i]=s[m];
            n[k-i+1]='\0';
            i=k+1;
            push(X, atof(n));
            cout<<n<<" ";
        }
        if(s[i]=='(')
        {
            push(Y,s[i]);
            i++;

        }
        if(s[i]==')')
        {
            while(Y->id!='(')
            {
                v=pop(X);
                w=pop(X);
                cout<<Y->id;
                if(Y->id=='/'&&v==0)
                {
                    cout<<endl;
                    cout <<"Oshibka! Delenie na 0";
                    return 0;
                }
                if(Y->id=='+')push(X,w+v);
                if(Y->id=='-')push(X,w-v);
                if(Y->id=='*')push(X,w*v);
                if(Y->id=='/')push(X,w/v);
                pop(Y);
            }
            pop(Y);
            i++;
        }
        if(priority(s[i])>=1&&s[i-1]!='(')
        {
            if(Y==NULL)push(Y,s[i]);
            else
            {
                if(priority(Y->id)<priority(s[i]))
                {
                    push(Y,s[i]);
                }
                else
                {
                    while(Y!=NULL&&priority(Y->id)>=priority(s[i]))
                    {
                        v=pop(X);
                        w=pop(X);
                        cout<<Y->id;
                        if(Y->id=='/'&&v==0)
                        {
                            cout<<endl;
                            cout <<"Oshibka! Delenie na 0";
                            return 0;
                        }
                        if(Y->id=='+')push(X,w+v);
                        if(Y->id=='-')push(X,w-v);
                        if(Y->id=='*')push(X,w*v);
                        if(Y->id=='/')push(X,w/v);
                        pop(Y);

                    }
                    push(Y,s[i]);
                }

            }
            i++;
        }
    }
    cout<<"="<< endl;
    cout <<"resultat: "<<X->id;
    return 0;
}
