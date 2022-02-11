<?php
    $liste_tel = "";
    $telephone = "";
    $telephone_err = "";
    if($_SERVER['REQUEST_METHOD'] == 'POST'){
        // Check if number phone is empty
        if (empty(trim($_POST['telephone']))) {
            $telephone_err = "Thanks to enter valid number phone";
        } else {
            $telephone = trim($_POST['telephone']);
        }
        if (empty($telephone_err)){
            $liste_tel = $telephone;
        }
    }
?>
<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
    <link rel="stylesheet" href="front.css">
    <title>Number Phone</title>
</head>
<body>
    <h1><center>Number Phone</center></h1>
    <dialog id="mydialog" open>  
        <form method="POST">
            Phone No.:
            <input type="tel" id="telephone" name="telephone" placeholder="Enter phone number" pattern="[0-9]{*}" />
            <span class="help-block"><?= $telephone_err ?></span>
        </form>
        <div>
            <button class="boutons">Enregistrer</button>
        </div>
        <br></br>
        <textarea id="data" name="data" rows="5" cols="33">
            <?= $liste_tel ?>
        </textarea>
	</dialog> 
</body>
</html>