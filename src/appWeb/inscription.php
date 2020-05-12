<?php

?>

<?php

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
	
	$req = $bdd->prepare('INSERT INTO personne(id_user, mdp_user) VALUES (:id_user, :mdp_user)') or die(print_r($bdd->errorInfo()));
	$req->execute(array(
		'id_user' => $identifiant,
		'mdp_user' => $password
	));
	$req->closeCursor();
	session_start();
	$_SESSION['id_personne'] = $identifiant;
	$_SESSION['id_user'] = $password;
	header('Location: accueil.php');
	exit();
}
?>
<?php include 'header.html';?>

	<div class="container mt-5">
		<div class="row">
			<div class="card bg-light col-6 offset-3 py-2">
				<form action="inscription.php" method="post" class="col-12">
					<div class="form-group">
						<label for="idft">Identifiant :</label>
						<input class="col-12" type="text" placeholder="Entrer identifiant" id="idft" name="idft" required>
					</div>
					<div class="form-group">
						<label for="pwd">Mot de passe :</label>
						<input class="col-12" type="password" placeholder="Entrer mot de passe" id="pwd" name="pwd" required>
					</div>
					
					<a href="main.php">Vous êtes déjà inscrit<a>
					
					<button class="btn btn-primary col-12 mt-2" type="submit">Inscription</button>
				</form>
			</div>
		</div>
	</div>

<?php include 'footer.html';?>