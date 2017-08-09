#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<algorithm>
using namespace std;
int card[40],ans[40],cardtemp[40],numcard[4];
int smalldealint[10];
inline int deal();
void read();
inline int is7()//��7�Եĺ���
{
    for(int i=0;i<36;i++)
    if(card[i]&&card[i]!=2) return 0;
    return 1;
}
inline int is131()//��13�۵ĺ���
{
    if((card[0]&&card[9]&&card[8]&&card[17]&&card[18]&&card[26]&&card[27]&&card[28]&&card[29]&&card[30]&&card[31]&&card[32]&&card[33])
    &&(card[0]+card[9]+card[8]+card[17]+card[18]+card[26]+card[27]+card[28]+card[29]+card[30]+card[31]+card[32]+card[33]==14))
    return 1;
    return 0;
}
inline int smalldeal(int p,int n);
inline int getnum(int p,int n)//��ͬ�ֻ�ɫ�����м���
{
    int num=0;
    for(int i=p;i<n+p;i++)
        num+=card[i];
    return num;
}
inline void output(int numans,int ans[]);
int main()
{
    int T;cin>>T;
    while(T--)
    {
        memset(ans,0,sizeof(ans));
        memset(cardtemp,0,sizeof(cardtemp));
        int numans=0;
        read();
        memset(numcard,0,sizeof(numcard));
        for(int i=0;i<28;i+=9)
            numcard[i/9]=getnum(i,9);
        copy(card,card+39,cardtemp);
        for(int i=0;i<34;i++)//ö�������ƿ�����
            if(cardtemp[i]<4)
            {
                copy(cardtemp,cardtemp+35,card);//��card����һ�£���Ϊ����Ĳ���Ҫ�޸�card����
                if(card[i+1]==0&&i!=0&&card[i-1]==0&&(card[i]==0||card[i]==3)) continue;//���ּ�֦
                //��������һ�¾Ͷ���
                card[i]++;//����������
                numcard[i/9]++;//��ͬ�ֻ�ɫ���Ƶĸ�����1
                if(is7()||is131()) numans+=ans[i]=1;//�����ʮ���ۻ�7��
                else if(deal()) numans+=ans[i]=1;//��Ȼ����ͨ�ĺ���
                memset(card,0,sizeof(card));//�������㣬ò���Ƿϻ�
                numcard[i/9]--;//��ͬ�ֻ�ɫ���Ƶĸ�������û�м���֮ǰ��״̬
            }
        output(numans,ans);//������
    }
    return 0;
}
inline int deal()//��ͨ���к��Ĵ�����
{
    int num2=0;
    for(int i=0;i<4;i++)
        if(numcard[i]%3==1) return 0;//�е�����
        else if (numcard[i]%3==2) num2++;//��һ�²�ͬ��ɫ�����м�����ɫ�ĸ�����3*k+2�ĸ���
    if(num2!=1) return 0;//���ͬ�ֻ�ɫ���Ƶĸ�����3*k+2����ʽ��û�л�ֹһ�� ���򲻿��ܺ���
    for(int i=0;i<3;i++)//���� �� �� ���Ƶ���ʽ�ܲ��ܺ�
    {
        if(numcard[i]%3==0)//���ͬ�ֻ�ɫ�Ƶĸ�����3�ı�����������û����
        {
            if(!smalldeal(i*9,9)) return 0;//3�ı������Ʋ��Ϸ�����������Ҳ���Ϸ�
        }
        else//˵���Ƶĸ�����3K+2�������ۣ�������Ҫö�������
        {
            int f=0;
            copy(&card[i*9],&card[i*9+9],smalldealint);//��Ϊsmalldeal������ֱ���޸����飬����Ҫ����һ��
            for(int j=i*9;j<i*9+9;j++)
            {
                copy(smalldealint,smalldealint+9,&card[i*9]);//���ݻ�ԭ
                 if(card[j]>1)
                {
                    card[j]-=2;//ö����
                    if(smalldeal(i*9,9)) {f=1;break;}//�ۺϷ��Ͳ���ö����
                }
            }
            if(!f) return 0;//ö���۶����Ϸ��������Ҳ���Ϸ���
        }
    }
    //���� ���ƣ���������ʲô��
    if(numcard[3]%3==2)//���ڷ�������
    for(int i=27;i<34;i++)
    {
        if(card[i]==4) return 0;//���ŷ�ֱ�ӷ��ؼ�ֵ
        if(card[i]==2) {card[i]=0;break;}//�������Ҳ��һ���ۣ��ҵ�һ���۾Ͳ�������
    }
    for(int i=27;i<35;i++)//��ôʣ�µķ��Ʊ���ȫ��3�Ż�0��
    if(card[i]&&card[i]!=3) return 0;
    return 1;
}
inline int smalldeal(int p,int n)//����3�ı��������ǲ���ȫ�����3��3���Ϸ���
{//�������ֵ
    for(int i=p;i<p+n;i++)
        if(card[i])
        {
            if(card[i]>=3) card[i]=card[i]-3;
            if(card[i])
            {
                if(!card[i+1]||!card[i+2]||i+2>=p+n) return 0;
                if(card[i]>card[i+1]||card[i]>card[i+2]) return 0;
                card[i+1]-=card[i],card[i+2]-=card[i];
                card[i]=0;
            }
        }
    return 1;
}
inline void read()//���뺯��
{
    memset(card,0,sizeof(card));
    for(int i=0;i<13;i++)
    {
        getchar();
        char a[5];
        scanf("%s",a);
        int num=(int)(a[0]-'0');
        if(a[1]=='m') card[num-1]++;
        if(a[1]=='s') card[num-1+9]++;
        if(a[1]=='p') card[num-1+18]++;
        if(a[1]=='c') card[num-1+27]++;
    }
}
inline void output(int numans,int ans[])//�������ĺ���
{
    if(!numans) printf("Nooten\n");//���û���ƿ�����
    else
    {
        cout<<numans;
        for(int i=0;i<35;i++)//����С������
        if(ans[i])
        {
            if(i/9==0) printf(" %dm",i%9+1);
            else if(i/9==1) printf(" %ds",i%9+1);
            else if(i/9==2) printf(" %dp",i%9+1);
            else printf(" %dc",i%9+1);
        }
       printf("\n");
    }
}

