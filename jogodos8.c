#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <curses.h>
/*
ncurses nao funciona no windows pq eu nao baixei ela aq.
->a logica principal desse codigo é gerar 8 números, de 1 ate 8
->esses 8 números SERÃO distintos
->pelo menos uma dessas posições deve ser nula, ja que no jogo existe um espaço vazio onde os quadrados passam para serem organizados
->um exemplo de matriz gerada é 
3 2 4   1 2 3
1 7 5   4 5 6 
8 6 0   7 8 0
->a logica da ordenaçao sera aplicada com grafo valorado nao orientado, pois o computador precisa avaliar os melhores caminhos a serem tomados para realizarem a ordenaçao
->alem dessa logica da matriz, é necessário implementar a chamada Distancia de Manhattan, que calcula a distancia entre 2 pontos em um plano euclidiano
->seguindo essa logica, e tendo em vista a matriz completamente ordenada ao lado da matriz randomica, dizemos que a distancia de manhattan do ponto '3' é 
igual a 2, pois o 3 está afastado por 2 pontos de sua posiçao original. detalhe: o sinal é desconsiderado, ou seja, pegamos apenas o módulo. 
->a formula é |x1-x2| + |y1-y2|, sendo x1 e y1 a posiçao desejada e x2 e y2 a posiçao atual.
*/
int jogodos8resolvivel(int game[3][3]){
int i, j, k, l, naoseiseehresolvivel=0;
    for(k=0;k<3;k++){
        for(i=0;i<3;i++){
            for(j=0;j<3;j++){
                for(l=0;l<3;l++){
                    if(game[j][l]<game[k][i] && j>=k && game[j][l]!=0 && game[k][i]!=0){
                        naoseiseehresolvivel++;
                        if(j==k){
                            if(l<i)
                                naoseiseehresolvivel--;
    }}}}}}
    return naoseiseehresolvivel%2;
}

int main(){
    int lin,col,var=0,auxrandomcol=0,auxrandomlin=0,temp,game[3][3],manhattan[3][3],aux[3][3],seraqueehresolvivel;
    char ch;
    srand(time(NULL)); //essa funçao impossibilita que a rand() gere sempre a mesma sequencia numerica, reiniciando a seed dessa funçao
    for (lin=0;lin<3;lin++){ //em sumo, coloca na matriz game e na matrix aux a sequencia 1 2 3 4 5 6 7 8 0
        for (col=0;col<3;col++){
            aux[lin][col]=var+1;
            game[lin][col]=var+1;
            var++;
                if (lin==2 && col==2){
                    game[lin][col]=0;
                    aux[lin][col]=0;
                }
        }
    }
    printf("\nImpressao pre randomizacao \t0=espaco vazio\n");
    for (lin=0;lin<3;lin++){
        for (col=0;col<3;col++){
            printf("%d ",game[lin][col]);
        }
        printf("\n");
    }
    for (int i=0;i<3;i++){ //resumindo, embaralha a matriz sorteando posiçoes aleatorias para colocar os numeros, usando rand
        for (int j=0;j<3;j++){
            auxrandomcol=(rand()%2)+1;
            auxrandomlin=(rand()%2)+1;
            temp=game[i][j];
            game[i][j]=game[auxrandomlin][auxrandomcol];
            game[auxrandomlin][auxrandomcol]=temp;
        }
    }
    printf("\nPos randomizacao \t0=espaco vazio\n");
    for (lin=0;lin<3;lin++){
        for (col=0;col<3;col++){
            printf("%d ",game[lin][col]);
        }
        printf("\n");
    }
    seraqueehresolvivel=jogodos8resolvivel(game);
    if(seraqueehresolvivel==0)
        printf("\tEssa matriz pode ser ordenada\n");
    else
        printf("\tEssa matriz nao pode ser ordenada\n");
    lin=0;
    col=0;
    auxrandomcol=0;
    auxrandomlin=0;
    //calculo da distancia de manhattan
    while (1){
        if (lin>2 || col>2)
            break;
        if (auxrandomlin>2 || auxrandomcol>2){
            auxrandomlin=0;
            auxrandomcol=0;
        }
        if (game[lin][col]==aux[auxrandomlin][auxrandomcol]){
            manhattan[lin][col]=((auxrandomlin-lin)+(auxrandomcol-col));
            lin++;
            col++;
            if (manhattan[auxrandomlin][auxrandomcol]<0){
                manhattan[auxrandomlin][auxrandomcol]= -(manhattan[auxrandomlin][auxrandomcol]);
            }
        }else{
            auxrandomlin++;
            auxrandomcol++;
        }

    }
    var=0;
    printf("\nDistancia de manhattan/geometria do taxi entre os pontos\n");
    for (lin=0;lin<3;lin++){
        for (col=0;col<3;col++){
            printf("O ponto %d esta %d casas distante de sua posicao original\n",var,manhattan[lin][col]);
            var++;
        }
    }
    return 0;
}
