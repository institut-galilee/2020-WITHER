<?php
session_start();

if(empty($_SESSION['id_personne']))
{
	header('Location: main.php');
	echo "yo";
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
	echo $nbr;

	if (isset($_POST['temp_max']))
	{
		
			$H2_nourriture = null;
			$H3_nourriture = null;
			$H4_nourriture = null;
			$temp_min = $_POST['temp_min'];
			$temp_max = $_POST['temp_max'];
			$qte_nourriture = $_POST['radionrt'];
			$H1_nourriture = $_POST['hun'];
			if (isset($_POST['hdeux'])){$H2_nourriture = $_POST['hdeux'];}
			if (isset($_POST['htrois'])){$H3_nourriture = $_POST['htrois'];}
			if (isset($_POST['hquatre'])){$H4_nourriture = $_POST['hquatre'];}
			
		if($nbr==0){
			$req2 = $bdd->prepare('INSERT INTO reglages(id_personne, temp_min, temp_max, qte_nourriture, H1_nourriture, H2_nourriture, H3_nourriture, H4_nourriture) VALUES (:id_personne, :temp_min, :temp_max, :qte_nourriture, :H1_nourriture, :H2_nourriture, :H3_nourriture, :H4_nourriture)') or die(print_r($bdd->errorInfo()));
			$req2->execute(array(
			'id_personne' => $identifiant,
			'temp_min' => $temp_min,
			'temp_max' => $temp_max,
			'qte_nourriture' => $qte_nourriture,
			'H1_nourriture' => $H1_nourriture,
			'H2_nourriture' => $H2_nourriture,
			'H3_nourriture' => $H3_nourriture,
			'H4_nourriture' => $H4_nourriture
			));
			$req2->closeCursor();
		}
		else {
			$req3 = $bdd->prepare('UPDATE reglages SET (id_personne, temp_min, temp_max, qte_nourriture, H1_nourriture, H2_nourriture, H3_nourriture, H4_nourriture) VALUES (:id_personne, :temp_min, :temp_max, :qte_nourriture, :H1_nourriture, :H2_nourriture, :H3_nourriture, :H4_nourriture) WHERE (id_personne = :id_personne)') or die(print_r($bdd->errorInfo()));
			$req3->bindParam(':id_personne', $identifiant);
			$req3->bindParam(':temp_min', $temp_min);
			$req3->bindParam(':temp_max', $temp_max);
			$req3->bindParam(':qte_nourriture', $qte_nourriture);
			$req3->bindParam(':H1_nourriture', $H1_nourriture);
			$req3->bindParam(':H2_nourriture', $H2_nourriture);
			$req3->bindParam(':H3_nourriture', $H3_nourriture);
			$req3->bindParam(':H4_nourriture', $H4_nourriture);
			
			/*$req3->execute(array(
			'id_personne' => $identifiant,
			'temp_min' => $temp_min,
			'temp_max' => $temp_max,
			'qte_nourriture' => $qte_nourriture,
			'H1_nourriture' => $H1_nourriture,
			'H2_nourriture' => $H2_nourriture,
			'H3_nourriture' => $H3_nourriture,
			'H4_nourriture' => $H4_nourriture
			));*/
			$req3->execute();
			$req3->closeCursor();
		}
		header('Location: accueil.php');
		exit();
		
	}

?>

<?php include 'header.html';?>
	<div class="card col-2 mt-2 ml-2 text-center">Connecté en tant que <?php echo $_SESSION['id_user'] ?></div>
	<a class="btn btn-primary mt-2 ml-2" href="accueil.php">Retour</a>
	<div class="container border mt-5">
		<div class="row mt-5 pb-5">
			<form action="reglages.php" method="post" class="col-12">
				<div class="row">
					<div class="card col-4 offset-1 bg-light">
						<h3 class="card-header bg-light">Température</h3>
						<div class="card-body">
							<div class="row my-1">
								<label class="col-8">Température minimale</label>
								<input type="number" min="-50" max="50" step="1" placeholder="(°C)"  name="temp_min" required class="col-3">
							</div>
							<div class="row my-1">
								<label class="col-8">Température maximale</label>
								<input type="number" min="-50" max="50" step="1" placeholder="(°C)" name="temp_max" required class="col-3">
							</div>
						</div>
					</div>
					<div class="card col-4 offset-2 bg-light">
						<h3 class="card-header bg-light">Nourriture</h3>
						<div class="card-body">
							<div class="row">
								<h5 class="offset-1">Quantité</h5>
							</div>
							<div class="row">	
								<div class="form-check col-5 offset-1">
								  <label class="form-check-label my-1">
									<input type="radio" class="form-check-input" name="radionrt">5 grammes
								  </label>
								</div>
								<div class="form-check col-5 offset-1">
								  <label class="form-check-label my-1">
									<input type="radio" class="form-check-input" name="radionrt" value="10">10 grammes
								  </label>
								</div>
							</div>
							<div class="row">
								<div class="form-check col-5 offset-1">
								  <label class="form-check-label my-1">
									<input type="radio" class="form-check-input" name="radionrt" value="15" checked>15 grammes
								  </label>
								</div>
								<div class="form-check col-5 offset-1">
								  <label class="form-check-label my-1">
									<input type="radio" class="form-check-input" name="radionrt" value="20">20 grammes
								  </label>
								</div>
							</div>
							<div class="row">
								<div class="form-check col-5 offset-1">
								  <label class="form-check-label my-1">
									<input type="radio" class="form-check-input" name="radionrt" value="25">25 grammes
								  </label>
								</div>
								<div class="form-check col-5 offset-1">
								  <label class="form-check-label my-1">
									<input type="radio" class="form-check-input" name="radionrt" value="30">30 grammes
								  </label>
								</div>
							</div>
							
							<hr>
							<div class="row">
								<h5 class="offset-1">Horaires</h5>
							</div>
							<div class="row my-1">
								<label class="offset-1">Horaire 1 :</label>
								<input type="time" name="hun" required class="offset-1">
							</div>
							<div class="row my-1">
								<label class="offset-1">Horaire 2 :</label>
								<input type="time" name="hdeux" class="offset-1">
							</div>
							<div class="row my-1">
								<label class="offset-1">Horaire 3 :</label>
								<input type="time" name="htrois" class="offset-1">
							</div>
							<div class="row my-1">
								<label class="offset-1">Horaire 4 :</label>
								<input type="time" name="hquatre" class="offset-1">
							</div>
						</div>
					</div>
				</div>
				<div class="row">
					<button type="submit" class="btn btn-primary offset-4 col-4 mt-4">Appliquer</button>
				</div>
			</form>
		</div>
	</div>
	
<?php include 'footer.html';
$req->closeCursor();?>