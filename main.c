#include<stdio.h>
#include<stdlib.h>
#include"main.h"
int main(){
    while(1){
        
        char a[1];
        printf("\e[1;1H\e[2J");
        printf("***********************************************************************\n");
        printf("--------------------------(  BIENVENUE  )------------------------------\n");
        printf("***********************************************************************\n");
        printf("---- Choisissez : (C)aissier ou (G)erant ou (Q)uitter le programme ----\n");
        scanf("%s",a);
        if(a[0]=='C'){
            FILE *fich=fopen("fff.txt","r");
            int n1=nbr_deproduit(fich); 
            produit t[n1];
            tab_deproduit(n1,t,fich);
            fclose(fich);
            double total=-1;
            while(1){
                printf("\e[1;1H\e[2J");
                if(total!=-1){
                    printf("Total à payer : %lf\n",total);
                    total=-1;
                }
                printf("----------------------------------------------------------------------\n");
                printf("----------------------( Mode Caissier )-------------------------------\n");
                printf("----------------------------------------------------------------------\n");
                printf("Appuyez sur :\n");
                printf("1) Pour demarrer un nouveau ticket :\n");
                printf("2) Pour revenir au menu principal :\n");
                int i=0;
                int b;  
                scanf("%d",&b);
                while(b!=1 && b!=2){
                printf("Erreur de saisie\n");
                printf("Appuyez sur :\n");
                printf("1) Pour demarrer un nouveau ticket :\n");
                printf("2) Pour revenir au menu principal :\n");      
                scanf("%d",&b);
                }
                if(b==1){
                    int te[100];
                    int tr[100];
                    for(int j=0;j<100;j++){
                        te[j]=-1;
                    }
                    while(1){
                        printf("\e[1;1H\e[2J");
                        printf("Saisissez: \n");
                        printf("           1) pour saisir apres un entier correspondant à L'ID produit\n");
                        printf("           2) pour afficher le panier en cours\n");
                        printf("           3) fin de commande :\n");
                        int z;
                        scanf("%d",&z);
                        while(z!=1 && z!=2 && z!=3){
                            printf("\e[1;1H\e[2J");
                            printf("Erreur de saisie\n");
                            printf("Saisissez: \n");
                            printf("           1) pour saisir apres L'ID produit\n");
                            printf("           2) pour afficher le panier en cours\n");
                            printf("           3) fin de commande :\n");
                            scanf("%d",&z);
                        }
                        if(z==1){
                            while(1){
                                printf("entrez l'Id de produit ou -1 pour quitter\n");
                                int e;
                                int r;
                                scanf("%d",&e);
                                while(e>n1){
                                    printf( "Id de produit n'existe pas\n");
                                    printf("Entrez l'id de produit et -1 pour quitter\n");
                                    scanf("%d",&e);
                                }
                                if(e!=-1){
                                    printf("Saisissez un entier correspond à la quantité de ce produit\n");
                                    scanf("%d",&r);
                                    if(r<1){
                                        printf("Erreur\n");
                                        continue;
                                    }
                                    if(t[e].stocks-r<0){
                                        printf("Non disponible dans le stock\n");
                                        continue;
                                    }
                                    else{            
                                        t[e].stocks=t[e].stocks-r;
                                        printf("  %s    Prix Unit : %f    Stocks : %d\n",t[e].nom,t[e].prix_unit,t[e].stocks); 
                                        te[i]=e;/*remplissage du tableau par les id du produit*/
                                        tr[i]=r;
                                        i++;
                                    }
                                } 
                                else{
                                    break;
                                }
                            }
                        }
                        if(z==2){
                            printf("----------------------------------------------------------------------\n");
                            printf("-------------------------   Gestion Panier   -------------------------\n");
                            printf("----------------------------------------------------------------------\n");
                            if(te[0]==-1){
                                printf("Panier Vide\n");
                            }
                            else{
                                int h=0;
                                while(h<100){
                                    if(te[h]!=-1){
                                        printf(" %s  id : %d   (x%d) =%f  \n",t[te[h]].nom,te[h],tr[h],(t[te[h]].prix_unit)*tr[h]); 
                                    }
                                    else{
                                        break;
                                    }
                                    h++;
                                }
                            }
                            printf("Entrez un entier pour sortir du panier\n");
                            int zzz;
                            scanf("%d",zzz);
                        }
                        if(z==3){
                            double s=0;
                            int f=0;
                            while(f<100){
                                if(te[f]!=-1){
                                    s+=(t[te[f]].prix_unit)*1.0*tr[f];
                                }
                                f++;
                            }
                            total=s;
                            FILE *fich=fopen("compta.txt","r");
                            int n2=nbr_decommande(fich);
                            compta cpta[n2];
                            tab_decompta(n2,cpta,fich);
                            fclose(fich);
                            compta nvcpta;
                            time_t timescamp=time(NULL);
                            tm *now=localtime(&timescamp);
                            nvcpta.date_achat.tm_year=now->tm_year+1900;
                            nvcpta.date_achat.tm_mon=now->tm_mon+1;
                            nvcpta.date_achat.tm_mday=now->tm_mday;
                            nvcpta.Somme=total;
                            if(nvcpta.date_achat.tm_year==cpta[n2-1].date_achat.tm_year && nvcpta.date_achat.tm_mon==cpta[n2-1].date_achat.tm_mon && nvcpta.date_achat.tm_mday==cpta[n2-1].date_achat.tm_mday){
                                nvcpta.ticket_id=cpta[n2-1].ticket_id+1;
                            } /* on a demander de l'aide à Oussama Roubai*/
                            else{nvcpta.ticket_id=0;}
                            FILE *fich2=fopen("compta.txt","a");
                            fwrite(&nvcpta,sizeof(compta),1,fich2);
                            fclose(fich2);
                            break;
                        }
                    }
                }
                if(b==2){
                    FILE *fich=fopen("fff.txt","w");
                    fwrite(t,sizeof(produit),n1,fich);
                    fclose(fich);
                    break;
                }
            }
        }
        if(a[0]=='G'){ 
            int c;
            printf("\e[1;1H\e[2J");
            while(1){
                FILE *fich=fopen("fff.txt","r");
                int n1=nbr_deproduit(fich);
                produit t[n1];
                tab_deproduit(n1,t,fich);
                fclose(fich);
                printf("----------------------------------------------------------------------------------------------------\n");
                printf("----------------------------------------(    Mode GERANT    )---------------------------------------\n");
                printf("----------------------------------------------------------------------------------------------------\n");
                printf("1) Voir la liste des produits en stocks :\n");
                printf("2) Modifier un produit :\n");
                printf("3) Ajouter nouveau produit catalogue :\n");
                printf("4) Afficher la compta :\n"); 
                printf("5) Pour revenir au menu principal :\n");
                scanf("%d",&c);
                while(c!=1 && c!=2 && c!=3 && c!=4 && c!=5){
                    printf("Erreur de saisie\n");
                    printf("1) Voir la liste des produits en stocks :\n");
                    printf("2) Modifier un produit :\n");
                    printf("3) Ajouter nouveau produit catalogue :\n");
                    printf("4) Afficher la compta :\n"); 
                    printf("5) Pour revenir au menu principal :\n");
                    scanf("%d",&c);
                }
                if(c==1){
                    Print_Produit(n1,t);
                }
                if(c==2){
                    printf("saisissez l'id du produit:\n");
                    int Id;
                    scanf("%d",&Id);
                    printf("           %s   Prix Unit : %lf      Stocks : %d\n",t[Id].nom,t[Id].prix_unit,t[Id].stocks);
                    printf("Renommez le produit:\n");
                    scanf("%s",t[Id].nom);
                    printf("Donnez un nouveau prix unitaire:\n");
                    scanf("%lf",&t[Id].prix_unit);
                    printf("Donnez le nouveau stockee:\n");
                    scanf("%d",&t[Id].stocks);
                    FILE *fich=fopen("fff.txt","w");
                    fwrite(t,sizeof(produit),n1,fich);
                    fclose(fich);
                }
                if(c==3){
                    FILE *fich=fopen("fff.txt","a");
                    produit k;
                    printf("Nommez le produit:\n");
                    scanf("%s",k.nom);
                    printf("Donnez un prix unitaire:\n");
                    scanf("%lf",&k.prix_unit);
                    printf("Donner le stock:\n");
                    scanf("%d",&k.stocks);
                    fwrite(&k,sizeof(produit),1,fich);
                    fclose(fich);
                }
                if(c==4){
                    FILE *fich=fopen("compta.txt","r");
                    int n2=nbr_decommande(fich);
                    compta uuu[n2];
                    tab_decompta(n2,uuu,fich);
                    fclose(fich);
                    printf("---------   COMPTABILITE   -------\n");
                    printf("DATE         TICKET ID       TOTAL\n");
                    for(int i=0;i<n2;i++){
                        printf("%d/%d/%d     %d              %lf\n",uuu[i].date_achat.tm_year,uuu[i].date_achat.tm_mon,uuu[i].date_achat.tm_mday,uuu[i].ticket_id,uuu[i].Somme);
                    }
                }
                if(c==5){
                    break;
                }
            }
        }
        if(a[0]=='Q'){
            printf("***********************************************************************\n");
            printf("--------------------------(  AU REVOIR  )------------------------------\n");
            printf("***********************************************************************\n");
            break;
        }  
    }
}



