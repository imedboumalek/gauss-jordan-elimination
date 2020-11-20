#include <stdio.h>
#include <stdlib.h>
const int n=3;
void creation_matrice(float table[n][n])
{
    int i=0,j=0;
    printf("remplir la matrice:\n");

    for (  i=0; i<n; i++)
    {
        for ( j=0; j<n; j++)
            scanf("%f",&table[i][j]);
    }
}
void creation_vecteur(float vecteur[n])
{
    int i=0;
    printf("creez le vecteur:\n");
    for ( i=0; i<n; i++)
        scanf("%f",&vecteur[i]);
}
void affichage_vecteur(float vecteur[n])
{
    int i;
    for ( i = 0; i < n; i++)
    {
        printf("%.2f\n",vecteur[i]);
    }

}

void affichage_matrice(float table[n][n])
{

    int i,j;
    for (  i=0; i<n; i++)
    {
        for ( j=0; j<n; j++)
        {
            printf("%.2f\t",table[i][j]);


        }

        printf("\n\n");

    }
}
void affichage_de_tout(float table[n][n],float vec[n])
{

    int i,j;
    for (  i=0; i<n; i++)
    {
        for ( j=0; j<n; j++)
        {
            printf("%.2f\t",table[i][j]);


        }
        printf("%.2f\n",vec[i]);
        printf("\n");

    }
}


void gausse(float table[n][n], float vecteur [n])
{
    int i,j,k;
    float x;
    for (k=0; k<n-1; k++)//changement de pivot
    {
        for (i=k+1; i<n; i++ ) //
        {
             x= table[i][k]/table[k][k];
            vecteur[i]=vecteur[i]-x*vecteur[k];
            for(j=k+1; j<n; j++)
                table[i][j]=table[i][j]-x*table[k][j];

        }
    }
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            if(j<i)
                table[i][j]=0;
}

void jordan(float table[n][n], float vec[n])
{
    int k,i;
    float x;
    gausse(table,vec);
    for(k=n-1; k>0; k--)
        for (i=k-1; i>=0; i--)
        {
            x= table[i][k]/table[k][k];
            vec[i]=vec[i]-x*vec[k];
            table[i][k]=0;
        }
}
void factorisation(float matrice[n][n],float L[n][n],float U[n][n])
{
    float sum=0,sum2=0;
    int k,i,j;
    for ( i = 0; i <n; i++)
    {
        U[0][i]=matrice[0][i];
        L[i][0]=matrice[i][0]/U[0][0];

    }
    for ( i = 1; i < n; i++)
    {
        for (j = 1; j < n; j++)
        {
            if (i<=j)
            {
                for (k=0; k<i; k++)
                {
                    sum=sum+L[i][k]*U[k][j];
                }
                U[i][j]=matrice[i][k]-sum;


            }

            else
            {
                for (k=0; k<i; k++)
                {
                    sum2=sum2+L[i][k]*U[k][j];
                }
                L[i][j]=(matrice[i][j]-sum)/U[j][j];

            }

        }

    }


}
void resolution_EQ(float table [n][n],float vec[n])
{
    float somme=0,x[n];
    int i=n-1,j;
    x[i]=vec[i]/table[i][i];
    for (i=n-2; i>=0; i--)
    {
        for (j=n-1; j>i; j--)
        {
            somme=somme+table[i][j]*x[j];
        }
        x[i]=(vec[i]-somme)/table[i][i];
        somme=0;
    }
    printf("solution eq: \n");
    for (i=1; i<=n; i++)
    {
        printf("x(%d)=%.2f \n",i,x[i-1]);
    }
}


int main()
{
    float matrice[n][n],vec[n];
    int choix;
    float L[n][n],U[n][n];
    printf("creez votre matrice: \n");
    creation_matrice(matrice);

    printf("la matrice avant le changement :\n");
    affichage_matrice(matrice);
    printf("quelle methode voulez-vous utiliser ? : \n ");
    printf("1=> gausse\n 2=> gausse-jordan \n 3=>factorisation\n");
    scanf("%d",&choix);
    switch(choix)
    {
    case 1:
        printf("==============gausse=============== \n");

        creation_vecteur(vec);
        gausse(matrice,vec);
        affichage_de_tout(matrice,vec);
        resolution_EQ(matrice,vec);
        printf("===============fin=================\n");
        break;
    case 2 :
        printf("===============jordan===========\n");

        creation_vecteur(vec);
        jordan(matrice,vec);
        affichage_de_tout(matrice,vec);
        resolution_EQ(matrice,vec);
        printf("===============fin==============\n");
        break;
    case 3:
        puts("matrice initiale=");
        affichage_matrice(matrice);
        factorisation(matrice,L,U);
        puts("L=");
        affichage_matrice(L);
        puts("U=");
        affichage_matrice(U);
        break;
    default:
        break;
    }
    system("pause");
    return 0;
}
