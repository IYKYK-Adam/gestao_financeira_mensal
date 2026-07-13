#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//STRUCT//
struct dados{
    int numero;
    char nome[20];
    int qtdDias;
    float meta;
    float dias[31][2];
};

//FUNCAO PARA META DE CONSUMO//
float metaConsumo(int mes)
{
    float meta=0;

    do{
        printf("|INFORME SUA META DO MES %02d| \n", mes);
        printf(">> ");
        scanf(" %f", &meta);

        if(meta<0){
            printf("Valor invalido! Digite novamente...\n\n");
        }
    }while (meta<0);

    printf("\n");

    return meta;
}

//FUNCAO PARA SELECIONAR O DIA//
int escolherDia(struct dados mes)
{
    int dia, sn;

    do{
        printf("\n");
        printf("deseja vizualizar os dias desse mes? \n");
        printf("[1]SIM  [2]NAO \n");
        printf(">> ");
        scanf("%d", &sn);

        printf("\n");

        switch (sn)
        {
            case 1:{

                printf("|DIAS DO MES %02d|\n", mes.numero);
                printf("dia\tvalor\n");
                for(int l=0; l<mes.qtdDias; l++){
                    for(int c=0; c<2; c++){
                        if(c==0){
                            printf("%.0f/%02d", mes.dias[l][c], mes.numero);
                        }
                        else{
                            printf("\tRS%.2f\t", mes.dias[l][c]);
                        }
                    }
                    printf("\n");
                }

                printf("\n\n");

                break;
            }

            case 2:{
                printf("\n");
                break;
            }

            default:{
                printf("Opcao invalida! \n");
                break;
            }
        }
    }while (sn!=1 && sn!=2);

    do{
        printf("|ESCOLHA O DIA| \n");
        printf(">> ");
        scanf("%d", &dia);

        if(dia<1||dia>mes.qtdDias){
            printf("\nERRO: dia selecionado nao compativel! \nDigite novamente...\n\n");
        }

    }while (dia<1||dia>mes.qtdDias);


    return dia;
}


//FUNCAO PARA ESCOLHER O VALOR QUE SERA ADICIONADO//
float escolherValor()
{
    float valor;

    do{
        printf("Digite o valor: \n");
        printf(">> RS");
        scanf("%f", &valor);

        if(valor<0){
            printf("ERRO: valor digitado invalido! \nDigite novamente...\n\n");
        }
    }while (valor<0);

    return valor;
}


//FUNCAO PARA FAZER UM RELATORIO DO MES//
void resumoMes(struct dados mes, float fixo, char descricao[100])
{

    float total=0;

    //calcular o total gasto no mes (sem valor fixo)
    for (int l=0; l<mes.qtdDias-1; l++){
            total+=mes.dias[l][1];
    }

    //relatorio do mes
    printf("|META DO MES: RS%.2f| \n\n", mes.meta);

    printf("|CUSTO FIXO| \n");
    printf("valor\t\tdescricao\n");
    printf("RS%.2f\t%s", fixo, descricao);

    printf("\n\n");

    printf("|RELATORIO DO MES| \n");
    printf("dia\tvalor\n");
    for(int l=0; l<mes.qtdDias; l++){
        for(int c=0; c<2; c++){
            if(c==0){
                printf("%.0f/%02d", mes.dias[l][c], mes.numero);
            }
            else{
                printf("\tRS%.2f\t", mes.dias[l][c]);
            }
        }
        printf("\n");
    }

    printf("\n");

    printf("|RELATORIO|\n");

    printf("|TOTAL DO MES C/CUSTO FIXO: RS%.2f| \n", total+fixo);
    printf("|TOTAL DO MES S/CUSTO FIXO: RS%.2f| \n", total);
    printf("\n");
    if(mes.meta-(total+fixo)>=0){
        printf("|SALDO DA META: RS%.2f|", mes.meta-(total+fixo));
    }else{
        printf("|SALDO DA META: RS0.00|\n");
        printf("|VOCE ULTRAPASSOU RS%.2f DA META|", (total+fixo)-mes.meta);
    }

    printf("\n\n");

}


//FUNCAO PARA ADICIONAR VALOR AO DIA//
struct dados adicionarCustoVariavel(int dia, float valor, struct dados mes)
{
    mes.dias[dia-1][1]+=valor;

    printf("|VALOR ADICIONADO COM SUCESSO|\n\n");

    //if(meta[mes])

    return mes;
}


//FUNCAO PARA DESCONTAR VALOR AO DIA//
struct dados descontarCustoVariavel(int dia, float valor, struct dados mes)
{


        mes.dias[dia-1][1]-=valor;

        //piso 0
        if(mes.dias[dia-1][1]<0){
            mes.dias[dia-1][1]=0;
        }


    printf("|VALOR DESCONTADO COM SUCESSO|\n\n");

    return mes;
}


//MENU PARA CADA MES//
struct dados menuFuncionalidades(struct dados mes, float fixo, char descricao[100]){

    int menu, dia, aux;
    float valor;

