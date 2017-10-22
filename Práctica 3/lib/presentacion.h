/************************************************************************
 LIBRERIA: presentacion.h 												
 AUTORES:																
 - Oledo Enriquez Gilberto Irving										
 - Alan�s Ram�rez Dami�n                                               
 - Mendieta Torres Alfonso Ulises                                      
 VERSI�N: 1.0                                                          
                                                                       
 DESCRIPCI�N: Cabecera de la libreria para recrear presentaciones m�s 
 agradables al usuario, permitiendo mostrar gr�ficos en el modo consola                            
                                                                       
 OBSERVACIONES: La implementaci�n de esta libreria es distinta si se 
 trata de Windows o Linux, ya que requerir� de funciones no ANSI C                                  
                                                                       
*************************************************************************/

//DECLARACI�N DE FUNCIONES
void gotoxy( int x, int y );	//Funci�n para mover el cursor de escritura de pantalla

void delay_ms(int t);			//Funci�n para esperar un tiempo en milisegundos

void cleanScreen(void);			//Funci�n para borrar la pantalla de la consola

int whereY(void);				//Funci�n que devuelve la coordenada Y en la que se ubica el cursor