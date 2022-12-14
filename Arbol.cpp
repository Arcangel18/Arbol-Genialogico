#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include <mysql.h>


using namespace std;



int romper = 0;

struct arbol
{
    arbol* izquierdo;  
    arbol* derecho;
    string dato;
    int edad;
    int m = 0 , h = 0;
    char caracterMujer[1], CaracterHombre[1];
    
    int numero;
    

};
struct Datos
{
    bool verf = false;
    int uno = 0;
    string nacionalidades[10];
    string nombres[20];
    string PadreHijo[20];
    string nacionali;

};
   
void padrehijo(arbol* nodo) {



    if ((nodo->izquierdo != NULL && nodo->derecho != NULL)) {


        cout << "\nHijo: " << nodo->dato << "\nMama: " << nodo->izquierdo->dato << " Papa:  " << nodo->derecho->dato<<endl;


        padrehijo(nodo->izquierdo);
        padrehijo(nodo->derecho);
    }
    else if (nodo->izquierdo != NULL) {

        cout << "\nHijo: " << nodo->dato << " Mama: " << nodo->izquierdo->dato<<endl;

        padrehijo(nodo->izquierdo);
       
    }
    else if (nodo->derecho != NULL) {

        cout << "\nHijo: " << nodo->dato << " Papa: " << nodo->derecho->dato<<endl;

        
        padrehijo(nodo->derecho);
    }



}

void MujeresPro(string Mujeres[])
{
    for (int i = 0; i < 20; i++)
    {
        cout << "\n" << i + 1 << ": " << Mujeres[i] << "";
    }

   
}




void HombresPro(string Hombres[]) {


    for (int i = 0; i < 20; i++)
    {
        cout << "\n" << i + 1 << ": " << Hombres[i] << "";
    }


}



void crear(arbol* nodo, Datos* group,int &valtemp,string Mujeres[],string Hombres[], int &contadorHPro, int &contadorMPro,int edades[])
{

    bool v = false;
  

    //do {


        if (group->verf == true)
        {

            cout << "\nIntroduzca al  siguiente familiar: \n";
            cin >> nodo->dato;
            group->nombres[group->uno] = nodo->dato;
            if (valtemp == 1) {

                Mujeres[contadorMPro] = nodo->dato;
                contadorMPro = contadorMPro + 1;

            }
            if (valtemp == 2)
            {

                Hombres[contadorHPro] = nodo->dato;
                contadorHPro = contadorHPro + 1;


            }

        }

        
       
        MYSQL* Conexion;
        MYSQL_ROW Fila;
        MYSQL_RES* resultado;
        Conexion = mysql_init(NULL);
        Conexion = mysql_real_connect(Conexion, "localhost", "root", "Latiatuya18.", "Paises", 3306, NULL, 0);

        do {
            romper = 0;
            
            string nacionali;

            cout << "Introduzca una nacionalidad \n(Solo la Forma Abreviada Ejemplo: Argentina = ARG) \n";
            cin >> nacionali;//toupper(nacionali);


            mysql_query(Conexion, "SELECT *FROM nacionalidad");


            resultado = mysql_store_result(Conexion);
            int num_fields = mysql_num_fields(resultado);


            while (Fila = mysql_fetch_row(resultado))
            {
                for (int i = 0; i < num_fields; i++)
                {
                    if (Fila[i + 2] == nacionali) {




                        cout << "\nSe encontro " << Fila[i + 2] << "\n";
                        group->nacionalidades[group->uno] = Fila[i];
                        romper = 1;







                        break;
                    }
                    else {
                        
                        // printf("nose encontro");

                        break;
                    }


                }

            }
        } while (romper != 1);


     // } while (romper!=1);
  

    cin.ignore();
    

    
            regresar:
            fflush(stdin);

            cout << "\nIntroduzca su edad: ";
            cin >> nodo->edad;
            edades[group->uno] = nodo->edad;
           /* if (group->verf == true) {


                if (valtemp == 1) {

                    if (edades[contadorMPro] < nodo->edad) {


                        
                    }
                    else if (edades[contadorMPro] >= nodo->edad) {
                        cout << "Edad Incorrecta M";
                        goto regresar;
                    }


                }
                if (valtemp == 2)
                {
                    if (edades[contadorHPro] < nodo->edad) {
                        contadorHPro = contadorHPro + 1;
                    }
                    else if (edades[contadorHPro] >= nodo->edad) {

                        cout << "Edad Incorrecta H";
                        goto regresar;
                    }



                }
            }*/



        group->verf = true;
        group->uno =group->uno + 1;
        system("pause");
        system("cls");
        cout << "\n" << nodo->dato << " Tiene Mama a la izquierda Introduzca S/N:\n";
        cin >> nodo->caracterMujer;
        
        cin.ignore();
        system("cls");

        if (strcmp(nodo->caracterMujer, "S") == 0) {
            valtemp = 1;
           
            nodo->izquierdo = new arbol;
            crear(nodo->izquierdo, group,valtemp,Mujeres,Hombres, contadorHPro, contadorMPro,edades);
        }
        else {
            valtemp = 0;
            nodo->izquierdo = NULL;
        }

        cout << "\n" << nodo->dato << " Tiene Algun Papa en la derecha de Introduzca S/N:\n";
        cin >> nodo->CaracterHombre;

        cin.ignore();
        system("cls");

        if (strcmp(nodo->CaracterHombre, "S") == 0)
        {

            valtemp = 2;
            nodo->derecho = new arbol;
            
            crear(nodo->derecho, group,valtemp,Mujeres,Hombres, contadorHPro,contadorMPro,edades);
        }

        else
        {
            valtemp = 0;
            nodo->derecho = NULL;
        }
        cout << nodo->dato;
    }

