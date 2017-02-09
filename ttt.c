#include<stdio.h>
#include<stdlib.h>
void print(char **arr)
{
   for(int i=0;i<3;i++)
   {
      for(int j=0;j<3;j++)
         printf("%c ",arr[i][j]);
      printf("\n");
   }
   printf("\n");
   
}

int check(char **arr)
{
   for(int i=0;i<3;i++)
   {
      if(arr[i][0]!='.' && arr[i][0]==arr[i][1] && arr[i][0]==arr[i][2])
      {
         if(arr[i][0]=='X')
           return 10;
         else
           return -10;
      }

      if(arr[0][i]!='.' && arr[0][i]==arr[1][i] && arr[0][i]==arr[2][i])
      {
         if(arr[0][i]=='X')
           return 10;
         else
           return -10;
      }
   }
   
   if(arr[0][0]!='.' && arr[0][0]==arr[1][1] && arr[0][0]==arr[2][2])
   {
      if(arr[0][0]=='X')
         return 10;
      else
         return -10;
   }

   if(arr[2][0]!='.' && arr[2][0]==arr[1][1] && arr[2][0]==arr[0][2])
   {
      if(arr[2][0]=='X')
         return 10;
      else
         return -10;
   }
   return 0;
}

int func(char ** arr,int count,int flag)
{
   int ans=check(arr);
   if(ans!=0)
      return ans;

   if(count>=9)
      return 0;
   

   int com;
   if(flag==-1)
      com=10;
   else
      com=-10;

   for(int i=0;i<3;i++)
   {
      for(int j=0;j<3;j++)
      {
         if(arr[i][j]=='.')
         {
            if(flag==-1)
            {
               arr[i][j]='O';
               int temp=func(arr,count+1,1);
               if(temp<com)
               {
                  com=temp;

               }
               arr[i][j]='.';
            }

            if(flag==1)
            {
               arr[i][j]='X';
               int temp=func(arr,count+1,-1);
               if(temp>com)
               {
                  com=temp;
               }
               arr[i][j]='.';
            }            
         }
      }
   }
   return com;
}

int main()
{
   char** arr=(char **)malloc(3*sizeof(char*));
   for(int i=0;i<3;i++)
   {
      arr[i]=(char *)malloc(3*sizeof(char));
   }

   int count=0;

   for(int i=0;i<3;i++)
   {
      for(int j=0;j<3;j++)
         arr[i][j]='.';
   }

   while(count<9)
   {
      int x,y,min=10;
      scanf("%d %d",&x,&y);
      arr[x-1][y-1]='X';
      count++;
      print(arr);
      if(check(arr)==10)
      {
         printf("YOU WIN\n");
         break;
      }
      if(count==9)
      {
         printf("DRAW\n");
         break;
      }
      

      for(int i=0;i<3;i++)
      {
         for(int j=0;j<3;j++)
         {
            if(arr[i][j]=='.')
            {
               arr[i][j]='O';
               if(func(arr,count+1,1)<=min)
               {
                  min=func(arr,count+1,1);
                  x=i; y=j;
               }
               arr[i][j]='.';
            }
         }
      }
      arr[x][y]='O';
      count++;

      print(arr);
      if(check(arr)==-10)
      {
         printf("YOU LOSE\n");
         break;
      }      
   }
   
   return 0;  
}
