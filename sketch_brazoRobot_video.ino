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


#define PIN_DISPARO_ULTRASONIDO_HORIZONTAL = 3;
#define PIN_MICROFONO_ULTRASONIDO_HORIZONTAL = 2;
#define RANGO_ULTRASONIDO_HORIZONTAL = 200;

const NewPing ULTRASONIDO_HORIZONTAL = sonar(PIN_DISPARO_ULTRASONIDO_HORIZONTAL, PIN_MICROFONO_ULTRASONIDO_HORIZONTAL, RANGO_ULTRASONIDO_HORIZONTAL);


#define PIN_SERVOMOTOR_HORIZONTAL = 4;
const Servo SERVOMOTOR_HORIZONTAL;

#define BAUDIOS_CONTROL 9600;

#define RANGO_INFERIOR_HORIZONTAL = 10;
#define RANGO_SUPERIOR_HORIZONTAL = 20;


void setup() {

  
  /* 
    Puerto serie para control posterior.
    No hace a la solución del problema
  */
  Serial.begin(BAUDIOS_CONTROL);
  
  SERVOMOTOR_HORIZONTAL.attach(PIN_SERVOMOTOR_HORIZONTAL);

}

void loop() {


  int distanciaControlHorizontal = ULTRASONIDO_HORIZONTAL.ping_cm();

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