void mostrararbol(arbol* nodo, int cont, Datos* group)
{

    if (nodo == NULL)
    {
        return;
    }
    else
    {
        mostrararbol(nodo->derecho, cont + 1, group);
        for (int i = 0; i < cont; i++)
        {
            cout << "             ";

        }
        cout << nodo->dato << endl;

        mostrararbol(nodo->izquierdo, cont + 1, group);
    }
}



int main()
{

    int opcion, cont = 0, validar = 0, Letraval, opc, reportes,valtemp=0,menor=0,mayor=0, suma;
    int vr = 0;

    string Mujeres[20],Hombres[20];
    int contadorMPro = 0,contadorHPro=0,Edades[10];

    

    arbol* nodo;
    Datos* group;
    group = new Datos();
    nodo = new arbol;



    do {

    inicio:
        cout << ("                                                  MENU DIDACTICO\n");
        cout << ("                                             1. Hoja de Presentacion\n");
        cout << ("                                             2. Crear Arbol Genealogico\n");
        cout << ("                                             3. Insertar Arbol Descendiente\n");
        cout << ("                                             4. Imprimir el Arbol Graficamente\n");
        cout << ("                                             5. Generar Reportes\n");
        cout << ("                                             6. Salir del Programa\n");


        if (validar > 0) {
            cout << "                                       \nRaiz del Arbol: " << nodo->dato << "\n";
           
        }

        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << ("                                             UNIVERSIDAD TECNOLOGICA DE PANAMA\n");
            cout << ("                                       FACULTAD DE INGENIERIA DE SISTEMAS COMPUTACIONALES\n");
            cout << ("                                          DEPARTAMENTO DE PROGRAMACION DE COMPUTADORAS\n");
            cout << ("                                                       LABORATORIO NO.1\n\n");
            cout << ("                                                         INTEGRANTES:\n");
            cout << ("                                                         Mahir Arcia\n");
            cout << ("                                                        GRUPO: 1lL123\n");

            system("pause");
            system("cls");
            break;

        case 2:


           
            
            
           cout << "Introduzca el Nombre de la Persona Central del Arbol: \n";
            cin >> nodo->dato;
            group->nombres[group->uno] = nodo->dato;
           
            validar = validar + 1;
            system("pause");
            system("cls");

            break;
        case 3:
            


                crear(nodo, group, valtemp, Mujeres, Hombres, contadorHPro, contadorMPro, Edades);
                suma = contadorHPro + contadorMPro+1;
            
            
            break;

        case 4:

            mostrararbol(nodo, cont, group);

            break;

        case 5:

            system("cls");
            cout << ("                                                  REPORTES\n");
            cout << ("                                             1. El nombre de todos los progenitores femeninos\n");
            cout << ("                                             2. El nombre de todos los progenitores masculinos\n");
            cout << ("                                             3. Todos los Padres con sus hijos\n");
            cout << ("                                             4. La nacionalidad de mis decendientes\n");
            cout << ("                                             5. Progenitor de mayor edad\n");
            cout << ("                                             6. Progenitor de menor edad\n");
            cout << ("                                             7. Regresar al menu anterior\n");
            cin >> reportes;

            switch (reportes)
            {
            case 1:

                cout << "Lista de Progenitores Femeninos del Arbol";
                
                MujeresPro(Mujeres);
                system("pause");


                break;
            case 2:

                cout << "Lista de Progenitores Masculinos del Arbol";
                
                HombresPro(Hombres);
                system("pause");


                break;
            case 3:

                cout << "Padres Y Sus Hijos";
                padrehijo(nodo);
                system("pause");



                break;
            case 4:

                for (int i = 0; i < suma; i++)
                {
                    cout  <<i+1<<": "<<group->nacionalidades[i] <<"\n";
                }

                break;
            case 5:
              
                for (int i = 0; i < suma; i++)
                {

                  
                    if (i == 0) {
                        mayor = Edades[i];
                       

                    }
                    else if (Edades[i] > mayor) {
                        mayor = Edades[i];
                    }
                        
                       


                    
                }

            
                cout<< "La edad mayor es " << mayor;
                
                break;

            case 6:
                for (int i = 0; i < suma; i++)
                {
                    if (i == 0) {
                        
                        menor = Edades[i];

                    }

                    else if (Edades[i] < menor) {
                        menor = Edades[i];
                    }



                    
                }
                cout << "La edad menor es " << menor;
                break;
            case 7:
                system("cls");
                goto inicio;
                break;
            }

            break;

        }

    } while (opcion != 6);

    cout << "Gracias Por participar\n";
    system("pause");

    return 0;

}


