#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//初始化
void Init(int row,int col,char arr[row][col],char term){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            arr[i][j]='#';
        }
    }
    for(int i=1;i<row-1;i++){
        for(int j=1;j<col-1;j++){
            arr[i][j]=term;
        }
    }
}

//输出图像(image(row,col,real);image(row,col,show);)
void image(int row,int col,char arr[row][col]){
    printf("0 |");
    for(int i=1;i<=col;i++){
        printf("%d",i);
        printf(" ");
    }
    printf("\n");
    for(int i=0;i<=col;i++){
        printf("--");
    }
    printf("\n");
    for(int i=0;i<row;i++){
        printf("%d |",i+1);
        for(int j=0;j<col;j++){
            printf("%c ",arr[i][j]);
            }
        printf("\n");
    }
}

//添加雷(num=-1为默认)
void set(int row,int col,char arr[row][col],int num){
    if(num==-1){
        num=(row-2)*(col-2)/7;
        printf("num=%d\n",num);
    }
    srand((unsigned int)time(NULL));    //设置随机数起点
    while(num!=0){
        int x=rand()%(col-2)+1;
        int y=rand()%(row-2)+1;
        int nx,ny;
        if(arr[x][y]!='*'){
            arr[x][y]='*';
            //添加周围雷数
            for(nx=-1;nx<2;nx++){
                for(ny=-1;ny<2;ny++){
                    if(arr[x+nx][y+ny]!='*'&&arr[x+nx][y+ny]!='#'){
                        arr[x+nx][y+ny]+=1;
                    }
                }
            }
            num--;
        }
    }
}

//最大值函数
int max(int x,int y){
    int z;
    if(x>y){
        z=x;
    }
    else{
        z=y;
    }
    return(z);
}

//排查
void findmine(int row,int col,char real[row][col],char show[row][col],int num){
    int x,y,n1,n2,nx,ny;
    char n;
    int result=(row-2)*(col-2)-num;
    while (result!=0&&result!=-1){
        //图像
        printf("\nresidue=%d\n",result);
        image(row,col,show);
        //输入
        printf("x=,y= ");
        scanf("%d,%d",&x,&y);
        //插旗
        if(x*y==0||x*y>(row-1)*(col-1)){
            printf("flag\n");
            printf("x=,y= ");
            scanf("%d,%d",&x,&y);
            if(x>=1&&x<=col&&y>=1&&y<=row&&show[y-1][x-1]=='*'){
                show[y-1][x-1]='&';
                num--;
            }
            else if(x>=1&&x<=col&&y>=1&&y<=row&&show[y-1][x-1]=='&'){
                show[y-1][x-1]='*';
                num++;
            }
            else{
            printf("again\n");
            continue;
            }
            printf("num=%d\n",num);
            image(row,col,show);
            continue;
        }
        //扫到雷
        if(x>=1&&x<=col&&y>=1&&y<=row&&real[y-1][x-1]=='*'){
            printf("\nlose\n");
            image(row,col,real);
            break;
        }
        //扫到*
        if(x>=1&&x<=col&&y>=1&&y<=row&&show[y-1][x-1]=='*'){
            //当检测数字为0时，向周围3*3范围检测，若为0，以检测到的0为起点向周围3*3范围检测，若不是0，则显示对应数字（可优化）
            if(real[y-1][x-1]=='0'){
                for(nx=-1;nx<2;nx++){
                    for(ny=-1;ny<2;ny++){
                        if(real[y-1+ny][x-1+nx]!='*'&&show[y-1+ny][x-1+nx]=='*'){
                            show[y-1+ny][x-1+nx]=real[y-1+ny][x-1+nx];
                            result--;
                            if(real[y-1+ny][x-1+nx]=='0'){
                                n1=nx;
                                n2=ny;
                                for(nx=-1;nx<2;nx++){
                                    for(ny=-1;ny<2;ny++){
                                        if(real[y-1+n2+ny][x-1+n1+nx]!='*'&&show[y-1+n2+ny][x-1+n1+nx]=='*'){
                                            show[y-1+n2+ny][x-1+n1+nx]=real[y-1+n2+ny][x-1+n1+nx];
                                            result--;
                                        }
                                    }
                                }
                                nx=n1;
                                ny=n2;
                            }
                        }
                    }
                }
            }
            else{
                show[y-1][x-1]=real[y-1][x-1];
                result--;
            } 
        }
        else{
            //扫到数字
            if(x>=1&&x<=col&&y>=1&&y<=row&&show[y-1][x-1]!='#'){
                n=48;
                for(nx=-1;nx<2;nx++){
                    for(ny=-1;ny<2;ny++){
                        if(show[y-1+ny][x-1+nx]=='&'){
                            n++;
                        }
                    }
                }
                if(n==show[y-1][x-1]){
                    for(nx=-1;nx<2;nx++){
                        for(ny=-1;ny<2;ny++){
                            if(show[y-1+ny][x-1+nx]!='&'&&real[y-1+ny][x-1+nx]=='*'){
                                printf("\nlose\n");
                                image(row,col,real);
                                result=-1;
                                goto out;
                            }
                            else if(show[y-1+ny][x-1+nx]!='#'&&show[y-1+ny][x-1+nx]!='&'&&show[y-1+ny][x-1+nx]=='*'){
                                show[y-1+ny][x-1+nx]=real[y-1+ny][x-1+nx];
                                result--;
                            }
                        }
                    }
                }
                continue;
            }
            printf("again\n");
        }
        out:;
    }
    if(result==0){
        printf("\nwin\n");
        image(row,col,real);
    }
}

int main(){
    int row,col,num;
    printf("row=");
    scanf("%d",&row);
    printf("col=");
    scanf("%d",&col);
    row+=2;
    col+=2;
    char real[row][col];
    char show[row][col];
    Init(row,col,real,'0');
    Init(row,col,show,'*');
    printf("land mine num=");
    scanf("%d",&num);
    set(row,col,real,num);
    image(row,col,real);
    findmine(row,col,real,show,num);
    return 0;
}