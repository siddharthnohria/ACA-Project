//Just run the program and enter the column(1-7) in which you want to insert the new X.
#include<stdio.h>
#include<stdlib.h>
void print(char **arr)       //function which prints out current status of game
{
   for(int i=0;i<6;i++)
   {
      for(int j=0;j<7;j++)
         printf("%c ",arr[i][j]);
      printf("\n");
   }
   printf("\n");
   
   return;
}

int fill(char **arr,int i)    //checks whether 'i'th column is full or not
{
   if(arr[0][i]=='.')
      return 0;
   else
      return 1;

}

void put(char **arr,int i,int flag)    // to put new character in column 'i'
{
   for(int j=5;j>=0;j--)
   {
      if(arr[j][i]=='.')
      {
         if(flag==1)            //my turn
            arr[j][i]='X';
         else                   //computer's turn
            arr[j][i]='O';
         
         break;
      }
   }
}

void remov(char **arr,int i)    // removes top most character from 'i'th column
{
   for(int j=4;j>=0;j--)
   {
      if(arr[j][i]=='.')
      {
         arr[j+1][i]='.';
         break;
      }
   }
   arr[0][i]='.';
}

int value(int x,int y)
{
         if(x>0 && y>0)
            return 0;
         
         if(x==3)
            return 100;
         if(y==3)
            return -100;

         if(x==2)
            return 10;
         if(y==2)
            return -10;

         if(x==1)
            return 1;
         if(y==1)
            return -1;
}  
int check(char **arr)     //assigns value to current state of game
{
   int count=0;
   int cntx,cnto;
   for(int i=0;i<6;i++)
   {
      for(int j=0;j<4;j++)
      {
         cntx=0;
         cnto=0;
         for(int k=j;k<j+4;k++)
         {
            if(arr[i][k]=='X')
               cntx++;
            if(arr[i][k]=='O')
               cnto++;
         }
         if(cntx==4)
            return 1000;
         if(cnto==4)
            return -1000;
         count=count+value(cntx,cnto);
       
      }
   }   

   for(int j=0;j<7;j++)
   {
      for(int i=0;i<3;i++)
      {
         cntx=0;
         cnto=0;
         for(int k=i;k<i+4;k++)
         {
            if(arr[k][j]=='X')
               cntx++;
            if(arr[k][j]=='O')
               cnto++;
         }
         if(cntx==4)
            return 1000;
         if(cnto==4)
            return -1000;
         count=count+value(cntx,cnto);
       
      }
   }   

   for(int i=0;i<3;i++)
   {
      for(int j=0;j<4;j++)
      {
         cntx=0;
         cnto=0;
         for(int k=0;k<4;k++)
         {
            if(arr[i+k][j+k]=='X')
               cntx++;
            if(arr[i+k][j+k]=='O')
               cnto++;
         }
         if(cntx==4)
            return 1000;
         if(cnto==4)
            return -1000;
         count=count+value(cntx,cnto);
       
      }
   }   

   for(int i=0;i<3;i++)
   {
      for(int j=3;j<7;j++)
      {
         cntx=0;
         cnto=0;
         for(int k=0;k<4;k++)
         {
            if(arr[i+k][j-k]=='X')
               cntx++;
            if(arr[i+k][j-k]=='O')
               cnto++;
         }
         if(cntx==4)
            return 1000;
         if(cnto==4)
            return -1000;
         count=count+value(cntx,cnto);
       
      }

   }

   return count;

}

int move(char **arr,int count,int flag,int depth,int alpha,int beta)
{ 
    int ans=check(arr);
   if(depth>=7)
   return ans;

   if(ans==1000 || ans==-1000)
   {
      return ans;
   }
  
   if(count==42)
      return 0;

   int com;
   if(flag==1)
      com=-1000;
   else
      com=1000;

   
   int sort[7],sort2[7];
   for(int i=0;i<7;i++)
   {
      sort2[i]=i;
      if(fill(arr,i)==1)
      {
         if(flag==1)
            sort[i]=-2000;
         else
            sort[i]=2000;
         continue;
      }   
      put(arr,i,1);
      sort[i]=check(arr);
      remov(arr,i);
   }

      for(int i=0;i<7;i++)
      {
         for(int j=i+1;j<7;j++)
         { 
            if((flag==1 && sort[j]>sort[i]) || (flag==-1 && sort[j]<sort[i]))
            {
               int temp=sort[i];     //swap functions
               sort[i]=sort[j];
               sort[j]=temp;

               temp=sort2[i];
               sort2[i]=sort2[j];
               sort2[j]=temp;
            }
         }
      }
      

   

   for(int i=0;i<7;i++)
   {
      if(fill(arr,sort2[i])==1)
         continue;
      
      if(flag==1)
      {
         put(arr,sort2[i],1);
         int temp=move(arr,count+1,-1,depth+1,alpha,beta);

         if(temp>=com)
         {
            com=temp;
         }
         
         if(com>alpha)
         {
            alpha=com;
         }
         
         remov(arr,sort2[i]);

         if(alpha>=beta)
            break;         
      }
      
      else
      {
         put(arr,sort2[i],-1);
         int temp=move(arr,count+1,1,depth+1,alpha,beta);
         if(temp<=com)
         {
            com=temp;
         }
         
         if(com<beta)
         { 
            beta=com;
         }

         remov(arr,sort2[i]);

         if(alpha>=beta)
            break;
      }
   }   
   return com;
}

 
int main()
{
   char** arr=(char **)malloc(6*sizeof(char*));
   for(int i=0;i<6;i++)
   {
      arr[i]=(char *)malloc(7*sizeof(char));
   }
   
   for(int i=0;i<6;i++)
   {
      for(int j=0;j<7;j++)
      {
         arr[i][j]='.';
      }
   }
   
   int count=0;

   while(count<42)
   {
      int x;
      scanf("%d",&x);
      put(arr,x-1,1);
      count++;
      print(arr);
      
      int ans=check(arr);
          
      if(ans==1000)
      {
         printf("YOU WIN\n");
         break;
      }
       
      if(count==42)
      {
         printf("DRAW\n");
         break;
      }

      int com=1000;
      for(int i=0;i<7;i++)
      {  
         if(fill(arr,i)==1)
            continue;

         put(arr,i,-1);

       int temp=move(arr,count+1,1,0,-2000,2000);

         if(temp<=com)
         {
            com=temp;
            x=i;
         }
         remov(arr,i);
      }
      put(arr,x,-1);
      count++;

      print(arr);
      if(check(arr)==-1000)
      {
         printf("YOU LOSE\n");
         break;
      }
      if(count==42)
      {
         printf("DRAW\n");
         break;
      }
   }

   return 0;
}

