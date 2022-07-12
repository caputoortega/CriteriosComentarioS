/*
 *  Primero contextualizo:
 *  
 * Este sketch permite la automatización de un brazo robotico
   para que pueda recolectar cajas provenientes de una cinta transportadora.
   La cajas tiene medidas fijas (5x5x5cm). El control de la cinta transportadora
   se hace en cinta.ino dentro de...
   Para este brazo utilizaremos dos tecnologías (Transductores), el sensor ultrasonico
   para estimar si la caja está o no adelante del brazo. (Se calcula la distancia)


(Especifico las tecnologías que voy  a usar)

   El actuador servomotor se utiliza para mover un segmento del brazo el ángulo determinado.
   En este caso se utilizarán 3, uno para la base (movimiento horizontal), otro para el brazo(Movimiento
   vertical) y otro para el agarre de la caja.


*/

/
//Incluyo librerias necesarias, esto es un sobre comentario necesario para el fin educativo.

//Servo permite mover el servo con un simple parametro especificando el angulo
#include <Servo.h>

//NewPing permite el calculo de distancias con múltiples ultrasonidos a la vez
//contando los que llegas y promediando el tiempo a partir del calculo de distancia
//con la formula física distancia = velocidad/Tiempo . Recordemos que la velocidad del sonido
//es de 343,2 m/s. El calculo sin libreria es posible. Pero esta simplifica mucho el uso del sensor.
#include <NewPing.h>


//Parametros del ultrasonido

//El pin hace el ultrasonido
int trigger1 = 3;

//Este es el microfono que recibe
int echo1 = 2;

//Max distancia del modelo usado
int max_distance = 200;


//Genero las clases necesarias.
NewPing sonar1(trigger1, echo1, max_distance);
Servo servoBase;

int pos = 0;

void setup() {
  // put your setup code here, to run once:

  //Serial para control posterior no necesario para la resolución del problema
  //Esto puede ser tomado como un sobre comentario necesario para el fin educativo de quien lo lee.
  Serial.begin(9600);

  //El servo está conectado en el pin 4.
  servoBase.attach(4);



}

void loop() {



  //Recolecto una única vez la distancia antes de hacer el control para descartar errores posteriores
  //de variación. El objeto devuelve la distancia en CM.
  int distancia1 = sonar1.ping_cm();


  //Si la distancia que se registra está entre el rango entonces hay caja.
  if ((distancia1 < 20) && (distancia1 > 10)) {

    Serial.println("HAY CAJA");

    //Comienzo movimiento de robot:
    
    for (pos = 0; pos <= 180; pos += 1)
    {
      //For para que sea un movimiento lento.
      servoBase.write(pos);
      delay(10);
    }

    //Continuo con el algoritmo blabla bla..

    //Este es el movimiento del servo 2

    // Este es el movimiento para el servo 3

    //Suelto la caja


    //Vuelvo a la posición inicial a la espera de la proxima caja.


    delay(3000);


    



  }





}
