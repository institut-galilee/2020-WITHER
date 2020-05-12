<?php
session_start();

if(empty($_SESSION['id_personne']))
{
	header('Location: main.php');
  exit();
}
?>

<?php
	try
	{
		$bdd = new PDO('mysql:host=localhost;dbname=iot_project;charset=utf8', 'root', '');
	}
	catch (Exception $e)
	{
			die('Erreur : ' . $e->getMessage());
	}
	
	

	$identifiant = $_SESSION['id_personne'];
	$req = $bdd->prepare('SELECT * FROM reglages WHERE id_personne = ?') or die(print_r($bdd->errorInfo()));
	$req->execute(array($identifiant));
	$nbr=$req->rowCount();
	if($nbr!=0){
		$donnees = $req->fetch();
	}
?>

<?php include 'header.html';?>
	<div class="card col-2 mt-2 ml-2 text-center">Connecté en tant que <?php echo $_SESSION['id_user'] ?></div>
	<a class="btn btn-primary mt-2 ml-2" href="main.php">Déconnexion</a>
	<div class="container">
		<div class="row">
			<div class="card col-4 offset-4 mt-3 py-5 bg-info">
				<p class="card-body col-4 offset-4">CAMERA</p>
			</div>
		</div>
		<div class="row mt-4">
			<div class="card col-4 offset-1 mt-5 pt-3 pb-2 bg-light">
				<div class="card-header bg-light">Température</div>
				<div class="card-body">
					<p>Minimimum acceptable : <div class="font-weight-bold"><?php if ($nbr!=0){ echo $donnees['temp_min'];} else { echo "--"; } ?>°C</div></p>
					<p>Maximum acceptable : <div class="font-weight-bold"><?php if ($nbr!=0){ echo $donnees['temp_max'];} else { echo "--"; } ?>°C</div></p>
				</div>
			</div>

			<div class="card col-4 offset-2 mt-5 pt-3 pb-2 bg-light">
				<div class="card-header bg-light">Nourriture</div>
				<div class="card-body">
					<p>Quantité : <div class="font-weight-bold"><?php if ($nbr!=0){ echo $donnees['qte_nourriture'];} else { echo "--"; } ?> grammes</div></p>
					<p>Horaire(s) : 
						<div class="font-weight-bold"><?php if ($nbr!=0){ echo $donnees['H1_nourriture'];} else { echo "--:--:--"; } ?> H</div>
						<div class="font-weight-bold"><?php if ($nbr!=0){ echo $donnees['H2_nourriture'];} else { echo "--:--:--"; } ?> H</div>
						<div class="font-weight-bold"><?php if ($nbr!=0){ echo $donnees['H3_nourriture'];} else { echo "--:--:--"; } ?> H</div>
						<div class="font-weight-bold"><?php if ($nbr!=0){ echo $donnees['H4_nourriture'];} else { echo "--:--:--"; } ?> H</div>
					</p>
				</div>
			</div>
		</div>
		<a class="btn btn-primary mt-5 col-4 offset-4" href="reglages.php">Réglages</a>
	</div>
	
<?php include 'footer.html';?>