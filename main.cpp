#include <iostream>
//Максимальный объем запросом от пользователя
#define MAX 20
using namespace std;

class bankers
{
    private:
        //количество выделенных ресурсов для каждого процесса
        int KolResAll[MAX][MAX];
        //максимальные требования к ресурсам для каждого процесса
        int maxRequirement[MAX][MAX];
        //количество необходимых ресурсов для каждого процесса
        int resourcesNeed[MAX][MAX];
        //кол доступных ресурсов
        int avail[MAX];
        //кол-во процессов
        int proces;
        //кол-во ресурс
        int resource;
        //порядок выполнения процессов и индекс
        int k,result[MAX];
        //Временная переменная для хранения номера процесса
        int numProc;
        //хранящий текущее количество доступных ресурсов
        int work[MAX];
        //завершен ли процесс
        int finish[MAX];

    public:
        bankers();
        void input();
        void method();
        //можно ли выполнить процесс
        int search(int);
        void display();
};

bankers::bankers()
{
    k=0;
    for(int i=0;i<MAX;i++)
    {
        for(int j=0;j<MAX;j++)
        {
            KolResAll[i][j]=0;
            maxRequirement[i][j]=0;
            resourcesNeed[i][j]=0;
        }
        avail[i]=0;
        result[i]=0;
        finish[i]=0;
    }
}

void bankers::input()
{
    int i,j;
    cout << "Введите количество процессов, не больше 20:";
    cin >> proces;
    cout << "Введите количество ресурсов, не больше 20:";
    cin >> resource;
    cout << "Введите выделенные ресурсы для каждого процесса: " << endl;
    for(i=0;i<proces;i++)
    {
        cout<<"\nпроцесс "<<i;
        for(j=0;j<resource;j++)
        {
            cout<<"\nресурс "<<j<<":";
            cin>>KolResAll[i][j];
        }
    }
    cout<<"Введите максимальное количество ресурсов, необходимых для каждого процесса:"<<endl;
    for(i=0;i<proces;i++)
    {
        cout<<"\nпроцесс "<<i;
        for(j=0;j<resource;j++)
        {
            cout<<"\nресурс "<<j<<":";
            cin>>maxRequirement[i][j];
            resourcesNeed[i][j]=maxRequirement[i][j]-KolResAll[i][j];
        }
    }
    cout << "Введите доступные в данный момент ресурсы в системе: \n";
    for(j=0;j<resource;j++)
    {
        cout<<"ресурс "<<j<<":";
        cin>>avail[j];
        work[j]=-1;
    }
    for(i=0;i<proces;i++){
        finish[i]=0;
    }
        
}

//определения безопасного порядка выполнения процессов
void bankers::method()
{
    int i=0,j,flag;
    while(1)
    {
        if(finish[i]==0)
        {
            numProc =search(i);
            if(numProc!=-1)
            {
                result[k++]=i;
                finish[i]=1;
                for(j=0;j<resource;j++)
                {
                    avail[j]=avail[j]+KolResAll[i][j];
                }
            }
        }
        i++;
        
        if(i==proces)
        {
            flag=0;
            for(j=0;j<resource;j++)
                if(avail[j]!=work[j])
                    flag=1;
            for(j=0;j<resource;j++)
                work[j]=avail[j];

            if(flag==0)
                break;
            else
                i=0;
        }
    }
}
//достаточно ли доступных ресурсов для выполнения процесса i
int bankers::search(int i)
{
    int j;
    for(j=0;j<resource;j++)
        if(resourcesNeed[i][j]>avail[j])
            return -1;
    return 0;
}

//Вывод
void bankers::display()
{
    int i,j;
    cout<<endl<<"OUTPUT:";
    cout<<endl<<"========";
    cout<<endl<<"PROCESS\t     ALLOTED\t     MAXIMUM\t     NEED\t   Available";
    for(i=0;i<proces;i++)
    {
        cout<<"\nP"<<i+1<<"\t     ";
        for(j=0;j<resource;j++)
        {
            cout<<KolResAll[i][j]<<"  ";
        }
        cout<<"\t     ";
        for (j=0;j<resource;j++)
        {
            cout<<maxRequirement[i][j]<<"  ";
        }
        cout<<"\t     ";
        for(j=0;j<resource;j++ )
        {
            cout<<resourcesNeed[i][j]<<"  ";
        }
        cout<<"\t     ";
        cout<<work[i];
    }
    cout<<"\nПоследовательность безопасных процессов такова: \n";
    for(i=0;i<k;i++)
    {
        int temp = result[i]+1 ;
        cout<<"P"<<temp<<" ";
    }
    cout<<"\nПоследовательность небезопасных процессов такова: \n";
    int flg=0;
    for (i=0;i<proces;i++)
    {
        if(finish[i]==0)
        {
        flg=1;
        }
        //???
        cout<<"P"<<i<<" ";
    }
    cout<<endl<<"RESULT:";
    cout<<endl<<"=======";
    if(flg==1)
        cout<<endl<<"Система находится в небезопасном состоянии, и может возникнуть взаимоблокировка!!";
    else
        cout<<endl<<"Система находится в безопасном состоянии, и взаимоблокировки не произойдет!!";
}

int main()
{
    cout<<" АЛГОРИТМ БАНКИРА "<<endl;
    bankers B;
    B.input ( );
    B.method ( );
    B.display ( );
}
