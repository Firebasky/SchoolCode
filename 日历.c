#include<stdio.h>
int day_sum(int year, int month);//月份天数
void printf_calendar(int year);//打印月份
int calendar_1(int year, int month, int calendar[6][7]);//把月份存放到数组里面
int calendar_2(int year, int month, int calendar[6][7],int day);//把下一个月存放到数组里面
void printf_week(int year, int month, int day);//打印某一天是那一个周，星期几
int main()
{
    int year, month, day;
    int flag,i;
    printf("choice one input or two input:");
    scanf("%d", &flag);
    //进行判断输入
	if(flag==1)
	{
        printf("Input the year:");
		scanf("%d",&year);
        for(i=1;i<=3;i++)
        {
            if(year<9999999&&year>0)//进行参数过滤
	 	    {
                 printf("The calendar of the year %d\n",year);
		         printf_calendar(year);
                 break;
             }
             else
             {
                 printf("error please again\n");//3次机会重新输入
                 printf("Input the year:");
		         scanf("%d",&year);       
            }
        }
	}
    if(flag==2)
    {
        printf("Input the year:");
		scanf("%d%*c%d%*c%d",&year,&month,&day);
        for(i=1;i<=3;i++)
        {
         //%*c作用时读取输入流中数字后的一个字符，并丢弃，使得后面的输入函数不能读到那个字符
         if((year<9999999&&year>0)&&(month<=12&&month>0)&&(day>0&&day<=31))//参数过滤
         {
            int temp,temp2;//进行交互的输入
            if(year>12&&year<32)//如果年和天数交互 dd/mm/yyyy
             {
                //如果年小于32 我们判断 用户输入的第一个数字为月或日
        	    //日和月 发生冲突时 默认为 dd mm yyyy 格式
                temp = day;
                day = year;
                year = temp;
             }
            if((year>0&&year<12)&&(month>12&&month<32)&&(day>31))//如果年和月份交互 mm/dd/yyyy
            {
                //交互年月mm/yyy/dd
                temp = month;
                month = year;
                 year = temp;
                //交互年日mm/dd/yyy
                temp2 = year;
                year = day;
                day = temp2;
            }
	        printf("The calendar of the year %d\n",year);//重新输入3次机会
            printf_week(year, month, day);//打印星期
            printf_calendar(year);//打印日历
            break;
         }
     
        else
        {
            printf("error please again\n");
            printf("Input the year:");
		    scanf("%d%*c%d%*c%d",&year,&month,&day);
         }
     }
    }
    else
    {
        printf("input error！！！\n");
    }
    return 0;
}
int day_sum(int year,int month)
{
	if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
    {
		return 31;
	}
    else if(month==2)
    {
	if((year%4==0 && year%100!=0)||(year%400==0))//判断闰年
    {
        return 29;//闰年
	}
		else
        {
			return 28;//平年
		}
	}
	else
    {
		return 30;
	}
}
//打印日历
void printf_calendar(int year)
{
    int i;
    int firstday;//每一年第一天星期几
    char month[12][12] ={"January 1","Febrary 2","March 3","April 4","May 5","June 6","July 7","August 8","September 9","October 10","November 11","December 12"};
	char *s="===================================";
	char *d="Sun  Mon  Tue  Web  Thu  Fri  Sat";
    firstday = (year + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400) % 7;
    //日历一排的打印，一排打印2个月，使用要创建俩个数组
 	int calendar1[6][7];//第一个
	int calendar2[6][7];//第二个
    for (i = 0; i < 12;i+=2)//因为一排打印所以循环6次
    {
        int m, q;//m表示月份，q表示星期数
		printf("%s%42s\n",month[i],month[i+1]);//打印月份
		printf("%s\t%s\n",s,s);//打印=
		printf("%s\t%s\n",d,d);//打印星期

        m = i;
        if(i==0)//第一个月
        {
            q = calendar_1(year, m + 1, calendar1);//月末星期数
            q = calendar_2(year, m + 2, calendar2, q);//上一个月末星期数
        }
        else//下一个月
        {
            q = calendar_2(year, m + 1, calendar1, q);
            q = calendar_2(year, m + 2, calendar2, q);
        }
        //打印全部日历
        for (int high = 0; high < 6;high++)
        {
            for (int leng = 0; leng < 7;leng++)
            {
                if(calendar1[high][leng]==0)//将0换成空格
                {
                    printf("     ");
                }
                else//修改格式
                {
                    if(calendar1[high][leng]<10)
                    {
                        printf("%d%c%c%c%c", calendar1[high][leng], ' ', ' ', ' ', ' ');
                    }
                    else
                    {
                        printf("%d%c%c%c", calendar1[high][leng], ' ', ' ', ' ');
                    }
                }
            }
            printf("\t");
            for (int lengleng = 0; lengleng < 7;lengleng++)
            {
                if(calendar2[high][lengleng]==0)//将0换成空格
                {
                    printf("     ");
                }
                else//修改格式
                {
                    if(calendar2[high][lengleng]<10)
                    {
                        printf("%d%c%c%c%c", calendar2[high][lengleng], ' ', ' ', ' ', ' ');
                    }
                    else
                    {
                        printf("%d%c%c%c", calendar2[high][lengleng], ' ', ' ', ' ');
                    }
                }
            }
            printf("\n");
        }
        //printf("\n");
        printf("%s\t%s\n",s,s);
    }
}
//存放1月的日历，并且返回月末的星期数
int calendar_1(int year, int month, int calendar[6][7])
{
    int fristday,monthsum;
    fristday = (year + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400) % 7;
    monthsum = day_sum(year, month);
    int n = 1,high;
    for (high = 0; high < 6;high++)
    {
        if(high==0)//第一排存在空格
        {
            for (int i = 0; i < fristday%7;i++)//取余数
            {
                calendar[high][i] = 0;
                //用0表示空格
            }                
            while(i<7)
            {
                calendar[high][i++] = n++;//开始存放
            }
       }
       else
       {
           for (int j = 0; j < 7;j++)//下面几排
           {
               calendar[high][j] = n++;
               if(n>monthsum+1)
               {
                   calendar[high][j] = 0;
                   //不存放超出的
               }
           }
       }
    }
    return (monthsum % 7 + fristday - 1);
}
//接收上一个月的星期数，返回月末的星期数，并且存放日历
int calendar_2(int year, int month, int calendar[6][7],int day)
{
    int fristday,monthsum;
    fristday = day + 1;
    monthsum = day_sum(year, month);
    int n = 1,high;
    for (high = 0; high < 6;high++)
    {
        if(high==0)//第一排存在空格
        {
            for (int i = 0; i < fristday%7;i++)//取余数
            {
                calendar[high][i] = 0;
                //用0表示空格
            }                
            while(i<7)
            {
                calendar[high][i++] = n++;//开始存放
            }
       }
       else
       {
           for (int j = 0; j < 7;j++)//下面几排
           {
               calendar[high][j] = n++;
               if(n>monthsum+1)
               {
                   calendar[high][j] = 0;
                   //不存放超出的
               }
           }
       }
    }
    return (monthsum % 7 + fristday - 1);
}
void printf_week(int year,int month,int day)//计算第几周和周几
{
    int fristday,sum=0;
    int q,a,b;
    //q表示星期几,a表示第几周,进行判断周是不是刚刚好除0
    fristday = (year + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400) % 7; //计算每年开始的的第一天星期几
	for(int i=1;i<month;i++)
    {	
        sum+=day_sum(year,i);
	}
	sum+=day;//总天数
    //计算星期几
    q = sum % 7 + fristday - 1;
    if(q>7)
    {
		q%=7;
	}
	//计算当前日期是这年的第几周
	b=(sum+fristday)%7;
	if(b==0)
    {
		a=(sum+fristday)/7;
	}
	else//b不等于0时，周加1
	{
		a=(sum+fristday)/7;
		a++;
	}
	printf("第%d周，星期%d\n",a,q);
}
