# Fiche personnelle d'activité

  

## Travail effectué durant le projet :

  

De par la situation exceptionnelle du confinement et étant le seul à avoir le matériel, j'ai du travailler sur le montage électrique de notre projet.

Pour cela j'ai procédé par étapes : je me suis d'abord concentré sur le moteur pas à pas et le thermistor.

( J'ai délaissé la partie caméra de notre projet au départ, car celle-ci impliquait de réaliser au préalable un serveur web. )

  

- Pour faire le montage électrique du moteur et du thermistor, je me suis inspiré des exercices fournis dans le [Starter Kit User Manual](https://www.elecrow.com/download/Starter%20Kit%20for%20Arduino(user%20manual).pdf).
(Voici les schémas électriques que j'ai réalisé via Fritzing pour le [moteur](https://github.com/institut-galilee/2020-WITHER/blob/master/src/images/stepper_motor_platine.pdf) et le [thermistor](https://github.com/institut-galilee/2020-WITHER/blob/master/src/images/thermistor_platine.pdf))

  

- Ensuite, concernant le codage, pour le thermistor j'utilise la relation de Steinhart-Hart pour convertir sa résistance en température [ici](https://github.com/institut-galilee/2020-WITHER/blob/master/src/Temperature/thermistor.ino). Pour le moteur pas à pas, on a deux fonctions disponibles [ici](https://github.com/institut-galilee/2020-WITHER/blob/master/src/step_motor/stepper_motor.ino). L'une permet de faire un pas dans un sens spécifié par un booléen, et l'autre permet de répéter les pas un certains nombre de fois.

  

- J'ai enfin crée un serveur web qui contenait au départ un bouton pour actionner le moteur pas à pas et un texte spécifiant la température de la pièce. J'ai ensuite ajouté à celui-ci la caméra qui renvoyait un aperçu de la cage en direct. Voici le serveur web [avec](https://github.com/institut-galilee/2020-WITHER/blob/master/src/foodApp_withCamera/foodApp_withCamera.ino) et [sans](https://github.com/institut-galilee/2020-WITHER/blob/master/src/foodApp_withoutCamera/foodApp_withoutCamera.ino) la caméra.

  

## Acquis permis par le projet:

  

Durant ce projet j'ai pu apprendre plusieurs notions que je ne connaissais pas auparavant (relation de Steinhart-Hart, diviseur de tension, rappel des notions de base en électronique...)

De plus, c'était la première fois que j'utilisais un ESP32 (j'avais déjà travaillé sur Arduino) et que je réalisais une application web en utilisant l'Arduino IDE.

  

Enfin, cette expérience nous a permis de réaliser un projet dont on a définit nous même le sujet, les contraintes et les limites, ce qui fût très enrichissant.