    do{

        printf("|MENU|\n");
        printf("1.Adicionar custo variavel\n2.Resumo do mes\n3.Remover custo variavel\n4.Voltar\n");
        printf(">> ");
        scanf("%d", &menu);

        switch(menu)
        {
            case 1:{

                dia=escolherDia(mes);

                printf("DIA ESCOLHIDO: %02d/%02d", dia, mes.numero);

                printf("\n\n");

                valor=escolherValor(dia, mes.numero);

                printf("VALOR ADICIONADO ESCOLHIDO: RS%.2f", valor);

                printf("\n\n");

                mes=adicionarCustoVariavel(dia, valor, mes);

                break;
            }

            case 2:{
                printf("\n");

                resumoMes(mes, fixo, descricao);

                printf("\n");

                break;
            }

            case 3:{

                dia=escolherDia(mes);

                printf("DIA ESCOLHIDO: %02d/%02d", dia, mes.numero);

                //verificar se nao tem nada no dia

                if(mes.dias[dia-1][1]==0){
                    printf("\n\nEsse dia nao tem valor adicionado!\n");

                    aux=1;
                }

                else{
                    aux=0;
                }

                printf("\n\n");

                if(aux==1){
                    break;
                }

                else{
                    valor=escolherValor(dia, mes.numero);

                    printf("VALOR A SER DESCONTADO: RS%.2f", valor);

                    //verificar se o valor que selecionou e maior que o que ele tem

                    if(mes.dias[dia-1][1]>valor){

                        printf("\n\n");

                        mes=descontarCustoVariavel(dia, valor, mes);

                        break;

                    }

                    else{
                        printf("\nEsse dia nao tem valor sufuciente pra ser descontado!\n\n");
                        break;
                    }

                }
            }

            case 4:{
                printf("\n");
                break;
            }

            default:{
                printf("\nOpcao invalida! Digite novamente.\n\n");
            }

        }

    }while(menu!=4);

    return mes;


}



//////////////
/////MAIN/////
//////////////

int main()
{

    //////VARIAVEIS//////

    int mes, menu;

    struct dados meses[12];

    float fixo=0;

    int desc;
    char descricao[100];

    //////////////PREENCHER MATRIZES//////////////

    meses[0].numero=1;
    strcpy(meses[0].nome, "JANEIRO");
    meses[0].qtdDias=31;

    meses[1].numero=2;
    strcpy(meses[1].nome, "FEVEREIRO");
    meses[1].qtdDias=28;

    meses[2].numero=3;
    strcpy(meses[2].nome, "MARCO");
    meses[2].qtdDias=31;

    meses[3].numero=4;
    strcpy(meses[3].nome, "ABRIL");
    meses[3].qtdDias=30;

    meses[4].numero=5;
    strcpy(meses[4].nome, "MAIO");
    meses[4].qtdDias=31;

    meses[5].numero=6;
    strcpy(meses[5].nome, "JUNHO");
    meses[5].qtdDias=30;

    meses[6].numero=7;
    strcpy(meses[6].nome, "JULHO");
    meses[6].qtdDias=31;

    meses[7].numero=8;
    strcpy(meses[7].nome, "AGOSTO");
    meses[7].qtdDias=31;

    meses[8].numero=9;
    strcpy(meses[8].nome, "SETEMBRO");
    meses[8].qtdDias=30;

    meses[9].numero=10;
    strcpy(meses[9].nome, "OUTUBRO");
    meses[9].qtdDias=31;

    meses[10].numero=11;
    strcpy(meses[10].nome, "NOVEMBRO");
    meses[10].qtdDias=30;

    meses[11].numero=12;
    strcpy(meses[11].nome, "DEZEMBRO");
    meses[11].qtdDias=31;

    for(int i=0; i<12; i++){
        meses[i].meta=-1;

        for(int l=0; l<31; l++){
            meses[i].dias[l][0]=l+1;
            meses[i].dias[l][1]=0;
        }
    }

    ////////////////////////////////////////////////

    printf("\n");

    //////PAGINA INICIAL//////

    printf("|TITULO| \n\n");

    //////MENU INICIAL//////

    do{
        printf("|MENU INICIAL| \n");
        printf("\n[1]Adicionar custo fixo \n[2]pular \n[ATENCAO]informacao nao editavel! \n>> ");
        scanf("%d", &menu);

        printf("\n");

        switch (menu)
        {
            case 1:{

                ////////////custo fixo////////////

                do{
                    printf("|INFORME SEU CUSTO FIXO| \n");
                    printf(">> ");
                    scanf(" %f", &fixo);

                    if(fixo<0){
                        printf("Valor invalido! Digite novamente...\n\n");
                    }
                }while (fixo<0);

                printf("\n");

                do{
                    printf("Deseja adicionar uma descricao para o custo fixo? \n[1]sim\n[2]nao\n>> ");
                    scanf("%d", &desc);

                    switch(desc){
                        case 1:{
                            printf("\nDescricao: ");
                            scanf(" %[^\n]s", descricao);
                            break;
                        }

                        case 2:{
                            strcpy(descricao, "---");
                            break;
                        }

                        default:{
                            printf("Opcao Invalida!\n\n");
                        }

                    }
                }while(desc!=1 && desc!=2);

                printf("\n");

                break;
            }

            case 2:{
                strcpy(descricao, "---");
                break;
            }

            default:
                printf("Opcao Invalida!\n\n");
                break;
        }

    }while(menu!=1 && menu!=2);
    ///////////////////////////////

    //////////MENU DE MES//////////

    do{
        printf("|SELECIONE O MES| \n");
        printf("1.Janeiro \n2.Fevereiro \n3.Marco \n4.Abril \n5.Maio \n6.Junho \n7.Julho \n8.Agosto \n9.Setembro \n10.Outubro \n11.Novembro \n12.Dezembro \n0.Sair \n\n");
        printf(">> ");
        scanf("%d", &mes);

        printf("\n");

        if(mes>=1 && mes<=12){
            printf("|%s| \n\n", meses[mes-1].nome);

            //meta de consumo
            if (meses[mes-1].meta<0){
                meses[mes-1].meta=metaConsumo(mes);
            }

            //menu
            meses[mes-1]=menuFuncionalidades(meses[mes-1], fixo, descricao);
        }
        else{
            if(mes!=0){
                printf("Nao existe esse mes. \n\n");
            }
        }

    }while(mes!=0);

    printf("Finalizando programa...\n");


    return 0;
}
