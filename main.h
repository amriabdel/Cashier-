#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
typedef struct tm tm;
typedef struct compta{
    tm date_achat;
    int ticket_id;
    double Somme;
}compta;
typedef struct produit{
        char nom[64]; 
        double prix_unit; 
        int stocks; 
}produit;
int nbr_decommande(FILE *fff){
    fseek(fff,0,SEEK_END);
    int f=ftell(fff);
    return f*1.0/sizeof(compta);
}
int nbr_deproduit(FILE *fff){
    fseek(fff,0,SEEK_END);
    int f=ftell(fff);
    return f*1.0/sizeof(produit);
}
void tab_decompta(int n, compta t[], FILE *fff){
    fseek(fff,0,SEEK_SET);
    fread(t,sizeof(compta),n,fff);
}
void tab_deproduit(int n, produit t[], FILE *fff){
    fseek(fff,0,SEEK_SET);
    fread(t,sizeof(produit),n,fff);
}
void Print_Produit(int l, produit t[]){
    printf("-------------------- %d PRODUITS DE CATALOGUE --------------------\n",l);
    for(int j=0;j<l;j++){
        printf("id : %d                %s   Prix Unit : %lf     Stocks : %d\n",j,t[j].nom,t[j].prix_unit,t[j].stocks);
    }
}

/* on a demander de l'aide à Oussama Roubai*/