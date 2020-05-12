<?php
try
{
	$bdd = new PDO('mysql:host=localhost;dbname=iot_project;charset=utf8', 'root', '');
}
catch (Exception $e)
{
        die('Erreur : ' . $e->getMessage());
}

$identifiant = $_POST['idft'];
$password = $_POST['pwd'];

$req = $bdd->prepare('SELECT id_user, mdp_user FROM personne WHERE id_user = ?') or die(print_r($bdd->errorInfo()));
$req->execute(array($identifiant));

$donnees = $req->fetch();

if ($donnees['id_user'] == $identifiant and $donnees['mdp_user'] == $password)
{
	header('Location: accueil.php');
  
}
else {
	header('Location: main.php');
}

$req->closeCursor();
exit();

?>