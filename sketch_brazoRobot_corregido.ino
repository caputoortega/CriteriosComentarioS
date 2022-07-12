/**
 * @file sketch_jul08a.ino
 * @author Bernardo Caputo (bernardo@caputo.com.ar)
 * @brief Automatiza un brazo robotico para recolectar cajas de 5cm^3 de una cinta transportadora
 * @version 0.1
 * @date 2022-07-12
 * 
 * @copyright UNDER MIT LICENCE 
 * 
 */

// { https://www.arduino.cc/reference/en/libraries/servo/ }
#include <Servo.h>
// { https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home }
#include <NewPing.h>

/*
 * 
 * FE DE ERRATAS:
 *    Durante la ejemplificación cometí un error de sintaxis
 *    en las directivas "#define". 
 *    Lo correcto es colocar:
 *     #define <nombre_variable> <valor_literal>
 *    Nótese que no lleva símbolo de asignación ni punto y coma
 *    al final de la instrucción.
 *    
 */
#define PIN_DISPARO_ULTRASONIDO_HORIZONTAL 3
#define PIN_MICROFONO_ULTRASONIDO_HORIZONTAL 2
#define RANGO_ULTRASONIDO_HORIZONTAL 200


/*
 * 
 * NOTA SOBRE "const" Y OBJETOS EN ARDUINO:
 *  En algunos casos, dependiendo la versión y los parámetros
 *  del compilador Arduino el uso de "const" en objetos como
 *  NewPing o Servo producen errores de compilación.
 *  En las pruebas de compilación que realicé en VSCode este
 *  problema no se daba, pero sí ocurre en Arduino IDE 1.8.19.
 *  Para solucionarlo se puede evitar el uso de "const" o
 *  modificar los parámetros del compilador añadiendo el flag
 *  "-fpermissive" para eliminar advertencias de código no con-
 *  -forme.
 *  Por cuestiones de practicidad, y para que pueda compilarse
 *  en Arduino IDE sin tener que editar la instalación en esta
 *  versión se elimina la declaración "const" de todos los ob-
 *  -jetos.
 *  
 ******************************************************************
 *  
 * FE DE ERRORES:
 *  De acuerdo a la documentación de NewPing.h para la versión
 *  que utilicé a la hora de compilar (1.9.4) la forma correcta
 *  de definir multiples sensores es crear un arreglo de tamaño
 *  n (donde n es la cantidad de sensores de ultrasonido dispo-
 *  -nibles) y definir cada elemento como un nuevo objeto NewPing
 *  pasando como parámetros al constructor los pines de disparo
 *  y microfono y, opcionalmente, el rango máximo del sensor.
 *  
 */
#define CANTIDAD_SENSORES_ULTRASONIDO 1
NewPing sonar[CANTIDAD_SENSORES_ULTRASONIDO] = {
  // ULTRASONIDO_HORIZONTAL
  NewPing(PIN_DISPARO_ULTRASONIDO_HORIZONTAL, PIN_MICROFONO_ULTRASONIDO_HORIZONTAL, RANGO_ULTRASONIDO_HORIZONTAL)
};

/*
 * 
 * Defino el valor del ultrasonido horizontal en 0 para que
 * coincida con el índice del elemento del arreglo sonar[n],
 * de esta manera puedo clarificar la llamada a este ultra-
 * -sonido en instrucciones futuras del algoritmo.
 * 
 */
#define ULTRASONIDO_HORIZONTAL 0


#define PIN_SERVOMOTOR_HORIZONTAL 4
Servo SERVOMOTOR_HORIZONTAL;

#define BAUDIOS_CONTROL 9600

#define RANGO_INFERIOR_HORIZONTAL 10
#define RANGO_SUPERIOR_HORIZONTAL 20


void setup() {

  
  /* 
    Puerto serie para control posterior.
    No hace a la solución del problema
  */
  Serial.begin(BAUDIOS_CONTROL);
  
  SERVOMOTOR_HORIZONTAL.attach(PIN_SERVOMOTOR_HORIZONTAL);

}

void loop() {

  /*
   * 
   * BUG:
   *  El método NewPing.ping_cm() retorna un valor de tipo
   *  "unsigned long", si utilizamos el tipo "int" no coin-
   *  -ciden los tipos y el algoritmo no compila.
   *  
   */
  unsigned long distanciaControlHorizontal = sonar[ULTRASONIDO_HORIZONTAL].ping_cm();

  bool cajaEstaEnRango = (distanciaControlHorizontal > RANGO_INFERIOR_HORIZONTAL)
                                                     &&
                         (distanciaControlHorizontal < RANGO_SUPERIOR_HORIZONTAL);

  if (cajaEstaEnRango) {

    Serial.println("HAY CAJA"); 
 
    //Comienzo movimiento de robot:
    //For para que sea un movimiento lento.
    for (int anguloServoHorizontal = 0; anguloServoHorizontal < 181; anguloServoHorizontal++)
    {
      SERVOMOTOR_HORIZONTAL.write(anguloServoHorizontal);
      delay(10);
    }


    /*

      TODO: 

        Movimiento servo vertical

        Movimiento servo agarre

        Soltar caja

        Vuelvo a pos. inicial a la espera de otra caja

    */

    // ? porque lo detiene 3 seg?
    delay(3000);

  }





}
