<?php
$errorMessage = 0;
if (isset($_POST['idft']))
{
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

	$req = $bdd->prepare('SELECT * FROM personne WHERE id_user = ?') or die(print_r($bdd->errorInfo()));
	$req->execute(array($identifiant));

	$donnees = $req->fetch();
	
	if($donnees['id_user'] != $identifiant || $donnees['mdp_user'] != $password) 
      {
        $errorMessage = 1;
      }
        else
		{
		$errorMessage = 0;
		session_start();
		$_SESSION['id_personne'] = $donnees['id_personne'];
		$_SESSION['id_user'] = $donnees['id_user'];
		header('Location: accueil.php');
		exit();
		}

	$req->closeCursor();
	
}
?>

<?php include 'header.html';?>

	<div class="container mt-5">
		<div class="row">
			<div class="card bg-light col-6 offset-3 py-2">
				<form action="main.php" method="post" class="col-12">
					<div class="form-group">
						<label for="idft">Identifiant :</label>
						<input class="col-12" type="text" placeholder="Entrer identifiant" id="idft" name="idft" required>
					</div>
					<div class="form-group">
						<label for="pwd">Mot de passe :</label>
						<input class="col-12" type="password" placeholder="Entrer mot de passe" id="pwd" name="pwd" required>
					</div>
					
					<?php if ($errorMessage == 1) { ?>
					<div class="alert alert-danger" role="alert">L'identifiant ou le mot de passe est incorrect</div>
					<?php } ?>
					<a href="inscription.php">Vous n'êtes pas inscrit<a>
					
					<button class="btn btn-primary col-12 mt-2 href="accueil.php" type="submit">Connexion</button>
				</form>
			</div>
		</div>
	</div>

<?php include 'footer.html';?>