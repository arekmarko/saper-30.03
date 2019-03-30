#include <stdio.h>
#include <time.h>
#include <allegro.h>
#define SIZE 16
#define XRES 700
#define YRES 700
#define RED makecol(255,75,60)
#define DRED makecol(150,15,10)
#define GREEN makecol(60,195,40)
#define PURPLE makecol(200,15,200)
#define BLUE makecol(0,0,255)
#define BLACK makecol(0,0,0)
#define WHITE makecol(255,255,255)
#define GRAY makecol(190,190,190)
#define ORANGE makecol(255,200,50)

int tablica[SIZE][SIZE];
int tab_r[SIZE][SIZE];

void bomba(int i,int j);
void pole_mina(int i,int j);
void pole_szare(int i,int j);
void pole_uzyte(int i,int j);
void podstawa();
void first_board();
void first_click(int tablica[SIZE][SIZE]);
int losuj_bomby(int tablica[SIZE][SIZE]);
int wypelnianie_tablicy(int tablica[SIZE][SIZE],int i,int j);
int odkryj(int tablica[SIZE][SIZE],int i,int j);
void double_click(int tablica[SIZE][SIZE],int i,int j);
int check_win(int tablica[SIZE][SIZE]);

void bomba(int i,int j)
{
    rectfill(screen,40*j,40*i,40+40*j,40+40*i,GRAY);
    circlefill(screen,20+40*j,20+40*i,11,makecol(30,30,60));
    rectfill(screen,40*j+19,40*i+6,40+40*j-19,40+40*i-6,makecol(30,30,60));
    rectfill(screen,40*j+6,40*i+19,40+40*j-6,40+40*i-19,makecol(30,30,60));
    rectfill(screen,40*j+11,40*i+11,40+40*j-11,40+40*i-11,makecol(30,30,60));
    rect(screen,40*j,40*i,40+40*j,40+40*i,BLACK);
}
void pole_mina(int i,int j)
{
    rectfill(screen,20+40*j,10+40*i,40+40*j-19,40+40*i-10,BLACK);
    triangle(screen,19+40*j,10+40*i,19+40*j,40*i+16,10+40*j,40*i+13,RED);
    triangle(screen,10+40*j,30+40*i,20+40*j,26+40*i,30+40*j,30+40*i,GREEN);
}
void pole_szare(int i,int j)
{
    triangle(screen, 40*j, 40*i, 40*j, 40+40*i, 40+40*j, 40*i, makecol( 220, 220, 220 ) );
    triangle(screen, 40+40*j, 40+40*i, 40*j, 40+40*i, 40+40*j, 40*i, makecol( 100, 100, 100 ) );
    rectfill(screen,40*j+6,40*i+6,40+40*j-6,40+40*i-6,makecol(180,180,180));
    rect(screen,40*j,40*i,40+40*j,40+40*i,BLACK);
}
void pole_uzyte(int i,int j)
{
    rectfill(screen,40*j,40*i,40+40*j,40+40*i,makecol(190,190,190));
    rect(screen,40*j,40*i,40+40*j,40+40*i,BLACK);
}
void pole_zielone(int i,int j)
{
    rectfill(screen,40*j,40*i,40+40*j,40+40*i,makecol(60,185,0));
    rectfill(screen,40*j+6,40*i+6,40+40*j-2,40+40*i-2,makecol(50,235,40));
    rect(screen,40*j,40*i,40+40*j,40+40*i,BLUE);
    rect(screen,40*j+1,40*i+1,40+40*j-1,40+40*i-1,BLUE);
}
void pole_fioletowe(int i,int j)
{
    rectfill(screen,40*j,40*i,40+40*j,40+40*i,makecol(155,20,155));
    rectfill(screen,40*j+6,40*i+6,40+40*j-2,40+40*i-2,makecol(200,15,200));
    rect(screen,40*j,40*i,40+40*j,40+40*i,BLUE);
    rect(screen,40*j+1,40*i+1,40+40*j-1,40+40*i-1,BLUE);
}
void podstawa()
{
    int i;
    printf("\t");
    for (i=1;i<SIZE+1;i++)
        textprintf_ex(screen,font,20+40*i,25,WHITE,-1,"%d",i);
    puts("");
    for (i=1;i<SIZE+1;i++){
        textprintf_ex(screen,font,25,20+40*i,WHITE,-1,"%d",i);
    }
}
void first_board()
{
    int i,j;
    for(i=1;i<SIZE+1;i++){
        for(j=1;j<SIZE+1;j++)
        {
            pole_szare(i,j);
            //rect(screen,40*i,40*j,40,40,BLUE);
        }
    }
}
void first_click(int tablica[SIZE][SIZE])
{
    int i,j,k,l;
    while(!key[KEY_ESC]){
        if ((mouse_b&1)==1 && mouse_y/40<=SIZE && mouse_x/40<=SIZE && mouse_y/40>0 && mouse_x/40>0)
        {
        i=mouse_y/40;
        j=mouse_x/40;
        rectfill(screen,40*j,40*i,40+40*j,40+40*i,makecol(190,190,190));
        rect(screen,40*j,40*i,40+40*j,40+40*i,BLACK);
        tablica[i][j]=9;
        tablica[i][j-1]=9;
        tablica[i][j+1]=9;
        tablica[i-1][j+1]=9;
        tablica[i-1][j]=9;
        tablica[i-1][j-1]=9;
        tablica[i+1][j-1]=9;
        tablica[i+1][j]=9;
        tablica[i+1][j+1]=9;
        losuj_bomby(tablica);
        for(k=1;k<=SIZE;k++){
            for(l=1;l<=SIZE;l++)
                wypelnianie_tablicy(tablica,k,l);
        }
        odkryj(tablica,i,j);
        break;
        }
    }
}
int losuj_bomby(int tablica[SIZE][SIZE])
{
    int i,k,l;
    srand(time(NULL));
    for (i=1;i<=(SIZE*SIZE/5);i++)
    {
        k=1+rand()%SIZE;
        l=1+rand()%SIZE;
        while (tablica[k][l]==-1 || tablica[k][l]==9)
        {
            k=1+rand()%SIZE;
            l=1+rand()%SIZE;
        }
            printf("K: %d\tL: %d\n",k,l);
        if (tablica[k][l]!=-1 || tablica[k][l]!=9){
            tablica[k][l]=-1;
            tab_r[k][l]=-1;
            //rectfill(screen,40*l,40*k,40+40*l,40+40*k,RED);
        }
    }
    return 0;
}
int wypelnianie_tablicy(int tablica[SIZE][SIZE],int i,int j)
{
   int b=0;
   if(tablica[i][j]!=-1){
    if(tablica[i+1][j]==-1 && i<SIZE)
        b++;
    if(tablica[i+1][j-1]==-1 && i<SIZE && j>1)
        b++;
    if(tablica[i+1][j+1]==-1 && i<SIZE && j<SIZE)
        b++;
    if(tablica[i][j-1]==-1 && j>1)
        b++;
    if(tablica[i][j+1]==-1 && j<SIZE)
        b++;
    if(tablica[i-1][j]==-1 && i>1)
        b++;
    if(tablica[i-1][j+1]==-1 && i>1 && j<SIZE)
        b++;
    if(tablica[i-1][j-1]==-1 && i>1 && j>1)
        b++;
    tablica[i][j]=b;
    tab_r[i][j]=b;
   }
   return 0;
}
void double_click(int tablica[SIZE][SIZE],int i,int j)
{
    int b=0;
    if (tab_r[i][j]>0 && tab_r[i][j]<9 && i<SIZE+1 && i>=1 && j<SIZE+1 && j>=1){
        printf("%d\t",tab_r[i][j]);
        if(tablica[i+1][j]==-2 && i<SIZE)
            b++;
        if(tablica[i+1][j-1]==-2 && i<SIZE && j>1)
            b++;
        if(tablica[i+1][j+1]==-2 && i<SIZE && j<SIZE)
            b++;
        if(tablica[i][j-1]==-2 && j>1)
            b++;
        if(tablica[i][j+1]==-2 && j<SIZE)
            b++;
        if(tablica[i-1][j]==-2 && i>1)
            b++;
        if(tablica[i-1][j+1]==-2 && i>1 && j<SIZE)
            b++;
        if(tablica[i-1][j-1]==-2 && i>1 && j>1)
            b++;
    }
    if (tab_r[i][j]==b){
        odkryj(tablica,i,j+1);
        odkryj(tablica,i,j-1);
        odkryj(tablica,i+1,j+1);
        odkryj(tablica,i+1,j-1);
        odkryj(tablica,i+1,j);
        odkryj(tablica,i-1,j+1);
        odkryj(tablica,i-1,j-1);
        odkryj(tablica,i-1,j);
    }
}
int odkryj(int tablica[SIZE][SIZE],int i,int j)
{
    if(tablica[i][j]==0 && i<SIZE+1 && i>=1 && j<SIZE+1 && j>=1)
    {
        rectfill(screen,40*j,40*i,40+40*j,40+40*i,GRAY);
        rect(screen,40*j,40*i,40+40*j,40+40*i,BLACK);
        tablica[i][j]=9;
        odkryj(tablica,i,j+1);
        odkryj(tablica,i+1,j);
        odkryj(tablica,i,j-1);
        odkryj(tablica,i-1,j);
        odkryj(tablica,i-1,j-1);
        odkryj(tablica,i-1,j+1);
        odkryj(tablica,i+1,j-1);
        odkryj(tablica,i+1,j+1);
        return 2;
    }
    else if (tablica[i][j]==1 && i<SIZE+1 && i>=1 && j<SIZE+1 && j>=1){
        pole_uzyte(i,j);
        textprintf_centre_ex(screen,font,20+40*j,20+40*i,BLUE,GRAY,"%d",tablica[i][j]);
        tablica[i][j]=9;
    }
    else if (tablica[i][j]==2 && i<SIZE+1 && i>=1 && j<SIZE+1 && j>=1){
        pole_uzyte(i,j);
        textprintf_centre_ex(screen,font,20+40*j,20+40*i,GREEN,GRAY,"%d",tablica[i][j]);
        tablica[i][j]=9;
    }
    else if (tablica[i][j]==3 && i<SIZE+1 && i>=1 && j<SIZE+1 && j>=1){
        pole_uzyte(i,j);
        textprintf_centre_ex(screen,font,20+40*j,20+40*i,RED,GRAY,"%d",tablica[i][j]);
        tablica[i][j]=9;
    }
    else if (tablica[i][j]==4 && i<SIZE+1 && i>=1 && j<SIZE+1 && j>=1){
        pole_uzyte(i,j);
        textprintf_centre_ex(screen,font,20+40*j,20+40*i,DRED,GRAY,"%d",tablica[i][j]);
        tablica[i][j]=9;
    }
    else if (tablica[i][j]==5 && i<SIZE+1 && i>=1 && j<SIZE+1 && j>=1){
        pole_uzyte(i,j);
        textprintf_centre_ex(screen,font,20+40*j,20+40*i,PURPLE,GRAY,"%d",tablica[i][j]);
        tablica[i][j]=9;
    }
    else if (tablica[i][j]==6 && i<SIZE+1 && i>=1 && j<SIZE+1 && j>=1){
        pole_uzyte(i,j);
        textprintf_centre_ex(screen,font,20+40*j,20+40*i,ORANGE,-1,"%d",tablica[i][j]);
        tablica[i][j]=9;
    }
    else if (tablica[i][j]==7 && i<SIZE+1 && i>=1 && j<SIZE+1 && j>=1){
        pole_uzyte(i,j);
        textprintf_centre_ex(screen,font,20+40*j,20+40*i,makecol(0,255,180),-1,"%d",tablica[i][j]);
        tablica[i][j]=9;
    }
    else if (tablica[i][j]!=-1 && tablica[i][j]!=9 && tablica[i][j]!=-2 && i<SIZE+1 && i>=1 && j<SIZE+1 && j>=1){
        pole_uzyte(i,j);
        textprintf_centre_ex(screen,font,20+40*j,20+40*i,WHITE,-1,"%d",tablica[i][j]);
        tablica[i][j]=9;
    }
    else if (tablica[i][j]==-1 && i<SIZE+1 && i>=1 && j<SIZE+1 && j>=1)
    {
        int k,l;
        for(k=1;k<SIZE+1;k++){
            for (l=1;l<SIZE+1;l++){
                if (tablica[k][l]==-1){
                    bomba(k,l);
                    //rectfill(screen,40*l,40*k,40+40*l,40+40*k,GREEN);
                }
            }
        }
        allegro_message("Przegrales\nZagraj ponownie");
        return 2;
        //exit(0);
        /*clear_bitmap(screen);
        for(k=1;k<SIZE+1;k++){
            for(l=1;l<SIZE+1;l++){
                tablica[k][l]=0;
                tab_r[k][l]=0;
            }
        }
        podstawa();
        first_board();
        first_click(tablica);*/
    }
}
int check_win(int tablica[SIZE][SIZE])
{
    int i,j;
    for(i=1;i<SIZE+1;i++){
        for(j=1;j<SIZE+1;j++)
        {
            if (tablica[i][j]!=9 && tablica[i][j]!=-1 && tablica[i][j]!=-2)
                return 0;
        }
    }
    allegro_message("Wygrales");
    exit(0);
}
int main()
{
    int i,j=0;
    int b=SIZE*SIZE/5;
    //int rozmiar=10;
    //printf("Podaj rozmiar gry\n");
    //scanf("%d",rozmiar);
    allegro_init();
    install_timer();
    install_keyboard();
    install_mouse();
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, XRES,YRES,0,0);
    set_color_depth(8);
    show_mouse(screen);
    clear_keybuf();
    podstawa();
    first_board();
    first_click(tablica);
    for(i=0;i<20;i++)
        printf("-");
    puts("");
    while(!key[KEY_ESC] && j==0){
        if ((mouse_b&1)==1 && mouse_y/40<=SIZE && mouse_x/40<=SIZE && tablica[mouse_y/40][mouse_x/40]!=-2 && j==0){
            if (odkryj(tablica,(mouse_y/40),(mouse_x/40))==2)
                break;
            double_click(tablica,mouse_y/40,mouse_x/40);
            if (check_win(tablica)==1){
                j=1;}
            else
                rest(150);}
        if ((mouse_b&2)==2 && tablica[mouse_y/40][mouse_x/40]!=9 && tablica[mouse_y/40][mouse_x/40]!=-2 && j==0){
            pole_mina(mouse_y/40,mouse_x/40);
            tablica[mouse_y/40][mouse_x/40]=-2;
            b--;
            rest(150);}
        if ((mouse_b&2)==2 && tablica[mouse_y/40][mouse_x/40]==-2 && j==0){
            tablica[mouse_y/40][mouse_x/40]=tab_r[mouse_y/40][mouse_x/40];
            pole_szare(mouse_y/40,mouse_x/40);
            b++;
            rest(150);
        }
        rectfill(screen,90,10,120,20,BLACK);
        textprintf_ex(screen,font,40,10,WHITE,-1,"Bomby: %d",b);
        rest(5);
    }
    allegro_exit();
    return 0;
    exit(0);
}
END_OF_MAIN();
